unsigned long Period; 
String str = "";
void setup() {
    Serial.begin(9600); 
    Serial2.begin(9600);    // 4번핀에서 펄스 발생을 위해 핀모드 셋팅

    Period = 21541 ;         // 16 비트 타이머니까 괄호 안의 값의 단위는 마이크로초입니다. 즉 1000000 일때 1초 주기로 타이머가 실행된답니다.
                              // 하루 항성일주는 86164 초입니다. 마이크로초로 바꾸자면 86164 x 1000000 마이크로초
                              // 만일 적도의의 총감속비가 마이크로스텝 포함하여 4,000,000 라고 한다면 적경축이 1 바퀴 돌기위해 스텝 모터 드라이버에 4,000,000 번의 펄스신호가 전달되어야 합니다.
                              // 펄스간 주기는  86164 x 1000000 / 4000000 = 21541 마이크로초라고 계산됩니다. 
}

void loop() {
    char c; 
    bool isColon=false;   // ':' 콜론부터 문자를 읽기위한 변수
    
    while( Serial2.available() ){
        c=Serial2.read();
        if(c==':') isColon=true;
        if( isColon && c!=' ' && c!='\n' && c!='\r' ) str.concat(c);
        delay(10);
        if(c=='#') break;
    }

    
    char STR[30]={0}; 
    str.toCharArray(STR,str.length()+1);

    Serial.print(str);
    if ( str==":GR#") {
        char LX[10];
        long VAL = 3600;
        sprintf(LX,"%02d:%02d:%02d#",VAL/3600,(VAL%3600)/60,VAL%60);
        
        Serial.print(LX); 
        Serial2.print(LX);
    }      // VAL 은 적경위치인데 단위가 시간입니다. 제가 임의의 값 3600 으로 했어요.. 한바퀴에 86400 이니 1시입니다.
    else if ( str==":GD#") {
        char LX[11], s_mark;
        long VAL = 36000;
        if(VAL>=0) s_mark='+';
        else s_mark='-';
        sprintf(LX, "%c%02d*%02d:%02d#", s_mark,VAL/3600,(VAL%3600)/60,VAL%60);
        
        Serial.print(LX); 
        Serial2.print(LX);
    } // 여기서 VAL 은 적위... 80도로 했어요
    str = "";           
}
