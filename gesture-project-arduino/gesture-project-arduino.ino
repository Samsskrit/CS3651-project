#include "gesture-project-arduino.h"
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
// #include <SD.h>

SoftwareSerial mySerial(10, 11); // RX, TX for DFPlayer Mini
DFRobotDFPlayerMini myDFPlayer;

// File rhythmFile;
unsigned long startTime;
unsigned long nextNoteTime = 0;
bool playing = false;
int i = 0;
int rhythmFileLength = 375;

const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  mySerial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) {
      Serial.println("DFPlayer Mini initialization failed!");
      while (true);
  }
  myDFPlayer.volume(30);
  Serial.println("DFPlayer initialized");

  myDFPlayer.play(1); // Play the first MP3 file on the SD card
  // delay(200);
  startTime = millis(); // Record the start time
  playing = true;

  loadNextNote();
}

void loop() {
  // if (!playing) return;

  unsigned long currentTime = millis() - startTime;

  // Check if it's time to light up the LED for the next note
  if (currentTime >= nextNoteTime && nextNoteTime > 0) {
    Serial.print(currentTime);
    Serial.print(" : ");
    Serial.println(nextNoteTime);
    lightUpLED();
    loadNextNote(); // Load the next note timing
  }
}

void lightUpLED() {
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

void loadNextNote() {
  
  if (i != rhythmFileLength) {
    nextNoteTime = (long) (rhythmFile[i] * 1000);
    Serial.print(rhythmFile[i] * 1000);
    Serial.print(" : Next note at: ");
    Serial.println(nextNoteTime);
    i++;
  } else {
    nextNoteTime = 0;
  }
  
}