/*
 * LEDDriver.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Omri Iluz
 */

#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

#include "hal.h"

#define sign(x) (( x > 0 ) - ( x < 0 ))

typedef struct Color Color;
struct Color {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

void ledDriverInit(int leds, GPIO_TypeDef *port, uint32_t mask, uint8_t **o_fb);
void setColorRGB(Color c, uint8_t *buf, uint32_t mask);
void testPatternFB(uint8_t *fb);
#endif /* LEDDRIVER_H_ */
