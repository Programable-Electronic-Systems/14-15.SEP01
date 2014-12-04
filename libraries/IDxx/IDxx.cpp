/*
 Arduino Library for IDxx family RFID readers
 go to https://www.sparkfun.com/datasheets/Sensors/ID-12-Datasheet.pdf for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2014
 by Jonathan Ruiz de Garibay

 */
using namespace std;
#include <Arduino.h>
#include "IDxx.h"

//
// begin
//
// initialize IDxx serial port
void IDxx::begin(Stream * serial, int p, char* c[], int i){
	_serial = serial;
	pin = p;
	size = i;
	for (int i = 0; i < size; i++){
		correct[i] = c[i];
	}
}                             


bool IDxx::isCorrect(){
	String s = readTagId();
	for (int i = 0; i < size; i++){
		String s1 = correct[i];
		if (s1.substring(0).equals(s1)){
			return true;
		}
	}
	return false;
}

//
// reset
//


//
// realTagId
//
// read tagId from RFID reader (12 hexadecimal characters); return "" if there is not a tag
String IDxx::readTagId() {

	String tagId = "";
	char data;
	int val = 0;
	int bytesread = 0;

	if (_serial->available() > 0) {
		if ((val = _serial->read()) == 10) {   // check for header 
			bytesread = 0;
			while (bytesread < 10){
				if (_serial->available() > 0){
					val = _serial->read();
					if (val == 10 || val == 13)
						break;
					//##?
				//	if((val>='0' && val<='9') || (val>='A' && val== 'Z')){
						tagId += "" + val;
						bytesread++;
						/*if (bytesread == 10){
							return tagId;
						}
					}*/
				}
			}
		}
	}

		return tagId ;
	

}