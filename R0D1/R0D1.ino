#include "RFID.h"
#define ReaderSerial Serial


enum status{
	NON_IDENTIFICATION,
	IDLE, //ocioso
	WALKING, //andando
	MUSIC, //reproducir musica
	RECIEVING_SONG, //recibiendo cancion
};
RFID r;
int rxRFID = 10;
int pinRFID = 6;
status robot;

void setup()
{
    Serial.begin(9600);
  ReaderSerial.begin(9600);

	robot = NON_IDENTIFICATION;
	r.begin(rxRFID, pinRFID, &ReaderSerial);
	// 5 = rx, 6 pin
  /* add setup code here */
}

void loop()
{
	switch (robot)
	{
	case NON_IDENTIFICATION:
		break;
	case IDLE:
		break;
	case WALKING:
		break;
	case MUSIC:
		break;
	case RECIEVING_SONG:
		break;
	default:
		break;
	}

  /* add main program code here */

}
