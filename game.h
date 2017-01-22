#include "player.h"

#define MAX_WINS 5

class Game {
private:
  bool __isWinning(Player& player);
  bool __isWinning(Player& player, Player& opponent, int match);

public:
  Player* player1;
  Player* player2;

  Game();

  void incPoints(Player& player);
  void decPoints(Player& player);
  void incWins(Player& player);
  void decWins(Player& player);

  int getMatch();
  Player* getTurn();
  Player* getWinner();
  Player* getWinner(int match);

  void reset();

  // These should be moved to scoreboard
  void swapSides();
  void displayScore();
  void displayWins();
};
