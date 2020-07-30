#include <Joystick.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
Encoder myEnc(5, 6);

Joystick_ Joystick;

void setup() {
  // Initialize Joystick Library
  Joystick.begin();
  }

long position = -999;

void loop() {  
  long newPos = myEnc.read();
  if(newPos >= position+4) {
    position = newPos;
    Joystick.pressButton(0);
    delay(75);
    Joystick.releaseButton(0);
  }
  if ( newPos <= position-4) {
    position = newPos;
    Joystick.pressButton(1);
    delay(75);
    Joystick.releaseButton(1);
    }
  else {
  }
}
