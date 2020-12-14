#include "SoftwareSerial.h"
#include <MsTimer2.h>


#define ENA 6
#define EN1 7
#define EN2 3
#define EN3 4
#define EN4 2
#define ENB 5

///////////////////////////////////////////////////////////////////////////////////////////////////
#define CAR_DIR_FW 0//0
#define CAR_DIR_BK 4//1
#define CAR_DIR_LF 1//2
#define CAR_DIR_RF 2//3
#define CAR_DIR_ST 3//4

///////////////////////////////////////////////////////////////////////////////////////////////////
#define FW 42
#define BK 41
#define LF 45
#define RF 44
///////////////////////////////////////////////////////////////////////////////////////////////////
int g_carDirection =CAR_DIR_ST;

bool state = LOW;

  unsigned long previousMillis = 0; // LED의 상태가 업데이트된 시간을 기록할 변수  
    
  const long forward_interval =850;    //전진 유지시간(전진 속도조절)  


void car_forward(bool state){
    //static boolean output = HIGH;
    digitalWrite(FW, state);
    //state!=state;    
}

void car_backward()
  {
  digitalWrite(BK, HIGH);
  }

  void car_left()
  {
  digitalWrite(LF, HIGH);
  }

  void car_right()
  {
  digitalWrite(RF, HIGH); 
  }

 void car_stop()
 {
  digitalWrite(FW, LOW); 
  digitalWrite(BK,LOW);
 }


void init_car_controller_board()
{  
  pinMode(FW, OUTPUT); //전진
  pinMode(BK, OUTPUT); //후진
  pinMode(LF, OUTPUT); //좌
  pinMode(RF, OUTPUT); //우

}

void new_move(){
  
}

 ///////////////////////////////////////////////////////////////////////////////////////////////////


 void car_update(){
    if(g_carDirection==CAR_DIR_FW)
    {
      car_forward(state); 
    }
    else
    if(g_carDirection==CAR_DIR_BK)
    {
      car_backward(); 
    }
    else
    if(g_carDirection==CAR_DIR_LF)
    {
      car_left(); 
    }
    else
    if(g_carDirection==CAR_DIR_RF)
    {
      car_right(); 
    }
    else
    if(g_carDirection==CAR_DIR_ST)
    {
      car_stop(); 
    }
 }

  ///////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_car_controller_board();

  /*MsTimer2::set(1000,car_stop);
  MsTimer2::start();*/
  

}



void loop() {
    //현재 시간을 기록
    //car_forward(true);  
  unsigned long currentMillis = millis();  
     
  //지난번 LED의 상태를 변경한 후 경과시간이 interval시간보다 크다면  
  if(currentMillis - previousMillis >= forward_interva) {  
    //LED의 상태를 변경한 시간을 기록한다.  
    previousMillis = currentMillis;     
        
    if (state == LOW)//LED가 꺼진상태면  
      state = HIGH; //LED를 켜진 상태로 하고   
    else//LED가 켜진상태라면  
      state = LOW; //LED를 꺼진상태로 한다.  
    
    //ledState변수에 저장된 값으로 ledPin핀의 상태를 설정한다.  
    car_forward(state);   
}
}
