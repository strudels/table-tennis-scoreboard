#include <RCSwitch.h> // library for receiver

extern RCSwitch rcSwitch;

#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_C 8
#define BUTTON_D 4

class Controller {
public:
  static const long masks[];
  static void setup();
  Controller();
  static int getButtonValue();
};
