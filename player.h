#define MAX_MATCHES 9

class Game;
class Player {
private:
  Game* __game;
  int __matchScores[MAX_MATCHES];
  int __wins;

public:
  Player(Game& game);

  int getScore();
  int getScore(int match);
  void setScore(int amount);
  int getWins();
  void setWins(int amount);

  void reset();
};
