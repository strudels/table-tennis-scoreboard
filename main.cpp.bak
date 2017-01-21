#include <stdarg.h> // for printf
#include <RCSwitch.h> // library for receiver
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include "scoreboard.h"

RCSwitch mySwitch = RCSwitch();

// Buttons for Remote 1
#define BUTTON_A_R1 1096321 // Lock button on remote
#define BUTTON_A_R1_MOD 1096329 // i.e. BUTTON_A & BUTTON_C
#define BUTTON_B_R1 1096322 //Unlock button on remote
#define BUTTON_B_R1_MOD 1096330// i.e. BUTTON_B & BUTTON_C
#define BUTTON_C_R1 1096328 //Trunk or lightning button
#define BUTTON_D_R1 1096324 //Alarm button on remote
#define BUTTON_D_R1_MOD 1096332// i.e. BUTTON_D & BUTTON_C

// Buttons for Remote 2
#define BUTTON_A_R2 31361// Lock button on remote
#define BUTTON_A_R2_MOD 31369// Lock button on remote
#define BUTTON_B_R2 31362 //Unlock button on remote
#define BUTTON_B_R2_MOD 31370 //Unlock button on remote
#define BUTTON_C_R2 31368 //Trunk or lightning button
#define BUTTON_D_R2 31364 //Alarm button on remote
#define BUTTON_D_R2_MOD 31372 //Alarm button on remote


void setup() {
  // Setup Serial for debugging
  Serial.begin(9600);

  // Setup remote receiver
  //I know it has an arg of 0, but this means input on digital pin 2
  mySwitch.enableReceive(0);

  // Setup 7-Segment display
  matrix.begin(0x70);

  // Show 7-Segment splash
  matrix.print(80.08);
  matrix.writeDisplay();

  // Enable colon
  matrix.drawColon(1);

  // Set pinmode to output for LED bar Graphs
  for(int i=0; i<5; i++) {
    pinMode(leftDisplay.winsGraph->pins[i], OUTPUT);
    pinMode(rightDisplay.winsGraph->pins[i], OUTPUT);
  }
  delay(3000);
  showScore();
}

void update(int command);

// New loop()
void loop() {
  // Wait for receiver to become available
  if (mySwitch.available()) {
    // First value retrieves encoding
    int value = mySwitch.getReceivedValue();

    // Read next value for command if encoding is good
    if (value == 0) {
	Serial.println("Unknown encoding");
        mySwitch.resetAvailable();
        return;
    } else {
	int buttonValue = mySwitch.getReceivedValue();
	update(buttonValue);
        mySwitch.resetAvailable();
    }
  }
}

void update(int command) {
  switch(command) {
    case BUTTON_A_R1:
    case BUTTON_A_R2:
      Serial.println("+1 left");
      addPoints(&leftDisplay, 1);
      break;
    case BUTTON_A_R1_MOD:
    case BUTTON_A_R2_MOD:
      Serial.println("-1 left");
      addPoints(&leftDisplay, -1);
      break;
    case BUTTON_B_R1:
    case BUTTON_B_R2:
      Serial.println("+1 right");
      addPoints(&rightDisplay, 1);
      break;
    case BUTTON_B_R1_MOD:
    case BUTTON_B_R2_MOD:
      Serial.println("-1 right");
      addPoints(&rightDisplay, -1);
      break;
    case BUTTON_D_R1:
    case BUTTON_D_R2:
      Serial.println("swapsides");
      swapSides();
      break;
    case BUTTON_D_R1_MOD:
    case BUTTON_D_R2_MOD:
      Serial.println("resetscore");
      resetScore();
      break;
    default:
      Serial.println("Unexpected button");
      delay(100);
      Serial.println(command);
      delay(100);
      break;
  }

  showScore();
}

int main() {
  init();
  setup();
  while(1) {
    loop();
  }
}
