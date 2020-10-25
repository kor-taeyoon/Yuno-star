
/*
    Name:       test_yuno_lx200.ino
    Created:	2020-09-23 오후 12:06:44
    Author:     Kimtaeyoon
*/

unsigned long period; 
String str = "";
long ra_pos = 3600;
long dec_pos = 36000;
char dec_sign = 0;

void setup(){
	pinMode(PC13, OUTPUT);
	digitalWrite(PC13, LOW);
	
    
    
    Serial.begin(9600);
    Serial3.begin(38400);
}

void loop(){ 
	if(Serial3.available()){
        str = Serial3.readStringUntil('#');
        //Serial.println(str);    for develop
    }
    
    
    
    /************************************************************************/
    /*                              1st                                     */
    /************************************************************************/
    if ( str==":GR" ) {
        char LX[10];
        sprintf(LX, "%02d:%02d:%02d#", ++ra_pos/3600, (ra_pos%3600)/60, ra_pos%60);
        Serial3.write(LX); 
    }
    else if ( str==":GD" ) {
        char LX[11];
        if(dec_pos>=0) dec_sign='+';
        else dec_sign='-';
        sprintf(LX, "%c%02d*%02d:%02d#", dec_sign, dec_pos/3600, (dec_pos%3600)/60, dec_pos%60);
        Serial3.write(LX); 
    }
    
    
     
    /************************************************************************/
    /*                              2nd                                     */
    /************************************************************************/
    else if( str.indexOf("Sr")>0 ){
        Serial3.write("1");
    }
    else if( str.indexOf("Sd")>0 ){
        Serial3.write("1");
    }
    
    

    /************************************************************************/
    /*                              last                                    */
    /************************************************************************/
    else if( (str==":CM") || (str==":CMR") ){
        Serial3.write("Coordinates  matched #");
        ra_pos+=10;
        dec_pos+=50;
        Serial.println("Master : Syncing");
    }
    else if( (str==":MS") ){
        Serial3.write("0");
        ra_pos+=10;
        dec_pos+=50;
        Serial.println("Master : slewing");
    }
    
    
    
    else{
        
    }
    str = "";
}
