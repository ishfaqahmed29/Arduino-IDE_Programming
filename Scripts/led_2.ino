#include "FastLED.h"
#define NUM_LEDS 50

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI

#define DATA_PIN 4
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup() {
    
    delay(2000);
    
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); 
   
}

void loop() {

  for(int i = 0; i < 40; i++){
    leds[i] = CRGB(255,80,255);
  }
    FastLED.show();
    delay(1000);

  for(int i = 0; i < 40; i++){
    leds[i] = CRGB(56,240,165);
  }
  FastLED.show();
  delay(3000);

  for(int i = 0; i < 40; i++){
    leds[i] = CRGB(155,120,255);
  }
  FastLED.show();
  delay(3000);

  for(int i = 0; i < 40; i++){
    leds[i] = CRGB(55,180,155);
  }
  FastLED.show();
  delay(3000);
}
