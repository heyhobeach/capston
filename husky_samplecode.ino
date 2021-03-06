#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);

void setup() {
    huskyConnect();
}

void loop() {
    huskyActive();
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("ID=")+result.ID);
        delay(300);
    }
    else{
        Serial.println("Object unknown!");
        delay(300);
    }
}

void checkId(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
      if(result.ID==1){
          Serial.println("1");
        }
    }
    else{
        Serial.println("Object unknown!");
        delay(300);
    }
}

void make_get(int num){
      HUSKYLENSResult result1 = huskylens.get(num);
      Serial.println(result1.ID);
      if (result1.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("ID=")+result1.ID+("Get Func"));
        delay(300);
    }
}
void huskyConnect() {
  Serial.begin(9600);
  mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void huskyActive() {
  if (!huskylens.request()) {
      Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
      delay(3000);   
    }
    else if(!huskylens.isLearned()) {
      Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
      delay(3000);
    }

    else if(!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      delay(3000);
    }

    else
    {
        Serial.println(F("######"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            checkId(result);
            make_get(1);
            printResult(result);
        }
        delay(1000);    
    }
}
