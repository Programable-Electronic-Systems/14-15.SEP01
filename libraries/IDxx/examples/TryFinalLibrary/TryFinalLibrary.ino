#include <SoftwareSerial.h>
#include <IDxx.h>

IDxx i;
SoftwareSerial mySerial(10, 11); // RX, TX
#define RFID_ACTIVE 2
char * c [] = {"hola", "esto", "es", "esparta"};

void setup() {
  // put your setup code here, to run once:
mySerial.begin(2400); // RFID reader SOUT pin connected to Serial RX pin at 2400bps 
pinMode(RFID_ACTIVE, OUTPUT);  
i.begin(&mySerial, RFID_ACTIVE, c, sizeof(c)/2);
Serial.begin(9600);
Serial.println(sizeof(c)/2);
i.isCorrect();
}

void loop() {
  // put your main code here, to run repeatedly:
  bool b = i.isCorrect();
  if(b){
    Serial.println("correcto");  
  }
  else{
    Serial.println("mas falso que una moneda de 13 leuros");  
  }
  delay(1000);
    
}
