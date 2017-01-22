#include "scoreDisplay.h"
#include "winDisplay.h"

class Game;
class ScoreBoard {
private:

  static int __leftTurnPin;
  static int __rightTurnPin;
  static ScoreDisplay* __leftScore;
  static ScoreDisplay* __rightScore;
  static WinDisplay* __leftWins;
  static WinDisplay* __rightWins;

  static void __displayScore();
  static void __displayWins();
  static void __displayTurn();

public:
  static Game* game;
  static Player* leftPlayer;
  static Player* rightPlayer;

  static void setup(Game& game, int leftTurnPin, int rightTurnPin);

  static void swapSides();
  static void update();
};
