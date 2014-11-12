/*
----Mapping----
Arduino Rx = RFID SOUT
Arduino D2 = RFID Enable
Arduino GND = RFID GND
Arduino 5v = RFID VCC
D2 means digital pin number 2.
*/

// RFID reader for Arduino 
// Wiring version by BARRAGAN <http://people.interaction-ivrea.it/h.barragan> 
// Modified for Arudino by djmatic
#include "C:\Users\Sergio\Documents\Arduino\R0D1\Visual Micro\RFID.h"

RFID r;
void setup() {
	r = new RFID(8, 8, 2);
}


void loop() {
	if (char[10] code = r.read() && code != 0){
		Serial.print(code);
	}
	
}
