#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int input_signal=7; 
int input_state=0;
int number_of_files=0; 
int sound_volume=30;

void setup()
{
  mySoftwareSerial.begin(9600);
  while(number_of_files == 0) {
    myDFPlayer.volume(sound_volume);
    number_of_files=myDFPlayer.readFileCounts();
    Serial.println("===================================");
    Serial.println("Number of files: " + number_of_files);
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