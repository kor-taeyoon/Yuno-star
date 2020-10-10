/*
    Name:       yuno_focuser_v1.ino
    Created:	2020-07-15 오전 10:16:20
    Author:     DESKTOP-QCUIDBD\Kimtaeyoon
*/

/*pin setting
d2 -> en
d3 -> ms1
d4 -> ms2
d5 -> ms3
d6 -> step
d7 -> dir
serial1 -> hc05
*/
char command = 0;
long current_position = 0;
long last_position = 0;
int current_microstepping = 1;
float interval;

const int en_pin = 2;
const int ms1 = 3;
const int ms2 = 4;
const int ms3 = 5;
const int step_pin = 6;
const int dir_pin = 7;

void setup() {
	pinMode(en_pin, OUTPUT);
	pinMode(ms1, OUTPUT);
	pinMode(ms2, OUTPUT);
	pinMode(ms3, OUTPUT);
	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	Serial1.begin(38400);
}

void loop() {
	if(Serial1.available()){
		command = Serial1.read();
		switch(command){
			//stepper work
			case 'i':
				digitalWrite(en_pin, LOW);
				digitalWrite(dir_pin, LOW);
				while(1){
					if(Serial1.available()&&Serial1.read() == 'e'){
						break;
					}
					digitalWrite(step_pin, HIGH);
					delayMicroseconds(interval);
					digitalWrite(step_pin, LOW);
					delayMicroseconds(interval);
					/*
					//accelrating
					
					*/
				}
				while(1){
					
				}
				
				
				//acceleration start until max speed
				break;
			
			
			case 'o':
				digitalWrite(en_pin, LOW);
				digitalWrite(dir_pin, HIGH);
				
				//deacceleration start until 0
				break;
			
			
			
			//change microstepping
			case '0' ://full
				set_microstepping(command);
			
			case '1'://2
				set_microstepping(command);
			
			case '2'://4
				set_microstepping(command);
			
			case '3'://8
				set_microstepping(command);
			
			case '4'://16
				set_microstepping(command);
			
			case '5'://32
				set_microstepping(command);
			
			case '6'://64
				set_microstepping(command);
			
			case '7'://128
				set_microstepping(command);
			
			//go back last position
			case 'b':
				set_microstepping('8');
				while(1){
					if(current_position == last_position){
						break;
					}
					digitalWrite(step_pin, HIGH);
					delay(1);
					digitalWrite(step_pin, LOW);
					delay(1);
					if(current_position - last_position >= 0){
						current_position += 32;
					}
					else{
						current_position -= 32;
					}
				}
				break;
			
			//stepper position initialize
			case 'c':
				break;
		}
	}
	else{
		digitalWrite(en_pin, HIGH);//stepper disable
	}
}

void set_microstepping(char target){
	switch(target){
		//change microstepping
		case '0' ://full
			digitalWrite(ms1, LOW);
			digitalWrite(ms2, LOW);
			digitalWrite(ms3, LOW);
			break;
		
		case '1'://2
			digitalWrite(ms1, HIGH);
			digitalWrite(ms2, LOW);
			digitalWrite(ms3, LOW);
			break;
		
		case '2'://4
			digitalWrite(ms1, LOW);
			digitalWrite(ms2, HIGH);
			digitalWrite(ms3, LOW);
			break;
		
		case '3'://8
			digitalWrite(ms1, HIGH);
			digitalWrite(ms2, HIGH);
			digitalWrite(ms3, LOW);
			break;
		
		case '4'://16
			digitalWrite(ms1, LOW);
			digitalWrite(ms2, LOW);
			digitalWrite(ms3, HIGH);
			break;
		
		case '5'://32
			digitalWrite(ms1, HIGH);
			digitalWrite(ms2, LOW);
			digitalWrite(ms3, HIGH);
			break;
		
		case '6'://64
			digitalWrite(ms1, LOW);
			digitalWrite(ms2, HIGH);
			digitalWrite(ms3, HIGH);
			break;
		
		case '7'://128
			digitalWrite(ms1, HIGH);
			digitalWrite(ms2, HIGH);
			digitalWrite(ms3, HIGH);
			break;
	}
}
