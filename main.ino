// This program makes 6 LEDs sync to Can't Feel My Face by The Weeknd.

#include <math.h> // library that contains the round function
#include <stdint.h> // library that contains int types of specific sizes

const int ledPins[] = {2, 3, 4, 5, 6, 8}; // array with all the LED pins
const int beatLength = round(60 / 0.432); // variable to store the length of a "beat" (sixteenth note in this program)
const int lightSplit = round(beatLength * 0.75); // variable to ensure lights are off for at least 3/4 of a beat between notes
const int beats = 1108; // total number of beats; until the start of last chorus
const int numOfLeds = 6; // number of LEDs

// data for the 1st/red LED (which represents the melody)
const int8_t musicData0[] = {
  1, 2, 3, // 1st bar (verse 1 start)
  2, 2, 1, 3, 2, 2, 1, 3, // 2nd bar
  2, 2, 1, 5, 1, 2, 3, // 3rd bar
  2, 2, 1, 3, 2, 2, 1, 3, // 4th bar
  2, 2, 1, 5, 1, 2, 3, // 5th bar
  2, 2, 1, 3, 2, 2, 1, 3, // 6th bar
  2, 2, 1, 5, 1, 2, 3, // 7th bar
  6, -4, 1, 2, 3, // 8th bar
  6, 2, 2, 2, 2, // 9th bar (verse 1 end, pre-chorus start)
  2, 2, 8, 2, 4, // 10th bar
  6, 2, 2, 2, 2, // 11th bar
  2, 2, 8, 2, 10, // 12th bar
  2, 2, 2, 2, // 13th bar
  2, 2, 8, 2, 4, // 14th bar
  6, 2, 2, 2, 2, // 15th bar
  2, 2, 6, 2, 2, 4, // 16th bar
  4, 4, 6, // 17th bar (pre-chorus end)
  2, 2, 2, 2, 2, 2, 2, 2, // 18th bar (chorus start)
  2, -10, 1, 2, 3, // 19th bar
  6, -4, 1, 2, 3, // 20th bar
  6, -2, 2, 2, -2, // 21st bar
  2, 2, 2, 2, 2, 2, 2, 2, // 22nd bar
  2, -10, 1, 2, 3, // 23rd bar
  6, -4, 1, 2, 3, // 24th bar
  6, -4, 1, 2, 3, // 25th bar (chorus end, verse 2 start)
  2, 2, 1, 3, 2, 2, 1, 3, // 26th bar
  2, 2, 1, 5, 1, 2, 3, // 27th bar
  2, 2, 1, 3, 2, 2, 1, 3, // 28th bar
  2, 2, 1, 5, 1, 2, 2, // 29th bar
  2, 2, 2, 2, 2, 2, 2, 3, // 30th bar
  2, 2, 1, 5, 1, 2, 3, // 31th bar
  6, -4, 1, 2, 3, // 32nd bar
  6, 2, 2, 2, 2, // 33rd bar (verse 2 end, pre-chorus start)
  2, 2, 8, 2, 4, // 34th bar
  6, 2, 2, 2, 2, // 35th bar
  2, 2, 8, 2, 10, // 36th bar
  2, 2, 2, 2, // 37th bar
  2, 2, 8, 2, 4, // 38th bar
  6, 2, 2, 2, 2, // 39th bar
  2, 2, 6, 2, 2, 4, // 40th bar
  4, 4, 6, // 41st bar (pre-chorus end)
  2, 2, 2, 2, 2, 2, 2, 2, // 42nd bar (chorus start)
  2, -10, 1, 2, 3, // 43rd bar
  6, -4, 1, 2, 3, // 44th bar
  6, -2, 2, 2, -2, // 45th bar
  2, 2, 2, 2, 2, 2, 2, 2, // 46th bar
  2, 2, 2, 2, 2, -2, 1, 2, 3, // 47th bar
  2, 1, 2, 3, 2, 1, 2, 3, // 48th bar
  6, 1, 2, 2, 3, // 49th bar
  12, 1, 2, 3, // 50th bar
  10, 1, 2, 3, // 51st bar
  10, 1, 2, 3, // 52nd bar
  6, 1, 2, 2, 3, // 53rd bar
  12, 1, 2, 3, // 54th bar
  10, 1, 2, 3, // 55th bar
  10, 1, 2, 3, // 56th bar
  6, -8, // 57th bar (chorus end)
  14, 1, 1,
  14, 2,
  14, 2,
  8, 2, 2, 2, 2,
  2, 2, 8, 2, 4,
  6, 2, 2, 2, 2,
  2, 2, 8, 2, 10,
  2, 2, 2, 2,
  2, 2, 8, 2, 4,
  6, 2, 2, 2, 2,
  2, 2, 6, 2, 2, 4,
  4, 4, -16,
  6
};

// data for the 3rd/yellow LED (represents the higher-pitched part of the percussion)
const int8_t musicData2[] = {
  -4, // 1st bar (verse 1 start)
  -128, // 2nd-9th bars (verse 1 end, pre-chorus start)
  -4, 2, -6, 2, -6, // 10th bar
  2, -6, 2, -6, // 11th bar
  2, -6, 2, -6, // 12th bar
  2, -6, 2, -6, // 13th bar
  2, -6, 2, -6, // 14th bar
  2, -6, 2, -6, // 15th bar
  2, -6, 2, -12, // 16th bar
  1, 1, 2, -6, // 17th bar (pre-chorus end)
  2, -6, 2, -6, // 18th bar (chorus start)
  2, -6, 2, -6, // 19th bar 
  2, -6, 2, -6, // 20th bar
  2, -4, 1, 1, 2, -6, // 21th bar
  2, -6, 2, -6, // 22nd bar
  2, -6, 2, -6, // 23rd bar
  2, -6, 2, -6, // 24th bar
  2, -4, 1, 1, 2, -14, // 25th bar (chorus end, verse 2 start)
  2, -6, // 26th bar
  2, -6, 2, -6, // 27th bar
  2, -6, 2, -6, // 28th bar
  2, -4, 1, 1, 2, -6, // 29th bar
  2, -6, 2, -6, // 30th bar
  2, -6, 2, -6, // 31st bar
  2, -6, 2, -6, // 32nd bar
  2, -4, 1, 1, 2, -6, // 33rd bar (verse 2 end, pre-chorus start)
  2, -6, 2, -6, // 34th bar
  2, -6, 2, -6, // 35th bar
  2, -6, 2, -6, // 36th bar
  2, -4, 1, 1, 2, -6, // 37th bar
  2, -6, 2, -6, // 38th bar
  2, -6, 2, -6, // 39th bar
  2, -6, 2, -12, // 40th bar
  1, 1, 2, -6, // 41st bar (pre-chorus end)
  2, -6, 2, -6, // 42nd bar (chorus start)
  2, -6, 2, -6, // 43rd bar 
  2, -6, 2, -6, // 44th bar
  2, -4, 1, 1, 2, -6, // 45th bar
  2, -6, 2, -6, // 46th bar
  2, -6, 2, -6, // 47th bar 
  2, -6, 2, -6, // 48th bar
  2, -4, 1, 1, 2, -6, // 49th bar
  2, -6, 2, -6, // 50th bar
  2, -6, 2, -6, // 51st bar 
  2, -6, 2, -6, // 52nd bar
  2, -4, 1, 1, 2, -6, // 53rd bar
  2, -6, 2, -6, // 54th bar
  2, -6, 2, -6, // 55th bar 
  2, -6, 2, -6, // 56th bar
  2, -4, 1, 1, 2, -2, // 57th bar (chorus end)
  -64,
  -8, 2, -4, 2,
   -2, 2, -4, 2, -14,
  2, -4, 2,
  -2, 2, -4, 2, -14,
  2, -4, 2,
  -2, 2, -4, 2, -14,
  2, -4, 2,
  -32
};

// data for the 5th/blue LED (represents the kick in the percussion)
const int8_t musicData4[] = {
  -4, // 1st bar (verse 1 start)
  -128, // 2nd-9th bars (verse 1 end, pre-chorus start)
  -128, // 10th-17th bars (pre-chorus end)
  2, -6, 2, -6, // 18th bar (chorus start)
  2, -6, 2, -6, // 19th bar
  2, -6, 2, -6, // 20th bar
  2, -6, 2, -6, // 21st bar
  2, -6, 2, -6, // 22nd bar
  2, -6, 2, -6, // 23rd bar
  2, -6, 2, -6, // 24th bar
  2, -6, 2, -22, // 25th-26th bars (chorus end, verse 2 start)
  2, -6, 2, -6, // 27th bar
  2, -6, 2, -6, // 28th bar
  2, -6, 2, -6, // 29th bar
  2, -6, 2, -6, // 30th bar
  2, -6, 2, -6, // 31st bar
  2, -6, 2, -6, // 32nd bar
  2, -6, 2, -6, // 33rd bar (verse 2 end, pre-chorus start)
  2, -6, 2, -6, // 34th bar
  2, -6, 2, -6, // 35th bar
  2, -6, 2, -6, // 36th bar
  2, -6, 2, -70, // 37th-41st bars (pre-chorus end)
  2, -6, 2, -6, // 42nd bar (chorus start)
  2, -6, 2, -6, // 43rd bar
  2, -6, 2, -6, // 44th bar
  2, -6, 2, -6, // 45th bar
  2, -6, 2, -6, // 46th bar
  2, -6, 2, -6, // 47th bar
  2, -6, 2, -6, // 48th bar
  2, -6, 2, -6, // 49th bar
  2, -6, 2, -6, // 50th bar
  2, -6, 2, -6, // 51st bar
  2, -6, 2, -6, // 52nd bar
  2, -6, 2, -6, // 53rd bar
  2, -6, 2, -6, // 54th bar
  2, -6, 2, -6, // 55th bar
  2, -6, 2, -6, // 56th bar
  2, -6, 2, -214 // 57th-70th bar (chorus end, pre-chorus start, pre-chorus end)
};

// data for the 2nd, 4th, and 6th / green LEDs (represents the bass)
const int8_t musicDataGreen[] = {
  -4, // 1st bar (verse 1 start)
  8, -8, // 2nd bar
  8, -8, // 3rd bar
  8, -24, // 4th-5th bars
  8, -8, // 6th bar
  8, -8, // 7th bar
  8, -24, // 8th-9th bars (verse 1 end, pre-chorus start)
  8, -8, // 10th bar
  8, -8, // 11th bar
  8, -24, // 12th-13th bars
  8, -8, // 14th bar
  8, -8, // 15th bar
  8, -24, // 16th-17th bars (pre-chorus end)
  1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 18th bar (chorus start)
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 19th bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 20th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 21st bar
  -1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 22nd bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 23rd bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 24th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 25th bar (chorus end, verse 2 start)
  -12, 2, 1, 1, // 26th bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 27th bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 28th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 29th bar
  -1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 30th bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 31st bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 32nd bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 33rd bar (verse 2 end, pre-chorus start)
  -1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 34th bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 35th bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 36th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 37th bar
  -64, // 38th-41st bars
  1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 42nd bar (chorus start)
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 43rd bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 44th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 45th bar
  -1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 46th bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 47th bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 48th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 49th bar
  1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 50th bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 51st bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 52nd bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 53rd bar
  1, 1, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 54th bar
  -2, 2, -1, 2, 1, 4, -1, 2, 1, // 55th bar
  -2, 2, -1, 2, 1, 4, 2, -1, 1, // 56th bar
  -2, 2, -1, 2, 1, 3, 1, -1, 1, 1, 1, // 57th bar (chorus end)
  8, -8,
  8, -8,
  8, -24,
  8, -8,
  8, -8,
  8, -24,
  8, -8,
  8, -8,
  8, -40
};

struct LEDData { // structure that represents the data for one LED
  const int8_t *musicData; // a pointer to the first element of the data array
  int index; // the current index in the data array
  int length; // the remaining length of the current note/rest
};

struct LEDData leds[numOfLeds] = { // an array to store the LEDData of each LED
  {musicData0, 0, 0}, // 1st LED, red
  {musicDataGreen, 0, 0}, // 2nd LED, green
  {musicData2, 0, 0}, // 3rd LED, yellow
  {musicDataGreen, 0, 0}, // 4th LED, green
  {musicData4, 0, 0}, // 5th LED, blue
  {musicDataGreen, 0, 0} // 6th LED, green
};



void setup() { // setup function that runs once at the beginning
  for (int i = 0; i < 6; i++) { // for loop that loops through the LED pins
    pinMode(ledPins[i], OUTPUT); // sets the current LED pin to output
  }
}

void loop() { // loop function that runs repeatedly
  
  for (int ledIndex = 0; ledIndex < 6; ledIndex++) { // for loop that loops through the LED indices
    leds[ledIndex].index = 0; // index set to 0 to start at the beginning of the song
    leds[ledIndex].length = 0; // length set to 0 to indicate there is no note already being played
  }
  
  for (int beat = 0; beat < beats; beat++) { // for loop that loops through every beat of the song
    for (int i = 0; i < numOfLeds; i++) {  // for loop that loops through the LEDs
      struct LEDData *led = &leds[i]; // stores a pointer to the LED data
      
      if (led->length == 0) { // if length is 0, I must move on to the next note/rest 
        if (led->musicData[led->index] > 0) { // if the next piece of data is positive, it is a note
          digitalWrite(ledPins[i], HIGH); // turns on the LED
          led->length = led->musicData[led->index]; // stores the number of beats until the next note/rest
        } else { // if the next piece of data is negative, it is a rest
          led->length = -led->musicData[led->index]; // stores the number of beats until the next note/rest
        }
        led->index++; // increments the index to move on to the next note/rest
      }
    }
    
    delay(beatLength - lightSplit); // waits less than a full beat
    
    for (int i = 0; i < numOfLeds; i++) { // for loop that loops through the LEDs
      struct LEDData *led = &leds[i]; // stores a pointer to the LED data
      
      led->length--; // decrements the length, indicating one beat has passed
      
      if (led->length == 0) { // if length is 0, the LED must be turned off before the next note/rest
        digitalWrite(ledPins[i], LOW); // turns off the LED
      }
    }
    
    delay(lightSplit); // waits the remaining time in the beat
  }
}
