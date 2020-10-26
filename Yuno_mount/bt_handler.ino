void bt_handler(){
    
    /* coordinate update */
    if ( command == ":GR" ) {
        char LX[10];
        sprintf(LX, "%02d:%02d:%02d#", (int)(ra_pos/3600), (int)((ra_pos%3600)/60), (int)(ra_pos%60));
        Serial3.write(LX);
        Serial.println(ra_pos);
    }
    else if ( command == ":GD" ) {
        char LX[11];
        sprintf(LX, "%c%02d*%02d:%02d#", dec_sign, (int)(dec_pos/3600), int((dec_pos%3600)/60), (int)(dec_pos%60));
        Serial3.write(LX);
        Serial.println(dec_pos);
    }


    /* available test */
    else if( command.startsWith(":Sr") ){
        temp = command.substring(3, 5);
        ra_pos = temp.toInt()*3600;
        temp = command.substring(6, 8);
        ra_pos += temp.toInt()*60;
        temp = command.substring(9, 11);
        ra_pos += temp.toInt();
        
        Serial3.write("1");//ra coordinate available
    }
    else if( command.startsWith(":Sd") ){
        temp = command.substring(4, 6);
        dec_pos = temp.toInt()*3600;
        temp = command.substring(7, 9);
        dec_pos += temp.toInt()*60;
        temp = command.substring(10, 12);
        dec_pos += temp.toInt();
        
        if( command[3] == '+' ) dec_sign = '+';
        else dec_sign = '-';
        
        Serial3.write("1");//dec coordinate available
    }
    
    
    /* sync */
    else if( (command == ":CM") ){
        Serial3.write("Coordinates  matched #");
        
        Serial.println("Master : Syncing");
    }
    
    
    /* slew to object */
    else if( (command==":MS") ){
        Serial3.write("0");
    }


    /* exception handling */
    else{
    
    }
}
