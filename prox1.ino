/*
  HC-SR04 Ping distance sensor]
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#include <SPI.h>
#include <Ethernet.h>

const char hueHubIP[] = "192.168.1.100";  // Hue hub IP
const char hueUsername[] = "HtBhcb007XSZQnThI9MKRl01gegMJhI0SYdn0hL4";
const int hueHubPort = 80;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 105); // Arduino IP

const int SOUND_SENSOR = A0; //pin for the Grove Sound Sensor

const int trigPin = 8;
const int echoPin = 7;

const int maxDistance = 30;
const int numOfLamps = 3;
const int maxBrightness = 254;

int loopCounter;

EthernetClient client;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Ethernet.begin(mac, ip);
}

void loop() {

  if (loopCounter == 20) {

    checkDistance();
    
    loopCounter = 0;
  }
  loopCounter++;
  delay(10);
}


void checkDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance < 4) {
  }

  if (distance >= maxDistance || distance <= 0) {
    Serial.println("Out of range");
  }
  else {

    int currentLampId = (distance / 10) + 1;
    int brightness = (distance % 10) * 25.4;
    Serial.print(distance);
    Serial.println();
    for (int i = 1; i <= numOfLamps ; i++) {
      if (i < currentLampId) {
        Serial.print("set lamp: ");
        Serial.print(i);
        Serial.print(" brightness: ");
        Serial.print(maxBrightness);
      }
      else if (i == currentLampId) {
        Serial.print("set lamp: ");
        Serial.print(i);
        Serial.print(" brightness: ");
        Serial.print( brightness);
      }
      else {
        Serial.print("turn of: ");
        Serial.print(i);
      }
      Serial.println();
    }
  }
}






