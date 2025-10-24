#include <Arduino.h>
#include <Servo.h>

//Initialize servo
Servo servo1;

void setup() {
  // put your setup code here, to run once:
  // Serial initilization at a baud rate of 9600
  Serial.begin(9600);
}

void readSerial(){
  // Checks if serial is avaliable (value greater than 0)
  if(Serial.available() >0){
    String command = Serial.readStringUntil('\n'); //Read serial until newline
    command.trim(); //Remove whitespace
    // If no command is received
    if(command.length() == 0){
      Serial.println("No motor command received");
      return;
    }
    // If a command is received
    else{
      // Initilize array of the size of the serial input string. Print out over serial the value that the axis was commanded to move
      const int commandSize = command.length() +1; //Command size is equal to length of command string +1
      char commands[commandSize]; 
      command.toCharArray(commands,commandSize); //create commands array using commmands and commandSize
      
      char *token; //The * character means that this variable is a pointer value (a variable that points to another variable)
      int axis1move = 0; //Acess first value in array (corresponds to axis 1)


      token = strtok(commands,","); //Getting the first value before the first comma
      
      if(token != NULL){ //If the token is not null
        axis1move = atoi(token); //Convert token to an integer
       

      }
      else{
        Serial.println(("token was null"));
      }

      if(axis1move >=0){ //Check if the value passed is valid
          int convertToMicroseconds = map(axis1move,0,180,1000,2000); //Map the values of the angle over serial (i.e. 0-180) to a microsecond value (1000-2000)
      }
      else{
        Serial.println("Valid number could not be parsed");
      }
      
      
      
    }
  }
  else{
    // If not print no serial avaliable
    Serial.println("No serial avaliable");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  readSerial(); //Call the read serial function
}