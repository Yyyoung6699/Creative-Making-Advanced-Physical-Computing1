#include "SoftwareSerial.h"
#include "DFPlayer_Mini_Mp3.h"

SoftwareSerial mySerial(10, 11);

const int trigPin = 3;
const int echoPin = 2;
long duration;
int distance;


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
  mp3_set_serial(mySerial);
  mp3_set_volume(20);
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



  if (distance <= 5) {
    mp3_play(1);
    delay(5000);
  }

}
