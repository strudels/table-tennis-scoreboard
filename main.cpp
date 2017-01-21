#include "game.h"
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

void setup() {
  // Magical arduino setup
  init();

  // Enable serial for debugging
  Serial.begin(9600);

  // Setup 7 segment display
  ScoreDisplay::setupDevice();
}

int main() {
  setup();
  Game currentGame;
  while(1) {
    // Show pointer values for player1 and player 2
    Serial.println("Show pointer values for player1 and player 2");
    Serial.println((int) currentGame.leftPlayer);
    Serial.println((int) currentGame.rightPlayer);
    Serial.println("");

    // Add almost over game with no winner
    currentGame.addPoints(*(currentGame.leftPlayer), 10);
    currentGame.addPoints(*(currentGame.rightPlayer), 9);
    // show scores before winner
    Serial.println("show scores before winner; should be 10-9");
    Serial.println(currentGame.leftPlayer->getScore());
    Serial.println(currentGame.rightPlayer->getScore());
    Serial.println("");
    // show winner, should be null
    Serial.println("show winner, should be null");
    Serial.println((int) &*(currentGame.getWinner()));
    Serial.println("");

    // add score to make winner
    currentGame.addPoints(*(currentGame.leftPlayer), 1);
    // show winner, should be a pointer
    Serial.println("show winner, should be a pointer");
    Serial.println(currentGame.leftPlayer->getScore());
    Serial.println(currentGame.rightPlayer->getScore());
    Serial.println((int) &*(currentGame.getWinner()));
    Serial.println("");

    // add score to other player to make 11-10, no winner
    currentGame.addPoints(*(currentGame.rightPlayer), 1);
    // show winner, should be null
    Serial.println("show winner after add score to other player to make 11-10, should be null");
    Serial.println((int) &*(currentGame.getWinner()));

    // swap sides, print out scores, should be opposite
    currentGame.swapSides();
    Serial.println("Show scores after swap, should be 10-11");
    Serial.println(currentGame.leftPlayer->getScore());
    Serial.println(currentGame.rightPlayer->getScore());
    Serial.println("");

    // add score to other player to make 10-12, winner should be original left
    currentGame.addPoints(*(currentGame.rightPlayer), 1);
    Serial.println("Show winner after point added to right, should be original left");
    Serial.println((int) &*(currentGame.getWinner()));
    Serial.println("");

    delay(1000000000);
  }
}
