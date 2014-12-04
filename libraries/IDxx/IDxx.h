/*
 Arduino Library for IDxx family RFID readers
 go to https://www.sparkfun.com/datasheets/Sensors/ID-12-Datasheet.pdf for more information
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2014
 by Jonathan Ruiz de Garibay

 */

#ifndef IDXX_h
#define IDXX_h

#include "Arduino.h"
using namespace std;

class IDxx
{
	public:
		void begin(Stream * serial, int p, char * c [], int i);
		bool isCorrect();
		String readTagId();

	private:
		Stream * _serial;
		char* correct[];
		int size;
		int pin;
};

#endif