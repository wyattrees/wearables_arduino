//
// Funky Town Band
// Plays the melody of Funky Town with you and flashes LED's along to the song
// 
// Author: Wyatt Rees
#include "pitches.h"
#define SPEAKER_PIN 3

// 0's are rests
int melody[] = {
  NOTE_C5, NOTE_C5, NOTE_AS4, NOTE_C5, 0, NOTE_G4, 0, NOTE_G4,
  NOTE_C5, NOTE_F5, NOTE_E5, NOTE_C5, 0
};
int numNotes = 13;
// 122 beats per minute in original song
float bpm = 122;
// song is in 4/4, so quarter note (qn) is 1 beat
// convert beats per minute to seconds per beat
float qn = 1/(bpm / 60);
// eigth note is half of quarter note duration
float en = qn / 2;
// half note is double quarter note duration
float hn = qn * 2;
// full bar duration
float fn = qn * 4;
float durations[] = {
  en, en, en, en, en, en, en, en, // first bar
  en, en, en, en, hn // second bar
};

int countInNotes[] = {
  NOTE_C4, 0, NOTE_C4, 0, NOTE_C4, 0, NOTE_C4, 0 
};
float countInDurs[] = {
  en, en, en, en, en, en, en, en
};


int leds[] = {
  8, 8, 7, 8, 0, 6, 0, 6, 8, 10, 9, 8, 0
};


/*
 * Play the main melody of Funky Town once through
 */
void playFunkytown(){
  
  for (int note = 0; note < numNotes; note++)
  {
    tone(SPEAKER_PIN, melody[note], durations[note]*1000);
    if (leds[note] != 0)
    {
      digitalWrite(leds[note], HIGH);
    }
    
    delay(durations[note]*1000-100);
    // turn LED off a bit early so it flashes for repeating notes
    digitalWrite(leds[note], LOW);
    delay(100);
  }
  noTone(SPEAKER_PIN);
}

/*
 * Play tones to count in a 4/4 beat at 122 bpm
 */
void playCountIn(){
  int toggle = 1;
  for (int note = 0; note < 8; note++)
  {
    tone(SPEAKER_PIN, countInNotes[note], countInDurs[note]*1000);
    if (toggle)
    {    
      digitalWrite(8, HIGH);
      toggle = 0;
    }
    else
    {
      toggle = 1;
    }
    delay(countInDurs[note]*1000);
    digitalWrite(8, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 6; i < 11; i++)
  {
    pinMode(i, OUTPUT);
  }
  noTone(SPEAKER_PIN);
  delay(5000);
  playCountIn();
  // just bass for two bars
  delay(fn*2*1000);
  playFunkytown();
  playFunkytown();
  // lyrics come in, no melody here
  delay(fn*2*1000);
  playFunkytown();
  playFunkytown();
  // second round of lyrics
  delay(fn*2*1000);
  playFunkytown();
  playFunkytown();
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
