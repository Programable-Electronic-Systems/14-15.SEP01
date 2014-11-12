#include "RFID.h"

enum status{
	NON_IDENTIFICATION,
	IDLE, //ocioso
	WALKING, //andando
	MUSIC, //reproducir musica
	RECIEVING_SONG, //recibiendo cancion
};
RFID rf;
#define rxRFID 5
#define pinRFID 6

status robot;

void setup()
{
	robot = NON_IDENTIFICATION;
	// 5 = rx, 6 pin
	rf =  RFID(rxRFID,pinRFID);
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
