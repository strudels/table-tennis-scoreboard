#include "game.h"

Game::Game() {
  this->player1 = new Player(*this);
  this->player2 = new Player(*this);
}

bool Game::__isWinning(Player& player) {
  return &player == this->getWinner();
}

bool Game::__isWinning(Player& player, Player& opponent, int match) {
  return ((player.getScore(match) >= 11) &&
	  (player.getScore(match) - opponent.getScore(match) >= 2));
}

void Game::incPoints(Player& player) {
  if (this->getWinner() == 0)
    player.setScore(player.getScore() + 1);
}

void Game::decPoints(Player& player) {
  if ((this->player1->getScore() == 0) && (this->player2->getScore() == 0)) {
    this->decWins(*(this->getWinner(this->getMatch() - 1)));
  } else if (player.getScore() > 0) {
    player.setScore(player.getScore() - 1);
  }
}

void Game::incWins(Player& player) {
  if (player.getWins() < MAX_WINS) {
    player.setWins(player.getWins() + 1);
  }
}

void Game::decWins(Player& player) {
  if (this->getMatch() > 0)
    player.setWins(player.getWins() - 1);
}

int Game::getMatch() {
  int matches = this->player1->getWins() + this->player2->getWins();

  // If someone has received max wins, keep the match as the final win
  if ((this->player1->getWins() >= MAX_WINS) ||
      (this->player2->getWins() >= MAX_WINS)) {
    return matches - 1;
  }

  return matches;
}

Player* Game::getTurn() {
  Player* lastWinner = this->getWinner(this->getMatch() - 1);
  Player* lastLoser = (lastWinner == this->player1 ?
		       this->player2 : this->player1);
  // If the score is 0-0, turn for the winner of the last match
  if ((this->player1->getScore() == 0) && (this->player2->getScore() == 0)) {
    return lastWinner;
  }

  // If score is 10-10 or greater, the turn is every serve
  if (this->player1->getScore() + this->player2->getScore() >= 20) {
    switch ((this->player1->getScore() + this->player2->getScore()) % 2) {
    case 0:
      return lastWinner;
    default:
      return lastLoser;
    }
  }

  // If score is less than 10-10, the turn is every other serve
  switch ((this->player1->getScore() + this->player2->getScore()) % 4) {
  case 0:
  case 1:
    return lastWinner;
  default:
    return lastLoser;
  }
}

Player* Game::getWinner() {
  return this->getWinner(this->getMatch());
}

Player* Game::getWinner(int match) {
  // Default values for if match that does not exist is asked for.
  if (match < 0)
    return this->player1;
  if (match >= MAX_MATCHES)
    return this->getWinner(MAX_MATCHES - 1);

  if (this->__isWinning(*(this->player1), *(this->player2), match))
    return this->player1;

  if (this->__isWinning(*(this->player2), *(this->player1), match))
    return this->player2;

  return 0;
}

void Game::reset() {
  this->player1->reset();
  this->player2->reset();
}
