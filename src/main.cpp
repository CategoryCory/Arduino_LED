#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define LED_PIN     13
#define HUE_PIN     A0
#define SAT_PIN     A1
#define VAL_PIN     A2
#define NUM_PIXELS  1
#define LCD_RS      12
#define LCD_ENABLE  11
#define LCD_DB4     5
#define LCD_DB5     4
#define LCD_DB6     3
#define LCD_DB7     2

float hue = 0;
float sat = 0;
float val = 0;

Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_RGB);
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup()
{
  Serial.begin(9600);
  pixels.begin();
  pixels.clear();
  lcd.begin(16, 2);
  lcd.print("Hello World");
}

void loop() 
{
  hue = (analogRead(HUE_PIN) / 1023.0) * 65535;
  sat = (analogRead(SAT_PIN) / 1023.0) * 255;
  val = (analogRead(VAL_PIN) / 1023.0) * 255;

  pixels.setPixelColor(0, pixels.ColorHSV(hue, sat, val));
  pixels.show();

  Serial.print("HSV(");
  Serial.print(hue / 65535.0 * 360);
  Serial.print(", ");
  Serial.print(sat / 255.0 * 100);
  Serial.print(", ");
  Serial.print(val / 255.0 * 100);
  Serial.print(")");
  Serial.println();

  delay(1000);
}
