////////////////////////////////////////////////////////////////////////
//  Matthew Kavanagh 
// 
//  Orbit
//  Functions.ino
//  *********
////////////////////////////////////////////////////////////////////////
//
// ###                                 #####                                                         
//  #  #    #   ##    ####  ######    #     # ###### #    # ###### #####    ##   #####  ####  #####  
//  #  ##  ##  #  #  #    # #         #       #      ##   # #      #    #  #  #    #   #    # #    # 
//  #  # ## # #    # #      #####     #  #### #####  # #  # #####  #    # #    #   #   #    # #    # 
//  #  #    # ###### #  ### #         #     # #      #  # # #      #####  ######   #   #    # #####  
//  #  #    # #    # #    # #         #     # #      #   ## #      #   #  #    #   #   #    # #   #  
// ### #    # #    #  ####  ######     #####  ###### #    # ###### #    # #    #   #    ####  #    #
//
////////////////////////////////////////////////////////////////////////
// Leave this the fuck alone. It's working, don't go screwing around with it
void drawImage(unsigned long time, const char picture[][totalLEDs][3], int pictureWidth) 
{
  unsigned long currentTime = millis(); // Get the current time (Unix Time)

  while(millis() < currentTime + (time * 1000)) 
  {
    for(int column = 0; column < pictureWidth; column ++)
    {
      for(int row = totalLEDs-1; row > -1; row --) // row number
      {
        currentLED[row].setRGB(
          picture[column] [row] [redVal], 
          picture[column] [row] [greenVal], 
          picture[column] [row] [blueVal]);
      }      
      FastLED.show();
      delayMicroseconds(800); // How wide the image is (800 seems good)
    }
    delayMicroseconds(1000); // Gap between images (1000 seems good)
  }
}

////////////////////////////////////////////////////////////////////////
//
//   #####                           #######                                          
//  #     # ##### #####  # #####     #       ###### ###### ######  ####  #####  ####  
//  #         #   #    # # #    #    #       #      #      #      #    #   #   #      
//   #####    #   #    # # #    #    #####   #####  #####  #####  #        #    ####  
//        #   #   #####  # #####     #       #      #      #      #        #        # 
//  #     #   #   #   #  # #         #       #      #      #      #    #   #   #    # 
//   #####    #   #    # # #         ####### #      #      ######  ####    #    #### 
//
//////////////////////////////////////////////////////////////////////// 
void startupEffect()
{
  int colour;
  for(int i = 0; i < 3; i ++) // A choice of colours
  {
    if(i == 0)      colour = 0xff0000; // red
    else if(i == 1) colour = 0xffa500; // orange
    else if(i == 2) colour = 0x00ff00; // green

    for(int led = 0; led < totalLEDs; led ++)
    {
      currentLED[led] = colour;
      FastLED.show();
      delay(25);
    }
  }

  off();
  delay(100);

  green();
  delay(200);

  off();
  delay(300);
}

void green()
{
  for(int led = 0; led < totalLEDs; led ++)
  {
    currentLED[led] = 0x00ff00;
  }
  FastLED.show(); 
}

void off()
{
  for(int led = 0; led < totalLEDs; led ++)
  {
    currentLED[led] = 0x000000;
  }
  FastLED.show();
}

void rainbow()
{
  for(int colour = 0; colour <= 255; colour ++) // the fast led library uses 0 to 255)
  {
    // button.tick();
    for(int i = 0; i < totalLEDs; i ++)
    {
      button.tick();
      currentLED[i].setHue(colour - i * (255 / totalLEDs));      
    }
    FastLED.show();
    delay(20);
  }

  // if(rainbowColour < 255)
  // {
  //   if(rainbowLED < totalLEDs)
  //   {
  //     currentLED[rainbowLED].setHue(colour - rainbowLED * (255 / totalLEDs));  
  //     rainbowLED ++;
  //   }
  //   else rainbowLED = 0;
  //   rainbowColour ++;
  // }
  // else rainbowColour = 0;
}

void singleColour()
{
  for(int i = 0; i < totalLEDs; i ++)
  {
    button.tick();
    currentLED[i] = CRGB::Red;
  }
  FastLED.show();
}


//////////////////////////////////////////////////////////////////////////////
// #     #                   #####                                          
// ##    # ###### #    #    #     # #####   ##   #####  ##### #    # #####  
// # #   # #      #    #    #         #    #  #  #    #   #   #    # #    # 
// #  #  # #####  #    #     #####    #   #    # #    #   #   #    # #    # 
// #   # # #      # ## #          #   #   ###### #####    #   #    # #####  
// #    ## #      ##  ##    #     #   #   #    # #   #    #   #    # #      
// #     # ###### #    #     #####    #   #    # #    #   #    ####  #      
//                                                                         
//////////////////////////////////////////////////////////////////////////////
void inOut()
{
  int off = 0x000000;

  for(int led = 0; led < totalLEDs; led ++)
  {
    currentLED[led].setHue((255 * (led + 1)) / 55); // Multiply first to remove rounding in an int 
    currentLED[totalLEDs - led - 1].setHue(255 - ((255 * (led + 1)) / 55));

    FastLED.show();

    delay(50);

    currentLED[led] = off;
    currentLED[totalLEDs - led - 1] = off;

    FastLED.show();
  }
}

void threeDown()
{
  int numLEDs = 3;

  // for(int i = 0; i < numLEDs; i ++)
  // {
  //   for(int j = 0; j < 15; j ++) // move down
  //   {
  //     currentLED[((totalLEDs / numLEDs) * i) + j] = 0xff0000;
  //     FastLED.show();      
  //   }
  //   delay(100);
  // }

  for(int i = 0; i < totalLEDs; i ++)
  {
    for(int j = 0; j < 255; j ++)
    {
      currentLED[i].setRGB(j,0,0);
      FastLED.show();
      delayMicroseconds(10);
    }

    delayMicroseconds(1);

    for(int d = 255; d >= 0; d --)
    {
      currentLED[i].setRGB(d,0,0);
      FastLED.show();
      delayMicroseconds(10);
    }

      // currentLED[i] = 0x000000;
      // FastLED.show();
  }
}

void newStartupEffectTwo()
{
  for(int j = 0; j < 255; j ++)
  {
    for(int i = 0; i < totalLEDs; i ++)
    {
      currentLED[i].setHue(j);
      FastLED.show();
    }
  }
}

void fadeDown()
{
  int numOfLEDs   = 10;
  int startingLED = 10;


  for(int i = startingLED; i >= startingLED - numOfLEDs; i --)
  {
    currentLED[i].setRGB((255 / numOfLEDs) * i, 0, 0);
  }
  FastLED.show();
}

void tester() // used as a tester program
{
  for(int i = 0; i < totalLEDs; i ++)
  {
    unsigned long currentTime = millis();

    if(currentTime - lastTime >= + 1 * 1000)
    {
      lastTime = currentTime;
      currentLED[i] = 0xff0000;
      FastLED.show();
      delay(2);

      currentLED[i] = 0x000000;
      FastLED.show();
      Serial << i << "Here" << endl;
    }
  }
}

void speeder() // used as a tester program
{
  for(int i = 0; i < totalLEDs; i ++)
  {
    currentLED[i] = 0xff0000;
    FastLED.show();
    delay(20);

    currentLED[i] = 0x000000;
    FastLED.show();
  }
}

////////////////////////////////////////////////////////////
//
// ######                                                  
// #     # #####  ######   ##   ##### #    # ###### #####  
// #     # #    # #       #  #    #   #    # #      #    # 
// ######  #    # #####  #    #   #   ###### #####  #    # 
// #     # #####  #      ######   #   #    # #      #####  
// #     # #   #  #      #    #   #   #    # #      #   #  
// ######  #    # ###### #    #   #   #    # ###### #    # 
//
////////////////////////////////////////////////////////////
void breather()
{
  for(int colour = 0; colour <= 255; colour ++)
  {
    unsigned long currentTime = millis();
    Serial << "Current Time: " << currentTime << endl;

    while(millis() < currentTime + 2 * 1000) // multiply by 1000 to get seconds
    {
      Serial << "New Time: " << millis() << endl;
      for(int LED = 0; LED < totalLEDs; LED ++)
      {
        currentLED[LED].setHue(colour);
      }
      // Serial << colour << endl;
      FastLED.show();
    }
  }
}