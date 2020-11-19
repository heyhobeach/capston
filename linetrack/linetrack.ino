void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValueA0 = digitalRead(A0);
  int sensorValueA1 = digitalRead(A1);
  int sensorValueA2 = digitalRead(A2);
  Serial.print("sensor 0 : ");
  Serial.print(sensorValueA0);
  Serial.print("sensor 1: ");
  Serial.print(sensorValueA1);
  Serial.print("sensor2 : ");
  Serial.println(sensorValueA2);
  delay(1000);
}
