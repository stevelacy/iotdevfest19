# ESP32-GPSTracker
> esp32 GPS duplex transceiver — simple esp32 GPS tracker


### Hardware

- 2 esp32 boards used: [Aliexpress](https://www.aliexpress.com/item/2pcs-TTGO-SX1278-LoRa-ESP32-0-96-inch-Blue-OLED-Display-Bluetooth-WIFI-Lora-Kit-32/32833821668.html) (most esp32 boards with Hardware serials and an OLED should be compatible)
- GPS module: [QRP Labs](http://www.qrp-labs.com/ultimategps.html)

#### Wiring

- GPS Tx is plugged into the Rx pin 12
- GPS Rx is plugged into the Tx pin 13

Once the GPS gets full lock it will start transmitting the coordinates to the second esp32 module.

The `SYNC_WORD` is used to differentiate between several tracking units. Changing it allows for several transmitter/receiver combos to be operating at the same time.

### Libraries
- [esp32](https://github.com/espressif/arduino-esp32)
- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
- [LoRa](https://github.com/sandeepmistry/arduino-LoRa)
- [SSD1306](https://github.com/ThingPulse/esp8266-oled-ssd1306)

### [MIT](./LICENSE)



- TinyGPS link: https://github.com/mikalhart/TinyGPSPl
us/archive/master.zip
- Board link: https://dl.espressif.com/dl/package_esp32_in
dex.json
