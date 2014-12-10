#if defined(ARDUINO) && ARDUINO >= 100

  #include "Arduino.h"

  #include "Platform.h"

  #include "SoftwareSerial.h"

#ifndef CDC_ENABLED

  // Shield Jumper on SW

  SoftwareSerial port(12,13);

#else

  // Shield Jumper on HW (for Leonardo)

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

enum Groups

{
  GROUP_0  = 0,
  GROUP_1  = 1,
};


enum Group0 
{
  G0_UNNAMED_COMMAND_0 = 0,
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



void setup()

{

#ifndef CDC_ENABLED

  // bridge mode?

  if (bridge.check())

  {

    cli();

    bridge.loop(0, 1, 12, 13);

  }

  // run normally

  Serial.begin(9600);

  Serial.println("Bridge not started!");

#else

  // bridge mode?

  if (bridge.check())

  {

    port.begin(9600);

    bridge.loop(port);

  }

  Serial.println("Bridge connection aborted!");

#endif

  port.begin(9600);



  while (!easyvr.detect())

  {

    Serial.println("EasyVR not detected!");

    delay(1000);

  }



  easyvr.setPinOutput(EasyVR::IO1, LOW);

  Serial.println("EasyVR detected!");

  easyvr.setTimeout(5);

  easyvr.setLanguage(4);


  group = EasyVR::TRIGGER;//<-- start group (customize)

}



void action();



void loop()

{
  group=GROUP_1;
  easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)



  Serial.print("Say a command in Group ");

  Serial.println(group);

  easyvr.recognizeCommand(group);



  do

  {

    // can do some processing while waiting for a spoken command

  }

  while (!easyvr.hasFinished());

  

  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off



  idx = easyvr.getWord();

  if (idx >= 0)

  {

    // built-in trigger (ROBOT)

    // group = GROUP_X; <-- jump to another group X

    return;

  }

  idx = easyvr.getCommand();

  if (idx >= 0)

  {

    // print debug message

    uint8_t train = 0;

    char name[32];

    Serial.print("Command: ");

    Serial.print(idx);

    if (easyvr.dumpCommand(group, idx, name, train))

    {

      Serial.print(" = ");

      Serial.println(name);

    }

    else

      Serial.println();

    easyvr.playSound(0, EasyVR::VOL_FULL);

    // perform some action

    action();

  }

  else // errors or timeout

  {

    if (easyvr.isTimeout())

      Serial.println("Timed out, try again...");

    int16_t err = easyvr.getError();

    if (err >= 0)

    {

      Serial.print("Error ");

      Serial.println(err, HEX);

    }

  }

}



void action()

{

    switch (group)

    {

    case GROUP_0:
      switch (idx)
      {
      case G0_UNNAMED_COMMAND_0:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_1:
      switch (idx)
      {
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
      break;
    }

}

