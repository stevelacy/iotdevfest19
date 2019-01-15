#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "SSD1306.h"

#define SCK      5    // GPIO5  -- SX1278's SCK
#define MISO     19   // GPIO19 -- SX1278's MISO
#define MOSI     27   // GPIO27 -- SX1278's MOSI
#define SS       18   // GPIO18 -- SX1278's CS
#define RST      14   // GPIO14 -- SX1278's RESET
#define DI0      26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND     433E6
#define LED_PIN  2
#define OLED_PIN 16
#define SYNC_WORD 0x01

TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

SSD1306 display(0x3c, 4, 15);
void setup() {
  pinMode(OLED_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(OLED_PIN, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(OLED_PIN, HIGH); // while OLED is running, set GPIO16 to high

  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa GPS Tracker");

  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // set LoRa to listen on one sync word
  LoRa.setSyncWord(SYNC_WORD);

  Serial.println("init ok");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "LoRa: " + String(SYNC_WORD));

  SerialGPS.begin(9600, SERIAL_8N1, 12, 13);

  display.display();
}

unsigned int delayedLoop = 0;

void loop() {
  // receive packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize); }

  if (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      if (delayedLoop == 10) {
        delayedLoop = 0;
        String msg = String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6);
        digitalWrite(LED_PIN, HIGH);
        sendMessage(msg);
        digitalWrite(LED_PIN, LOW);
        display.drawString(0, 30, "Transmitting GPS");
        display.display();
      }
      else {
        delayedLoop++;
      }
    }
  }
  else {
    if (millis() > 5000 && gps.charsProcessed() < 10) {
      Serial.println(F("No GPS detected: check wiring."));
      display.drawString(0, 30, "No GPS Module attached");
      display.display();
    }
  }

  delay(1);
}

void sendMessage(String msg) {
  // send packet
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
}

void cbk(int packetSize) {
  String packet = "";
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  loraData(packet);
}

void loraData(String packet){
  String rssi = "RSSI " + String(LoRa.packetRssi(), DEC);
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "LoRa: " + String(SYNC_WORD));
  display.drawStringMaxWidth(0 , 15 , 128, packet);
  display.drawString(0, 45, rssi);
  display.display();
}
