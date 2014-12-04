#include <SoftwareSerial.h>
#include <IDxx.h>

IDxx i;
SoftwareSerial mySerial(12, 14); // RX, TX
#define RFID_ACTIVE 13
char * c [] = {"0F02782075"};

void setup() {
  // put your setup code here, to run once:
mySerial.begin(2400); // RFID reader SOUT pin connected to Serial RX pin at 2400bps 
pinMode(RFID_ACTIVE, OUTPUT);  
i.begin(&mySerial, RFID_ACTIVE, c, sizeof(c)/2);
Serial.begin(2400);
Serial.println(sizeof(c)/2);
digitalWrite(RFID_ACTIVE, LOW);                  // Activate the RFID reader

}

void loop() {

  // put your main code here, to run repeatedly:
  
  String s = "";
  s = i.readTagId();
  Serial.println(s);
  delay(1000);
    
}
