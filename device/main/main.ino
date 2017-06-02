/*
 * Phult@gmail.com
 * https://github.com/phult
 * 
 * A robot simulates dog behavior
 */
#include <Servo.h>
Servo myservo;
const int alertLightPin = 13;
const int proximitySensorTrigPin = 9;
const int proximitySensorEchoPin = 8;
const int engine2APin = 7;
const int engine2BPin = 6;
const int engine1APin = 4;
const int engine1BPin = 5;
const int servoPin = 3;
const int motionSensorPin = 2;

const int IMPACT_DISTANCE = 15; //cm
void setup() {
  pinMode(proximitySensorTrigPin,OUTPUT);
  pinMode(proximitySensorEchoPin,INPUT);
  pinMode(engine1APin,OUTPUT);
  pinMode(engine1BPin,OUTPUT);
  pinMode(engine2APin,OUTPUT);
  pinMode(engine2BPin,OUTPUT);
  pinMode(alertLightPin,OUTPUT);
  myservo.attach(servoPin);
  spinServo(90);
  Serial.begin(9600);  
}
bool ison = false;
void loop() {     
  //onLight(alertLightPin);
  //measureDistance(proximitySensorTrigPin,proximitySensorEchoPin);
  //digitalWrite(13, 0);
  //spinServo(0);
  //delay(5000);
  //spinServo(180);
 

  
  /*
   *    readSerialPort();
 Serial.print(1);
  */
 if(isImpact()){
  goBack();
  delay(170);
  stop();
  int turn = decideTurn();
  delay(200);
  if(turn==0){
    turnLeft();
  }else if(turn==1){
    turnRight();
  }
  stop();
  delay(500);
  goAhead();
  delay(500);
 }else{
  if(onMotion()){
    goAhead();
    onLight(alertLightPin);
  }else{
    stop();
    offLight(alertLightPin);
  }
  
  //goAhead();
 }

}

void goAhead(){
  digitalWrite(engine1APin, LOW);
  digitalWrite(engine1BPin, HIGH);
  digitalWrite(engine2APin, LOW);
  digitalWrite(engine2BPin, HIGH);    
}

void goBack(){
  digitalWrite(engine1APin, HIGH);
  digitalWrite(engine1BPin, LOW);
  digitalWrite(engine2APin, HIGH);
  digitalWrite(engine2BPin, LOW);      
}

void stop(){
  digitalWrite(engine1APin, LOW);
  digitalWrite(engine1BPin, LOW);
  digitalWrite(engine2APin, LOW);
  digitalWrite(engine2BPin, LOW);  
  
}

void turnLeft(){
  digitalWrite(engine1APin, LOW);
  digitalWrite(engine1BPin, HIGH);
  digitalWrite(engine2APin, LOW);
  digitalWrite(engine2BPin, LOW);
  delay(320);
}

void turnRight(){  
  digitalWrite(engine1APin, LOW);
  digitalWrite(engine1BPin, LOW);
  digitalWrite(engine2APin, LOW);
  digitalWrite(engine2BPin, HIGH);
  delay(310);
}

void turnLeftBack(){
  digitalWrite(engine1APin, HIGH);
  digitalWrite(engine1BPin, LOW);
  digitalWrite(engine2APin, LOW);
  digitalWrite(engine2BPin, LOW);
  delay(320);
  goBack();
  delay(200);
}

void turnRightBack(){
  digitalWrite(engine1APin, LOW);
  digitalWrite(engine1BPin, LOW);
  digitalWrite(engine2APin, HIGH);
  digitalWrite(engine2BPin, LOW);
  delay(350);
  goBack();
  delay(200);
}

void onLight(int pin){
  digitalWrite(pin, 1);
}
void offLight(int pin){        
  digitalWrite(pin, LOW);
}
void blinkLight(int pin, int interval){
  onLight(pin);
  delay(interval);           
  offLight(pin);
  delay(interval); 
}
int measureDistance(int trigPin, int echoPin){
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách
  /* Phát xung từ chân trig */
  digitalWrite(trigPin, 0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trigPin, 0);   // tắt chân trig  
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echoPin, HIGH);  
  // Tính khoảng cách đến vật.
  distance = int(duration/2/29.412);
  Serial.println(distance);
  return distance;
}
bool isImpact(){  
  return measureDistance(proximitySensorTrigPin,proximitySensorEchoPin) <= IMPACT_DISTANCE ? true:false;
}
void spinServo(int angle){
  myservo.write(angle);
  delay(500);
}
int decideTurn(){
  int retval = 1;
  spinServo(0);
  int rightDistance = measureDistance(proximitySensorTrigPin,proximitySensorEchoPin);
  spinServo(180);
  int leftDistance= measureDistance(proximitySensorTrigPin,proximitySensorEchoPin);
  spinServo(90);
  if(leftDistance > rightDistance){
    retval = 0;
  }else{
    retval = 1;
  }
  return retval;
}
bool onMotion(){
  int retval = digitalRead(motionSensorPin);
  return retval == 1? true: false;  
}
char character;
void readSerialPort() {  
  if (Serial.available()) {
    /*
    int dataByte = Serial.read();
    if(dataByte==1){
      onLight(alertLightPin);
    }else{
      offLight(alertLightPin);
    }   
    */   
    character = Serial.read();
    //Serial.println("echo:"+character);  
  }
  if(character!=' '){
    if (character=='1') {
     onLight(alertLightPin);
    } else {
      offLight(alertLightPin);
    }
  }
  delay(100);
}

