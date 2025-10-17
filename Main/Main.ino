#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Adafruit_BNO055.h>
#include "SparkFun_TB6612.h"
#include <utility/imumaths.h>
#include "PWMDcMotor.hpp"
#include <Servo.h>
// Would reccomend setting up all the global variables here
// Initialize bno
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
#define SEALEVELPRESSURE_HPA (1013.25)  //Default sea level pressure

Adafruit_BMP3XX bmp;

// Records the time since the last sensor update and recording to the SD card and also sending data to basestation
unsigned long previousSensorUpdate = 0;
unsigned long lastSensorUpdate = 0;
// Update the sensor values and write to the SD card every 500 ms (half a second)
long sensorUpdateInterval = 500;

// Declare vars for environmental sensor in preparation of writing to file
double envTemp = 0.0;
double envPressure = 0.0;
double envAltitude = 0.0;

// Declare vars for IMU sensor in preparation for writing values to a file
double posX = 0.0;
double posY = 0.0;
double posZ = 0.0;

// Setup array for characters
const byte numberOfChars = 32;
char receivedValues[numberOfChars];
// Setup file for recording sensor data
File sensorDataFile;
char endMarker = '\n';
// Setup PWM
const int PWMA = 8;
const int bin1 = 6;
const int bin2 = 7;
const int speed = 5;
// Defined motor speed
int motorSpeed = 0;
/* Define servos
Axis 0- Bottom Motor (turret) - 25kg servo
Axis 1- Joint 1 - GM9
Axis 2- Joint 2 - GM9
Axis 3-Wrist - MG996 55g
Axis 4- End Effector- 45 kg servo
*/
Servo axis0Servo;
Servo axis1Servo;
Servo axis2Servo;
Servo axis3Servo;
Servo axis4Servo;

String motorAssignment;
String motorSpeedAssignmentUnfiltered;
int motorSpeedAssignment;
String concatenatedString;


void setup() {
  // Setup serial baud rate at 9600
  Serial.begin(9600);
  // Not really nessecerray except for debugging
  pinMode(LED_BUILTIN, OUTPUT);
  // TODO: Determine pins- other values are min and max (also look into)
  axis0Servo.attach(0, 700, 2000);
  axis1Servo.attach(1, 700, 2000);
  axis2Servo.attach(2, 700, 2000);
  axis3Servo.attach(3, 700, 2000);

  pinMode(40, OUTPUT);  // Output to Libre

  pinMode(PWMA, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);

  const int sdOutputPin = 9;
  // Check sensor communications
  if (!SD.begin(sdOutputPin)) {
    Serial.println("SD Card Initialization failed. Check card formatting and wiring.");
  } else {
    Serial.println("SD Card initilization succeded");
    if (!bmp.begin_I2C()) {
      Serial.println("No BMP388 sensor is detected. Please check wiring, pin assignment in both hardware and software,etc. ");
    }
    if (!bno.begin()) {
      Serial.println("No BNO055 detected. Check wiring and pin assignment.")
    }

    // Set up sensor sampling rates
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  }
  void loop() {
    // Check the current time 
    unsigned long currentIMUTime = millis();
    // Check if the serial is avaliable
    if(Serial.avaliable() >0){
      // Take the serial output on the current line
      String command = Serial.readStringUntil('\n')
      command.trim()

      // Add command buffer to an array to allow for easier processing
      char commandBuffer[command.length() +1]
      command.toCharArray(commandBuffer,command.length() +1)

      char token =""
      char delimiter ="a1:"
      char token = strtok(commandBuffer, delimiter)
      int axis1Move = atoi(token)

      delimiter = ",ax2:"
      token = strtok(NULL,delimiter)
      int axis2Move = atoi(token)

    }
  }
