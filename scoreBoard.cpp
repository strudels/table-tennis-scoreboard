#include "game.h"
#include "scoreBoard.h"

void ScoreBoard::setup(Game& game, int leftTurnPin, int rightTurnPin) {
  ScoreBoard::game = &game;
  ScoreBoard::leftPlayer = game.player1;
  ScoreBoard::rightPlayer = game.player2;

  ScoreBoard::__leftTurnPin = leftTurnPin;
  ScoreBoard::__rightTurnPin = rightTurnPin;
  ScoreBoard::__leftScore = new ScoreDisplay(SCORE_DISPLAY_IS_LEFT);
  ScoreBoard::__rightScore = new ScoreDisplay(SCORE_DISPLAY_IS_RIGHT);
  ScoreBoard::__leftWins = new WinDisplay(WIN_DISPLAY_IS_LEFT);
  ScoreBoard::__rightWins = new WinDisplay(WIN_DISPLAY_IS_RIGHT);

  pinMode(leftTurnPin, OUTPUT);
  pinMode(rightTurnPin, OUTPUT);
}

void ScoreBoard::__displayScore() {
  ScoreBoard::__leftScore->write(ScoreBoard::leftPlayer->getScore());
  ScoreBoard::__rightScore->write(ScoreBoard::rightPlayer->getScore());
}

void ScoreBoard::__displayWins() {
  ScoreBoard::__leftWins->write(ScoreBoard::leftPlayer->getWins());
  ScoreBoard::__rightWins->write(ScoreBoard::rightPlayer->getWins());
}

void ScoreBoard::__displayTurn() {
  if (ScoreBoard::game->getTurn() == ScoreBoard::leftPlayer) {
    digitalWrite(ScoreBoard::__leftTurnPin, 1);
    digitalWrite(ScoreBoard::__rightTurnPin, 0);
  } else {
    digitalWrite(ScoreBoard::__leftTurnPin, 0);
    digitalWrite(ScoreBoard::__rightTurnPin, 1);
  }
}

void ScoreBoard::swapSides() {
  Player* other = ScoreBoard::leftPlayer;
  ScoreBoard::leftPlayer = ScoreBoard::rightPlayer;
  ScoreBoard::rightPlayer = other;

  ScoreBoard::update();
}

void ScoreBoard::update() {
  ScoreBoard::__displayScore();
  ScoreBoard::__displayWins();
  ScoreBoard::__displayTurn();
}

Game* ScoreBoard::game;
Player* ScoreBoard::leftPlayer;
Player* ScoreBoard::rightPlayer;
int ScoreBoard::__leftTurnPin;
int ScoreBoard::__rightTurnPin;
ScoreDisplay* ScoreBoard::__leftScore;
ScoreDisplay* ScoreBoard::__rightScore;
WinDisplay* ScoreBoard::__leftWins;
WinDisplay* ScoreBoard::__rightWins;