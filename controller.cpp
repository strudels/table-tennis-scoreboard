#include "controller.h"

const long Controller::masks[] = {1096320, 31360};  // {remote1, remote2}

RCSwitch rcSwitch = RCSwitch();

void Controller::setup() {
  // Setup remote receiver
  //I know it has an arg of 0, but this means input on digital pin 2
  rcSwitch.enableReceive(0);
}

int Controller::getButtonValue() {
  long value;
  while(1) {
    if (rcSwitch.available()) {
      // First value retrieves encoding
      value = rcSwitch.getReceivedValue();

      // Read next value for command if encoding is good
      if (value == 0) {
	Serial.println("Unknown encoding");
	rcSwitch.resetAvailable();
	continue;
      } else {
	value = rcSwitch.getReceivedValue();
	rcSwitch.resetAvailable();
	// Xor'ing with mask gives us only the parts not covered by the mask
	for(int i = 0; i < 2; i++) {
	  if (((Controller::masks[i] >> 4) & (value >> 4)) == 0)
	    return value ^ Controller::masks[i];
	}
      }
    }
  }
}
