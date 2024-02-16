#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "color_types.h"

#define LED_PIN     13
#define BTN_PIN     2
#define HUE_PIN     A0
#define SAT_PIN     A1
#define VAL_PIN     A2
#define NUM_PIXELS  1
#define LCD_RS      3
#define LCD_ENABLE  4
#define LCD_DB4     8
#define LCD_DB5     9
#define LCD_DB6     10
#define LCD_DB7     11

AnalogColorValues analogValues;
NeoPixelColor neoPixelColor;
HSVColor hsvColor;
RGBColor rgbColor;

char hsv[17] = {};
char rgb[17] = {};

Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_RGB);
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void print_to_lcd(void)
{
  sprintf(hsv, "HSV(%d,%d,%d)", hsvColor.hue, hsvColor.sat, hsvColor.val);
  sprintf(rgb, "RGB(%d,%d,%d)", rgbColor.red, rgbColor.green, rgbColor.blue);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(hsv);
  lcd.setCursor(0, 1);
  lcd.print(rgb);
}

void setup()
{
  pinMode(BTN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), print_to_lcd, LOW);

  pixels.begin();
  pixels.clear();
  lcd.begin(16, 2);
  lcd.print("Awaiting input");
}

void loop()
{
  analogValues.analog_hue = analogRead(HUE_PIN);
  analogValues.analog_sat = analogRead(SAT_PIN);
  analogValues.analog_val = analogRead(VAL_PIN);

  neoPixelColor.led_hue = (analogValues.analog_hue * 65535) / 1023;
  neoPixelColor.led_sat = ((uint32_t)analogValues.analog_sat * 255) / 1023;
  neoPixelColor.led_val = ((uint32_t)analogValues.analog_val * 255) / 1023;

  hsvColor.hue = ((uint32_t)neoPixelColor.led_hue * 360) / 65535;
  hsvColor.sat = (neoPixelColor.led_sat * 100) / 255;
  hsvColor.val = (neoPixelColor.led_val * 100) / 255;

  hsv2rgb(&rgbColor, hsvColor.hue, hsvColor.sat, hsvColor.val);

  pixels.setPixelColor(0, pixels.ColorHSV(neoPixelColor.led_hue, neoPixelColor.led_sat, neoPixelColor.led_val));
  pixels.show();
}
