#include "scoreDisplay.h"

Adafruit_7segment sevenSegment = Adafruit_7segment();

void ScoreDisplay::setupDevice() {
  sevenSegment.begin(0x70);
  sevenSegment.print(80.08);
  sevenSegment.writeDisplay();
  sevenSegment.drawColon(1);
}

ScoreDisplay::ScoreDisplay() {
}

ScoreDisplay::ScoreDisplay(int side) {
  switch(side) {
    case SCORE_DISPLAY_IS_LEFT:
      this->__leftDigit = 0;
      this->__rightDigit = 1;
      break;
    case SCORE_DISPLAY_IS_RIGHT:
      this->__leftDigit = 3;
      this->__rightDigit = 4;
      break;
  }
}

void ScoreDisplay::write(int score) {
  sevenSegment.writeDigitNum(this->__leftDigit, score / 10, 0);
  sevenSegment.writeDigitNum(this->__rightDigit, score % 10, 0);
  sevenSegment.writeDisplay();
}

void ScoreDisplay::reset() {
  this->write(0);
}
