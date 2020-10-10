unsigned long Period; 
String str = "";
long ra_pos = 3600;
long dec_pos = 36000;
char dec_sign = 0;
/*
    Name:       test_yuno_lx200.ino
    Created:	2020-09-23 오후 12:06:44
    Author:     Kimtaeyoon
*/
void setup(){
	Serial.begin(9600);
	
}

void loop(){ 
    while(!(str.startsWith("#:") && str.endsWith("#"))){
        if(Serial.available()){
            str.concat((char)Serial.read());
        }
    }	
		
	
    if ( str=="#:GR#") {
        char LX[10];
        sprintf(LX,"%02d:%02d:%02d#",ra_pos/3600,(ra_pos%3600)/60,ra_pos%60);
        Serial.write(LX); 
    }
	
    else if ( str=="#:GD#") {
        char LX[11], s_mark;
        if(dec_pos>=0) dec_sign='+';
        else dec_sign='-';
        sprintf(LX, "%c%02d*%02d:%02d#", s_mark,dec_pos/3600,(dec_pos%3600)/60,dec_pos%60);
        Serial.write(LX); 
    }
	
    else{
		
    }
	
    str = "";
}
