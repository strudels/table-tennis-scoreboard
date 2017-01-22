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

#ifdef SCOREBOARD_H
#define SCOREBOARD_H

extern Game* ScoreBoard::game;
extern Player* ScoreBoard::leftPlayer;
extern Player* ScoreBoard::rightPlayer;
extern int ScoreBoard::__leftTurnPin;
extern int ScoreBoard::__rightTurnPin;
extern ScoreDisplay* ScoreBoard::__leftScore;
extern ScoreDisplay* ScoreBoard::__rightScore;
extern WinDisplay* ScoreBoard::__leftWins;
extern WinDisplay* ScoreBoard::__rightWins;

#endif SCOREBOARD_H
