#include "game.h"

Game::Game() {
  this->player1 = new Player(*this);
  this->player2 = new Player(*this);
  this->__turn = this->player1;
}

bool Game::__isWinning(Player& player) {
  return &player == this->getWinner();
}

bool Game::__isWinning(Player& player, Player& opponent) {
  return player.getScore() >= 11 && player.getScore() - opponent.getScore() >= 2;
}

void Game::incPoints(Player& player) {
  if (not this->__isWinning(player))
    player.setScore(player.getScore() + 1);

  if (this->__isWinning(player)) {
    this->__turn = &player;
    this->incWins(player);
  }
}

void Game::decPoints(Player& player) {
  if (this->player1->getScore() > 0)
    player.setScore(player.getScore() - 1);

  if ((this->player1->getScore() == 0) && (this->player2->getScore() == 0)) {
    this->decWins(player);
    this->__turn = this->getWinner();
  }
}

void Game::incWins(Player& player) {
  if (this->getMatch() < MAX_MATCHES) {
    player.setWins(player.getWins() + 1);
  }
}

void Game::decWins(Player& player) {
  if (this->getMatch() > 0)
    player.setWins(player.getWins() - 1);
}

int Game::getMatch() {
  return this->player1->getWins() + this->player2->getWins();
}

Player* Game::getTurn() {
  return this->__turn;
}

Player* Game::getWinner() {
  if (this->__isWinning(*(this->player1), *(this->player2)))
    return this->player1;

  if (this->__isWinning(*(this->player2), *(this->player1)))
    return this->player2;

  return 0;
}

void Game::reset() {
  this->player1->reset();
  this->player2->reset();
}
