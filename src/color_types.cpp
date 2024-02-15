#include <math.h>
#include "color_types.h"

void hsv2rgb(RGBColor * const rgb, uint16_t hue, uint8_t sat, uint8_t val)
{
    float r, g, b;
	
	float h = hue / 360.0;
	float s = sat / 100.0;
	float v = val / 100.0;
	
	int i = floor(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);
	
	switch (i % 6) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}

	rgb->red = r * 255;
	rgb->green = g * 255;
	rgb->blue = b * 255;
}
