#define TRIGGER_PIN 12
#define ECHO_PIN 13 

#define ENA 6
#define EN1 7
#define EN2 3 

#define EN3 4
#define EN4 2
#define ENB 5

int distance;
int speed = 150;

void setup()
{
  //Serial.begin(9600);
  pinMode(TRIGGER_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
}
void loop()
{ 
  int return_cm;
  return_cm=checkDistance();
  move_cart(return_cm);
}

long microsecondsToInches(long microseconds)
{
  return microseconds/74/2; //초음파 걸린시간/74/2 -> 인치변환
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds/29/2; //초음파 걸린시간/74/2 -> cm변환
}

int checkDistance(){
    long duration, cm;
  digitalWrite(TRIGGER_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN,LOW);
  duration=pulseIn(ECHO_PIN,HIGH);
  cm=microsecondsToCentimeters(duration);
  delay(300);
  return cm;
}

void move_cart(int distance){
    if(distance>105) // 전진범위 
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, speed);
  delay(300);
  }
  else if(distance<65) // 후진범위
  {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, speed);

    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, speed);
    delay(300);
  }

else if(distance>80&&distance<100) // 정지범위
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, speed);

    digitalWrite(EN3, LOW);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, speed);
    delay(300);
}
}
