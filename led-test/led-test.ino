#include <FastLED.h>
#define NUM_LEDS 10
#define DATA_PINS 10
#define t 2000 / 9

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PINS>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i == NUM_LEDS - 2) {
      leds[i] = CRGB::Green; FastLED.show(); delay(t);
    } else {
      leds[i] = CRGB::Red; FastLED.show(); delay(t);
    }
    leds[i] = CRGB::Black; FastLED.show();
  }

}
