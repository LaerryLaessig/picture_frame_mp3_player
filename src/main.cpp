#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int input_signal=7; 
int input_state=0;
long number_of_files=0; 
int sound_volume=30;

void setup()
{
  

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
    
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  while(number_of_files == 0) {
    myDFPlayer.volume(sound_volume);
    number_of_files=myDFPlayer.readFileCounts();
    Serial.println("===================================");
    Serial.print(" Number of files: ");
    Serial.print(number_of_files);
  }
  pinMode(input_signal, INPUT);
}

void loop()
{
input_state=digitalRead(input_signal);
if (input_state == HIGH) { 
 myDFPlayer.play(random(0, number_of_files));  
 } 
}