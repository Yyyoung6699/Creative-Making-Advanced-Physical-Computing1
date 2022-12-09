#include <Servo.h>

const int SOUND_PIN = A0;
const int servoPIN = 13;
int buzzPin = 9;    //蜂鸣器
int touch = 2;    //触摸
Servo myservo;//命名
int pos;//角度命名


void setup() {
  myservo.attach(servoPIN);
  pinMode(touch, INPUT);
  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(SOUND_PIN);
  Serial.println(value);

  long frequency = 500; //频率, 单位Hz

  if (digitalRead(2) && value >= 120) {
    myservo.write(180);
    
    tone(buzzPin, frequency );
    delay(5000);

  }
  else {
    noTone(buzzPin);//停止发声
  }



  //pos = map(value, 0, 1023, 0, 180);
  //myservo.write(pos);

  if (value >= 150) {
    myservo.write(180);
    delay(3000);
  }
  if (value >= 40 && value < 120) {
    myservo.write(90);
    delay(500);
  }

  if (digitalRead(2) && value < 40) {
    myservo.write(0);
    delay(500);
  }



}
