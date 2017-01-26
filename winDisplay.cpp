#include "winDisplay.h"

#define WIN_DISPLAY_I2C_ADDR 0x71

Adafruit_24bargraph winsBarGraph = Adafruit_24bargraph();

void WinDisplay::Setup() {
  winsBarGraph.begin(WIN_DISPLAY_I2C_ADDR);
  for(int i = 0; i < TOTAL_LEDS; i++) {
    winsBarGraph.setBar(i, LED_OFF);
  }
  winsBarGraph.writeDisplay();
}

WinDisplay::WinDisplay(int side) {
  switch(side) {
  case WIN_DISPLAY_IS_LEFT:
    this->__offset = 0;
    break;
  case WIN_DISPLAY_IS_RIGHT:
    this->__offset = 12;
    break;
  }
}

void WinDisplay::write(int amount, int color) {
  for(int i = this->__offset; i < this->__offset + amount; i++) {
    winsBarGraph.setBar(i, color);
  }
  winsBarGraph.writeDisplay();
}

void WinDisplay::reset() {
  this->write(TOTAL_LEDS / 2, LED_OFF);
}
