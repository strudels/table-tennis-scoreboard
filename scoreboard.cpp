#include "scoreboard.h"

Adafruit_7segment matrix = Adafruit_7segment();

int currentGame = 0;

struct Graph leftGraph = {{4,5,6,7,8}, GRAPH_PIN_VALUES, 0};
// One of these pins is bad; will have to change that pin to 14 (Analog pin 0)
struct Graph rightGraph = {{9,10,11,12,13}, GRAPH_PIN_VALUES, 0};

struct ScoreDisplay leftDisplay = {&leftGraph, INIT_SCORES};
struct ScoreDisplay rightDisplay = {&rightGraph, INIT_SCORES};

int readButtons() {
  int numPressed = 0;
  for(int i=0; i<4; i++) {
    buttons[i] = digitalRead(i);
    numPressed += buttons[i];
  }
  return numPressed;
}

void setCurrentGame(int gameNum) {
  if(gameNum < 0) {
    gameNum = 0;
  } else if(gameNum>9) {
    gameNum = 0;
  }
  currentGame = gameNum;
}

void _addWinsToGraph(struct Graph* winner, int numWins){
  if((winner->wins + numWins) > 5){
    winner->wins = 5;
  } else if ((winner->wins + numWins) < 0) {
    winner->wins = 0;
  } else {
    winner->wins += numWins;
  }
}

void _renderGraph(struct Graph* g) {
  for(int i=0; i<5; i++) {
    if(i+1 <= g->wins) {
      digitalWrite(g->pins[i], g->pinValues[i] ^ 1);
    } else {
      digitalWrite(g->pins[i], g->pinValues[i]);
    }
  }
}

struct ScoreDisplay* getWinner() {
  struct ScoreDisplay* ahead;
  struct ScoreDisplay* behind;
  if(leftDisplay.scores[currentGame] > rightDisplay.scores[currentGame]) {
    ahead = &leftDisplay;
    behind = &rightDisplay;
  } else {
    ahead = &rightDisplay;
    behind = &leftDisplay;
  }

  if(ahead && ahead->scores[currentGame]>=11 &&
      (ahead->scores[currentGame] - behind->scores[currentGame]) >= 2) {
    return ahead;
  } else {
    return 0;
  }
}

void addPoints(struct ScoreDisplay* recvDisplay, int points) {
  struct ScoreDisplay* otherDisplay;
  struct ScoreDisplay* winner = getWinner();

  // If the winner has won 5 games, don't allow points to be added
  if(winner && winner->winsGraph->wins >= 5 && points > 0) {
    return;
  }

  // If win condition is already present before adding points,
  if(winner == recvDisplay) {
    if(points > 0) {
      // move to next game.
      _addWinsToGraph(recvDisplay->winsGraph, 1);
      setCurrentGame(currentGame + 1);
      return;
    } else if(recvDisplay->winsGraph->wins >= 5){
      // Subtract win from winner.
      _addWinsToGraph(recvDisplay->winsGraph, -1);
      recvDisplay->scores[currentGame] += points;
      return;
    }
  }

  // Determine which display is the display being modified.
  if(recvDisplay == &leftDisplay) {
    otherDisplay = &rightDisplay;
  } else {
    otherDisplay = &leftDisplay;
  }

  // If otherDisplay has score of 0, and this display's score is now negative,
  // go back to last game.
  if(recvDisplay->scores[currentGame] + points < 0) {
    // Ensure that a score is not below 0
    recvDisplay->scores[currentGame] = 0;
    if(otherDisplay->scores[currentGame] == 0) {
      setCurrentGame(currentGame - 1);
      winner = getWinner();
      _addWinsToGraph(winner->winsGraph, -1);
    }
    return;
  }

  // Add points to recvDisplay
  recvDisplay->scores[currentGame] += points;
  winner = getWinner();

  // If adding points causes win condition, add win after 3 seconds.
  if(winner == recvDisplay) {
    showScore();
    delay(3000);
    _addWinsToGraph(recvDisplay->winsGraph, 1);
    if(winner->winsGraph->wins < 5) {
      setCurrentGame(currentGame + 1);
      recvDisplay->scores[currentGame] = 0;
      otherDisplay->scores[currentGame] = 0;
    }
  }
}

void resetScore() {
  for(int i=0; i<9; i++) {
    leftDisplay.scores[i] = 0;
    rightDisplay.scores[i] = 0;
  }
  _addWinsToGraph(leftDisplay.winsGraph, -5);
  _addWinsToGraph(rightDisplay.winsGraph, -5);
  setCurrentGame(0);
}

void copyDisplay(struct ScoreDisplay* original, struct ScoreDisplay* copy) {
  for(int i=0; i<9; i++) {
    copy->scores[i] = original->scores[i];
  }
  copy->winsGraph->wins = original->winsGraph->wins;
}

void swapSides() {
  // store leftDisplay in a temporary ScoreDisplay variable
  struct Graph tempGraph = {{0,0,0,0,0}, GRAPH_PIN_VALUES, 0};
  struct ScoreDisplay tempDisplay = {&tempGraph, INIT_SCORES};

  copyDisplay(&leftDisplay, &tempDisplay);
  copyDisplay(&rightDisplay, &leftDisplay);
  copyDisplay(&tempDisplay, &rightDisplay);
}

void showScore() {
  // Display left score
  matrix.writeDigitNum(0, leftDisplay.scores[currentGame] / 10, 0);
  matrix.writeDigitNum(1, leftDisplay.scores[currentGame] % 10, 0);
  
  // Display right score
  matrix.writeDigitNum(3, rightDisplay.scores[currentGame] / 10, 0);
  matrix.writeDigitNum(4, rightDisplay.scores[currentGame] % 10, 0);
  matrix.writeDisplay();
  _renderGraph(leftDisplay.winsGraph);
  _renderGraph(rightDisplay.winsGraph);
}
