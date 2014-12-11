#if defined(ARDUINO) && ARDUINO >= 100
  #include "SoftwareSerial.h"

#ifndef CDC_ENABLED
  // Shield Jumper on SW
  SoftwareSerial port(12,13);
#else
  #define port Serial1
#endif

#else // Arduino 0022 - use modified NewSoftSerial
  #include "WProgram.h"
  #include "NewSoftSerial.h"
  NewSoftSerial port(12,13);

#endif

#include "EasyVR.h"
EasyVR easyvr(port);

//Groups and Commands

enum Groups{
  GROUP_1  = 1,
};

enum Group1 
{
  G1_ADELANTE = 0,
  G1_ATRAS = 1,
  G1_DERECHA = 2,
  G1_IZQUIERDA = 3,
  G1_STOP = 4,
  G1_STAR_WARS = 5,
  G1_DIGIMON = 6,
};

EasyVRBridge bridge;
int8_t group, idx;

void setup(){

  if (bridge.check())  {
    cli();
    bridge.loop(0, 1, 12, 13);
  }

  Serial.begin(9600);
  Serial.println("Bridge not started!");
  port.begin(9600);

  while (!easyvr.detect()){
    Serial.println("EasyVR not detected!");
    delay(1000);
  }

  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(5);
  easyvr.setLanguage(4);
  group=GROUP_1;
}

void action();

void loop(){
  Serial.print("Say a command in Group ");
  Serial.println(group);
  easyvr.recognizeCommand(group);

  do {

  }  while (!easyvr.hasFinished());
  
  idx = easyvr.getCommand();
  if (idx >= 0) {
    Serial.print("Command: ");
    Serial.println(idx);
    action();
  }

  else {
    if (easyvr.isTimeout())
      Serial.println("Timed out, try again...");
    int16_t err = easyvr.getError();
    if (err >= 0) {
      Serial.print("Error ");
      Serial.println(err, HEX);
    }
  }
}



void action(){
  switch (idx) {
    case G1_ADELANTE:
      Serial.println("Adelante");
      break;
    case G1_ATRAS:
      Serial.println("Atras");
      break;
    case G1_DERECHA:
      Serial.println("Derecha");
      break;
    case G1_IZQUIERDA:
      Serial.println("Izquierda");
      break;
    case G1_STOP:
      Serial.println("Stop");
      break;
    case G1_STAR_WARS:
      Serial.println("Star wars");
      break;
    case G1_DIGIMON:
      Serial.println("Digimon");
      break;
  }
}

