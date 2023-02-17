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
#include <FastLED.h>        //https://github.com/FastLED/FastLED
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
#define ON  LOW
#define OFF HIGH // Inverse logic, active low 

#define LEDBrightness 10
#define totalLEDs     8
#define powerLED      D4
#define data          D6

#define width(array) sizeof(array) / sizeof(array[0])

#define drawPicture(time, picture) drawImage(time, picture, sizeof(picture) / sizeof(picture[0]))

#define redVal   0
#define greenVal 1
#define blueVal  2



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
CRGB currentLED[totalLEDs*5]; // RGB colour space

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
String inString;

char dataIn;

int dataSize;
int pictureWidth;

int slice = 0;

char testBuffer[3];


char test[][totalLEDs][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {237, 28, 36}, {237, 28, 36}, {0, 0, 0}, {0, 162, 232}, {0, 0, 0}}, {{0, 0, 0}, {255, 242, 0}, {0, 0, 0}, {0, 0, 0}, {237, 28, 36}, {237, 28, 36}, {0, 162, 232}, {0, 0, 0}}, {{163, 73, 164}, {163, 73, 164}, {163, 73, 164}, {163, 73, 164}, {163, 73, 164}, {163, 73, 164}, {163, 73, 164}, {163, 73, 164}}, {{0, 0, 0}, {0, 0, 0}, {0, 162, 232}, {0, 162, 232}, {0, 0, 0}, {0, 0, 0}, {237, 28, 36}, {0, 0, 0}}, {{0, 162, 232}, {0, 162, 232}, {0, 162, 232}, {0, 0, 0}, {255, 242, 0}, {255, 242, 0}, {237, 28, 36}, {0, 0, 0}}};
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
  Serial << endl;

  FastLED.addLeds<NEOPIXEL, data>(currentLED, (totalLEDs * 5));
  FastLED.setBrightness(LEDBrightness * 2.55);
  // FastLED.setCorrection(TypicalLEDStrip);

  pinMode(powerLED, OUTPUT);
  digitalWrite(powerLED, OFF);   
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

  // while(Serial.available())
  // {
  //   char ch = Serial.read();
  //   Serial << ch << endl;
  // }
  int startChar = Serial.read();

  if(startChar == '&')
  {
    int count = Serial.readBytes(testBuffer, 3);
  }

  else if(startChar == '*')
  {
    // for(int i = 0; i < 4; i ++)
    // {
    //   Serial << testBuffer[i] << endl;
    // }
    // Serial << testBuffer << endl;
    Serial.println(testBuffer);
  }

  else if(startChar >= 0) 
  {
    // Discard unknown characters
  }


	// drawImage(5, test, width(test));

  // Serial << FastLED.getFPS() << endl;



	// while(Serial.available() > 0)
	// {
	// 	dataSize = Serial.read();

 //    switch(dataSize)
 //    {
 //      case 42: Serial << "* was pressed" << endl; break;

 //    }
	// 	Serial << "Serial data read in: " << dataSize << endl;
	// }

	// // if(strcmp(inString, "Hello") == 0)  // Compares the difference between 2 strings (0 means identicle)
	// // {
	// // 	Serial << "Hello was recieved" << endl;
	// // }

	// Serial << dataSize << endl;
	
}

void drawImage(unsigned long time, char pattern[][totalLEDs][3], int pictureWidth)
{

	unsigned long currentTime = millis();

	while(millis() < currentTime + (time * 1000))
	{
    Serial << "Running" << endl;
		for(int slice = 0; slice < pictureWidth; slice ++)
		{
			for(int LED = totalLEDs - 1; LED > - 1; LED --)
			{
				currentLED[(slice * 8) + LED].setRGB(pattern[slice] [LED] [redVal], 
                                             pattern[slice] [LED] [greenVal], 
                                             pattern[slice] [LED] [blueVal]);
				// delay(100);
			}

			FastLED.show();
		}
    delay(1);  // Prevents a WTR
	}
}

// void serialEvent()
// {
//   while(Serial.available())
//   {
//     char ch = Serial.read();
//     Serial << ch << endl;
//   }
//   Serial << "Event Occured" << endl;
// }