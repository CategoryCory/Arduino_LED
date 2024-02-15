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

LEDColor ledColor;
HSVColor hsvColor;
RGBColor rgbColor;

char hsv[32] = {};
char rgb[32] = {};

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
  ledColor.led_hue = (uint16_t)((analogRead(HUE_PIN) / 1023.0) * 65535);
  ledColor.led_sat = (uint8_t)((analogRead(SAT_PIN) / 1023.0) * 255);
  ledColor.led_val = (uint8_t)((analogRead(VAL_PIN) / 1023.0) * 255);

  hsvColor.hue = (uint16_t)(ledColor.led_hue / 65535.0 * 360);
  hsvColor.val = (uint8_t)(ledColor.led_val / 255.0 * 100);
  hsvColor.sat = (uint8_t)(ledColor.led_sat / 255.0 * 100);

  hsv2rgb(&rgbColor, hsvColor.hue, hsvColor.sat, hsvColor.val);

  pixels.setPixelColor(0, pixels.ColorHSV(ledColor.led_hue, ledColor.led_sat, ledColor.led_val));
  pixels.show();
}
