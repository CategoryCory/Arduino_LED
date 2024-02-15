#ifndef COLOR_TYPES_H_
#define COLOR_TYPES_H_

#include <stdint.h>

typedef struct {
  uint16_t led_hue;
  uint8_t led_sat;
  uint8_t led_val;
} LEDColor;

typedef struct {
  uint16_t hue;
  uint8_t sat;
  uint8_t val;
} HSVColor;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} RGBColor;

void hsv2rgb(RGBColor * const rgb, uint16_t hue, uint8_t sat, uint8_t val);

#endif      // COLOR_TYPES_H_