#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

#define SEALEVELPRESS (1013.25);
// Initilizated variables
char testString ="";

int oneNum = 1;

double posX = 0.0;
double posY = 0.0;
double posZ = 0.0;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


}

void readSerial(){
  if(Serial.available() >0){
    String command = Serial.readStringUntil('\n'); //Read serial until newline
    command.trim(); //Remove whitespace
    if(command.length() == 0){
      Serial.println("No motor command received");
    }
  }
  else{
    Serial.println("No serial avaliable");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  readSerial();
}
