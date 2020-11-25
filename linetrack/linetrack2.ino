#define CAR_DIR_FW 0
#define CAR_DIR_BK 1
#define CAR_DIR_LF 2
#define CAR_DIR_RF 3
#define CAR_DIR_ST 4

#define TRIGGER_PIN1 8
#define ECHO_PIN1 9

int g_carDirection =CAR_DIR_ST;

int g_carSpeed=130;
int t_carSpeed=230;//회전속도

#define ENA 6
#define EN1 7
#define EN2 3

#define EN3 4
#define EN4 2
#define ENB 5


void init_car_controller_board()
{  
  pinMode(ENA, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  pinMode(TRIGGER_PIN1,OUTPUT);
  pinMode(ECHO_PIN1,INPUT);
}
void car_forward()
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, g_carSpeed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, g_carSpeed);
  
  }

void car_backward()
 {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, g_carSpeed);

  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, g_carSpeed);
  
  }

  void car_left()
 {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, t_carSpeed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, t_carSpeed);
  
  }

  void car_right()
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, t_carSpeed);

  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, t_carSpeed);
  
  }

 void car_stop(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  }

  void car_update(){
    if(g_carDirection==CAR_DIR_FW)
    {
      car_forward(); 
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

void print_car_info()
{
  Serial.println("direction value"+ g_carDirection);
  Serial.println("speed pwm value" + g_carSpeed);
}

#define LT_MODULE_X0 A0 // 흰색
#define LT_MODULE_X1 A1 //파란색

void init_line_tracer_modules()
{
  pinMode(LT_MODULE_X0, INPUT);
  pinMode(LT_MODULE_X1, INPUT);
}

bool It_isLeft()
{
  int ret = digitalRead(LT_MODULE_X1); //파란색 A1
  return ret==1? true : false;
}

/*bool It_isForward()
{
  int ret1 = digitalRead(LT_MODULE_X0);
  int ret2 = digitalRead(LT_MODULE_X1);
  return ret1==1? true : false;
  return ret2==1? true : false;
}*/

bool It_isRight()
{
  int ret = digitalRead(LT_MODULE_X0); //흰색 A0
  return ret==1? true : false;
}


long microsecondsToInches(long microseconds)
{
  return microseconds/74/2; //초음파 걸린시간/74/2 -> 인치변환
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds/29/2; //초음파 걸린시간/29/2 -> cm변환
}


int checkDistance1(){
    long duration, cm;
  digitalWrite(TRIGGER_PIN1,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN1,LOW);
  duration=pulseIn(ECHO_PIN1,HIGH);
  cm=microsecondsToCentimeters(duration);
  //delay(300);
  return cm;
}

void It_mode_update()
{
  int return_cm1;
  return_cm1=checkDistance1();
  int ll=It_isLeft();
  int rr=It_isRight();
  Serial.print(return_cm1);
  if(return_cm1>20&&ll&&rr)
  {
    g_carDirection=CAR_DIR_FW;
  }
 /* else
  if(return_cm0>=30)
  {
    g_carDirection=CAR_DIR_ST;
  }
  else
  if(return_cm2>=30)
  {
    g_carDirection=CAR_DIR_ST;
  }
 */
  else
  if(return_cm1<10||!ll&&!rr)
  {
    g_carDirection=CAR_DIR_ST;
  }
  else
  if(ll&&!rr)
  {
    g_carDirection=CAR_DIR_LF;
    delay(30);
  }
  else
  if(rr&&!ll)
  {
    g_carDirection=CAR_DIR_RF;
    delay(30);
  }
  
  
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_car_controller_board();
  print_car_info();
}

void loop() {
  // put your main code here, to run repeatedly:
  car_update();
  It_mode_update();
}
