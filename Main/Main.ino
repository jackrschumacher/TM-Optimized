#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Adafruit_BNO055.h>
#include "SparkFun_TB6612.h"
#include <utility/imumaths.h>
#include "PWMDcMotor.hpp" //Determine if this is being used
#include <Servo.h>

// Pin defnitions- these can obviously be changed
#define PWMB 11
#define BIN1 9
#define BIN2 10
#define STBY 41

// Setup BNO55
Adafruit_BNO055 bno = Adafruit_BNO055(55); 
#define SEALEVELPRESSURE_HPA (1013.25) //This value is used to calculate the current altitude

// Setup BMP3XX 
Adafruit_BMP3XX bmp;


unsigned long IMUCheckTimeElapsed = 0UL;
unsigned long IMUUpdateInterval = 100UL;

unsigned long EnvCheckTimeElapsed = 0UL;
unsigned long EnvUpdateInterval = 100UL;

// Declare vars for environmental sensor in preparation of writing to file
double envTemp = 0.0;
double envPressure = 0.0;
double envAltitude = 0.0;

// Declare vars for IMU sensor in preperation for writing values to a file
double posX = 0.0;
double posY = 0.0;
double posZ = 0.0;


void setup(){

}
void loop(){
  
}