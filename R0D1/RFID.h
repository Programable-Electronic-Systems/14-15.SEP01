/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Uno, Platform=avr, Package=arduino

	RFID.h library designed by Sergio Ausin
	This library works with the RFID reader of parallax
	Released to public domain
*/
#ifndef RFID_h
#define RFID_h
#include "Arduino.h"
#include <SoftwareSerial.h>


class RFID{
public:
	RFID(int r, int p);
	char* read();
	void setActivate(boolean a);
	boolean isActivated();
private:
	int  val = 0;
	char code[10];
	int bytesread = 0;
	int rx;
	int tx;
	int pin;
	boolean activate = true;
};
#endif
