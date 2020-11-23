#define CAR_DIR_FW 0
#define CAR_DIR_BK 1
#define CAR_DIR_LF 2
#define CAR_DIR_RF 3
#define CAR_DIR_ST 4

int g_carDirection =CAR_DIR_ST;

int g_carSpeed=100;

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
  analogWrite(ENA, g_carSpeed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, g_carSpeed);
  
  }

  void car_right()
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, g_carSpeed);

  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, g_carSpeed);
  
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

void It_mode_update()
{
  int ll=It_isLeft();
  int rr=It_isRight();
  if(ll&&rr)
  {
    g_carDirection=CAR_DIR_FW;
  }
  else
  if(!ll&&!rr)
  {
    g_carDirection=CAR_DIR_ST;
  }
  else
  if(ll&&!rr)
  {
    g_carDirection=CAR_DIR_LF;
  }
  else
  if(rr&&!ll)
  {
    g_carDirection=CAR_DIR_RF;
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
