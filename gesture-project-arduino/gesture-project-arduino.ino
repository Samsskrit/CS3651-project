#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <SD.h>

SoftwareSerial mySerial(10, 11); // RX, TX for DFPlayer Mini
DFRobotDFPlayerMini myDFPlayer;

File rhythmFile;
unsigned long startTime;

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);

    if (!myDFPlayer.begin(mySerial)) {
        Serial.println("DFPlayer Mini initialization failed!");
        while (true);
    }
    myDFPlayer.volume(20);

    if (!SD.begin(4)) {
        Serial.println("SD card initialization failed!");
        while (true);
    }

    rhythmFile = SD.open("../output/rhythm.txt");
    if (!rhythmFile) {
        Serial.println("Failed to open rhythm.txt");
        while (true);
    }

    myDFPlayer.play(1); // Play the first MP3 file on the SD card
    startTime = millis(); // Record the start time
}

void loop() {
    static unsigned long nextEventTime = 0;
    static int velocity = 0;

    // Check if we need to load the next rhythm event
    if (nextEventTime == 0 && rhythmFile.available()) {
        String line = rhythmFile.readStringUntil('\n');
        int commaIndex = line.indexOf(',');
        nextEventTime = line.substring(0, commaIndex).toInt();
        velocity = 31;
    }

    // Check if it's time to trigger the next event
    unsigned long currentTime = millis() - startTime;
    if (currentTime >= nextEventTime && nextEventTime > 0) {
        Serial.print("Trigger event at: ");
        Serial.print(currentTime);
        Serial.print(" ms, Velocity: ");
        Serial.println(velocity);

        // Trigger your event here (e.g., flash LED, vibrate motor)
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN, LOW);

        // Reset for the next event
        nextEventTime = 0;
    }
}