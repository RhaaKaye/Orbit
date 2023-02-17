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
// #include "OneButton.h"
// #include <stdlib.h>

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

#define LEDBrightness 10 // As a percentage
#define powerLED      13
#define data          2 // Yellow wire
#define clock         3 // Green wire

#define OFF LOW
#define ON HIGH

#define redVal   0
#define greenVal 1
#define blueVal  2

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
CRGB currentLED[totalLEDs]; // RGB colour space
OneButton button(24, false);
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

// Startup Effects
void startupEffect();
void newStartupEffect();

void newStartupEffectTwo();

// Colours
void green();
void off();

// General Effects
void rainbow();
void singleColour();
void inOut();
void threeDown();

void fadeDown();

void tester();
void speeder();

void breather();

// button
void myClickFunction();

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
// int off = 0x000000;

uint32_t colours[24] = { // https://www.w3schools.com/colors/colors_picker.asp
            0xff4000, 0xff8000, 0xffbf00, 0xffff00, 0xbfff00, 0x80ff00,
            0x40ff00, 0x00ff00, 0x00ff40, 0x00ff80, 0x00ffbf, 0x00ffff,
            0x00bfff, 0x0080ff, 0x0040ff, 0x0000ff, 0x4000ff, 0x8000ff,
            0xbf00ff, 0xff00ff, 0xff00bf, 0xff0080, 0xff0040, 0xff0000            
            };

unsigned int lastTime;
int state = 1;

int rainbowColour = 0;
int rainbowLED = 0;
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

  // FastLED.addLeds<APA102, data, clock, BGR >(currentLED, totalLEDs).setCorrection( 0xff0050  );
  // FastLED.addLeds<APA102, data, clock, BGR >(currentLED, totalLEDs);

  FastLED.addLeds<APA102, BGR >(currentLED, totalLEDs);
  FastLED.setBrightness(LEDBrightness * 2.55);
  FastLED.setDither( 0 ); // Need to play around with this

  pinMode(powerLED, OUTPUT);
  digitalWrite(powerLED, ON);

  button.attachClick(myClickFunction);

  button.setDebounceTicks(80);
  // rainbow();
  // startupEffect();

  // pinMode(24, INPUT_PULLUP);
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
	button.tick();

	if(state == 1)
	{
		rainbow();
	}
	else if(state == 2)
	{
		singleColour();
	}
	// if(!digitalRead(24))
	// {
	// 	Serial << "Working" << endl;
	// }
	// fadeDown();
	// inOut();

	// newStartupEffect();
	// breather();
	// srainbow();
	// speeder();
	// threeDown();
	// rainbow();
	// drawImage(15,Logo, width(Logo));

	// drawPicture(10, squares);
	// drawPicture(10, AX);
	// drawPicture(10, X);
	// drawPicture(10, BB);
	// drawPicture(10, BY);
	// drawPicture(10, BW);
	// drawPicture(10, P);
	// drawPicture(10, BC);
	// drawPicture(10, AE);
	// drawPicture(10, AL);

	// drawPicture(10, BT);	
	// drawPicture(10, space);
	// drawPicture(10, ruby);
	// drawImage(10, AX, width(AX));
	// drawImage(10, B, width(B));
	// drawImage(10, C, width(C));
	// drawImage(10, D, width(D));
	// drawImage(10, E, width(E));
	// drawImage(10, F, width(F));
	// drawImage(10, G, width(G));
	// drawImage(10, H, width(H));

	
	// drawImage(10, Flag, width(Flag));

	// drawImage(10, Code, width(Code));

	// drawPicture(10, Code);

	

// drawImage(10, turt, width(turt));

	// drawImage(10, BB, width(BB));
	// drawImage(10, AX, width(AX));
	// drawImage(10, BL, width(BL));
	// drawImage(10, X , width(X));
	// drawImage(10, BY, width(BY));
	// drawImage(10, AG, width(AG));
	// drawImage(10, BW, width(BW));
	// drawImage(10, AH, width(AH));
	// drawImage(10, AT, width(AT));


	// rainbow();
	// singleColour();
}

void myClickFunction() 
{
	Serial << "Button Clicked" << endl;
  if (state == 1)
    state = 2;
  else
    state = 1;

  Serial << state << endl;
} // myClickFunction