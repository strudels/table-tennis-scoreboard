#include "player.h"

Player::Player() {
  this->reset();
}

int Player::getScore() {
  return this->__score;
}

void Player::setScore(int amount) {
  this->__score = amount;
}

int Player::getWins() {
  return this->__wins;
}

void Player::setWins(int amount) {
  this->__wins = amount;
}

void Player::reset() {
  this->__score = 0;
  this->__wins = 0;
}
