ARDUINO_DIR            = /usr/share/arduino
TARGET                 = scoreboard
USER_LIB_PATH          = ./libraries
ARDUINO_LIBS           = Wire Adafruit-LED-Backpack-Library Adafruit-GFX-Library rc-switch
MCU                    = atmega328p
F_CPU                  = 16000000
ARDUINO_PORT           = /dev/ttyUSB0
AVRDUDE_ARD_BAUDRATE   = 115200
AVRDUDE_ARD_PROGRAMMER = arduino

include /usr/share/arduino/Arduino.mk
