// Wyatt Rees
// Feb 18, 2022
// Low vision aid
// Plays a tone that increases in frequency as user gets closer to a wall or other object
// in D major
#include "pitches.h"
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define speakerPin 4

int triggered[5] = {0,0,0,0,0};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

int getDistance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}


void loop() {
  int distance = getDistance();
  if (distance < 50 && distance >= 40)
  {
    // we're in D major folks
    if (!triggered[0]) {
      tone(speakerPin, NOTE_D4, 600);
      triggered[0] = 1;
      for (int i = 1; i < 5; i++) {
        triggered[i] = 0;
      }
    }
    
  }
  else if (distance < 40 && distance >= 30)
  {
    if (!triggered[1]) {
      tone(speakerPin, NOTE_E4, 600);
      triggered[0] = 0;
      triggered[1] = 1;
      for (int i = 2; i < 5; i++) {
        triggered[i] = 0;
      }
    }
  }
  else if(distance < 30 && distance >= 20)
  {
    if (!triggered[2]) {
      tone(speakerPin, NOTE_FS4, 600);
      triggered[0] = 0;
      triggered[1] = 0;
      triggered[2] = 1;
      for (int i = 3; i < 5; i++) {
        triggered[i] = 0;
      }
    }
  }
  else if (distance < 20 && distance >= 10) {
    if (!triggered[3]) {
      tone(speakerPin, NOTE_G4, 600);
      for (int i = 0; i < 3; i++) {
        triggered[i] = 0;
      }
      triggered[3] = 1;
      triggered[4] = 0;
    }
  }
  else if (distance < 10) {
    if (!triggered[4]) {
      tone(speakerPin, NOTE_A4, 600);
      for (int i = 0; i < 4; i++) {
        triggered[i] = 0;
      }
      triggered[4] = 1;
    }
  }
  else {
    noTone(4);
    for (int i = 0; i < 5; i++) {
        triggered[i] = 0;
     }
  }
}
