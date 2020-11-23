int direction = 1;
int speed = 50;

#define ENA 6
#define EN1 7
#define EN2 3 

#define EN3 4
#define EN4 2
#define ENB 5

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
}
void loop()
{
  if(direction == 1)
 {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, speed);
  }
  else if(direction == 4)
  {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, speed);

    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, speed);
  }

else if(direction == 0)
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
}
