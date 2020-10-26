void track(){
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));//for develop
    digitalWrite(PA12, HIGH);
    digitalWrite(PA12, LOW);
}

void guide(){
    if(digitalRead(PB6)){
        digitalWrite(PA12, HIGH);
        digitalWrite(PA12, LOW);
    }
    if(digitalRead(PB7)){
        digitalWrite(PA12, HIGH);
        digitalWrite(PA12, LOW);
    }
    if(digitalRead(PB8)){
        digitalWrite(PA12, HIGH);
        digitalWrite(PA12, LOW);
    }
    if(digitalRead(PB9)){
        digitalWrite(PA12, HIGH);
        digitalWrite(PA12, LOW);
    }
}

void flip(){
    
}

void change_micro(int dan){
    switch(dan){
    case 0:
        digitalWrite(PB4, LOW);
        digitalWrite(PB3, LOW);
        digitalWrite(PA15, LOW);
        digitalWrite(PA8, LOW);
        digitalWrite(PB15, LOW);
        digitalWrite(PB14, LOW);
        break;
    case 1:
        digitalWrite(PB4, HIGH);
        digitalWrite(PB3, LOW);
        digitalWrite(PA15, LOW);
        digitalWrite(PA8, HIGH);
        digitalWrite(PB15, LOW);
        digitalWrite(PB14, LOW);
        break;
    case 2:
        digitalWrite(PB4, LOW);
        digitalWrite(PB3, HIGH);
        digitalWrite(PA15, LOW);
        digitalWrite(PA8, LOW);
        digitalWrite(PB15, HIGH);
        digitalWrite(PB14, LOW);
        break;
    case 3:
        digitalWrite(PB4, HIGH);
        digitalWrite(PB3, HIGH);
        digitalWrite(PA15, LOW);
        digitalWrite(PA8, HIGH);
        digitalWrite(PB15, HIGH);
        digitalWrite(PB14, LOW);
        break;
    case 4:
        digitalWrite(PB4, LOW);
        digitalWrite(PB3, LOW);
        digitalWrite(PA15, HIGH);
        digitalWrite(PA8, LOW);
        digitalWrite(PB15, LOW);
        digitalWrite(PB14, HIGH);
        break;
    case 5:
        digitalWrite(PB4, HIGH);
        digitalWrite(PB3, LOW);
        digitalWrite(PA15, HIGH);
        digitalWrite(PA8, HIGH);
        digitalWrite(PB15, LOW);
        digitalWrite(PB14, HIGH);
        break;
    case 6:
        digitalWrite(PB4, LOW);
        digitalWrite(PB3, HIGH);
        digitalWrite(PA15, HIGH);
        digitalWrite(PA8, LOW);
        digitalWrite(PB15, HIGH);
        digitalWrite(PB14, HIGH);
        break;
    case 7:
        digitalWrite(PB4, HIGH);
        digitalWrite(PB3, HIGH);
        digitalWrite(PA15, HIGH);
        digitalWrite(PA8, HIGH);
        digitalWrite(PB15, HIGH);
        digitalWrite(PB14, HIGH);
        break;
    }
}