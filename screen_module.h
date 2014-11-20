//screen_module.h
#ifndef _SCREEN_MODULE_H_
#define _SCREEN_MODULE_H_

#include "pic24_all.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64
#define LCDWIDTH 128
#define LCDHEIGHT 64

#define BLACK 0
#define WHITE 1
#define INVERSE 2

#define SWITCH1_DOWN	(_RB14 == 0)
#define SWITCH1_UP	(_RB14 == 1)

#define BUTTON1_PRESSED	(_RB0 == 0)
#define BUTTON1_RELEASED	(_RB0 == 1)

#define BUTTON2_PRESSED	(_RB1 == 0)
#define BUTTON2_RELEASED	(_RB1 == 1)

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

void display(void);
void writeString(char* psz_s1);
void clearDisplay(void);
void setTextColor(uint16_t c);  ////
void setTextSize(uint8_t s);
void drawArrowN(void);
void drawArrowNE(void);
void drawArrowE(void);
void drawArrowSE(void);
void drawArrowS(void);
void drawArrowSW(void);
void drawArrowW(void);
void drawArrowNW(void);
void writeDistance(char* psz_s2);
void setCursor(int16_t x, int16_t y);
void invertDisplay(uint8_t i);
void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
void drawFastVLine(int16_t x, int16_t __y, int16_t __h, uint16_t color);
void drawFastVLine(int16_t x, int16_t __y, int16_t __h, uint16_t color);
void proximity20(void);
void proximity30(void);
void proximity40(void);
void proximity50(void);



#endif  //_SCREEN_MODULE_H_

