#include <dummy.h>
# include <BluetoothSerial.h>
BluetoothSerial SerialBT;

const int freq = 5000;
const int res = 8;
void Forward();
void Backward();
void Right();
void Left();
void Stop();

int trig1 = 32;
int echo1 = 33;
int trig2 = 23;
int echo2 = 19;
const int Motor_1_forward = 26;  
const int Motor_1_backward = 27;


const int Motor_3_forward = 14;    
const int Motor_3_backward = 12;
const int ena = 25;
const int enb = 13;
int distance1=0;
int distance2=0;
int Motor_speed = 175;
char command;
long duration1=0;
long duration2=0;

void setup() {

  Serial.begin(115200);
  ledcSetup(0, freq, res);
  ledcSetup(1, freq, res);
  ledcAttachPin(25, 0);
  ledcAttachPin(13, 1);
  pinMode(Motor_1_forward, OUTPUT);
  pinMode(Motor_1_backward, OUTPUT);
  pinMode(Motor_3_forward, OUTPUT);
  pinMode(Motor_3_backward, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  SerialBT.begin("ESP32test");
  SerialBT.println("The device started, now you can pair it with bluetooth");
 
  Stop();
}

void loop() {
  
 digitalWrite(trig1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig1, HIGH);
delayMicroseconds(10);
digitalWrite(trig1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echo1, HIGH);
// Calculating the distance
distance1= duration1*0.034/2;

 digitalWrite(trig2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig2, HIGH);
delayMicroseconds(10);
digitalWrite(trig2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echo2, HIGH);
// Calculating the distance
distance2= duration2*0.034/2; 

  Serial.print("Distance1:");
  Serial.println(distance1);
  Serial.print("Distance2:");
  Serial.println(distance2);
  
  SerialBT.print("Distance1:");
  SerialBT.println(distance1);
  SerialBT.print("Distance2:");
  SerialBT.println(distance2);
  
  if(distance1<=9 ){
   Left();
   Serial.println("LEFT");
  }
  else if(distance2<=9 ){
   Right();
   Serial.println("RIGHT");
  }
  else  {
    Forward();
    Serial.println("FORWARD");
  }

}


void Right() {
  digitalWrite(Motor_1_forward, LOW);
  digitalWrite(Motor_1_backward, HIGH);
  digitalWrite(Motor_3_forward, HIGH);
  digitalWrite(Motor_3_backward, LOW);
  ledcWrite(0, Motor_speed);
  ledcWrite(1, Motor_speed);
  SerialBT.println("Left");
  SerialBT.println(Motor_speed);  // to test if the function is working or not
}

void Left() {
  digitalWrite(Motor_1_forward, HIGH);
  digitalWrite(Motor_1_backward, LOW);
  digitalWrite(Motor_3_forward, LOW);
  digitalWrite(Motor_3_backward, HIGH);
  ledcWrite(0, Motor_speed);
  ledcWrite(1, Motor_speed);
  SerialBT.println("Right");
  SerialBT.println(Motor_speed);// to test if the function is working or not
}

void Backward() {
  digitalWrite(Motor_1_forward, HIGH);
  digitalWrite(Motor_1_backward, LOW);
  digitalWrite(Motor_3_forward, HIGH);
  digitalWrite(Motor_3_backward, LOW);
  ledcWrite(0, Motor_speed);
  ledcWrite(1, Motor_speed);
  SerialBT.println("Forward");
  SerialBT.println(Motor_speed);// to test if the function is working or not
}

void Forward() {
  digitalWrite(Motor_1_forward, LOW);
  digitalWrite(Motor_1_backward, HIGH);
  digitalWrite(Motor_3_forward, LOW);
  digitalWrite(Motor_3_backward, HIGH);
  ledcWrite(0, Motor_speed);
  ledcWrite(1, Motor_speed);
  SerialBT.println("Backward");
  SerialBT.println(Motor_speed);// to test if the function is working or not
}


void Stop() {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  digitalWrite(Motor_1_forward, LOW);
  digitalWrite(Motor_1_backward, LOW);
  digitalWrite(Motor_3_forward, LOW);
  digitalWrite(Motor_3_backward, LOW);
  SerialBT.println("Stop");
  SerialBT.println(Motor_speed);// to test if the function is working or not
}
