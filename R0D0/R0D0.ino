#include <SOMO14D.h>

#include <IDxx.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>

/* Altavoz */
int option = 0;
const int DIGIMON = 1; 
const int GOT = 2;
const int MARIODEAD = 3;
const int MARIOTHEME = 4;
const int LOTR = 5;
const int ZELDA = 6;
const int IMPERIAL = 7;
SOMO14D somo14d;

/*LCD*/
LiquidCrystal lcd(2, 3, 4, 5, 6 , 7);

/* Servos */
#define MOTOR_DERECHA 9
#define MOTOR_IZQUIERDA 8
Servo ruedaBuena; //izquierda
Servo ruedaMala; //derecha


/*RFID*/ 
IDxx id;
SoftwareSerial mySR(12, 14); // RX, TX
#define ENABLE 13
String clave = "0F02782075";
String s;
char * c [] = {"0F02782075"};

/*Ultrasonidos*/
#define ECHOPIN 25                           
// Pin to receive echo pulse
#define TRIGPIN 23                            // Pin to send trigger pulse
int distance;

/*Bluetooth*/
SoftwareSerial mySerial(10, 11); // RX, TX
char ch;
boolean change = false;

enum status{
	NON_IDENTIFICATION,
	IDLE,//ocioso
	WALKING, //andando
        MUSIC, //reproducir musica
        VOICE, //ver voz
};
status robot;
String data;

void setup()
{	
  Serial1.begin(2400);
  pinMode(ENABLE, OUTPUT);
  id.begin(&Serial1, ENABLE, c, sizeof(c)/2);
  digitalWrite(ENABLE, LOW);
  Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}
	data = "";

	robot =	NON_IDENTIFICATION;
	// 5 = rx, 6 pin
	/* add setup code here */
	Serial.println("Inicializacion hecha");
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}
	ruedaBuena.attach(MOTOR_IZQUIERDA);
	ruedaMala.attach(MOTOR_DERECHA);
	mySerial.begin(9600);
        lcd.begin(16, 2);
        lcd.setCursor(0,1);
        clear("Hola, soy R0D0");
        delay(1000);
        pinMode(ECHOPIN, INPUT);
        pinMode(TRIGPIN, OUTPUT);
        s = "";
        somo14d.begin(29, 28, 27);
     //   somo14d.play(1);

}

void loop()
{


	switch (robot)
	{
	case NON_IDENTIFICATION:
              Serial.println("Identificate");

                s = id.readTagId();
                Serial.println(s);
                delay(1000);
                if(s.equals(clave)){
                        Serial.println("identificado, modo IDLE activado");
			robot = IDLE;
                        clear("ocioso");
		}
                else{
                   
                }

		break;
	case IDLE:
                //lcd.clear();

		read();
		switch (ch)
		{
		case 'w':
			robot = WALKING;
			//leer arduino
	                clear("Modo andar");
                        somo14d.play(IMPERIAL);

			break;
		case 'm':
                        clear("Music :)");
			robot = MUSIC;
                        somo14d.play(option);
			break;
                case 'v':
                        clear("Voz");
                        robot = VOICE;
		default:
			break;
		}
		break;
	case WALKING:
		read();
                calculateDistance();
                Serial.println(distance);
                if(distance < 10){
                  ch = 's';
                }
		switch (ch)
		{
		case 'u':
                        if(!change){
                          clear("Adelante");
                        }
                        
                          ruedaBuena.write(0); // set servo to mid-point (90°)
                          ruedaMala.write(180);
                        
			break;
                case 's':
                        ruedaBuena.write(90); // set servo to mid-point (90°)
                        ruedaMala.write(90);
                        robot = IDLE;
                        break;
                case 'l':
                        //lcd:clear();
                        if(!change){
                          clear("Left");
                        }
                          ruedaBuena.write(90);
                          ruedaMala.write(180);
                        
                        break;
                case 'r':
                        //lcd.clear();
                        if(!change){
                        clear("right");
                        }
                          ruedaBuena.write(0);
                          ruedaMala.write(90);  
                                  
		default:
			break;
		}
		break;
	case MUSIC:
              read();
              Serial.println(option);
              switch(ch){
                  case 'l':
                    if(change){
                      option--;  
                      calculateOption();
                      somo14d.play(option);
                      change = false;
                    }
                  break;
                  case 'r':
                    if(change){
                      option++;
                      calculateOption();
                      somo14d.play(option);
                      change = false;
                    }
	         break;
                case 's':
                robot = IDLE;
                
                change = false;
                break;
                	default:
                		break;
        	}
          break;
        
        default:
        break;
    }

	/* add main program code here */

}

void read(){
	if (mySerial.available()){
                ch = mySerial.read();  
		Serial.write(ch);
		change = true;
	}
	if (Serial.available()){
		mySerial.write(Serial.read());
	}
}


void clear(const char* s){
  lcd.write("                ");
  lcd.write(s);
}

int calculateDistance(){
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  distance = pulseIn(ECHOPIN, HIGH);        // Read in times pulse
  distance= distance/58;                        // Calculate distance from time of pulse
  Serial.println(distance);                     
//  delay(250); 
  return distance;
  
}

void calculateOption(){
  if(option == 0){
    option = 7;
  }  
  else if(option > 7){
    option = 1;  
  }

}
