//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 엔진모드 
#define CAR_DIR_FW 0//0
#define CAR_DIR_BK 4//1
#define CAR_DIR_ST 3//4
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 전면 초음파
#define TRIGGER_PIN_1 26
#define ECHO_PIN_1 27
#define TRIGGER_PIN_2 28
#define ECHO_PIN_2 29
#define TRIGGER_PIN_3 30
#define ECHO_PIN_3 31

// 후면 초음파
#define TRIGGER_PIN_4 32
#define ECHO_PIN_4 33
#define TRIGGER_PIN_5 34
#define ECHO_PIN_5 35
#define TRIGGER_PIN_6 36
#define ECHO_PIN_6 37
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 모터 드라이브
#define FW 42
#define BK 41
#define LF 45
#define RF 44
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
//카트 초기 상태 
int g_carDirection =CAR_DIR_ST;                                                                 
char toSend="1";
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
//허스키렌즈 통신
HUSKYLENS huskylens1; //HUSKYLENS I2C : green line >> SDA; blue line >> SCL // 허스키렌즈 전면?
HUSKYLENS huskylens2; //HUSKYLENS UART : RX >> D12, TX >> D13 // 허스키렌즈 측면?
SoftwareSerial HuskySerial(12,13); 

//허스키 반환 ID값
int husky_1_return_id = 0;
int husky_2_return_id = 0;
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 엔진 시간상태에 따른 속도조절
bool state = LOW; // 엔진꺼짐 초기화
unsigned long previousMillis = 0; // 카트의 상태가 업데이트된 시간을 기록할 변수  
long forward_interval = 2000;  //전진 유지시간(전진 속도조절)
long backward_interval = 2000; //후진 유지시간(전진 속도조절)    
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
//초음파 거리 초기화
int return_cm1 = 0;
int return_cm2 = 0;
int return_cm3 = 0;
int return_cm4 = 0;
int return_cm5 = 0;
int return_cm6 = 0;

//초음파 거리 cm변환 및 반환
long microsecondsToCentimeters(long microseconds)
{
  return microseconds/29/2;
}

// 각각의 초음파 시간측정 및 거리값
int checkDistance_1(){
long duration, cm;
  digitalWrite(TRIGGER_PIN_1,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1,LOW);
  duration=pulseIn(ECHO_PIN_1,HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}
int checkDistance_2(){
long duration, cm;
  digitalWrite(TRIGGER_PIN_2,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2,LOW);
  duration=pulseIn(ECHO_PIN_2,HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}
int checkDistance_3(){
long duration, cm;
  digitalWrite(TRIGGER_PIN_3,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_3,LOW);
  duration=pulseIn(ECHO_PIN_3,HIGH);
  cm=microsecondsToCentimeters(duration);
  return cm;
}
int checkDistance_4(){
long duration, cm;
  digitalWrite(TRIGGER_PIN_4,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_4,LOW);
  duration=pulseIn(ECHO_PIN_4,HIGH);
  cm=microsecondsToCentimeters(duration);
  return cm;
}
int checkDistance_5(){
long duration, cm;
  digitalWrite(TRIGGER_PIN_5,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_5,LOW);
  duration=pulseIn(ECHO_PIN_5,HIGH);
  cm=microsecondsToCentimeters(duration);
  return cm;
}
int checkDistance_6(){
long duration, cm;
  digitalWrite(TRIGGER_PIN_6,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_6,LOW);
  duration=pulseIn(ECHO_PIN_6,HIGH);
  cm=microsecondsToCentimeters(duration);
  return cm;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★//
//------------------------------------------------------------------------------------------------------------------------------------------//
void setup() {
    Serial.begin(9600); //허스키렌즈 측면 통신 
    Serial1.begin(9600); // 블루투스 통신
    
    husky1_set();
    husky2_set();
    set_engine();
    set_dis_sensor();
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 허스키렌즈 전면 I2C통신 연결
void husky1_set() {
     Wire.begin();
             Serial.println("HuskyLens_1 : Connection succeeded");
        while (!huskylens1.begin(Wire)) {
        Serial.println(F("HuskyLens_1 : Connection failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck Arduino or Board."));
      }
     Serial.println("husky1 connected");
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 허스키렌즈 측면? UART통신 연결
void husky2_set() {
     HuskySerial.begin(9600);
             Serial.println("HuskyLens_2 : Connection succeeded");
        while (!huskylens2.begin(HuskySerial)) {
        Serial.println(F("HuskyLens_2 : Connection failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>UART)"));
        Serial.println(F("2.Please recheck the Arduino or Board."));
        }
     Serial.println("husky2 connected");
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void set_engine() {  
    pinMode(FW, OUTPUT); //전진
    pinMode(BK, OUTPUT); //후진
} 
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void set_dis_sensor() {
    pinMode(TRIGGER_PIN_1,OUTPUT);
    pinMode(ECHO_PIN_1,INPUT);
    pinMode(TRIGGER_PIN_2,OUTPUT);
    pinMode(ECHO_PIN_2,INPUT);
    pinMode(TRIGGER_PIN_3,OUTPUT);
    pinMode(ECHO_PIN_3,INPUT);

    pinMode(TRIGGER_PIN_4,OUTPUT);
    pinMode(ECHO_PIN_4,INPUT);
    pinMode(TRIGGER_PIN_5,OUTPUT);
    pinMode(ECHO_PIN_5,INPUT);
    pinMode(TRIGGER_PIN_6,OUTPUT);
    pinMode(ECHO_PIN_6,INPUT);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★//
//------------------------------------------------------------------------------------------------------------------------------------------//
void loop() {
    husky1_result();
    husky2_result();

    bt_send_value();
    bt_manual_move();

    follow_cart_move();
    call_cart_move();
    //return_cart_move();

}
//------------------------------------------------------------------------------------------------------------------------------------------//
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 허스키렌즈 전면? 상태 및 인식된 ID값
void husky1_result() {
    if (!huskylens1.request()) {
      Serial.println(F("HuskyLens_1 : Fail to request data from HUSKYLENS, recheck the connection!"));
    }
    else if(!huskylens1.isLearned()) {
      Serial.println(F("HuskyLens_1 : Nothing learned, press learn button on HUSKYLENS to learn one!"));
    }
    else if(!huskylens1.available()) {
      Serial.println(F("HuskyLens_1 : No block appears on the screen!"));
    }
    else
    {
        Serial.println(F("#-#-#-# HuskyLens_1 : recognized id value #-#-#-#"));
        while (huskylens1.available())
        {
            Serial.println("huskyready");
            HUSKYLENSResult result = huskylens1.read();
            if (result.command == COMMAND_RETURN_BLOCK){
                //Serial.println(String() + F("ID=") + result.ID);
                String s = (String() + result.ID);
                husky_1_return_id = s.toInt();
                Serial.println(husky_1_return_id);
            }
            else {
                Serial.println("HuskyLens_1 : Object unknown!");
            }
        }    
    }  
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 허스키렌즈 측면? 상태 및 인식된 ID값
void husky2_result() {
    if (!huskylens2.request()) {
      Serial.println(F("HuskyLens_2 : Fail to request data from HUSKYLENS, recheck the connection!"));
     }
    else if(!huskylens2.isLearned()) {
      Serial.println(F("HuskyLens_2 : Nothing learned, press learn button on HUSKYLENS to learn one!"));
     }
    else if(!huskylens2.available()) {
      Serial.println(F("HuskyLens_2 : No block appears on the screen!"));
     }
    else
    {
        Serial.println(F("#-#-#-# HuskyLens_2 : recognized id value #-#-#-#"));
        while (huskylens2.available())
        {
            //Serial.println("huskyready");
            HUSKYLENSResult result = huskylens2.read();
            if (result.command == COMMAND_RETURN_BLOCK){
                //Serial.println(String() + F("ID=") + result.ID);
                String s = (String() + result.ID);
                husky_2_return_id = s.toInt();
                Serial.println(husky_2_return_id);
            }
            else {
                Serial.println("HuskyLens_2 : Object unknown!");
            }
        }    
    }  
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
//블루투스 값 전송 및 읽기
void bt_send_value() {
    if(Serial1.available()) {
    
      toSend = (char)Serial1.read();
      Serial.println(toSend);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void bt_manual_move()
{
  Serial.println("Send is: " + toSend);
    if (toSend == '1') // 정지
    {  
      car_stop();
    }
    else if (toSend == '2') // 전진 
    { 
      car_forward();
    }
    else if (toSend == '3') // 후진
    { 
      car_backward();
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void no_delay_forward(){
  Serial.println("go");
  digitalWrite(FW,HIGH);
}
// 전진
void car_forward()  {
     //static boolean output = HIGH;
     Serial.print("go");
     digitalWrite(FW, state);
     unsigned long currentMillis = millis();  
     
     //지난번 LED의 상태를 변경한 후 경과시간이 interval시간보다 크다면  
     if(currentMillis - previousMillis >= forward_interval) {  
     //LED의 상태를 변경한 시간을 기록한다.  
     previousMillis = currentMillis;     
     }  
     if (state == LOW){//LED가 꺼진상태면 
      forward_interval=800; 
      state = HIGH;
     }//LED를 켜진 상태로 하고   
     else{//LED가 켜진상태라면
      forward_interval= 3000;   
      state = LOW; //LED를 꺼진상태로 한다.
     }
     husky_1_return_id = 0;     
     //ledState변수에 저장된 값으로 ledPin핀의 상태를 설정한다.     
}
// 후진
void car_backward() {
    digitalWrite(BK, HIGH);
    /*
    //Serial.println("gogogo");
     //static boolean output = HIGH;
     digitalWrite(BK, state);
     unsigned long currentMillis = millis();  
     
     //지난번 LED의 상태를 변경한 후 경과시간이 interval시간보다 크다면  
     if(currentMillis - previousMillis >= backward_interval) {  
     //LED의 상태를 변경한 시간을 기록한다.  
     previousMillis = currentMillis;     
     }  
     if (state == LOW){//LED가 꺼진상태면  
      state = HIGH;
     }//LED를 켜진 상태로 하고   
     else{//LED가 켜진상태라면  
      state = LOW; //LED를 꺼진상태로 한다.
     }
     husky_1_return_id = 0;     
     //ledState변수에 저장된 값으로 ledPin핀의 상태를 설정한다.
     */  
}


// 정지
void car_stop() {
    digitalWrite(FW, LOW); 
    digitalWrite(BK, LOW);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
// 거리값 대입
void follow_cart_move() { 
    return_cm1 = checkDistance_1();
    return_cm2 = checkDistance_2(); // 전면(팔로우)
    return_cm3 = checkDistance_3();
    return_cm4 = checkDistance_4();
    return_cm5 = checkDistance_5();
    return_cm6 = checkDistance_6();

    Serial.println(return_cm2);
//허스키렌즈에 ID값 학습되지 않은 태그 인식 시 정지(팔로우)
    if(return_cm2 <= 40 || husky_1_return_id == 0 || return_cm2 >=70)
    {
     car_stop();
    }
//허스키렌즈에 1번 ID값 태그 인식 시 전진(팔로우)
    else if(return_cm2 <= 60 && return_cm2 >= 50 && husky_1_return_id == 1) 
    {
     //car_forward();
     no_delay_forward();
     Serial.println("Go");
    }
//허스키렌즈에 2번 ID값 태그 인식 시 전진(팔로우)   
    else if(return_cm2 <= 60 && return_cm2 >= 50 && husky_1_return_id == 2) 
    {
     car_backward();
     Serial.println("bk");
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void call_cart_move() {
    if(toSend == '5')
    {
      no_delay_forward();
      if(husky_2_return_id == 1 && toSend == '5') // 첫 번째 좌석
      {
        car_stop();
        toSend = '1';
      }
      
    }
    else if(toSend == '6')
    {
      no_delay_forward();
      if(husky_2_return_id == 2 && toSend == '6') // 두 번째 좌석
      {
        car_stop();
        toSend = '1';
      }
    }
    else if(toSend == '7')
    {
      car_backward();
      if(husky_2_return_id == 3 && toSend == '7') // 복귀
      {
        car_stop();
        toSend = '1';
      }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
/*void return_cart_move() {
  if(toSend == '7')
    {
      car_backward();
      if(husky_2_return_id == 3 && toSend == '7') // 첫 번째 좌석
      {
        car_stop();
        toSend = '0';
      }
    }
}*/
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
