/*
    Name:       yuno_star_rev1.1.ino
    Created:	2020-07-25
    Author:     tae
*/

/*command
0,1,2,3,4,5,6,7 -> 2^n microstepping change
i -> in
o -> out
*/
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#include <AccelStepper.h>

//pin out
const int en_pin = 0;
const int ms0_pin = 0;
const int ms1_pin = 0;
const int ms2_pin = 0;
const int step_pin = 0;
const int dir_pin = 0;
const int bluetooth_tx = 2;
const int bluetooth_rx = 3;

//object
SoftwareSerial bluetooth_Serial(bluetooth_tx, bluetooth_rx);
SimpleTimer timer1;
AccelStepper focuser(1, step_pin, dir_pin);
//first input var 1, means it connected with driver.

//global variable
char command = 0;
short current_gear = 4;//default
bool CanGo = false;


void command_refresher();
void micro_changer(int gear);
//Main block
void setup(){
	bluetooth_Serial.begin(9600);
	Serial.begin(9600);
	pinMode(en_pin, OUTPUT);
	pinMode(ms0_pin, OUTPUT);
	pinMode(ms1_pin, OUTPUT);
	pinMode(ms2_pin, OUTPUT);
	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	
	focuser.setMaxSpeed(1000);
	focuser.setSpeed(500);
	
	timer1.setInterval(command_refresher, 50);//20hz
	
	digitalWrite(en_pin, HIGH);
	digitalWrite(dir_pin, LOW);
	micro_changer(4);
}//initializing end

void loop(){
	timer1.run();
	if(CanGo)focuser.runSpeed();
}//loop end


//==================================================
//==================== Functions ===================
//==================================================
void command_refresher(){
	//refresh
	if(bluetooth_Serial.available()){
		command = bluetooth_Serial.read();
	} else{
		command = 0;
	}
	
	//processing
	if(48<=command && command <= 55){
		micro_changer(1<<(command-48));
		//command -> 2^(command) micro-stepping.
	} else if(command == 'i'){
		CanGo = true;
		digitalWrite(en_pin, LOW);
		digitalWrite(dir_pin, LOW);
	} else if(command == 'o'){
		CanGo = true;
		digitalWrite(en_pin, LOW);
		digitalWrite(dir_pin, HIGH);
	} else if(command == 'e'){
		CanGo = false;
		digitalWrite(en_pin, HIGH);
	}
}

void micro_changer(int gear){
	switch(gear){
		case 1:
			digitalWrite(ms0_pin, LOW);
			digitalWrite(ms1_pin, LOW);
			digitalWrite(ms2_pin, LOW);
			break;
		case 2:
			digitalWrite(ms0_pin, HIGH);
			digitalWrite(ms1_pin, LOW);
			digitalWrite(ms2_pin, LOW);
			break;
		case 4:
			digitalWrite(ms0_pin, LOW);
			digitalWrite(ms1_pin, HIGH);
			digitalWrite(ms2_pin, LOW);
			break;
		case 8:
			digitalWrite(ms0_pin, HIGH);
			digitalWrite(ms1_pin, HIGH);
			digitalWrite(ms2_pin, LOW);
			break;
		case 16:
			digitalWrite(ms0_pin, LOW);
			digitalWrite(ms1_pin, LOW);
			digitalWrite(ms2_pin, HIGH);
			break;
		case 32:
			digitalWrite(ms0_pin, HIGH);
			digitalWrite(ms1_pin, LOW);
			digitalWrite(ms2_pin, HIGH);
			break;
		case 64:
			digitalWrite(ms0_pin, LOW);
			digitalWrite(ms1_pin, HIGH);
			digitalWrite(ms2_pin, HIGH);
			break;
		case 128:
			digitalWrite(ms0_pin, HIGH);
			digitalWrite(ms1_pin, HIGH);
			digitalWrite(ms2_pin, HIGH);
			break;
	}
}