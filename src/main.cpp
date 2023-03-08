#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int input_signal=7; 
int input_state=LOW;
long number_of_files=0; 
int sound_volume=70;
int rnd_number=0;
int val = 0;
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
    Serial.println(number_of_files);
  }
  pinMode(input_signal, INPUT);
}

void wait_mp3_finished() {
  delay(1000);

}

void loop()
{
  val = digitalRead(input_signal);
if (val == HIGH) { 
 if(input_state == LOW) { 
  rnd_number = random(number_of_files);
  Serial.print("Play file: ");
  Serial.println(rnd_number);
  myDFPlayer.play(rnd_number);  
  wait_mp3_finished();
  input_state = HIGH;
 } 
} else {
  Serial.println("Motion ends");
  input_state = LOW;
}
}
