#include "game.h"

Game::Game() {
  this->__player1 = new Player();
  this->leftPlayer = this->__player1;
  this->__player2 = new Player();
  this->rightPlayer = this->__player2;

  this->__leftScore = new ScoreDisplay(SCORE_DISPLAY_IS_LEFT);
  this->__rightScore = new ScoreDisplay(SCORE_DISPLAY_IS_RIGHT);
  this->__leftWins = new WinDisplay(WIN_DISPLAY_IS_LEFT);
  this->__rightWins = new WinDisplay(WIN_DISPLAY_IS_RIGHT);
}

void Game::addPoints(Player& player, int amount) {
  player.setScore(player.getScore() + amount);
}

bool Game::__isWinning(Player& player, Player& opponent) {
  return player.getScore() >= 11 && player.getScore() - opponent.getScore() >= 2;
}

Player* Game::getWinner() {
  if (this->__isWinning(*(this->__player1), *(this->__player2))) {
    return this->__player1;
  }

  if (this->__isWinning(*(this->__player2), *(this->__player1))) {
    return this->__player2;
  }

  return NULL;
}

void Game::swapSides() {
  Player* other = this->leftPlayer;
  this->leftPlayer = this->rightPlayer;
  this->rightPlayer = other;
  this->displayScore();
  this->displayWins();
}

void Game::reset() {
  this->__player1->reset();
  this->__player2->reset();
  this->__leftScore->reset();
  this->__rightScore->reset();
  this->__leftWins->reset();
  this->__rightWins->reset();

  this->leftPlayer = this->__player1;
  this->rightPlayer = this->__player2;
}

void Game::displayScore() {
  this->__leftScore->write(this->leftPlayer->getScore());
  this->__rightScore->write(this->rightPlayer->getScore());
}

void Game::displayWins() {
  this->__leftWins->write(this->leftPlayer->getWins());
  this->__rightWins->write(this->rightPlayer->getWins());
}
