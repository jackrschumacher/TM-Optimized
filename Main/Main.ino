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
  } 
  else {
    Serial.println("SD Card initialization succeeded");
  }
  if (!bmp.begin_I2C()) {
    Serial.println("No BMP388 sensor is detected. Please check wiring, pin assignment in both hardware and software,etc. ");
  }
  if (!bno.begin()) {
    Serial.println("No BNO055 detected. Check wiring and pin assignment.");
  }

    // Set up sensor sampling rates
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);


}

void readSerialCommand(){
  // Check if serial is avaliable
  if(Serial.available() >0){
    // Read until newline character
    String command = Serial.readStringUntil('\n');
    command.trim(); //Remove leading space

    // If the string is empty, skip
    if(command.length() ==0) return;

    // Convert the command into a string array 
    const int commandBufferSize = command.length() +1;
    char commandBuffer[commandBufferSize];
    command.toCharArray(commandBuffer,commandBufferSize);

    char *axisLabel;
    // Since we have 5 axis (0,1,2,3,4)
    int axisIndex[5] = {0};

    for (int i =0; i < 5; i++){
      // Only first iteration has the command buffer
      if(i==0){
        axisLabel = strtok(commandBuffer,":");
      }
      else{
        axisLabel = strtok(NULL,":");
      }
      // If no axis label is found
      if(axisLabel == NULL){
        Serial.println("Axis label missing for axis");
        Serial.println(i);
        break;
      }

      // Convert into integer and add to an array. Also cap out of range value at max (0 or 180)
      if(axisIndex[i]<0) axisIndex[i] =0;
      if(axisIndex[i] > 180) axisIndex[i] =180;
    }
    // Turn on builtin LED to indicate command being received by the board
    digitalWrite(LED_BUILTIN, HIGH);
    axis0Servo.write(axisIndex[0]);
    axis1Servo.write(axisIndex[1]);
    axis2Servo.write(axisIndex[2]);
    axis3Servo.write(axisIndex[3]);
    axis4Servo.write(axisIndex[4]);

  }
  else{
    Serial.println("Serial not avaliable. Check connection.");
  }
}
void collectSensorData(){
  if(millis() - previousSensorUpdate >= sensorUpdateInterval){
    // Set previous to current
    previousSensorUpdate = millis();
    // Turn on LED to indicate that command sent
    digitalWrite(LED_BUILTIN, HIGH);

		imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
		sensors_event_t getIMUEvent;
		bno.getEvent(&getIMUEvent);

    // Define positions from the accelerometer
    posX = euler.x();
		posY = euler.y();
		posZ = euler.z();
		uint8_t system, gyro, accel, mag = 0;
		

    // TODO: Clean up and Figure out reason for dulicate data collection
    sensorDataFile = SD.open("sensorData.csv", FILE_WRITE);
		if (sensorDataFile){
		  sensorDataFile.print("posX ,");
		  sensorDataFile.print(posX);
		  sensorDataFile.print("posY ,");
		  sensorDataFile.print(posY);
		  sensorDataFile.print("posZ ,");
		  sensorDataFile.print(posZ);
		  sensorDataFile.print("acceleration ,");
      sensors_event_t accelerometerData;
      bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
     // sensorDataFile.print(printEvent(&accelerometerData));
		  sensorDataFile.println(accel, DEC);
      


		  sensorDataFile.close();
		}
		else
		{
		 // Serial.println("Unable to write to the sensor data file. Check wiring and pin assignments");
		}

    concatenatedString.concat(posX);
		concatenatedString.concat(",");
		concatenatedString.concat(posY);
		concatenatedString.concat(",");
		concatenatedString.concat(posZ);
		concatenatedString.concat(",");
    concatenatedString.concat("$");
	  sensors_event_t accelerometerData;
		bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
		concatenatedString.concat(accel);
		concatenatedString.concat("$");


    	  if (!bmp.begin_I2C())
	  {
		//Serial.println("Sensor is not able to perform the reading. Please check that the sensor is connected correctly (wiring and software)");
		return;
	  }

	  unsigned long currentEnvTime = millis(); // Get the current time in milliseconds- could this possibly be merged into the main function


		envTemp = bmp.temperature;
		envPressure = bmp.pressure / 100;
		envAltitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

		/**Writes the following to the SD card
		 * The Current Environment sensor time (timestamp)
		 * Temperature sensor reading/data
		 * Pressure sensor reading/data
		 * Altitude sensor reading/data
		 */
    sensorDataFile = SD.open("sensorData.csv", FILE_WRITE);
		if (sensorDataFile)
		{

		  // TODO: There is a better way to do this with headers, but this will work for now
		  // sensorDataFile.print("currentEnvTime ,");
		  // sensorDataFile.print(currentEnvTime);
		  sensorDataFile.print("envTemp ,");
		  sensorDataFile.print(envTemp);
		  sensorDataFile.print("envPressure ,");
		  sensorDataFile.print(envPressure);
		  sensorDataFile.print("envAltitude ,");
		  sensorDataFile.print(envAltitude);
		  sensorDataFile.close();
		}
		// else{
		//   Serial.print("Sensor data is unable to be written to a file. Please check wiring and pin assignments");

		// }

		// Serial.println("Current time between Environmental sensor update");
		// Serial.println(currentEnvTime);
		// Serial.println(" Celsius");
		// Serial.println(envTemp); // TODO: This is in celsius! Do we want to have this in Fahrenheit?
		// Serial.println("Pressure");
		// Serial.println(envPressure); // TODO: This is in HPA. Do we want that?
		// Serial.println("Altitude:");
		// Serial.println(envAltitude); // TODO: This is in meters. Determine if we want to use this for units, or change to something else
		// Serial.println(" meters");
		
		Serial.print(envTemp);
		concatenatedString.concat(envTemp);
		concatenatedString.concat(",");
		concatenatedString.concat(envPressure);
		concatenatedString.concat(",");
		concatenatedString.concat(envAltitude);
		// concatenatedString.concat("$");
		// Serial.print(",");
		// Serial.print(envPressure);
		// Serial.print(",");
		// Serial.print(envAltitude);
		// Serial.print("$");
		
		Serial.println(concatenatedString);
    concatenatedString = "";
		
		digitalWrite(LED_BUILTIN, LOW);	
    

  }

  
}


void loop() {
  // Check the current time 
  unsigned long currentIMUTime = millis();
  // Check if the serial is avaliable
  readSerialCommand();
  collectSensorData();
}
