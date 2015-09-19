Table Tennis Scoreboard
=======================

Uses Adafruit 1.2" 7-segment display:
    https://learn.adafruit.com/adafruit-led-backpack/1-2-inch-7-segment-backpack

Build instructions (on ubuntu)
------------------------------
  1) Ensure that the necessary libraries are installed::
       sudo apt-get install arduino arduino-core arduino-mk

  2) Init submodules to get modules for 7-segment display::
       git submodule init
       git submodule update

  3) Build project::
       make

  4) Upload project to arduino (NOTE, if your arduino is not on /dev/ttyUSB0,
     edit Makefile to the correct value)::
       make upload
