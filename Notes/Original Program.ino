/*
*This sketch outputs images to persistence of vision led strips
*It uses FastLed to drive APA102 leds, sending colour values from
*arrays held in flash memory (designated by 'const'). You need to
*set the number of slices you have made your image into,
*e.g. bmp image of 60 pixels high by 150 wide
* would give 60 num_leds and
* 150 slices (number of slices you have made your image into)
*/

#include "FastLED.h"

#define NUM_LEDS 60
#define DATA_PIN 2
#define CLOCK_PIN 3
CRGB leds[NUM_LEDS];
int numberOfSlices = 150;

void setup() {

delay(200);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
}

const unsigned int array1[] = { 0x000100, 0x000100, 0x000100, 0x000100, 0x000100, 0x000100, /*etc .. add your values here*/}; //end of array

const unsigned int array2[] = { /*different image output from the tool goes here if additional images wanted - just rename array1[] to another name, any name will do*/}; //end of array

void loop() {
PoiSonic(8000,array1);
//PoiSonic(2000, array2); 
/*first value is time to show the image, second value is array of colour values to use*/
/*put other code for patterns and more arrays here*/
}

void PoiSonic(unsigned long time, const unsigned int array[]){
unsigned long currentTime = millis();
 while (millis()< currentTime + (time)) {

int f= numberOfSlices;
int z; //a counter
int j=NUM_LEDS;

    for (int x=0;x<f;x++){
     for(z=NUM_LEDS;z>0;z--){
       leds[z-1]=array[x+((j-z)*f)];}
     FastLED.show();
     delayMicroseconds(40); //may need to increase / decrease depending on spin rate
     }       
    delayMicroseconds(1000); //may need to increase / decrease depending on spin rate
   }
 }