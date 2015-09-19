#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

// Libraries for 7-Segment display
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

// Define remote buttons
#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_C 2
#define BUTTON_D 3

// Define Bar Graph pin orientation
#define GRAPH_PIN_VALUES {0,0,0,0,1}

// Define initial scores
#define INIT_SCORES {0,0,0,0,0,0,0,0,0}

// matrix for 7 segment display
Adafruit_7segment matrix = Adafruit_7segment();

// Index of current game, out of 9.
int currentGame = 0;

//struct to represent a bar Graph
struct Graph {
  int pins[5];
  int pinValues[5];
  int wins;
};

struct ScoreDisplay {
  struct Graph* winsGraph;
  int scores[9];
};

//bar Graphs
struct Graph leftGraph = {{4,5,6,7,8}, GRAPH_PIN_VALUES, 0};
// One of these pins is bad; will have to change that pin to 14 (Analog pin 0)
struct Graph rightGraph = {{9,10,11,12,13}, GRAPH_PIN_VALUES, 0};

// Displays for each side of the table.
struct ScoreDisplay leftDisplay = {&leftGraph, INIT_SCORES};
struct ScoreDisplay rightDisplay = {&rightGraph, INIT_SCORES};

/*
* Setup logger to use Serial Console
*/
void setupLogger() {
  Serial.begin(9600);
}

/*
* Log message
*/
void log(const char* msg) {
  Serial.println(msg);
}

/*
* Sets the current game number, and ensures that the game number is always
* valid.
*/
void setCurrentGame(int gameNum) {
  if(gameNum < 0) {
    gameNum = 0;
  } else if(gameNum>9) {
    gameNum = 0;
  }
  currentGame = gameNum;
}

/*
* Adds an arbitrary number of wins to a Graph; a Graph can have no more than 5
* and no fewer than 0 wins.
*/
void _addWinsToGraph(struct Graph* winner, int numWins){
  if((winner->wins + numWins) > 5){
    winner->wins = 5;
  } else if ((winner->wins + numWins) < 0) {
    winner->wins = 0;
  } else {
    winner->wins += numWins;
  }
}

/*
* Actually displays Graph struct on LED bar Graph.
*/
void _renderGraph(struct Graph* g) {
  for(int i=0; i<5; i++) {
    if(i+1 <= g->wins) {
      digitalWrite(g->pins[i], g->pinValues[i] ^ 1);
    } else {
      digitalWrite(g->pins[i], g->pinValues[i]);
    }
  }
}

/*
* Get the victor ScoreDisplay, if there is one. If there is not, return
* NULL pointer.
*/
struct ScoreDisplay* getWinner() {
  struct ScoreDisplay* ahead;
  struct ScoreDisplay* behind;
  if(leftDisplay.scores[currentGame] > rightDisplay.scores[currentGame]) {
    ahead = &leftDisplay;
    behind = &rightDisplay;
  } else if(leftDisplay.scores[currentGame] < rightDisplay.scores[currentGame]) {
    ahead = &rightDisplay;
    behind = &leftDisplay;
  }
  
  if(ahead->scores[currentGame]>=11 &&
      (ahead->scores[currentGame] - behind->scores[currentGame]) >= 2) {
    return ahead;
  } else {
    return 0;
  }
}

/*
* Adds an arbitrary number of points to a recvDisplay.
*
* If a win condition is reached, the recvDisplay will display the winning
* score for 5 seconds, and then zero out the displayed game score and
* increment the LED bar Graph on the winning side.
*
* If recvDisplay's current score becomes negative from a subtraction, it will
* be set to 0. If the other ScoreDisplay's current score is 0, then the score
* of the previous game will be displayed.
*
* If subtracting points from a ScoreDisplay results in a loss of a win
* condition, a win will be removed from the ScoreDisplay's LED bar Graph.
*/
void addPoints(struct ScoreDisplay* recvDisplay, int points) {
  struct ScoreDisplay* otherDisplay;
  struct ScoreDisplay* winner = getWinner();
  
  // If the winner has won 5 games, don't allow points to be added
  if(winner && winner->winsGraph->wins >= 5 && points > 0) {
    return;
  }
  
  // If win condition is already present before adding points,
  if(winner == recvDisplay && points > 0) {
    // move to next game.
    _addWinsToGraph(winner->winsGraph, 1);
    setCurrentGame(currentGame + 1);
    return;
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
  
  // If adding points causes win condition, add win after 5 seconds.
  if(winner == recvDisplay) {
    showScore();
    delay(5000);
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

// Swaps the contents of leftDisplay and rightDisplay
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

void setup() {
  // Setup Serial console for debuging
  setupLogger();
  
  // Setup 7-Segment display
  matrix.begin(0x70);
  
  // Show 7-Segment splash
  matrix.print(80.08);
  matrix.writeDisplay();
  
  // Enable colon
  matrix.drawColon(1);
  
  // Set pinmode to input for remote buttons
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_C, INPUT);
  pinMode(BUTTON_D, INPUT);
  
  // Set pinmode to output for LED bar Graphs
  for(int i=0; i<5; i++) {
    pinMode(leftDisplay.winsGraph->pins[i], OUTPUT);
    pinMode(rightDisplay.winsGraph->pins[i], OUTPUT);
  }
}


void loop() {
  // If modifier button is pressed.
  if(digitalRead(BUTTON_C)) {
    if(digitalRead(BUTTON_A)){
      // Add point to left display
      addPoints(&leftDisplay, -1);
      
    } else if (digitalRead(BUTTON_B)){
      // Add point to right display
      addPoints(&rightDisplay, -1);
      
    } else if (digitalRead(BUTTON_D)) {
      // Ensure that reset buttons are held for 5 seconds before resetting.
      for(int i=0; i<50; i++) {
        delay(100);
        if(!(digitalRead(BUTTON_C) && digitalRead(BUTTON_D))) {
          return;
        }
      }
      resetScore();
    }
  // If modifier button is not pressed.
  } else {
    if(digitalRead(BUTTON_A)){
      // Add point to left display
      addPoints(&leftDisplay, 1);
      
    } else if (digitalRead(BUTTON_B)){
      // Add point to right display
      addPoints(&rightDisplay, 1);
      
    } else if (digitalRead(BUTTON_D)) {
      swapSides();
    }   
  }
  
  delay(2000);
  // Show Current Score
  showScore();
}