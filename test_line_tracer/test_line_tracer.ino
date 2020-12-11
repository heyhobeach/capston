//#define SENSOR_THRESHOLD 200


#define SENSOR_F_L B01
#define SENSOR_F_R B10

#define SENSOR_B_L B01
#define SENSOR_B_R B10

#define LT_MODULE_F0 22
#define LT_MODULE_F1 23
#define LT_MODULE_B0 24
#define LT_MODULE_B1 25



void init_line_tracer_modules()
{
  Serial.begin(9600);
  pinMode(LT_MODULE_F0, INPUT);//22
  pinMode(LT_MODULE_F1, INPUT);//23
  pinMode(LT_MODULE_B0, INPUT);//24
  pinMode(LT_MODULE_B1, INPUT);//25
  
}

void setup() {
  // put your setup code here, to run once:
  init_line_tracer_modules();
}

void loop() {
  /*Serial.print("Sensor1 ->"); 
  Serial.println(digitalRead(LT_MODULE_X0));
  Serial.print("Sensor2 ->"); 
  Serial.println(digitalRead(LT_MODULE_X1));*/
  int onLine1=((digitalRead(LT_MODULE_F0)==1)?SENSOR_F_L:0)|((digitalRead(LT_MODULE_F1)==1)?SENSOR_F_R:0);
  int onLine2=((digitalRead(LT_MODULE_B0)==1)?SENSOR_B_L:0)|((digitalRead(LT_MODULE_B1)==1)?SENSOR_B_R:0);
  Serial.print("onLine1->");
  Serial.println(onLine1);
  Serial.print("onLine2->");
  Serial.println(onLine2);
}
