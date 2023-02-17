#include "FastLED.h"
#define NUM_LEDS 55
CRGB leds[NUM_LEDS];

void Fire(int Cooling, int Sparking, int SpeedDelay); 
void setPixelHeatColor(int Pixel, byte temperature);
void showStrip();
void setPixel(int Pixel, byte red, byte green, byte blue);

void setAll(byte red, byte green, byte blue);

void setup()
{
  FastLED.addLeds<APA102, BGR >(leds, NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop() 
{
  byte colors[3][3] = { {0xff, 0x00, 0x00}, 
                        {0xff, 0xff, 0xff}, 
                        {0x00, 0x00, 0xff} };

  BouncingColoredBalls(3, colors, false);
}

void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) 
{
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );

  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];

  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  
  boolean ballBouncing[BallCount];
  boolean ballsStillBouncing = true;
  
  for (int i = 0 ; i < BallCount ; i++) 
  {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0; 
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
    ballBouncing[i]=true; 
  }

  while (ballsStillBouncing) 
  {
    for (int i = 0 ; i < BallCount ; i++) 
    {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) 
      {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) 
        {
          if (continuous) 
          {
            ImpactVelocity[i] = ImpactVelocityStart;
          } 

          else 
          {
            ballBouncing[i]=false;
          }
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    ballsStillBouncing = false; // assume no balls bouncing

    for (int i = 0 ; i < BallCount ; i++) 
    {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);

      if ( ballBouncing[i] ) 
      {
        ballsStillBouncing = true;
      }
    }
    
    showStrip();
    setAll(0,0,0);
  }
}

void setAll(byte red, byte green, byte blue) 
{
  for(int i = 0; i < NUM_LEDS; i++ ) 
  {
    setPixel(i, red, green, blue); 
  } 
  showStrip();
}

void setPixel(int Pixel, byte red, byte green, byte blue) 
{
 leds[NUM_LEDS - Pixel].r = red;
 leds[NUM_LEDS - Pixel].g = green;
 leds[NUM_LEDS - Pixel].b = blue;
}

void showStrip() 
{ 
  FastLED.show();
}