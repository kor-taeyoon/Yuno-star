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
