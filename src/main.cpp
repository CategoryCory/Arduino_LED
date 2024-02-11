#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     2
#define HUE_PIN     A0
#define SAT_PIN     A1
#define VAL_PIN     A2
#define NUM_PIXELS  1

float hue = 0;
float sat = 0;
float val = 0;

Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_RGB);

void setup()
{
  pixels.begin();
  pixels.clear();
}

void loop() 
{
  hue = (analogRead(HUE_PIN) / 1023.0) * 65535;
  sat = (analogRead(SAT_PIN) / 1023.0) * 255;
  val = (analogRead(VAL_PIN) / 1023.0) * 255;

  pixels.setPixelColor(0, pixels.ColorHSV(hue, sat, val));
  pixels.show();
}
