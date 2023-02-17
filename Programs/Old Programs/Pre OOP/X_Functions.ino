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
void crissCross()
{
  unsigned long currentMillis = millis();

  // Serial << inOutStep << "\t" << endl;

  // Multiply first to remove rounding in an int 
  // currentLED[inOutStep].setHue((255 * (inOutStep + 1)) / totalLEDs);
  currentLED[inOutStep].setHue(255);

  // currentLED[totalLEDs - inOutStep - 1].setHue(255 - ((255 * (inOutStep + 1)) / 55));

  FastLED.show();  

  if(currentMillis - inOutMillis >= inOutInterval) // if time has elapsed go to next led
  {
    inOutMillis = currentMillis; // take new time
    currentLED[inOutStep] = 0x000000;
    // currentLED[totalLEDs - inOutStep - 1] = 0x000000;

    FastLED.show();

    // Serial << inOutStep << "\t";
    
    if(inOutStep < 55) 
    {
      Serial << "Now" << " ";
      inOutStep ++;
    }
    else
    {
      Serial << "Here" << " ";
      inOutStep = 0;
    }

    Serial << inOutStep << endl;
  }
}


void rainbow()
{
  unsigned long currentMillis = millis();

  if(currentMillis - rainbowMillis >= rainbowInterval) 
  {
    rainbowMillis = currentMillis;

    if(rainbowStep < 255)
    {
      for(int i = 0; i < totalLEDs; i ++)
      {
        currentLED[i].setHue(rainbowStep - i * (255 / totalLEDs));  
        FastLED.show();
      }
      rainbowStep ++;
    }

    else 
    {
      rainbowStep = 0;
    }
  }
}