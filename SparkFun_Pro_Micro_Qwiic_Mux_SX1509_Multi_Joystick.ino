// Ground digital pins 0 through 15 of each SX1509 to press the
// joystick buttons 1-128 across two respective joysticks as reported by windows.
// 256 total buttons.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only. (M.Geders confirms it works with Pro Micro too)
//
// Joystick Library by Matthew Heironimus
// 7-6-20 by M. Geders
//--------------------------------------------------------------------

#include <Joystick.h>  //Needed to make it a Windows joystick
#include <Wire.h>  //Include the I2C library (required)
#include <SparkFunSX1509.h>  // Include SX1509 library
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

void QWIICMUX(uint8_t bus)
{
  Wire.beginTransmission(0x72);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
// ADD1  ADD0  I2C address
// 0     0     0x3E
// 0     1     0x3F
// 1     0     0x70
// 1     1     0x71

const byte SX1509_ADDRESS_1 = 0x3E;  // First SX1509 I2C address
SX1509 io_SX1509_1;  // Create an SX1509 object named io_SX1509_1

const byte SX1509_ADDRESS_2 = 0x3F;  // Second SX1509 I2C address
SX1509 io_SX1509_2;  // Create an SX1509 object named io_SX1509_2

const byte SX1509_ADDRESS_3 = 0x70;  // Third SX1509 I2C address
SX1509 io_SX1509_3;  // Create an SX1509 object named io_SX1509_3

const byte SX1509_ADDRESS_4 = 0x71;  // Fourth SX1509 I2C address
SX1509 io_SX1509_4;  // Create an SX1509 object named io_SX1509_4

const byte SX1509_ADDRESS_5 = 0x3E;  // First SX1509 I2C address
SX1509 io_SX1509_5;  // Create an SX1509 object named io_SX1509_5

const byte SX1509_ADDRESS_6 = 0x3F;  // Second SX1509 I2C address
SX1509 io_SX1509_6;  // Create an SX1509 object named io_SX1509_6

const byte SX1509_ADDRESS_7 = 0x70;  // Third SX1509 I2C address
SX1509 io_SX1509_7;  // Create an SX1509 object named io_SX1509_7

const byte SX1509_ADDRESS_8 = 0x71;  // Fourth SX1509 I2C address
SX1509 io_SX1509_8;  // Create an SX1509 object named io_SX1509_8

const byte SX1509_ADDRESS_9 = 0x3E;  // First SX1509 I2C address
SX1509 io_SX1509_9;  // Create an SX1509 object named io_SX1509_9

const byte SX1509_ADDRESS_10 = 0x3F;  // Second SX1509 I2C address
SX1509 io_SX1509_10;  // Create an SX1509 object named io_SX1509_10

const byte SX1509_ADDRESS_11 = 0x70;  // Third SX1509 I2C address
SX1509 io_SX1509_11;  // Create an SX1509 object named io_SX1509_11

const byte SX1509_ADDRESS_12 = 0x71;  // Fourth SX1509 I2C address
SX1509 io_SX1509_12;  // Create an SX1509 object named io_SX1509_12

const byte SX1509_ADDRESS_13 = 0x3E;  // First SX1509 I2C address
SX1509 io_SX1509_13;  // Create an SX1509 object named io_SX1509_13

const byte SX1509_ADDRESS_14 = 0x3F;  // Second SX1509 I2C address
SX1509 io_SX1509_14;  // Create an SX1509 object named io_SX1509_14

const byte SX1509_ADDRESS_15 = 0x70;  // Third SX1509 I2C address
SX1509 io_SX1509_15;  // Create an SX1509 object named io_SX1509_15

const byte SX1509_ADDRESS_16 = 0x71;  // Fourth SX1509 I2C address
SX1509 io_SX1509_16;  // Create an SX1509 object named io_SX1509_16


Joystick_ Joystick1(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   128, 0,                  // Button Count, Hat Switch Count
                   false, false, false,     // no X, Y, or Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

Joystick_ Joystick2(0x04, JOYSTICK_TYPE_GAMEPAD,
                   128, 0,                  // Button Count, Hat Switch Count
                   false, false, false,     // no X, Y, or Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

void setup() {

  //Initialize all the sensors

  QWIICMUX(0);

  io_SX1509_1.begin(SX1509_ADDRESS_1);
  io_SX1509_2.begin(SX1509_ADDRESS_2);
  io_SX1509_3.begin(SX1509_ADDRESS_3);
  io_SX1509_4.begin(SX1509_ADDRESS_4);

  // Call io.pinMode(<pin>, <mode>) to set any SX1509 pin as
  // either an INPUT, OUTPUT, INPUT_PULLUP, or ANALOG_OUTPUT
  
  //Make all the ports on all the SX1509's inputs
  for (int x = 0 ; x < 16 ; x++)
  {
    io_SX1509_1.pinMode(x, INPUT_PULLUP);
    io_SX1509_2.pinMode(x, INPUT_PULLUP);
    io_SX1509_3.pinMode(x, INPUT_PULLUP);
    io_SX1509_4.pinMode(x, INPUT_PULLUP);
  }

  QWIICMUX(1);
    
  io_SX1509_5.begin(SX1509_ADDRESS_5);
  io_SX1509_6.begin(SX1509_ADDRESS_6);
  io_SX1509_7.begin(SX1509_ADDRESS_7);
  io_SX1509_8.begin(SX1509_ADDRESS_8);

  // Call io.pinMode(<pin>, <mode>) to set any SX1509 pin as
  // either an INPUT, OUTPUT, INPUT_PULLUP, or ANALOG_OUTPUT

  //Make all the ports on all the SX1509's inputs
  for (int x = 0 ; x < 16 ; x++)
  {
    io_SX1509_5.pinMode(x, INPUT_PULLUP);
    io_SX1509_6.pinMode(x, INPUT_PULLUP);
    io_SX1509_7.pinMode(x, INPUT_PULLUP);
    io_SX1509_8.pinMode(x, INPUT_PULLUP);
  }

    QWIICMUX(2);

  io_SX1509_9.begin(SX1509_ADDRESS_9);
  io_SX1509_10.begin(SX1509_ADDRESS_10);
  io_SX1509_11.begin(SX1509_ADDRESS_11);
  io_SX1509_12.begin(SX1509_ADDRESS_12);

  // Call io.pinMode(<pin>, <mode>) to set any SX1509 pin as
  // either an INPUT, OUTPUT, INPUT_PULLUP, or ANALOG_OUTPUT
  
  //Make all the ports on all the SX1509's inputs
  for (int x = 0 ; x < 16 ; x++)
  {
    io_SX1509_9.pinMode(x, INPUT_PULLUP);
    io_SX1509_10.pinMode(x, INPUT_PULLUP);
    io_SX1509_11.pinMode(x, INPUT_PULLUP);
    io_SX1509_12.pinMode(x, INPUT_PULLUP);
  }

      QWIICMUX(3);

  io_SX1509_13.begin(SX1509_ADDRESS_13);
  io_SX1509_14.begin(SX1509_ADDRESS_14);
  io_SX1509_15.begin(SX1509_ADDRESS_15);
  io_SX1509_16.begin(SX1509_ADDRESS_16);

  // Call io.pinMode(<pin>, <mode>) to set any SX1509 pin as
  // either an INPUT, OUTPUT, INPUT_PULLUP, or ANALOG_OUTPUT
  
  //Make all the ports on all the SX1509's inputs
  for (int x = 0 ; x < 16 ; x++)
  {
    io_SX1509_13.pinMode(x, INPUT_PULLUP);
    io_SX1509_14.pinMode(x, INPUT_PULLUP);
    io_SX1509_15.pinMode(x, INPUT_PULLUP);
    io_SX1509_16.pinMode(x, INPUT_PULLUP);
  }

  // Initialize Joystick Library
  Joystick1.begin();
  Joystick2.begin();
}

// Last state of the button
int lastButtonState1[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                           };

int lastButtonState2[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                           };

void loop() {

  QWIICMUX(0);

  // Read pin values from the first SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_1.digitalRead(index);
    if (currentButtonState != lastButtonState1[index])
    {
      Joystick1.setButton(index, currentButtonState);
      lastButtonState1[index] = currentButtonState;
    }
  }

  // Read pin values from the second SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_2.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 16])
    {
      Joystick1.setButton(index + 16, currentButtonState);
      lastButtonState1[index + 16] = currentButtonState;
    }
  }

  // Read pin values from the third SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_3.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 32])
    {
      Joystick1.setButton(index + 32, currentButtonState);
      lastButtonState1[index + 32] = currentButtonState;
    }
  }

  // Read pin values from the fourth SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_4.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 48])
    {
      Joystick1.setButton(index + 48, currentButtonState);
      lastButtonState1[index + 48] = currentButtonState;
    }
  }


    QWIICMUX(1);

  // Read pin values from the first SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_5.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 64])
    {
      Joystick1.setButton(index + 64, currentButtonState);
      lastButtonState1[index + 64] = currentButtonState;
    }
  }
  
  // Read pin values from the second SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_6.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 80])
    {
      Joystick1.setButton(index + 80, currentButtonState);
      lastButtonState1[index + 80] = currentButtonState;
    }
  }

  // Read pin values from the third SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_7.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 96])
    {
      Joystick1.setButton(index + 96, currentButtonState);
      lastButtonState1[index + 96] = currentButtonState;
    }
  }

  // Read pin values from the fourth SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_8.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 112])
    {
      Joystick1.setButton(index + 112, currentButtonState);
      lastButtonState1[index + 112] = currentButtonState;
    }
  }

  QWIICMUX(2);

  // Read pin values from the first SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_9.digitalRead(index);
    if (currentButtonState != lastButtonState2[index])
    {
      Joystick2.setButton(index, currentButtonState);
      lastButtonState2[index] = currentButtonState;
    }
  }
  
  // Read pin values from the second SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_10.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 16])
    {
      Joystick2.setButton(index + 16, currentButtonState);
      lastButtonState2[index + 16] = currentButtonState;
    }
  }

  // Read pin values from the third SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_11.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 32])
    {
      Joystick2.setButton(index + 32, currentButtonState);
      lastButtonState2[index + 32] = currentButtonState;
    }
  }

  // Read pin values from the fourth SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_12.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 48])
    {
      Joystick2.setButton(index + 48, currentButtonState);
      lastButtonState2[index + 48] = currentButtonState;
    }
  }

  QWIICMUX(3);

  // Read pin values from the first SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_13.digitalRead(index);
    if (currentButtonState != lastButtonState2[index+ 64])
    {
      Joystick2.setButton(index + 64, currentButtonState);
      lastButtonState2[index + 64] = currentButtonState;
    }
  }
  
  // Read pin values from the second SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_14.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 80])
    {
      Joystick2.setButton(index + 80, currentButtonState);
      lastButtonState2[index + 80] = currentButtonState;
    }
  }

  // Read pin values from the third SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_15.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 96])
    {
      Joystick2.setButton(index + 96, currentButtonState);
      lastButtonState2[index + 96] = currentButtonState;
    }
  }

  // Read pin values from the fourth SX1509
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_16.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 112])
    {
      Joystick2.setButton(index + 112, currentButtonState);
      lastButtonState2[index + 112] = currentButtonState;
    }
  }

  delay(50);
}
