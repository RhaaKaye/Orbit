#include "FastLED.h"
#include "Streaming.h"
#define totalLEDs 55

CRGB currentLED[totalLEDs];

int step = 0;

// int newRed[5];
// int newGreen[5];
// int newBlue[5];

// int oldRed[5];
// int oldGreen[5];
// int oldBlue[5];

int newRed;
int newGreen;
int newBlue;

int oldRed;
int oldGreen;
int oldBlue;

bool fadeUP = true;

int currentMillis;


int k;

int i;

int zones = 3;


uint32_t colours[24] = { // https://www.w3schools.com/colors/colors_picker.asp
            0xff4000, 0xff8000, 0xffbf00, 0xffff00, 0xbfff00, 0x80ff00,
            0x40ff00, 0x00ff00, 0x00ff40, 0x00ff80, 0x00ffbf, 0x00ffff,
            0x00bfff, 0x0080ff, 0x0040ff, 0x0000ff, 0x4000ff, 0x8000ff,
            0xbf00ff, 0xff00ff, 0xff00bf, 0xff0080, 0xff0040, 0xff0000            
            };

void chooseNewColour(int k);
void chooseNewColour();
int upDown(int newVal, int oldVal);


void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<APA102, BGR>(currentLED, totalLEDs);
  FastLED.setBrightness(10  );

  chooseNewColour();

  // Serial << newRed[1] 
}


// void loop() // Put this in the main program
// {
//   Serial << "\t Old Red: " << oldRed << "\t Old Green: " << oldGreen << "\t Old Blue: " << oldBlue << endl; 

//   if(newRed - oldRed != 0 || newGreen - oldGreen != 0 || newBlue - oldBlue != 0)
//   {
//     oldRed   = upDown(newRed, oldRed);
//     oldGreen = upDown(newGreen, oldGreen);
//     oldBlue  = upDown(newBlue, oldBlue);
//   }

//   else if(newRed - oldRed == 0 && newGreen - oldGreen == 0 && newBlue - oldBlue == 0)
//   {
//     chooseNewColour();
//   }

//   for(int i = 0; i < totalLEDs; i ++)
//   {
//     currentLED[i].setRGB(oldRed, oldGreen, oldBlue);
//   }
//   FastLED.show();


//   delay(20);
// }

void chooseNewColour() // need to include the rndom seed here
{
  randomSeed(analogRead(0));
  int colour = random(0,24);

  Serial << colour << endl;
  uint32_t newColour = colours[colour]; // Pick a random colour from the table

  newRed   = (newColour & 0xff0000) >> 16;
  newGreen = (newColour & 0x00ff00) >> 8;
  newBlue  = (newColour & 0x0000ff);
}


// void chooseNewColour(int k) // need to include the rndom seed here
// {
//   randomSeed(analogRead(0));
//   int colour = random(0,24);

//   Serial << colour << endl;
//   uint32_t newColour = colours[colour]; // Pick a random colour from the table

//   newRed[k]   = (newColour & 0xff0000) >> 16;
//   newGreen[k] = (newColour & 0x00ff00) >> 8;
//   newBlue[k]  = (newColour & 0x0000ff);
// }

int upDown(int newVal, int oldVal)
{
  if     (newVal - oldVal > 0)  return oldVal + 1;
  else if(newVal - oldVal < 0)  return oldVal - 1;  
  else if(newVal - oldVal == 0) return newVal;
}

/* V6 colour fade (still needs work)
void loop()
{
  

  for(int k = 0; k <= 1; k ++)
    // k = 1;
  {
 
    // Serial << "Fade Up: " << fadeUP << "\t Old Red: " << oldRed[k] << "\t Old Green: " << oldGreen[k] << "\t Old Blue: " << oldBlue[k] << endl; 

    if(fadeUP)
    {
      if((newRed[k] - oldRed[k] != 0) || (newGreen[k] - oldGreen[k] != 0) || (newBlue[k] - oldBlue[k] != 0))
      {
        // Serial << "1" << endl;
        oldRed[k]   = upDown(newRed[k],   oldRed[k]);
        oldGreen[k] = upDown(newGreen[k], oldGreen[k]);
        oldBlue[k]  = upDown(newBlue[k],   oldBlue[k]);
      }
      else if((newRed[k] - oldRed[k] == 0) && (newGreen[k] - oldGreen[k] == 0) && (newBlue[k] - oldBlue[k] == 0))
      {
        // Serial << "2" << endl;
        fadeUP = false;

        newRed[k] = 0; // Set the new colour to off
        newGreen[k] = 0;
        newBlue[k] = 0;
      }
    }

    else if(!fadeUP)
    {
      if((newRed[k] - oldRed[k] != 0) || (newGreen[k] - oldGreen[k] != 0) || (newBlue[k] - oldBlue[k] != 0))
      {
        // Serial << "3" << endl;
        oldRed[k]   = upDown(0, oldRed[k]);
        oldGreen[k] = upDown(0, oldGreen[k]);
        oldBlue[k]  = upDown(0, oldBlue[k]);
      }
      else if((newRed[k] - oldRed[k] == 0) && (newGreen[k] - oldGreen[k] == 0) && (newBlue[k] - oldBlue[k] == 0))
      {
        // Serial << "4" << endl;
        fadeUP = true;

        chooseNewColour(k);
      }
    }


    for(int i = 0; i < totalLEDs; i ++)
    {
      currentLED[i].setRGB(oldRed[0], oldGreen[0], oldBlue[0]);
    }
      // for(int a = 14; a <= 19; a ++) currentLED[a].setRGB(oldRed[k], oldGreen[k], oldBlue[k]); // Zone 2

      // for(int a = 3;  a <= 8;  a ++) currentLED[a].setRGB(oldRed[0], oldGreen[0], oldBlue[0]); // Zone 1
      // for(int a = 14; a <= 19; a ++) currentLED[a].setRGB(oldRed[1], oldGreen[1], oldBlue[1]); // Zone 2
      // for(int a = 25; a <= 30; a ++) currentLED[a].setRGB(oldRed[2], oldGreen[2], oldBlue[2]); // Zone 3
      // for(int a = 36; a <= 41; a ++) currentLED[a].setRGB(oldRed[3], oldGreen[3], oldBlue[3]); // Zone 4
      // for(int a = 47; a <= 52; a ++) currentLED[a].setRGB(oldRed[4], oldGreen[4], oldBlue[4]); // Zone 5


    delay(5);
    FastLED.show();
  }


  // delay(10);
}
*/
/*
void loop() V3 5 working zones
{
  for(int k = 0; k < 5; k ++)
  {
    if(newRed[k] - oldRed[k] != 0 || newGreen[k] - oldGreen[k] != 0 || newBlue[k] - oldBlue[k] != 0)
    {
      oldRed[k]   = upDown(newRed[k],   oldRed[k]);
      oldGreen[k] = upDown(newGreen[k], oldGreen[k]);
      oldBlue[k]  = upDown(newBlue[k],   oldBlue[k]);
    }

    else if(newRed[k] - oldRed[k] == 0 && newGreen[k] - oldGreen[k] == 0 && newBlue[k] - oldBlue[k] == 0)
    {
      chooseNewColour(k);
    }

    for(int a = 3;  a <= 8;  a ++) currentLED[a].setRGB(oldRed[0], oldGreen[0], oldBlue[0]); // Zone 1
    for(int a = 14; a <= 19; a ++) currentLED[a].setRGB(oldRed[1], oldGreen[1], oldBlue[1]); // Zone 2
    for(int a = 25; a <= 30; a ++) currentLED[a].setRGB(oldRed[2], oldGreen[2], oldBlue[2]); // Zone 3
    for(int a = 36; a <= 41; a ++) currentLED[a].setRGB(oldRed[3], oldGreen[3], oldBlue[3]); // Zone 4
    for(int a = 47; a <= 52; a ++) currentLED[a].setRGB(oldRed[4], oldGreen[4], oldBlue[4]); // Zone 5


    
    FastLED.show();
  }

  delay(10);
}
*/


/*
V2 Individual
void loop()
{
  for(int k = 0; k < totalLEDs; k ++)
  {
    if(newRed[k] - oldRed[k] != 0 || newGreen[k] - oldGreen[k] != 0 || newBlue[k] - oldBlue[k] != 0)
    {
      oldRed[k]   = upDown(newRed[k], oldRed[k]);
      oldGreen[k] = upDown(newGreen[k], oldGreen[k]);
      oldBlue[k]  = upDown(newBlue[k], oldBlue[k]);
    }

    else if(newRed[k] - oldRed[k] == 0 && newGreen[k] - oldGreen[k] == 0 && newBlue[k] - oldBlue[k] == 0)
    {
      chooseNewColour(k);
    }


    currentLED[k].setRGB(oldRed[k], oldGreen[k], oldBlue[k]);
    FastLED.show();
  }


  delay(0);
}
*/


V1 all together
void loop()
{
  k = 5;

  if(newRed[k] - oldRed[k] != 0 || newGreen[k] - oldGreen[k] != 0 || newBlue[k] - oldBlue[k] != 0)
  {
    oldRed[k]   = upDown(newRed[k], oldRed[k]);
    oldGreen[k] = upDown(newGreen[k], oldGreen[k]);
    oldBlue[k]  = upDown(newBlue[k], oldBlue[k]);
  }

  else if(newRed[k] - oldRed[k] == 0 && newGreen[k] - oldGreen[k] == 0 && newBlue[k] - oldBlue[k] == 0)
  {
    chooseNewColour(k);
  }

  for(int i = 0; i < totalLEDs; i ++)
  {
    currentLED[i].setRGB(oldRed[k], oldGreen[k], oldBlue[k]);
  }
  FastLED.show();


  delay(6);
}
