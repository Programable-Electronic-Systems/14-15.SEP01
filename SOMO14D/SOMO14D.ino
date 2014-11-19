/*
  BasicPlayer
  Play the first song of the microSD memory
 
  This example code is in the public domain.
  
  Connections:
    SOMO-14D clk pin to arduino pin 8
    SOMO-14D data pin to arduino pin 9
    SOMO-14D busy pin to arduino pin 10
*/
 
#include "SOMO14D.h"
const int HELLO = 0; 
const int BYE = 1;
const int MOVING = 2;
const int STREAMING = 3;
const int WORKCOMPLETED = 4;

SOMO14D somo14d;

void setup() {
  
  somo14d.begin(8, 9, 10);
  somo14d.play(HI);
}

void loop() {

  delay(10);
}
