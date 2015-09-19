#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include "scoreboard.h"

/*
* Setup logger to use Serial Console
*/
void setupLogger();

/*
* Log message
*/
void log(const char* msg);

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

int main() {
  init();
  setup();
  while(1) {
    loop();
  }
}

void setupLogger() {
  Serial.begin(9600);
}

void log(const char* msg) {
  Serial.println(msg);
}
