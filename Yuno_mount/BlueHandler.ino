
void BlueHandler(){    
    /* coordinate update */
    if ( command == ":GR" ) {
        char LX[10];
        sprintf(LX, "%02d:%02d:%02d#", (int)(ra_pos/3600), (int)((ra_pos%3600)/60), (int)(ra_pos%60));
        Serial3.write(LX);
        //Serial.println(ra_pos);
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
        //Serial.println(dec_pos);
    }
    




    /* Manual Move */
    else if( (command==":Me") ){
        // Go East activate
        RA_stepper.moveTo(1000000);
    }
    else if( (command==":Mw") ){
        // Go West activate
        RA_stepper.moveTo(-1000000);
    }
    else if( (command==":Ms") ){
        // Go South activate
        DEC_stepper.moveTo(-1000000);
    }
    else if( (command==":Mn") ) {
        // Go North activate
        DEC_stepper.moveTo(1000000);
    }
    
    else if( (command==":Qe") ){
        // Stop manual move
        RA_stepper.stop();
    }
    else if( (command==":Qw") ){
        // Stop manual move
        RA_stepper.stop();
    }
    else if( (command==":Qs") ){
        // Stop manual move
        DEC_stepper.stop();
    }
    else if( (command==":Qn") ){
        // Stop manual move
        DEC_stepper.stop();
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
        RA_stepper.setCurrentPosition(ra_CorToPos(ra_pos_target));
        DEC_stepper.setCurrentPosition(dec_CorToPos(dec_pos_target));
        
        Serial3.write("N/A#");
        Serial.println("Master : synced");
    }
    
    
    
    
    
    /* slew to object */
    else if( (command==":MS") ){
        Serial3.write("0"); // reply that target is possible
        long RA_togo = 0, DEC_togo = 0;
        
        /* RA */
        RA_togo = ra_pos_target - ra_pos;
        if( abs(RA_togo) >= 43200 ){
            if( RA_togo >= 0 ) RA_togo -= 86400;
            else RA_togo += 86400;
        }
        RA_stepper.move(ra_CorToPos(RA_togo));
        
        /* DEC */
        DEC_togo = dec_pos_target - dec_pos;
        DEC_stepper.move(dec_CorToPos(DEC_togo));
    }


    /* exception handling */
    else{
        
    }
}
