#include "game.h"

Player::Player(Game& game) {
  this->reset();
  this->__game = &game;
}

int Player::getScore() {
  return this->__matchScores[this->__game->getMatch()];
}

int Player::getScore(int match) {
  return this->__matchScores[match];
}

void Player::setScore(int amount) {
  this->__matchScores[this->__game->getMatch()] = amount;
}

int Player::getWins() {
  return this->__wins;
}

void Player::setWins(int amount) {
  this->__wins = amount;
}

void Player::reset() {
  for(int i = 0; i < MAX_MATCHES; i++) {
    this->__matchScores[i] = 0;
  }
  this->__wins = 0;
}
