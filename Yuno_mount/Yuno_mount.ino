/*
    Name:       Yuno_mount.ino
    Created:	2020-10-26-월 오후 6:50:50
    Author:     DESKTOP-QCUIDBD\Kimtaeyoon
*/
#include <Arduino.h>
#include <AccelStepper.h>

/* constant */
// 24 * 60 * 60 = 86400 ~= 86164
// 
const unsigned period = 0;  //86164 sec per day


/* global variable */
String command = "";
String temp_string = "";
long temp_long = 0;
long ra_pos = 0;
long dec_pos = 0;
char dec_sign = '+';
long ra_pos_target = 0;
long dec_pos_target = 0;
char dec_sign_target = '+';
AccelStepper RA_stepper(AccelStepper::DRIVER, PA12, PA11);
AccelStepper DEC_stepper(AccelStepper::DRIVER, PB13, PB12);


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
    Timer1.attachCompare1Interrupt(TrackingPulse);
    
    /* serial comm */
    Serial.begin(9600);     //for develop
    Serial3.begin(38400);   //bluetooth
    
    /* stepper initialize */
    RA_stepper.setMaxSpeed(2000);
    RA_stepper.setAcceleration(1000);
    RA_stepper.setCurrentPosition(0);
    DEC_stepper.setMaxSpeed(20000);
    DEC_stepper.setAcceleration(10000);
    DEC_stepper.setCurrentPosition(0);
    
    
}

/* loop */
void loop(){
    if(Serial3.available()){
        command = Serial3.readStringUntil('#');
        BlueHandler();
        Serial.println(command);    //for develop
        command = "";
    }
    RA_stepper.run();
    DEC_stepper.run();
}
