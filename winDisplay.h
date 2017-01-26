// Libraries for 24-LED bar graph
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define WIN_DISPLAY_IS_LEFT 0
#define WIN_DISPLAY_IS_RIGHT 1

#define TOTAL_LEDS 24

class WinDisplay {
private:
  int __offset;

public:
  static void Setup();
  WinDisplay(int side);
  void write(int amount, int color);
  void reset();
};
