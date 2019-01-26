# Presentaion Layout

## Presentaion Setup

Speaker must assign unique HEX number to chairs (0x00 .. 0x0f)

## Presentation Steps

Announce giveaway for first completed.

1) Basic LoRa, esp32, and low power radio explanation

2) Hardware descriptions (w/ photos)

3) Assemble chip and GPS module:
    
    a) Attach antennas to both boards
    
    b) Attach 6-wire-set to GPS module
    
    #### NOTE: DO NOT PLUG IN UPSIDE DOWN; USE MINIMAL FORCE

4) Setup Arduino:

    a) Install Arduino

    b) In Arduino `Tools > Manage Libraries` (screenshots for each lib)
      
    c) Search for and install `lora` (by Sandeep Mistry) via Arduino GUI

    d) Search for and install `esp8266 and ESP32 Oled Driver for SSD1306` via Arduino GUI

    f) Download `https://github.com/mikalhart/TinyGPSPlus/archive/master.zip`. In Arduino go to `Sketch > Include Library > Add .ZIP Library...` and then find the file you downloaded above.
    
    e) Install board manager for esp32 by `Tools > Board > Boards Manager`. In boards manager type `ESP32`. Install the lone entry. 

      ##### This is an OS specfic install:

      On Mac, XCode will be required. See: `https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/mac.md`

    h) `git clone https://github.com/stevelacy/iotdevfest19`

    i) In Arduino, `File > Open` the project. (Should see code in arduino editor)

    j) Change the board that is being programmed `Tools > Board > ESP32 Dev Module`

    k) In the source code change the value of `SYNC_WORD` to the hexidecimal humber written on your bag (it will start with 0x0 and then either a single number or letter):

      ```
      // Change this line!
      #define SYNC_WORD 0x01 // <-- here
      //
      ```

    l) Click checkmark to verify libs are installed and code compiles.



#### PAUSE: Ensure all users done with step 4.

5) Flash Hardware

    a) plug either LoRa board into laptop USB. There should be an antenna attached. The screen should light up and display some text.

    b) MAC OSX only: An arduino port needs to be selected. If no port is available install drivers from `https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers`

    c) click "Right Arrow" icon to flash/upload and wait until it says "Done Uploading".

    d) Unplug the flashed LoRa from the laptop USB and set it aside.

    e) Plug the *other* LoRa board into laptop USB. Repeat steps c and d.

#### PAUSE Ensure all users are done with step 5.
  
6) Assemble the Bread Board:

  a) With one of the LoRa boards in hand with the antenna pointing down (rat tail down), plug the LoRa board into the top row of bread board (position 1) centered left-to-right. Make sure it's pushed all the way in.

  b) With the GPS module with 6-wire-set-attached plug the 6-wire-set into the breadboard so that the white wire's pin goes to pin25 and the yellow wire's pin goes to pin30. Plug it all the way in. 

  c) Attach the orange wire from gps_red(pin26) to +5V(pin2).

  d) Attach the blue from gps_black(pin29) to GND(pin1).
  
  e) Attach the yellow wire from gps_green(pin28) to RX(pin17).

  f) Attach the white wire from gps_blue(pin27) to TX(pin16).

7) Power to the receiver:

  a) Plug the *other* LoRa (the one that is not attached to the bread board) into the laptop USB.

  b) Ensure it is powered on with text that says "LoRa" and YOUR number (non-hex)
  
8) Power to the transmitter:

  a) Plug the breadboard assembly (the one with the wire attached) into the other laptop usb.

9) Putting it all together:

  a) The transmitter should say "transmitting gps". The gps light should be red.

  b) The GPS module needs to acquire GPS lock. This may happen inside depending on the room. Flashing green means GPS lock is acquired.

  c) The receiver should show zeroes for lat and long. Upon connection with the transmitter the reciever will show the GPS module's lat and long.