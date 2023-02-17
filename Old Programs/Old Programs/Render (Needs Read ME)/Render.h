#ifndef RENDER_H
#define RENDER_H
#include "FastLED.h"
// #include "OneButton.h"

class Render
{
	public:
		Render(int totalLEDs, CRGB *currentLED);

    // need to change the 55 to totalLEDs somehow
		void drawImage(unsigned long time, const char picture[][55][3], int pictureWidth); 
    void reset();

	private:
		CRGB *currentLED; // LED strip object
    // OneButton button; // Button object

    int totalLEDs; 
    int currentTime;

    int column;

    // Timing Stuff
    long currentMillis;
    long lastMillis;

    int interval;

};
#endif