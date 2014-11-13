#include "Arduino.h"
#include "RFID.h"

void RFID::begin(int r, int p, Stream * s){
	this->serial = s;
	this->val = 0;
	this->bytesread = 0;

	rx = r;
	pin = p;
	digitalWrite(this->pin, LOW);

}

void RFID::setSerial(Stream * s){
	serial = s;
}

void RFID::setPin(int p){
	this->pin = p;
}

void RFID::setR(int r){
	this->rx = r;
}

char* RFID::read(){
	if (this->activate){
		if (serial->available() > 0) {          // if data available from reader 
			if ((val = serial->read()) == 10) {   // check for header 
				bytesread = 0;
				while (bytesread < 10) {              // read 10 digit code 
					if (serial->available() > 0) {
						val = serial->read();
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

