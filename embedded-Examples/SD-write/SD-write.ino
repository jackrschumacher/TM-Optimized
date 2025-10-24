#include <SPI.h>
#include <SD.h>

int sdOutputPin =1; //Change this

File randomFile; //Initialize file variable

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(!SD.begin(sdOutputPin)){
    Serial.println("SD Card Initialization failed. Check card formatting and wiring.");
  }
  else{
    Serial.println("SD Card initialization succeeded");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // Set up some random variables for mocking up data
  long random1 = random(1,200);
  long random2 = random(1,200);
  long random3 = random(1,200);
  long random4 = random(1,200);



  randomFile = SD.open("data.txt" ,FILE_WRITE); //Write to file
  // Check if file exists
  if(randomFile){
    // Write values to file
    randomFile.print("Random 1: ");
    randomFile.print(random1);
    randomFile.print("Random 2: ");
    randomFile.print(random2);
    randomFile.print("Random 3: ");
    randomFile.print(random3);
    randomFile.print("Random 4: ");
    randomFile.print(random4);
    // Close file
    randomFile.close();
  }
  else{
    // If cannot open file (file does not exist)
    Serial.println("Cannot open file.");
  }
}
