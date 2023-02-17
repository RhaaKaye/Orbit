#include "Render.h"
#include "Streaming.h"
#include "Arduino.h"
// #include "Images.h" // Uncomment this later
using namespace std;

Render::Render(int totalLEDs, CRGB *currentLED)
{
  this -> totalLEDs = totalLEDs;
  this -> currentLED = currentLED;
  // this -> button = button;
  column = 0;
}

void Render::drawImage(unsigned long time, const char picture[][55][3], int pictureWidth) 
{
  currentTime = millis(); // Get the current time (Unix Time)

  while(millis() < currentTime + (time * 1000)) 
  {
    if(column < pictureWidth)
    {
      for(int row = totalLEDs-1; row > -1; row --) // row number
      {
        currentLED[row].setRGB(
          picture[column] [row] [0], 
          picture[column] [row] [1], 
          picture[column] [row] [2]);
      }      
      FastLED.show();
      column ++;
      delayMicroseconds(800); // How wide the image is (800 seems good)
    }
    else
    {
      column = 0;
    }
    delayMicroseconds(1000); // Gap between images (1000 seems good)    
  }
  Serial << millis() - currentTime << endl;
}

void Render::reset()
{
  column = 0;
}