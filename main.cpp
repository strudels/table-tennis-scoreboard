#include "game.h"
#include "controller.h"
#include "scoreBoard.h"
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

#define LEFT_TURN_PIN 3
#define RIGHT_TURN_PIN A0

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
  Serial.println(bitRead(PORTC, 0));
}

int main() {
  // Magical arduino setup
  init();

  // Enable serial for debugging
  Serial.begin(9600);
  Serial.println("Hello world");

  // Setup 7 segment display
  ScoreDisplay::setupDevice();

  // Setup 4 button remote controller
  Controller::setup();

  // game and ScoreBoard singleton
  Game* game = new Game();
  Player* winner;
  int buttonValue;
  ScoreBoard::setup(*game, LEFT_TURN_PIN, RIGHT_TURN_PIN);

  Serial.println("Starting loop");
  delay(3000);
  ScoreBoard::update();
  while(1) {
    bool hadDecrement = false;
    buttonValue = Controller::getButtonValue();
    if (buttonValue == BUTTON_A) {
      game->incPoints(*ScoreBoard::leftPlayer);
    } else if (buttonValue == BUTTON_B) {
      game->incPoints(*ScoreBoard::rightPlayer);
    } else if (buttonValue == BUTTON_D) {
      ScoreBoard::swapSides();
    } else if (buttonValue == (BUTTON_A | BUTTON_C)) {
      game->decPoints(*ScoreBoard::leftPlayer);
      hadDecrement = true;
    } else if (buttonValue == (BUTTON_B | BUTTON_C)) {
      game->decPoints(*ScoreBoard::rightPlayer);
      hadDecrement = true;
    } else if (buttonValue == (BUTTON_D | BUTTON_C)) {
      game->reset();
    }

    ScoreBoard::update();
    debugGames();

    winner = game->getWinner();
    // If there is a winner that has not achieved maximum wins and is also not
    // the result of a revert to previous match via decrement
    if (winner && winner->getWins() < MAX_WINS && not hadDecrement) {
      // Delay to display score of current match before incrementing wins and
      // displaying new match.
      delay(3000);
      game->incWins(*winner);
      ScoreBoard::update();
      debugGames();
    }

    delay(200);
  }
}
