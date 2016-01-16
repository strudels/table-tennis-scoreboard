#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include "scoreboard.h"

void setup() {
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
  delay(3000);
  showScore();
}


void loop() {
  if(!readButtons()) {
    return;
  }

  // If modifier button is pressed.
  if(buttons[BUTTON_C]) {
    if(buttons[BUTTON_A]){
      // Add point to left display
      addPoints(&leftDisplay, -1);

    } else if (buttons[BUTTON_B]){
      // Add point to right display
      addPoints(&rightDisplay, -1);

    } else if (buttons[BUTTON_D]) {
      // Ensure that reset buttons are held for 3 seconds before resetting.
      for(int i=0; i<30; i++) {
        delay(100);
	readButtons();
        if(!(buttons[BUTTON_C] && buttons[BUTTON_D])) {
          return;
        }
      }
      resetScore();
    }
  // If modifier button is not pressed.
  } else {
    if(buttons[BUTTON_A]){
      // Add point to left display
      addPoints(&leftDisplay, 1);

    } else if (buttons[BUTTON_B]){
      // Add point to right display
      addPoints(&rightDisplay, 1);

    } else if (buttons[BUTTON_D]) {
      swapSides();
    }
  }

  // Show Current Score
  showScore();
  delay(500);
}

int main() {
  init();
  setup();
  while(1) {
    loop();
  }
}
