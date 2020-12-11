#define SENSOR_THRESHOLD 200
#define SENSOR_F_L B01
#define SENSOR_F_R B10

#define LT_MODULE_X0 22
#define LT_MODULE_X1 23

void init_line_tracer_modules()
{
  Serial.begin(9600);
  pinMode(LT_MODULE_X0, INPUT);//a0
  pinMode(LT_MODULE_X1, INPUT);//a1
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
  int onLine1=((digitalRead(LT_MODULE_X0)==1)?SENSOR_F_L:0)|((digitalRead(LT_MODULE_X1)==1)?SENSOR_F_R:0);
  Serial.print("onLine1->");
  Serial.println(onLine1);
}
