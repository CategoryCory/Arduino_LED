#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     2
#define POT_PIN     A3
#define NUM_PIXELS  3

int potValue = 0;

Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_RGB);

void setup()
{
  pixels.begin();
  pixels.clear();
}

void loop() 
{
  potValue = analogRead(POT_PIN) * 65535 / 1023;

  for (int i = 0; i < NUM_PIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.ColorHSV((potValue + (i * 65535 / 3)) % 65535, 255, 8));
    pixels.show();
  }
}
