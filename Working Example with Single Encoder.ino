// Ground digital pins 0 through 15 of each SX1509_Fast to press the
// joystick buttons 1-128 across two respective joysticks as reported by windows.
// 256 total buttons.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only. (M.Geders confirms it works with Pro Micro too)
//
// 7-31-20 by M. Geders
// Joystick Library by Matthew Heironimus
// SparkFunSX1509_Fast Library by BmCha
//--------------------------------------------------------------------

#include <Joystick.h>  //Needed to make it a Windows joystick
#include <Wire.h>  //Include the I2C library (required)
#include <SparkFunSX1509_Fast.h>  // Include SX1509_Fast Fast library
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

int currentEncoderState_A = 1;  // these are used to store the state history of the previous 3 scans on pin A
int PrevEncoderState_A = 1;
int PrevPrevEncoderState_A =1;
int PrevPrevPrevEncoderState_A = 1;

int currentEncoderState_B = 1;  // these are used to store the state history of the previous 3 scans on pin A
int PrevEncoderState_B = 1;
int PrevPrevEncoderState_B =1;
int PrevPrevPrevEncoderState_B = 1;

void QWIICMUX(uint8_t bus)
{
  Wire.beginTransmission(0x72);  // TCA9548A address is 0x70
  Wire.setClock(400000);
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

// SX1509_Fast I2C address (set by ADDR1 and ADDR0 (00 by default):
// ADD1  ADD0  I2C address
// 0     0     0x3E
// 0     1     0x3F
// 1     0     0x70
// 1     1     0x71

const byte SX1509_ADDRESS_1 = 0x3E;  // First SX1509_Fast I2C address
SX1509_Fast io_SX1509_1;  // Create an SX1509_Fast object named io_SX1509_1

const byte SX1509_ADDRESS_2 = 0x3F;  // Second SX1509_Fast I2C address
SX1509_Fast io_SX1509_2;  // Create an SX1509_Fast object named io_SX1509_2

const byte SX1509_ADDRESS_3 = 0x70;  // Third SX1509_Fast I2C address
SX1509_Fast io_SX1509_3;  // Create an SX1509_Fast object named io_SX1509_3

const byte SX1509_ADDRESS_4 = 0x71;  // Fourth SX1509_Fast I2C address
SX1509_Fast io_SX1509_4;  // Create an SX1509_Fast object named io_SX1509_4

const byte SX1509_ADDRESS_5 = 0x3E;  // First SX1509_Fast I2C address
SX1509_Fast io_SX1509_5;  // Create an SX1509_Fast object named io_SX1509_5

const byte SX1509_ADDRESS_6 = 0x3F;  // Second SX1509_Fast I2C address
SX1509_Fast io_SX1509_6;  // Create an SX1509_Fast object named io_SX1509_6

const byte SX1509_ADDRESS_7 = 0x70;  // Third SX1509_Fast I2C address
SX1509_Fast io_SX1509_7;  // Create an SX1509_Fast object named io_SX1509_7

const byte SX1509_ADDRESS_8 = 0x71;  // Fourth SX1509_Fast I2C address
SX1509_Fast io_SX1509_8;  // Create an SX1509_Fast object named io_SX1509_8

const byte SX1509_ADDRESS_9 = 0x3E;  // First SX1509_Fast I2C address
SX1509_Fast io_SX1509_9;  // Create an SX1509_Fast object named io_SX1509_9

const byte SX1509_ADDRESS_10 = 0x3F;  // Second SX1509_Fast I2C address
SX1509_Fast io_SX1509_10;  // Create an SX1509_Fast object named io_SX1509_10

const byte SX1509_ADDRESS_11 = 0x70;  // Third SX1509_Fast I2C address
SX1509_Fast io_SX1509_11;  // Create an SX1509_Fast object named io_SX1509_11

const byte SX1509_ADDRESS_12 = 0x71;  // Fourth SX1509_Fast I2C address
SX1509_Fast io_SX1509_12;  // Create an SX1509_Fast object named io_SX1509_12

const byte SX1509_ADDRESS_13 = 0x3E;  // First SX1509_Fast I2C address
SX1509_Fast io_SX1509_13;  // Create an SX1509_Fast object named io_SX1509_13

const byte SX1509_ADDRESS_14 = 0x3F;  // Second SX1509_Fast I2C address
SX1509_Fast io_SX1509_14;  // Create an SX1509_Fast object named io_SX1509_14

const byte SX1509_ADDRESS_15 = 0x70;  // Third SX1509_Fast I2C address
SX1509_Fast io_SX1509_15;  // Create an SX1509_Fast object named io_SX1509_15

const byte SX1509_ADDRESS_16 = 0x71;  // Fourth SX1509_Fast I2C address
SX1509_Fast io_SX1509_16;  // Create an SX1509_Fast object named io_SX1509_16


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

  //Serial.begin(115200);
  //Initialize all the sensors

  QWIICMUX(0);

  io_SX1509_1.begin(SX1509_ADDRESS_1);
  io_SX1509_2.begin(SX1509_ADDRESS_2);
  io_SX1509_3.begin(SX1509_ADDRESS_3);
  io_SX1509_4.begin(SX1509_ADDRESS_4);

  // Call io.pinMode(<pin>, <mode>) to set any SX1509_Fast pin as
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

  // Call io.pinMode(<pin>, <mode>) to set any SX1509_Fast pin as
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

  // Call io.pinMode(<pin>, <mode>) to set any SX1509_Fast pin as
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

  // Call io.pinMode(<pin>, <mode>) to set any SX1509_Fast pin as
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
  io_SX1509_1.readInputs();
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
  io_SX1509_2.readInputs();
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
  io_SX1509_3.readInputs();
 
// I want to be able to call the following as a function (or library thingy)
 
 int currentEncoderState_A = io_SX1509_3.digitalRead(0);  //Reads Encoder Pin A
 int currentEncoderState_B = io_SX1509_3.digitalRead(1);   //Reads Encoder Pin B

 int Encoder_A = ((PrevPrevPrevEncoderState_A << 7) + (PrevPrevEncoderState_A << 6) + (PrevEncoderState_A << 5) + (currentEncoderState_A << 4));  //This stores the previous 3 states plus the current one in a handy way for the most accurate comparative use.

 int Encoder_B = ((PrevPrevPrevEncoderState_B << 3) + (PrevPrevEncoderState_B << 2) + (PrevEncoderState_B << 1) + (currentEncoderState_B));

 int Encoder_A1 = ((PrevPrevEncoderState_A << 5) + (PrevEncoderState_A << 4) + (currentEncoderState_A << 3)); //This stores the previous 2 states plus the current one in a handy way for a slightly more error tolerant comparative use.

 int Encoder_B1 = ((PrevPrevEncoderState_B << 2) + (PrevEncoderState_B << 1) + (currentEncoderState_B));

 int Encoder_A2 = ((PrevEncoderState_A << 3) + (currentEncoderState_A << 2)); //This stores the previous states plus the current one in a handy way for a slightly more the most error tolerant comparative use.

 int Encoder_B2 = ((PrevEncoderState_B << 1) + (currentEncoderState_B));
 
 int EncoderSum = Encoder_A + Encoder_B;  // When we compare the last 3 states of each encoder, we can determine direction of spin with a good deal of accuracy
 int EncoderSum1 = Encoder_A1 + Encoder_B1;  // A little less accurate, but it can still detect direction of spin.
 int EncoderSum2 = Encoder_A2 + Encoder_B2;  // Since this one only uses the previous state to determin direction it's the least confident way.

   // Encoder Logic Error Handling Matrix condition check and resultant action goes here
   if ((EncoderSum) == 57 ||  // All these EncoderSum checks compare the previous 3 states to see if they match the ideal series of what should happen going from any of the 4 possible quadrature states.
       (EncoderSum) == 156 ||
       (EncoderSum) == 198 ||
       (EncoderSum) == 99 ||
       (EncoderSum) == 157 ||  // Starting here, it allows for some error.  i.e. what happens if a scan misses a state change that happened on any of the three previous positions.
       (EncoderSum) == 189 ||
       (EncoderSum) == 185 ||
       (EncoderSum) == 214 ||
       (EncoderSum) == 212 ||
       (EncoderSum) == 148 ||
       (EncoderSum) == 98 ||
       (EncoderSum) == 66 ||
       (EncoderSum) == 70 ||
       (EncoderSum) == 41 ||
       (EncoderSum) == 43 ||
       (EncoderSum) == 107 ||
       (EncoderSum1) == 25 ||  //  Same as above, but it only compares the previous 2 states.
       (EncoderSum1) == 12 ||
       (EncoderSum1) == 38 ||
       (EncoderSum1) == 51 ||
       (EncoderSum1) == 13 ||  //  Again allowing for various missed states.
       (EncoderSum1) == 29 ||
       (EncoderSum1) == 44 ||
       (EncoderSum1) == 50 ||
       (EncoderSum1) == 34 ||
       (EncoderSum1) == 17 ||
       (EncoderSum1) == 19 ||
       (EncoderSum2) == 13 ||  // Now we use only the previous state (and the uniquely identifiable directions as some results overlap with the opposite direction.
       (EncoderSum2) == 4 ||
       (EncoderSum2) == 2 ||
       (EncoderSum2) == 11)
       {
         Joystick1.setButton(32, 1);
         //Serial.println("This should only display when Joy32 is being pressed");
       }
 

   // Encoder Logic Error Handling Matrix condition check and resultant action goes here
   else if ((EncoderSum) == 147 || 
       (EncoderSum) == 201 ||
       (EncoderSum) == 108 ||
       (EncoderSum) == 54 ||
       (EncoderSum) == 217 ||
       (EncoderSum) == 219 ||
       (EncoderSum) == 155 ||
       (EncoderSum) == 109 ||
       (EncoderSum) == 197 ||
       (EncoderSum) == 73 ||
       (EncoderSum) == 38 ||
       (EncoderSum) == 36 ||
       (EncoderSum) == 100 ||
       (EncoderSum) == 146 ||
       (EncoderSum) == 178 ||
       (EncoderSum) == 182 ||
       (EncoderSum1) == 11 ||
       (EncoderSum1) == 33 ||
       (EncoderSum1) == 52 ||
       (EncoderSum1) == 30 ||
       (EncoderSum1) == 41 ||
       (EncoderSum1) == 43 ||
       (EncoderSum1) == 53 ||
       (EncoderSum1) == 37 ||
       (EncoderSum1) == 22 ||
       (EncoderSum1) == 20 ||
       (EncoderSum1) == 10 ||
       (EncoderSum1) == 26 ||
       (EncoderSum2) == 7 ||
       (EncoderSum2) == 1 ||
       (EncoderSum2) == 8 ||
       (EncoderSum2) == 14)
       {
         Joystick1.setButton(33, 1);
         //Serial.println("This should only display when Joy33 is being pressed");
       }

 if( (EncoderSum) == 255 ||  //if the encoder has been seen as stationary for the past 3 cycles including the current...
     (EncoderSum) == 15  ||
     (EncoderSum) == 0   ||
     (EncoderSum) == 240 )
 {
 Joystick1.setButton(32, 0);  // ...then I guess we should let go of the joystick buttons
 Joystick1.setButton(33, 0);
 }
 else {};
 
 PrevPrevPrevEncoderState_A = PrevPrevEncoderState_A;  //Update the history of the encoder states no matter what happens so the next time we scan we'll be good to go.
 PrevPrevEncoderState_A = PrevEncoderState_A;
 PrevEncoderState_A = currentEncoderState_A;
 
 PrevPrevPrevEncoderState_B = PrevPrevEncoderState_B;
 PrevPrevEncoderState_B = PrevEncoderState_B;
 PrevEncoderState_B = currentEncoderState_B;
  
  for (int index = 2; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_3.digitalRead(index);
    if (currentButtonState != lastButtonState1[index + 32])
    {
      Joystick1.setButton(index + 32, currentButtonState);
      lastButtonState1[index + 32] = currentButtonState;
    }
  }

  // Read pin values from the fourth SX1509
  io_SX1509_4.readInputs(); 
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
  io_SX1509_5.readInputs();
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
  io_SX1509_6.readInputs();
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
  io_SX1509_7.readInputs();
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
  io_SX1509_8.readInputs();
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
  io_SX1509_9.readInputs();
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
  io_SX1509_10.readInputs();
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
  io_SX1509_11.readInputs();
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
  io_SX1509_12.readInputs();
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
  io_SX1509_13.readInputs();
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_13.digitalRead(index);
    if (currentButtonState != lastButtonState2[index+64])
    {
      Joystick2.setButton(index+64, currentButtonState);
      lastButtonState2[index+64] = currentButtonState;
    }
  }
  
  // Read pin values from the second SX1509
  io_SX1509_14.readInputs();
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
  io_SX1509_15.readInputs();
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
  io_SX1509_16.readInputs();
  for (int index = 0; index < 16; index++)
  {
    int currentButtonState = !io_SX1509_16.digitalRead(index);
    if (currentButtonState != lastButtonState2[index + 112])
    {
      Joystick2.setButton(index + 112, currentButtonState);
      lastButtonState2[index + 112] = currentButtonState;
    }
  }

  //Serial.println(micros());
  //delay(50);
}