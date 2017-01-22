#include "controller.h"

const long Controller::masks[] = {1096320, 7436928};  // {remote1, remote2}

RCSwitch rcSwitch = RCSwitch();

void Controller::setup() {
  // Setup remote receiver
  //I know it has an arg of 0, but this means input on digital pin 2
  rcSwitch.enableReceive(0);
}

int Controller::getButtonValue() {
  long value;
  while(1) {
    rcSwitch.resetAvailable();
    // First value retrieves encoding
    value = rcSwitch.getReceivedValue();

    // Read next value for command if encoding is good
    if (value == 0) {
      continue;
    } else {
	Serial.println(value);
	value = rcSwitch.getReceivedValue();
	// Xor'ing with mask gives us only the parts not covered by the mask
	for(int i = 0; i < 2; i++) {
	    if ((Controller::masks[i] & value) == Controller::masks[i]) {
	    Serial.println(value ^ Controller::masks[i]);
	    return value ^ Controller::masks[i];
	    }
	}
    }
  }
}
