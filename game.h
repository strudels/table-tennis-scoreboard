#include "player.h"
#include "scoreDisplay.h"
#include "winDisplay.h"

class Game {
private:
  Player* __turn;
  Player* __player1;
  Player* __player2;
  ScoreDisplay* __leftScore;
  ScoreDisplay* __rightScore;
  WinDisplay* __leftWins;
  WinDisplay* __rightWins;
  bool __isWinning(Player& player, Player& opponent);

public:
  Player* leftPlayer;
  Player* rightPlayer;
  Game();
  void addPoints(Player& player, int amount);
  Player* getWinner();
  void swapSides();
  void reset();
  void displayScore();
  void displayWins();
};
