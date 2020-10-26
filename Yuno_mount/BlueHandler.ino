
void BlueHandler(){
    
    /* coordinate update */
    if ( command == ":GR" ) {
        char LX[10];
        sprintf(LX, "%02d:%02d:%02d#", (int)(abs(RA_stepper.currentPosition())/3600), (int)((abs(RA_stepper.currentPosition())%3600)/60), (int)(abs(RA_stepper.currentPosition())%60));
        Serial3.write(LX);
        Serial.println(RA_stepper.currentPosition());
    }
    else if ( command == ":GD" ) {
        char LX[11];
        if( DEC_stepper.currentPosition()>=0 ){
            sprintf(LX, "+%02d*%02d:%02d#", (int)(abs(DEC_stepper.currentPosition())/3600), (int)((abs(DEC_stepper.currentPosition())%3600)/60), (int)(abs(DEC_stepper.currentPosition())%60));
        }
        else{
            sprintf(LX, "-%02d*%02d:%02d#", (int)(abs(DEC_stepper.currentPosition())/3600), (int)((abs(DEC_stepper.currentPosition())%3600)/60), (int)(abs(DEC_stepper.currentPosition())%60));
        }
        Serial3.write(LX);
        Serial.println(DEC_stepper.currentPosition());
    }


    /* available test */
    else if( command.startsWith(":Sr") ){   //RA coordinate test
        
        temp_string = command.substring(3, 5);
        ra_pos_target = temp_string.toInt()*3600;
        temp_string = command.substring(6, 8);
        ra_pos_target += temp_string.toInt()*60;
        temp_string = command.substring(9, 11);
        ra_pos_target += temp_string.toInt();
        
        Serial3.write("1");//available
    }
    else if( command.startsWith(":Sd") ){   //DEC coordinate test
        if( command[3] == '+' ){
            temp_string = command.substring(4, 6);
            dec_pos_target = temp_string.toInt()*3600;
            temp_string = command.substring(7, 9);
            dec_pos_target += temp_string.toInt()*60;
            temp_string = command.substring(10, 12);
            dec_pos_target += temp_string.toInt();
        }
        else{
            temp_string = command.substring(4, 6);
            dec_pos_target = -temp_string.toInt()*3600;
            temp_string = command.substring(7, 9);
            dec_pos_target -= temp_string.toInt()*60;
            temp_string = command.substring(10, 12);
            dec_pos_target -= temp_string.toInt();
        }
        
        Serial3.write("1");//available
    }
    
    
    /* sync */
    else if( (command == ":CM") ){
        RA_stepper.setCurrentPosition(ra_pos_target);
        DEC_stepper.setCurrentPosition(dec_pos_target);
        
        Serial3.write("Coordinates  matched #");
        
        Serial.println("Master : Syncing");
    }
    
    
    /* slew to object */
    else if( (command==":MS") ){
        Serial3.write("0");//possible
        long RA_togo = 0, DEC_togo = 0;
        
        /* RA */
        RA_togo = ra_pos_target - RA_stepper.currentPosition();
        RA_stepper.move(RA_togo);
        
        /* DEC */
        DEC_togo = dec_pos_target - DEC_stepper.currentPosition();
        DEC_stepper.move(DEC_togo);
        
        //problem1. RA 24 to 0?
        
        
    }


    /* exception handling */
    else{
        
    }
}
