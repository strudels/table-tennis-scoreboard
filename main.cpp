#include "game.h"
#include "controller.h"
#include "scoreBoard.h"
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

#define LEFT_TURN_PIN 0
#define RIGHT_TURN_PIN 1

void debugGames() {
  Serial.print("Left Score: ");
  Serial.println(ScoreBoard::leftPlayer->getScore());
  Serial.print("Right Score: ");
  Serial.println(ScoreBoard::rightPlayer->getScore());

  Serial.print("Left wins: ");
  Serial.println(ScoreBoard::leftPlayer->getWins());
  Serial.print("Right wins: ");
  Serial.println(ScoreBoard::rightPlayer->getWins());

  Serial.print("Left Turn: ");
  Serial.println(bitRead(PORTD, LEFT_TURN_PIN));
  Serial.print("Right Turn: ");
  Serial.println(bitRead(PORTD, RIGHT_TURN_PIN));
}

int main() {
  // Magical arduino setup
  init();

  // Enable serial for debugging
  Serial.begin(9600);

  // Setup 7 segment display
  ScoreDisplay::setupDevice();

  // Setup 4 button remote controller
  Controller::setup();

  // game and ScoreBoard singleton
  Game game;
  ScoreBoard::setup(game, LEFT_TURN_PIN, RIGHT_TURN_PIN);

  while(1) {
    int value = Controller::getButtonValue();
    if (value == BUTTON_A) {
      game.incPoints(*ScoreBoard::leftPlayer);
    } else if (value == BUTTON_B) {
      game.incPoints(*ScoreBoard::rightPlayer);
    } else if (value == BUTTON_D) {
      ScoreBoard::swapSides();
    } else if (value == (BUTTON_A & BUTTON_C)) {
      game.decPoints(*ScoreBoard::leftPlayer);
    } else if (value == (BUTTON_B & BUTTON_C)) {
      game.decPoints(*ScoreBoard::rightPlayer);
    } else if (value == (BUTTON_D & BUTTON_C)) {
      game.reset();
      break;
    }

    debugGames();

    ScoreBoard::update();
    delay(200);
  }
}
