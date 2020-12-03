
void TrackingPulse(){
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));//for develop
    digitalWrite(PA12, HIGH); 
    digitalWrite(PA12, LOW);
}

void ra_MicroStepChanger(int dan){
    switch(dan){
        case 0:
            digitalWrite(PB4, LOW);
            digitalWrite(PB3, LOW);
            digitalWrite(PA15, LOW);
            break;
        case 1:
            digitalWrite(PB4, HIGH);
            digitalWrite(PB3, LOW);
            digitalWrite(PA15, LOW);
            break;
        case 2:
            digitalWrite(PB4, LOW);
            digitalWrite(PB3, HIGH);
            digitalWrite(PA15, LOW);
            break;
        case 3:
            digitalWrite(PB4, HIGH);
            digitalWrite(PB3, HIGH);
            digitalWrite(PA15, LOW);
            break;
        case 4:
            digitalWrite(PB4, LOW);
            digitalWrite(PB3, LOW);
            digitalWrite(PA15, HIGH);
            break;
        case 5:
            digitalWrite(PB4, HIGH);
            digitalWrite(PB3, LOW);
            digitalWrite(PA15, HIGH);
            break;
        case 6:
            digitalWrite(PB4, LOW);
            digitalWrite(PB3, HIGH);
            digitalWrite(PA15, HIGH);
            break;
        case 7:
            digitalWrite(PB4, HIGH);
            digitalWrite(PB3, HIGH);
            digitalWrite(PA15, HIGH);
            break;
    }
}

void dec_MicroStepChanger(int dan){
    switch(dan){
        case 0:
            digitalWrite(PA8, LOW);
            digitalWrite(PB15, LOW);
            digitalWrite(PB14, LOW);
            break;
        case 1:
            digitalWrite(PA8, HIGH);
            digitalWrite(PB15, LOW);
            digitalWrite(PB14, LOW);
            break;
        case 2:
            digitalWrite(PA8, LOW);
            digitalWrite(PB15, HIGH);
            digitalWrite(PB14, LOW);
            break;
        case 3:
            digitalWrite(PA8, HIGH);
            digitalWrite(PB15, HIGH);
            digitalWrite(PB14, LOW);
            break;
        case 4:
            digitalWrite(PA8, LOW);
            digitalWrite(PB15, LOW);
            digitalWrite(PB14, HIGH);
            break;
        case 5:
            digitalWrite(PA8, HIGH);
            digitalWrite(PB15, LOW);
            digitalWrite(PB14, HIGH);
            break;
        case 6:
            digitalWrite(PA8, LOW);
            digitalWrite(PB15, HIGH);
            digitalWrite(PB14, HIGH);
            break;
        case 7:
            digitalWrite(PA8, HIGH);
            digitalWrite(PB15, HIGH);
            digitalWrite(PB14, HIGH);
            break;
    }
}

long ra_CorToPos(double Cor){
    return (long)(((double)Cor*100.0)/27.0);
}

long ra_PosToCor(double Pos){
    return (long)(((double)Pos*27.0)/100.0);
}

long dec_CorToPos(double Cor){
    return (long)(((double)Cor*40.0)/81.0);
}

long dec_PosToCor(double Pos){
    return (long)(((double)Pos*81.0)/40.0);
}
