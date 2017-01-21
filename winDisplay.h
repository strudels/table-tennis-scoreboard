#include <Arduino.h>

#define WIN_DISPLAY_IS_LEFT 0
#define WIN_DISPLAY_IS_RIGHT 1

#define LEFT_WIN_DISPLAY_PINS {4, 5, 6, 7, 8}
#define RIGHT_WIN_DISPLAY_PINS {9, 10, 11, 12, 13}

class WinDisplay {
private:
  int __wins;
  int __graphPins[5];  // Pin numbers used to control each LED in graph

public:
  // Pin values necessary to turn off all LEDs
  // Flipping these values will turn on the LEDs
  const static bool pinDefaults[];
  const static int leftDisplayPins[];
  const static int rightDisplayPins[];
  WinDisplay(int side);
  void write(int amount);
  void reset();
};
