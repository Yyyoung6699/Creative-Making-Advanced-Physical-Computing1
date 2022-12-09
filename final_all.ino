#include "SoftwareSerial.h"
#include "DFPlayer_Mini_Mp3.h"
#include <Servo.h>
SoftwareSerial mySerial(10, 11);
//speaker
const int trigPin = 3;
const int echoPin = 2;
long duration;
int distance;
bool firstRun = true;
bool buzzerRun = true;
//servo
const int SOUND_PIN = A0;
const int servoPIN = 13;
int buzzPin = 9;    //蜂鸣器
int touch = 4;    //触摸
Servo myservo;//命名
int pos;//角度命名

void setup() {
  // put your setup code here, to run once:
  //speaker
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
  mp3_set_serial(mySerial);
  mp3_set_volume(25);
  while (!Serial) {
    ;
  }
  //servo
  myservo.attach(servoPIN);
  pinMode(touch, INPUT);
  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (firstRun == true && distance <= 50) {
    mp3_play(1);
    firstRun = false;
    delay(17000);
  }

  int value = analogRead(SOUND_PIN);
  Serial.println(value);

  long frequency = 500; //频率, 单位Hz

  if (digitalRead(4) && value >= 80) {
    myservo.write(180);//触摸+声音大，转向怒+蜂鸣器叫
    tone(buzzPin, frequency );//buzzer screaming
    delay(5000);
  }
  else {noTone(buzzPin);//停止发声
  }
  //pos = map(value, 0, 1023, 0, 180);
  //myservo.write(pos);

  if (value >= 150) {
    mp3_play(4);
    myservo.write(180);//大声说话转向愤怒，愤怒音效
    delay(3000);
  }
  if (value >= 40 && value < 120) {
    mp3_play(3);//低声说话转向笑，播放笑声
    myservo.write(90);
    delay(3000);
  }
  if (digitalRead(4) && value < 40 && myservo.read() != 0) {
    mp3_play(2);//触摸转向忧郁，播放哭
    myservo.write(0);
    delay(7000);
  }
}
