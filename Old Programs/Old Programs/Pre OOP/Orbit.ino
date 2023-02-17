////////////////////////////////////////////////////////////////////////
//  Matthew Kavanagh 
// 
//  Orbit 
//  Orbit V2.ino
//  2018
//  *********
////////////////////////////////////////////////////////////////////////
// Notes
// 
// Old Method - 20784 bytes (7%)
// New Method - 20624 bytes (7%)
//
// Hardware SPI used, no need to specify connections
//
////////////////////////////////////////////////////////////////////////
//  ###                                                  
//   #  #    #  ####  #      #    # #####  ######  ####  
//   #  ##   # #    # #      #    # #    # #      #      
//   #  # #  # #      #      #    # #    # #####   ####  
//   #  #  # # #      #      #    # #    # #           # 
//   #  #   ## #    # #      #    # #    # #      #    # 
//  ### #    #  ####  ######  ####  #####  ######  ####  
//
////////////////////////////////////////////////////////////////////////
#include <Streaming.h>
#include <FastLED.h>
#include "Images.h"
#include "OneButton.h"


////////////////////////////////////////////////////////////////////////
//
//  ######                                                        
//  #     # ###### ###### # #    # # ##### #  ####  #    #  ####  
//  #     # #      #      # ##   # #   #   # #    # ##   # #      
//  #     # #####  #####  # # #  # #   #   # #    # # #  #  ####  
//  #     # #      #      # #  # # #   #   # #    # #  # #      # 
//  #     # #      #      # #   ## #   #   # #    # #   ## #    # 
//  ######  ###### #      # #    # #   #   #  ####  #    #  #### 
//
////////////////////////////////////////////////////////////////////////
#define totalLEDs     55 // Defined in Images.h

#define LEDBrightness 1 // As a percentage
#define powerLED      13

#define OFF LOW
#define ON HIGH

#define redVal   0
#define greenVal 1
#define blueVal  2

#define buttonPin 24

#define width(array) sizeof(array) / sizeof(array[0])

#define drawPicture(time, picture) drawImage(time, picture, sizeof(picture) / sizeof(picture[0]))

////////////////////////////////////////////////////////////////////////
//
//  #     #                                                  
//  #     #   ##   #####  #####  #    #   ##   #####  ###### 
//  #     #  #  #  #    # #    # #    #  #  #  #    # #      
//  ####### #    # #    # #    # #    # #    # #    # #####  
//  #     # ###### #####  #    # # ## # ###### #####  #      
//  #     # #    # #   #  #    # ##  ## #    # #   #  #      
//  #     # #    # #    # #####  #    # #    # #    # ######
//
////////////////////////////////////////////////////////////////////////
CRGB currentLED[totalLEDs]; // RGB singleColourur space
// OneButton button(buttonPin, false);

////////////////////////////////////////////////////////////////////////
//
// ######  
// #     # #####   ####  #####  ####  ##### #   # #####  ######  ####
// #     # #    # #    #   #   #    #   #    # #  #    # #      #
// ######  #    # #    #   #   #    #   #     #   #    # #####   ####
// #       #####  #    #   #   #    #   #     #   #####  #           #
// #       #   #  #    #   #   #    #   #     #   #      #      #    #
// #       #    #  ####    #    ####    #     #   #      ######  ####
//
////////////////////////////////////////////////////////////////////////
// Image Drawing
void drawImage(unsigned long time, const char picture[][totalLEDs][3], int pictureWidth);

// General Effects
// void rainbow();
void crissCross();

void pictures();

// button
void myClickFunction();

void rainbow();
void resetAll();
////////////////////////////////////////////////////////////////////////
//
//  #     #                                                    
//  #     #   ##   #####  #   ##   #####  #      ######  ####  
//  #     #  #  #  #    # #  #  #  #    # #      #      #      
//  #     # #    # #    # # #    # #####  #      #####   ####  
//   #   #  ###### #####  # ###### #    # #      #           # 
//    # #   #    # #   #  # #    # #    # #      #      #    # 
//     #    #    # #    # # #    # #####  ###### ######  #### 
//
////////////////////////////////////////////////////////////////////////
// Now defined in Images.h

unsigned int lastTime;
int state = 1; // used to determine the current state of the poi
int maxStates = 2;

// Rainbow variables
int rainbowStep     = 0;
int rainbowLED      = 0;
int rainbowInterval = 2;
unsigned rainbowMillis   = 0;

// In out variables
int inOutStep = 0;
int inOutInterval = 50;
unsigned inOutMillis = 0;


////////////////////////////////////////////////////////////////////////
//
//  ######                                                #####                                          
//  #     # #####   ####   ####  #####    ##   #    #    #     # #####   ##   #####  ##### #    # #####
//  #     # #    # #    # #    # #    #  #  #  ##  ##    #         #    #  #  #    #   #   #    # #    #
//  ######  #    # #    # #      #    # #    # # ## #     #####    #   #    # #    #   #   #    # #    #
//  #       #####  #    # #  ### #####  ###### #    #          #   #   ###### #####    #   #    # #####  
//  #       #   #  #    # #    # #   #  #    # #    #    #     #   #   #    # #   #    #   #    # #      
//  #       #    #  ####   ####  #    # #    # #    #     #####    #   #    # #    #   #    ####  #      
//
////////////////////////////////////////////////////////////////////////
void setup() 
{
  delay(200);

  Serial.begin(115200);

  FastLED.addLeds<APA102, BGR >(currentLED, totalLEDs);
  FastLED.setBrightness(LEDBrightness * 2.55);
  // FastLED.setDither( 0 ); // Need to play around with this

  // pinMode(powerLED, OUTPUT);
  // digitalWrite(powerLED, ON);

  // button.attachClick(myClickFunction);
  // button.setDebounceTicks(80);

  Serial << "ready" << endl;
}

///////////////////////////////////////////////////////////////////////
//
//  #     #                    ######                                            
//  ##   ##   ##   # #    #    #     # #####   ####   ####  #####    ##   #    # 
//  # # # #  #  #  # ##   #    #     # #    # #    # #    # #    #  #  #  ##  ## 
//  #  #  # #    # # # #  #    ######  #    # #    # #      #    # #    # # ## # 
//  #     # ###### # #  # #    #       #####  #    # #  ### #####  ###### #    # 
//  #     # #    # # #   ##    #       #   #  #    # #    # #   #  #    # #    # 
//  #     # #    # # #    #    #       #    #  ####   ####  #    # #    # #    # 
//
//////////////////////////////////////////////////////////////////////
void loop() 
{
  crissCross();
  // rainbow();
  // switch (state)
  // {
  //   case 1:
  //     // rainbow();
  //     // inOut();
  //     break;

  //   case 2:
  //     // inOut();
  //     break;

  //   // case 3:
  //   //   // pictures();
  //     // break;
  // }
  


	// if(state == 1)
	// {
	// 	// rainbow();
	// }
	// else if(state == 2)
	// {
	// 	singleColour();
	// }
  // button.tick();
	
}
// void pictures()
// {
//   // drawPicture(Time, Image);
//   drawPicture(10,squares);
// }

// void myClickFunction() 
// {
//   resetAll();
//   if(state < maxStates)
//   {
//     state ++;
//   }
//   else
//   {
//     state = 1;
//   }
  
//   Serial << "Button Clicked \t" << state << endl;
// }


// void resetAll()
// {
//   rainbowStep = 0;
//   inOutStep = 0;
//   Serial << "Resetting" << endl;

//   for(int i = 0; i < totalLEDs; i ++)
//   {
//     // Serial << "Resetting LED: " << i << endl;
//     currentLED[i] = 0x000000;
//   }
//   FastLED.show();
// }

