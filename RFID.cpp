#include "Arduino.h"
#include "RFID.h"
#include <SoftwareSerial.h>

RFID::RFID(int r, int p){
	this->val = 0;
	this->bytesread = 0;
	Serial.begin(4800);
	rx = r;
	pin = p;
	digitalWrite(this->pin, LOW);

}

char* RFID::read(){
	if (this->activate){
		SoftwareSerial rf = SoftwareSerial(rx, 500);
		if (Serial.available() > 0) {          // if data available from reader 
			if ((val = rf.read()) == 10) {   // check for header 
				bytesread = 0;
				while (bytesread < 10) {              // read 10 digit code 
					if (Serial.available() > 0) {
						val = Serial.read();
						if ((val == 10) || (val == 13)) { // if header or stop bytes before the 10 digit reading 
							break;                       // stop reading 
						}
						code[bytesread] = val;         // add the digit           
						bytesread++;                   // ready to read next digit  
					}
				}
				if (bytesread == 10) {              // if 10 digit read is complete 
					return code;
				}
			}
		}
	}
	return 0;

}
void RFID::setActivate(boolean a){
	this->activate = a;
	if (a){
		digitalWrite(this->pin, LOW);
	}
	else{
		digitalWrite(this->pin, HIGH);
	}
}
boolean RFID::isActivated(){
	return this->activate;
}

