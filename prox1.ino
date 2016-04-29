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

int analogInputVal = 0;
long detectionSpanInitial = 0;
long detectionSpan = 0;
int claps = 0;
int currentClaps = 0;

const int THRESHOLD = 90; //the sound level that will be treated as a 'clap'
const int SOUND_SAMPLE_LENGTH = 500; //the amount of ms to wait before determining to turn off/on
const int CLAP_DURATION_WINDOW = 1500; //the amount of ms max to make the number of claps specified (ms)
const int CLAPS_FOR_TRIGGER_ON_OFF = 2; //the number of claps for the relay to trigger

int loopCounter;

EthernetClient client;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Ethernet.begin(mac, ip);
}

void loop() {

  if (loopCounter == 50) {

//    checkDistance();
    loopCounter = 0;
  }
//  checkSound();
//  loopCounter++;

  setRandomColorOnGroup();
  
  delay(500);
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
        turnOnOffLamp(i, true);
        setBrightness(i, maxBrightness);
      }
      else if (i == currentLampId) {
        Serial.print("set lamp: ");
        Serial.print(i);
        Serial.print(" brightness: ");
        Serial.print( brightness);
        turnOnOffLamp(i, true);
        setBrightness(i, brightness);
      }
      else {
        Serial.print("turn of: ");
        Serial.print(i);
        turnOnOffLamp(i, false);
      }
      Serial.println();
    }
  }
}

void checkSound() {

  analogInputVal = analogRead(SOUND_SENSOR);

  if (analogInputVal >= THRESHOLD)
  {
    Serial.println(analogInputVal);
    if (claps == 0)
    {
      detectionSpanInitial = detectionSpan = millis();
      claps++;
    }
    else if (claps > 0 && millis() - detectionSpan >= 200)
    {
      detectionSpan = millis();
      claps++;
    }
  }

  if (millis() - detectionSpanInitial >= 400)
  {
//    setGroupBrightness(lightState ? 200 : 0);
//    lightState = !lightState;
//      delay(1000);
      
    if (claps == CLAPS_FOR_TRIGGER_ON_OFF)
    {
      //      setRandomColorOnLamp(1);
      //      setRandomColorOnLamp(2);
      //      setRandomColorOnLamp(3);


  
//      setGroupBrightness(lightState ? 200 : 0);
//    lightState = !lightState;
      setRandomColorOnGroup();

      String command;
      //      turnOnOffLamp(3, !lightState);
      //      turnOnOffLamp(2, !lightState);
      //      turnOnOffLamp(1, !lightState);


      

      Serial.println("Command sent");
//      delay(750);

    }
    claps = 0;
  }
}




