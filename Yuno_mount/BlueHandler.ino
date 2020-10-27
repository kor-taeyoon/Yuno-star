
void BlueHandler(){
    
    /* coordinate update */
    if ( command == ":GR" ) {
        char LX[10];
        sprintf(LX, "%02d:%02d:%02d#", (int)(ra_pos/3600), (int)((ra_pos%3600)/60), (int)(ra_pos%60));
        Serial3.write(LX);
        Serial.println(ra_pos);
    }
    else if ( command == ":GD" ) {
        char LX[11];
        if( dec_pos >=0 ){
            sprintf(LX, "+%02d*%02d:%02d#", (int)(abs(dec_pos)/3600), (int)((abs(dec_pos)%3600)/60), (int)(abs(dec_pos)%60));
        }
        else{
            sprintf(LX, "-%02d*%02d:%02d#", (int)(abs(dec_pos)/3600), (int)((abs(dec_pos)%3600)/60), (int)(abs(dec_pos)%60));
        }
        Serial3.write(LX);
        Serial.println(dec_pos);
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
        Serial.println("Master : synced");
    }
    
    
    /* slew to object */
    else if( (command==":MS") ){
        Serial3.write("0");//possible
        long RA_togo = 0, DEC_togo = 0;
        
        /* calculate how far to go */
        
        
        /* RA */
        RA_togo = ra_pos_target - ra_pos;
        if( abs(RA_togo) >= 43200 ){
            if( RA_togo >= 0 ) RA_togo -= 86400;
            else RA_togo += 86400;
        }
        RA_stepper.move(RA_togo);
        
        /* DEC */
        DEC_togo = dec_pos_target - dec_pos;
        DEC_stepper.move(DEC_togo);
    }


    /* exception handling */
    else{
        
    }
}
