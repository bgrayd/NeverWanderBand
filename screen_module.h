//screen_module.h
#ifndef _SCREEN_MODULE_H_
#define _SCREEN_MODULE_H_

#include "pic24_all.h"


#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64
#define LCDWIDTH 128
#define LCDHEIGHT 64

#define BLACK 0
#define WHITE 1
#define INVERSE 2

void drawFastVLine(int16_t x, int16_t __y, int16_t __h, uint16_t color);

typedef struct screenData_t{
	int16_t i16_x;
	int16_t i16_y;
	uint16_t u16_textColor;
	uint16_t u16_backgroundColor;
	uint8_t u8_textSize;
	uint8_t b_wrap;
	int16_t i16_width;
	int16_t i16_height;
	uint8_t u8_i2cAddr;
} screenData_t;

static screenData_t screenData;

void initScreen();




#endif  //_SCREEN_MODULE_H_