
/*
    Name:       test_yuno_lx200.ino
    Created:	2020-09-23 오후 12:06:44
    Author:     Kimtaeyoon
*/
#include <Arduino.h>
#include <AccelStepper.h>

/* constant */
const unsigned period = 0;  //86164 sec per day

/* global variable */
String command = "";
String temp = "";
long ra_pos = 0;
long dec_pos = 0;
char dec_sign = '+';



/* setup */
void setup(){
    
    /* pin out setup */
    pinMode(PB4, OUTPUT);   //ra m0
    pinMode(PB3, OUTPUT);   //ra m1
    pinMode(PA15, OUTPUT);  //ra m2
    pinMode(PA12, OUTPUT);  //ra step
    pinMode(PA11, OUTPUT);  //ra dir
    pinMode(PA8, OUTPUT);   //dec m0
    pinMode(PB15, OUTPUT);  //dec m1
    pinMode(PB14, OUTPUT);  //dec m2
    pinMode(PB13, OUTPUT);  //dec step
    pinMode(PB12, OUTPUT);  //dec dir
    pinMode(LED_BUILTIN, OUTPUT);
    
    /* guide port */
    pinMode(PB6, INPUT);    //+RA (Left)
    pinMode(PB7, INPUT);    //+DEC(Up)
    pinMode(PB8, INPUT);    //-DEC(Down)
    pinMode(PB9, INPUT);    //-RA (Right)
    
    /* tracking */
    Timer1.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    Timer1.setPeriod(1000000);    //us
    Timer1.attachCompare1Interrupt(track);
    
    /* serial comm */
    Serial.begin(9600);     //for develop
    Serial3.begin(38400);   //bluetooth
}

/* loop */
void loop(){ 
	if(Serial3.available()){
        command = Serial3.readStringUntil('#');
        bt_handler();
        Serial.println(command);    //for develop
        command = "";
    }
    
}
