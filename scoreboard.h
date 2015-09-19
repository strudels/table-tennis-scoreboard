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
extern Adafruit_7segment matrix;

// Index of current game, out of 9.
extern int currentGame;

// struct to represent a bar Graph
struct Graph {
  int pins[5];
  int pinValues[5];
  int wins;
};

// struct to represent a display
struct ScoreDisplay {
  struct Graph* winsGraph;
  int scores[9];
};

//bar Graphs
extern struct Graph leftGraph;
// One of these pins is bad; will have to change that pin to 14 (Analog pin 0)
extern struct Graph rightGraph;

// Displays for each side of the table.
extern struct ScoreDisplay leftDisplay;
extern struct ScoreDisplay rightDisplay;

/*
 * Sets the current game number, and ensures that the game number is always
 * valid.
 */
void setCurrentGame(int gameNum);

/*
 * Adds an arbitrary number of wins to a Graph; a Graph can have no more than 5
 * and no fewer than 0 wins.
 */
void _addWinsToGraph(struct Graph* winner, int numWins);

/*
 * Actually displays Graph struct on LED bar Graph.
 */
void _renderGraph(struct Graph* g);

/*
 * Get the victor ScoreDisplay, if there is one. If there is not, return
 * NULL pointer.
 */
struct ScoreDisplay* getWinner();

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
void addPoints(struct ScoreDisplay* recvDisplay, int points);

/*
 * Reset score to initial value, I.E. 0-0 with no wins.
 */
void resetScore();

/*
 * Copy the contents of one ScoreDisplay to the other. Note, that pin numbers
 * and pin values for the display's graph are not copied.
 */
void copyDisplay(struct ScoreDisplay* original, struct ScoreDisplay* copy);

/*
 * Swap the contents of leftDisplay and rightDisplay.
 */
void swapSides();

/*
 * Show score on scoreboard.
 */
void showScore();
