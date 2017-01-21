#include "winDisplay.h"

const bool WinDisplay::pinDefaults[] = {false, false, false, false, true};
const int WinDisplay::leftDisplayPins[] = {4, 5, 6, 7, 8};
const int WinDisplay::rightDisplayPins[] = {9, 10, 11, 12, 13};

WinDisplay::WinDisplay(int side) {
  const int *graphPins;
  switch(side) {
    case WIN_DISPLAY_IS_LEFT:
      graphPins = WinDisplay::leftDisplayPins;
      break;
    case WIN_DISPLAY_IS_RIGHT:
      graphPins = WinDisplay::rightDisplayPins;
      break;
    default:
      // Should probably be some debug here.
      return;
  }

  // initialize graph pins
  for(int i = 0; i < 5; i++) {
    this->__graphPins[i] = graphPins[i];
    pinMode(graphPins[i], OUTPUT);
  }
}

void WinDisplay::write(int amount) {
  for(int i = 0; i < 5; i++) {
    if (i+1 <= amount) {
      // Bit flipping the pinDefault turns the LED on.
      digitalWrite(this->__graphPins[i], ((int)(this->pinDefaults[i])) ^ 1);
    } else {
      // No bit flip of the pinDefaults turns the LED off.
      digitalWrite(this->__graphPins[i], ((int)(this->pinDefaults[i])));
    }
  }
}

void WinDisplay::reset() {
  this->write(0);
}
