// Libraries for 7-Segment display
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

// matrix for 7 segment display
extern Adafruit_7segment sevenSegment;

#define SCORE_DISPLAY_IS_LEFT 0
#define SCORE_DISPLAY_IS_RIGHT 1

class ScoreDisplay {
 private:
  int __leftDigit;
  int __rightDigit;

 public:
  static void setupDevice();
  ScoreDisplay();
  ScoreDisplay(int side);
  void write(int score);
  void reset();
};
