//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
#define ENA 6
#define EN1 7
#define EN2 3
#define EN3 4
#define EN4 2
#define ENB 5
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
int Distance = 0;                               
int Trigger_Pin = 8;                               
int Echo_Pin = 9;                                   

char toSend="1";
int car_Speed = 255;  //직 후 110~130 

//String return_id;
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
HUSKYLENS huskylens1; //HUSKYLENS green line >> SDA; blue line >> SCL
HUSKYLENS huskylens2;
//SoftwareSerial BTSerial(12,13); //Bluetooth HC-06 TX >> D12, RX >> D13
SoftwareSerial HuskySerial(12,13); //huskylens RX >> 16, TX >> 17
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    
    husky1_set();
    husky2_set();
    motor_set();
    sensor_set();
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void husky1_set() {
     Wire.begin();
             Serial.println("husky1 OK"); //I2C
        while (!huskylens1.begin(Wire)) {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(1500);
      }
     Serial.println("husky1 connected");
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void husky2_set() {
     HuskySerial.begin(9600);
             Serial.println("husky2 OK"); // UART
        while (!huskylens2.begin(HuskySerial)) {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>UART)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(1500);
        }
     Serial.println("husky2 connected");
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void motor_set() {
    pinMode(ENA, OUTPUT);
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(EN3, OUTPUT);
    pinMode(EN4, OUTPUT);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void sensor_set() {
    pinMode(Trigger_Pin, OUTPUT);
    pinMode(Echo_Pin, INPUT); 
    delay(100);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void loop() {
    husky1_result();
    husky2_result();
    cal_distance();
    bt_send_value();
    bt_value_move();
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void husky1_result() {
    if (!huskylens1.request()) {
      Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
      delay(1500);
    }
    else if(!huskylens1.isLearned()) {
      Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
      delay(1500);
    }
    else if(!huskylens1.available()) {
      Serial.println(F("No block appears on the screen!"));
      delay(1500);
    }
    else
    {
        Serial.println(F("###########"));
        while (huskylens1.available())
        {
            HUSKYLENSResult result = huskylens1.read();
            if (result.command == COMMAND_RETURN_BLOCK){
                Serial.println(String()+F("ID=")+result.ID);
                delay(1500);
            }
            else {
                Serial.println("Object unknown!");
                delay(1500);
            }
        }    
    }  
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void husky2_result() {
    if (!huskylens2.request()) {
      Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
      delay(1500);
    }
    else if(!huskylens2.isLearned()) {
      Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
      delay(1500);
    }
    else if(!huskylens2.available()) {
      Serial.println(F("No block appears on the screen!"));
      delay(1500);
    }
    else
    {
        Serial.println(F("###########"));
        while (huskylens2.available())
        {
            HUSKYLENSResult result = huskylens2.read();
            if (result.command == COMMAND_RETURN_BLOCK){
                Serial.println(String()+F("ID=")+result.ID);
                delay(1500);
            }
            else {
                Serial.println("Object unknown!");
                delay(1500);
            }
        }    
    }  
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void cal_distance() {
    digitalWrite(Trigger_Pin, LOW);
    digitalWrite(Echo_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigger_Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger_Pin, LOW);
    
    Distance = pulseIn(Echo_Pin, HIGH) / 29.0 / 2.0;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void bt_send_value() {
    if(Serial1.available()) {
      toSend = (char)Serial1.read();
      Serial.println(toSend);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void bt_value_move() {
    if (toSend == '1') {  // Stop
      car_stop();
    }

else if (toSend == '2') { // Forward
      car_forward();
    }

else if (toSend == '3') { // Backward
      car_backward();
    }
else if (toSend == '4') { //
  
    }
else if (toSend == '5') { //
  
    }
else if (toSend == '6') { //
  
    }
else if (toSend == '7') { //
  
    }   
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void car_forward() {
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, car_Speed);

    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, car_Speed); 
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void car_backward() {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, car_Speed);

    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, car_Speed);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//
void car_stop() {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------//