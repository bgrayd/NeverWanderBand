//screen_module.c
//data - RB6
//clk - RB7
//D/C (SA0) - RB2
//Cs - RB3
//rst - RB5
//button1 - RB0
//button2 - RB1

#include "glcdfont.c"
#include "screen_module.h"
#include "pic24_all.h"


#define CONFIG_SLAVE_ENABLE() CONFIG_RB3_AS_DIG_OUTPUT()
#define SLAVE_ENABLE()          _LATB3 = 0  //low true assertion
#define SLAVE_DISABLE()         _LATB3 = 1
#define DCCONFIG()		CONFIG_RB2_AS_DIG_OUTPUT()
#define DCHIGH()		_LATB2 = 1
#define DCLOW()			_LATB2 = 0
#define ENABLE_SLAVE()		SLAVE_ENABLE()
#define DISABLE_SLAVE()		SLAVE_DISABLE()
#define RSTHIGH()               _LATB5 = 1
#define RSTLOW()		_LATB5 = 0

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x10
#define SSD1306_SWITCHCAPVCC 0x20

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x20

static inline void CONFIG_BUTTON1(){
	CONFIG_RB0_AS_DIG_INPUT();
	ENABLE_RB0_PULLUP();
	DELAY_US(1);
}


static inline void CONFIG_BUTTON2(){
	CONFIG_RB1_AS_DIG_INPUT();
	ENABLE_RB1_PULLUP();
	DELAY_US(1);
}


static inline void CONFIG_SWITCH1(){
	CONFIG_RB14_AS_DIG_INPUT();
	ENABLE_RB14_PULLUP();
	DELAY_US(1);
}



void configSPI1(void) {
  //spi clock = 40MHz/1*4 = 40MHz/4 = 10MHz
  SPI1CON1 = SEC_PRESCAL_1_1 |     //1:1 secondary prescale
             PRI_PRESCAL_4_1 |     //4:1 primary prescale
             CLK_POL_ACTIVE_HIGH | //clock active high (CKP = 0)
             SPI_CKE_ON          | //out changes active to inactive (CKE=1)
             SPI_MODE8_ON        | //8-bit mode
             MASTER_ENABLE_ON;     //master mode

  CONFIG_SDO1_TO_RP(6);      //use RP6 for SDO
  CONFIG_RP6_AS_DIG_PIN();   //Ensure that this is a digital pin
  CONFIG_SCK1OUT_TO_RP(7);   //use RP7 for SCLK
  CONFIG_RP7_AS_DIG_PIN();   //Ensure that this is a digital pin
  CONFIG_RB5_AS_DIG_OUTPUT();      //use RP5 for RST                   needs to be carefully removed
  CONFIG_RP5_AS_DIG_PIN();   //Ensure that this is a digital pin
  RSTHIGH();
  

  CONFIG_SLAVE_ENABLE();     //slave select config
  //CONFIG_SLAVE_ORDY();       //output ready from slave
  SLAVE_DISABLE();           //disable slave
  SPI1STATbits.SPIEN = 1;    //enable SPI mode
}

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

static uint8_t buffer[1024] = { 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x04, 0x0C, 0x18, 0x38, 0x78, 0x38, 0x30, 0xB0, 0x90, 0xC0, 0xC0, 0xE0, 0xE0,
0x60, 0x70, 0x70, 0x30, 0x30, 0x38, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E,
0x06, 0x06, 0x06, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8E, 0x9F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x9E, 0x8E, 0x86, 0x86, 0x86, 0x86, 0x06, 0x06, 0x06, 0x0E, 0x8E, 0x8C, 0x8C, 0xCC,
0xCC, 0x1C, 0x18, 0x18, 0x18, 0x38, 0x30, 0x30, 0x70, 0x60, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0x80,
0x80, 0x00, 0x20, 0x20, 0x60, 0x60, 0xF0, 0xF0, 0x70, 0x10, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0xC0, 0xE0, 0xF0, 0x78, 0x3C, 0x3C, 0x1E, 0x0E, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x81, 0x80, 0xC0,
0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x08, 0x0C, 0x04, 0x04, 0x06, 0x02, 0x02, 0x03, 0x83, 0x81,
0x81, 0xC1, 0x41, 0x41, 0x41, 0x40, 0x20, 0x20, 0x20, 0xA0, 0xA0, 0xA0, 0xE0, 0xE0, 0xE0, 0xE0,
0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFD, 0xFD, 0x7F, 0x3F, 0x1F, 0xCF, 0xFF, 0xFF, 0xFF, 0x3F,
0x06, 0x06, 0x04, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0xE0, 0xC0, 0xC0, 0x81, 0x01, 0x03,
0x03, 0x07, 0x0F, 0x0E, 0x1E, 0x3C, 0x78, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38, 0x3E, 0x3F, 0x3F,
0x27, 0x23, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xFC, 0x1E, 0x07, 0x03, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xB0, 0x98, 0xCC, 0xC6, 0xE2, 0xE1, 0xF1, 0xF1, 0xF0,
0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x02,
0x02, 0x04, 0x0C, 0x18, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0E,
0x7C, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x41, 0x43, 0x6F, 0x6F, 0x7F, 0x7E, 0x7C, 0x70,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x7C, 0xFC, 0xFC, 0xE4,
0x84, 0x04, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x67, 0x7F, 0x7F, 0xF0, 0xF0, 0xF8, 0x78, 0x7C,
0x7C, 0x7C, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F,
0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00,
0x80, 0xC0, 0x60, 0x30, 0x1E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0,
0xFC, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xC4, 0xE4, 0xFC, 0xFC, 0xFC, 0x7C, 0x0C,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07,
0x0F, 0x1F, 0x3E, 0x7C, 0x78, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x01, 0x03, 0x06, 0x0E,
0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x40, 0xC0, 0xC0, 0x80, 0x81, 0x81, 0x02, 0x02, 0x02,
0x04, 0x04, 0x04, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x09, 0x0B, 0x03, 0x17, 0x0E, 0x0E, 0x1C, 0x18,
0x38, 0x30, 0x70, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0xF8, 0xFF, 0xFF, 0x3F, 0x02, 0x03, 0x81, 0x81,
0x80, 0x80, 0xC0, 0x40, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x06, 0x06, 0x03, 0x03, 0x01,
0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0x78, 0x7C, 0x3E, 0x1F, 0x0F, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x40, 0x30, 0x38, 0x3C, 0x3C, 0x1C, 0x18, 0x19, 0x11, 0x03, 0x03, 0x07, 0x07, 0x0E, 0x0E, 0x0C,
0x1C, 0x1C, 0x18, 0x38, 0x38, 0x30, 0x30, 0x70, 0x70, 0x60, 0x60, 0x61, 0xE1, 0xC1, 0xC1, 0xC1,
0xC3, 0xC3, 0xC2, 0xC2, 0xC2, 0x82, 0x82, 0x86, 0xC6, 0xE6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
0x06, 0x06, 0xE6, 0xE6, 0xC2, 0x83, 0x83, 0x83, 0xC7, 0xC7, 0xCF, 0xC1, 0xC1, 0xC1, 0xC1, 0xE1,
0x60, 0x60, 0x60, 0x70, 0x30, 0x30, 0x38, 0x38, 0x18, 0x1C, 0x1C, 0x0C, 0x0E, 0x0E, 0x07, 0x07,
0x13, 0x13, 0x19, 0x19, 0x3C, 0x3C, 0x30, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xC1, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80,
0xC0, 0x80, 0x81, 0x01, 0x01, 0x81, 0x81, 0xC1, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x01, 0x03, 0x06, 0x0C, 0x0F,
0x0F, 0x0F, 0x00, 0x04, 0x0E, 0x0F, 0x0D, 0x0D, 0x0D, 0x0F, 0x0B, 0x06, 0x00, 0x03, 0x07, 0x0E,
0x08, 0x0C, 0x0F, 0x03, 0x03, 0x00, 0x06, 0x0E, 0x0F, 0x0D, 0x0D, 0x0D, 0x0B, 0x06, 0x00, 0x00,
0x0F, 0x0F, 0x0F, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x0E, 0x0C, 0x0F, 0x01,
0x01, 0x03, 0x0F, 0x0C, 0x0E, 0x0F, 0x03, 0x00, 0x0C, 0x0D, 0x0D, 0x09, 0x0B, 0x0F, 0x0F, 0x0E,
0x00, 0x00, 0x0F, 0x0F, 0x0E, 0x01, 0x01, 0x03, 0x0F, 0x0E, 0x00, 0x00, 0x06, 0x0E, 0x0F, 0x09,
0x09, 0x09, 0x0F, 0x0F, 0x0F, 0x00, 0x04, 0x0E, 0x0F, 0x0D, 0x0D, 0x0D, 0x0F, 0x0B, 0x06, 0x00,
0x00, 0x0F, 0x0F, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void initScreen(){
	configSPI1();
	screenData.i16_x = 0;
	screenData.i16_y = 0;
	screenData.u16_textColor = 0;
	screenData.u16_backgroundColor = 0;
	screenData.u8_textSize = 1;
	screenData.b_wrap = 1;
	screenData.i16_width = LCDWIDTH;
	screenData.i16_height = LCDHEIGHT;
	screenData.u8_i2cAddr = 0x3D;  //the I2C address of the screen
	RSTLOW();
	DELAY_MS(10);
	RSTHIGH();
	DCCONFIG();

 // Init sequence for 128x64 OLED module
    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    ssd1306_command(0x80);                                  // the suggested ratio 0x80
    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    ssd1306_command(0x3F);
    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    ssd1306_command(0x0);                                   // no offset
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0
    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
    if (0) 
      { ssd1306_command(0x10); }
    else 
      { ssd1306_command(0x14); }
    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
    ssd1306_command(0x00);                                  // 0x0 act like ks0108
    ssd1306_command(SSD1306_SEGREMAP | 0x1);
    ssd1306_command(SSD1306_COMSCANDEC);
    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
    if (0) 
      { ssd1306_command(0x9F); }
    else 
      { ssd1306_command(0xCF); }
    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
    if (0) 
      { ssd1306_command(0x22); }
    else 
      { ssd1306_command(0xF1); }
    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
    
  ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
}

// editted from https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp#L337
void ssd1306_command(uint8_t c) { 
    // SPI
    // the way the screen is designed, commands need the D/C pin low
    SLAVE_DISABLE();
    DCLOW();
	SLAVE_ENABLE();
    ioMasterSPI1(c);
	SLAVE_DISABLE();
}

void ssd1306_data(uint8_t c){
	//SPI
	//send 8-bits of data
	SLAVE_DISABLE();
	DCHIGH();
	SLAVE_ENABLE();
	ioMasterSPI1(c)	;
	SLAVE_DISABLE();
}	


// editted from https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp#L476
void display(void) {
  ssd1306_command(SSD1306_COLUMNADDR);
  ssd1306_command(0);   // Column start address (0 = reset)
  ssd1306_command(LCDWIDTH-1); // Column end address (127 = reset)

  ssd1306_command(SSD1306_PAGEADDR);
  ssd1306_command(0); // Page start address (0 = reset)
  ssd1306_command(7); // Page end address

    // SPI
    DISABLE_SLAVE();
	DCHIGH();
	ENABLE_SLAVE();
	
	uint16_t i = 0;
    for (i; i<(LCDWIDTH*LCDHEIGHT/8); i++) {
      ioMasterSPI1(buffer[i]);
      //ssd1306_data(buffer[i]);
    }
    DISABLE_SLAVE();
 }

//edited from https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L469
void setTextSize(uint8_t s) {
  screenData.u8_textSize = (s > 0) ? s : 1;
}

// edited from https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L479
void setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg 
  // to the same as fg instead of using a flag
  screenData.u16_textColor = screenData.u16_backgroundColor = c;
}

//https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L464
void setCursor(int16_t x, int16_t y) {
  screenData.i16_x = x;
  screenData.i16_y = y;
}

//https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp#L536
void clearDisplay(void) {
  memset(buffer, 0, (LCDWIDTH*LCDHEIGHT/8));
}

//https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L407
void write(uint8_t c) {
  if (c == '\n') {
    screenData.i16_y += screenData.u8_textSize*8;
    screenData.i16_x  = 0;
  } else if (c == '\r') {
    // skip em
  } else {
    drawChar(screenData.i16_x, screenData.i16_y, c, screenData.u16_textColor, screenData.u16_backgroundColor,screenData.u8_textSize);
    screenData.i16_x += screenData.u8_textSize*6;
    if (screenData.b_wrap && (screenData.i16_x > (screenData.i16_width - screenData.u8_textSize*6))) {
      screenData.i16_y += screenData.u8_textSize*8;
      screenData.i16_x = 0;
    }
  }
}

//char psz_s;
void writeString(char* psz_s){
    //uint8_t length = 0;
	uint8_t counter = 0;
    //length = strlen(psz_s);
    char string;
    while(*(psz_s + counter) != 0){ 
    string = (*(psz_s + counter));
	write(string);
    counter++;
	}
}

//based off of code from Adafruit and can be found at https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp#L659
void drawFastVLine(int16_t x, int16_t __y, int16_t __h, uint16_t color) {

  // do nothing if we're off the left or right side of the screen
  if(x < 0 || x >= LCDWIDTH) { return; }

  // make sure we don't try to draw below 0
  if(__y < 0) { 
    // __y is negative, this will subtract enough from __h to account for __y being 0
    __h += __y;
    __y = 0;

  } 

  // make sure we don't go past the height of the display
  if( (__y + __h) > LCDHEIGHT) { 
    __h = (LCDHEIGHT - __y);
  }

  // if our height is now negative, punt 
  if(__h <= 0) { 
    return;
  }

  // this display doesn't need ints for coordinates, use local byte registers for faster juggling
  uint8_t y = __y;
  uint8_t h = __h;


  // set up the pointer for fast movement through the buffer
  uint8_t *pBuf = buffer;
  // adjust the buffer pointer for the current row
  pBuf += ((y/8) * SSD1306_LCDWIDTH);
  // and offset x columns in
  pBuf += x;

  // do the first partial byte, if necessary - this requires some masking
  uint8_t mod = (y&7);
  if(mod) {
    // mask off the high n bits we want to set 
    mod = 8-mod;

    // note - lookup table results in a nearly 10% performance improvement in fill* functions
    // register uint8_t mask = ~(0xFF >> (mod));
    static uint8_t premask[8] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
    uint8_t mask = premask[mod];

    // adjust the mask if we're not going to reach the end of this byte
    if( h < mod) { 
      mask &= (0XFF >> (mod-h));
    }

  switch (color) 
    {
    case WHITE:   *pBuf |=  mask;  break;
    case BLACK:   *pBuf &= ~mask;  break;
    case INVERSE: *pBuf ^=  mask;  break;
    }
  
    // fast exit if we're done here!
    if(h<mod) { return; }

    h -= mod;

    pBuf += SSD1306_LCDWIDTH;
  }


  // write solid bytes while we can - effectively doing 8 rows at a time
  if(h >= 8) { 
    if (color == INVERSE)  {          // separate copy of the code so we don't impact performance of the black/white write version with an extra comparison per loop
      do  {
      *pBuf=~(*pBuf);

        // adjust the buffer forward 8 rows worth of data
        pBuf += SSD1306_LCDWIDTH;

        // adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
        h -= 8;
      } while(h >= 8);
      }
    else {
      // store a local value to work with 
      uint8_t val = (color == WHITE) ? 255 : 0;

      do  {
        // write our value in
      *pBuf = val;

        // adjust the buffer forward 8 rows worth of data
        pBuf += SSD1306_LCDWIDTH;

        // adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
        h -= 8;
      } while(h >= 8);
      }
    }

  // now do the final partial byte, if necessary
  if(h) {
    mod = h & 7;
    // this time we want to mask the low bits of the byte, vs the high bits we did above
    // register uint8_t mask = (1 << mod) - 1;
    // note - lookup table results in a nearly 10% performance improvement in fill* functions
    static uint8_t postmask[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
    uint8_t mask = postmask[mod];
    switch (color) 
    {
      case WHITE:   *pBuf |=  mask;  break;
      case BLACK:   *pBuf &= ~mask;  break;
      case INVERSE: *pBuf ^=  mask;  break;
    }
  }
}



//https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L205
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  	drawFastHLine(x, y, w, color);
  	drawFastHLine(x, y+h-1, w, color);
  	drawFastVLine(x, y, h, color);
  	drawFastVLine(x+w-1, y, h, color);
}

//based off of code from Adafruit and can be found at https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L226
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
			    uint16_t color) {
  // Update in subclasses if desired!
	int16_t i =x;
  for (i; i<x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}



// based off https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp#L105
// the most basic function, set a single pixel
void drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= screenData.i16_width) || (y < 0) || (y >= screenData.i16_height))
    return;

  // x is which column
    switch (color) 
    {
      case WHITE:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] |=  (1 << (y&7)); break;
      case BLACK:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] &= ~(1 << (y&7)); break; 
      case INVERSE: buffer[x+ (y/8)*SSD1306_LCDWIDTH] ^=  (1 << (y&7)); break; 
    }
    
}



//based off code from Adafruit found at https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L430
// Draw a character
void drawChar(int16_t x, int16_t y, unsigned char c,
			    uint16_t color, uint16_t bg, uint8_t size) {

  if((x >= screenData.i16_width)            || // Clip right
     (y >= screenData.i16_height)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;
  int8_t i=0;
  for (i; i<6; i++ ) {
    uint8_t line;
    if (i == 5) 
      line = 0x0;
    else 
      line = pgm_read_byte(font+(c*5)+i);
    int8_t j = 0;
    for (j; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          drawPixel(x+i, y+j, color);
        else {  // big size
          fillRect(x+(i*size), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1) // default size
          drawPixel(x+i, y+j, bg);
        else {  // big size
          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}


//possible error with the swap!!!!!!!!!!
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t temp1;
  int16_t temp2;
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    //swap(x0, y0);
    //swap(x1, y1);
    temp1 = x0;
    temp2 = y0;
    y0 = temp1;
    x0 = temp2;

    temp1 = x1;
    temp2 = y1;
    y1 = temp1;
    x1 = temp2;
  }

  if (x0 > x1) {
    //swap(x0, x1);
    //swap(y0, y1);
    temp1 = x0;
    temp2 = x1;
    x0 = temp2;
    x1 = temp1;

    temp1 = y0;
    temp2 = y1;
    y0 = temp2;
    y1 = temp1;
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  // Update in subclasses if desired!
  drawLine(x, y, x+w-1, y, color);
}

uint16_t distanceloc = 0;

void drawArrowNE(void){
    distanceloc = 1;
    drawLine(64, 32, 120, 9, 1);
    drawLine(64, 33, 120, 10, 1);
    drawLine(64, 31, 120, 8, 1);
    
	drawPixel(120,7,1);
	drawPixel(119,7,1);
	drawPixel(118,7,1);
	drawPixel(117,7,1);
	drawPixel(116,7,1);
	drawPixel(115,7,1);
	drawPixel(114,7,1);
	drawPixel(113,7,1);

	drawPixel(120,8,1);
	drawPixel(119,8,1);
	drawPixel(118,8,1);
	drawPixel(117,8,1);
	drawPixel(116,8,1);
	drawPixel(115,8,1);
	drawPixel(114,8,1);

	drawPixel(120,9,1);
	drawPixel(119,9,1);
	drawPixel(118,9,1);
	drawPixel(117,9,1);
	drawPixel(116,9,1);
	drawPixel(115,9,1);

	drawPixel(120,10,1);
	drawPixel(119,10,1);
	drawPixel(118,10,1);
	drawPixel(117,10,1);
	drawPixel(116,10,1);

	drawPixel(120,11,1);
	drawPixel(119,11,1);
	drawPixel(118,11,1);
	drawPixel(117,11,1);

	drawPixel(120,12,1);
	drawPixel(119,12,1);
	drawPixel(118,12,1);

	drawPixel(120,13,1);
	drawPixel(119,13,1);

	drawPixel(120,14,1);
}

void drawArrowN(void){
  distanceloc = 1;
  drawFastVLine(64, 6, 31, 1);
  drawFastVLine(65, 6, 31, 1);
  drawFastVLine(63, 6, 31, 1);
  drawPixel(65, 5, 1);
  drawPixel(65, 6, 1);
  drawPixel(65, 7, 1);
  drawPixel(65, 8, 1);
  drawPixel(65, 9, 1);
  drawPixel(66, 6, 1);
  drawPixel(66, 7, 1);
  drawPixel(66, 8, 1);
  drawPixel(66, 9, 1);
  drawPixel(67, 7, 1);
  drawPixel(67, 8, 1);
  drawPixel(67, 9, 1);
  drawPixel(68, 8, 1);
  drawPixel(68, 9, 1);
  drawPixel(69, 9, 1);
  drawPixel(63, 5, 1);
  drawPixel(63, 6, 1);
  drawPixel(63, 7, 1);
  drawPixel(63, 8, 1);
  drawPixel(63, 9, 1);
  drawPixel(62, 7, 1);
  drawPixel(62, 7, 1);
  drawPixel(62, 8, 1);
  drawPixel(62, 9, 1);
  drawPixel(61, 7, 1);
  drawPixel(61, 8, 1);
  drawPixel(61, 9, 1);
  drawPixel(60, 8, 1);
  drawPixel(60, 9, 1);
  drawPixel(59, 9, 1);
  drawPixel(64, 5, 1);
  drawPixel(62, 6, 1);
}

void drawArrowE(void){
    distanceloc = 1;
    drawFastHLine(64, 32, 48, 1);
    drawFastHLine(64, 31, 48, 1);
    drawFastHLine(64, 33, 48, 1);

    drawPixel(112, 28, 1);
    drawPixel(112, 29, 1);
    drawPixel(112, 30, 1);
    drawPixel(112, 31, 1);
    drawPixel(112, 32, 1);
    drawPixel(112, 33, 1);
    drawPixel(112, 34, 1);
    drawPixel(112, 35, 1);
    drawPixel(112, 36, 1);

    drawPixel(113, 29, 1);
    drawPixel(113, 30, 1);
    drawPixel(113, 31, 1);
    drawPixel(113, 32, 1);
    drawPixel(113, 33, 1);
    drawPixel(113, 34, 1);
    drawPixel(113, 35, 1);

    drawPixel(114, 30, 1);
    drawPixel(114, 31, 1);
    drawPixel(114, 32, 1);
    drawPixel(114, 33, 1);
    drawPixel(114, 34, 1);

    drawPixel(115, 31, 1);
    drawPixel(115, 32, 1);
    drawPixel(115, 33, 1);
	
    drawPixel(116, 32, 1);
}

void drawArrowS(void){
    distanceloc = 2;
    drawFastVLine(63, 32, 24, 1);
    drawFastVLine(64, 32, 24, 1);
    drawFastVLine(65, 32, 24, 1);

	drawPixel(60, 56, 1);   
	drawPixel(61, 56, 1);  
	drawPixel(62, 56, 1);  
	drawPixel(63, 56, 1);  
	drawPixel(64, 56, 1);  
	drawPixel(65, 56, 1);  
	drawPixel(66, 56, 1);  
	drawPixel(67, 56, 1);  
	drawPixel(68, 56, 1); 

	drawPixel(61, 57, 1);  
	drawPixel(62, 57, 1);  
	drawPixel(63, 57, 1);  
	drawPixel(64, 57, 1);  
	drawPixel(65, 57, 1);  
	drawPixel(66, 57, 1);  
	drawPixel(67, 57, 1);

	drawPixel(62, 58, 1);  
	drawPixel(63, 58, 1);  
	drawPixel(64, 58, 1);  
	drawPixel(65, 58, 1);  
	drawPixel(66, 58, 1);  

	drawPixel(63, 59, 1);  
	drawPixel(64, 59, 1);  
	drawPixel(65, 59, 1); 

	drawPixel(64, 60, 1);   
}

void drawArrowW(void){
    distanceloc = 1;
    drawFastHLine(16, 32, 48, 1);
    drawFastHLine(16, 31, 48, 1);
    drawFastHLine(16, 33, 48, 1);

	drawPixel(15, 28, 1);
    drawPixel(15, 29, 1);
    drawPixel(15, 30, 1);
    drawPixel(15, 31, 1);
    drawPixel(15, 32, 1);
    drawPixel(15, 33, 1);
    drawPixel(15, 34, 1);
    drawPixel(15, 35, 1);
    drawPixel(15, 36, 1);

    drawPixel(14, 29, 1);
    drawPixel(14, 30, 1);
    drawPixel(14, 31, 1);
    drawPixel(14, 32, 1);
    drawPixel(14, 33, 1);
    drawPixel(14, 34, 1);
    drawPixel(14, 35, 1);

    drawPixel(13, 30, 1);
    drawPixel(13, 31, 1);
    drawPixel(13, 32, 1);
    drawPixel(13, 33, 1);
    drawPixel(13, 34, 1);

    drawPixel(12, 31, 1);
    drawPixel(12, 32, 1);
    drawPixel(12, 33, 1);

    drawPixel(11, 32, 1);
}

void drawArrowSE(void){
    distanceloc = 2;
	drawLine(64, 32, 120, 56, 1);
    drawLine(64, 33, 120, 57, 1);
    drawLine(64, 31, 120, 55, 1);
    
	drawPixel(121,59,1);
	drawPixel(120,59,1);
	drawPixel(119,59,1);
	drawPixel(118,59,1);
	drawPixel(117,59,1);
	drawPixel(116,59,1);
	drawPixel(115,59,1);
	drawPixel(114,59,1);

	drawPixel(121,58,1);
	drawPixel(120,58,1);
	drawPixel(119,58,1);
	drawPixel(118,58,1);
	drawPixel(117,58,1);
	drawPixel(116,58,1);
	drawPixel(115,58,1);

	drawPixel(121,57,1);
	drawPixel(120,57,1);
	drawPixel(119,57,1);
	drawPixel(118,57,1);
	drawPixel(117,57,1);
	drawPixel(116,57,1);

	drawPixel(121,56,1);
	drawPixel(120,56,1);
	drawPixel(119,56,1);
	drawPixel(118,56,1);
	drawPixel(117,56,1);

	drawPixel(121,55,1);
	drawPixel(120,55,1);
	drawPixel(119,55,1);
	drawPixel(118,55,1);

	drawPixel(121,54,1);
	drawPixel(120,54,1);
	drawPixel(119,54,1);

	drawPixel(121,53,1);
	drawPixel(120,53,1);

	drawPixel(121,52,1);
}

void drawArrowSW(void){
    distanceloc = 2;
    drawLine(8, 57, 64, 33, 1);
	drawLine(8, 56, 64, 32, 1);
	drawLine(8, 55, 64, 31, 1);
    
	drawPixel(4,54,1);
	drawPixel(4,55,1);
	drawPixel(4,56,1);
	drawPixel(4,57,1);
	drawPixel(4,58,1);
	drawPixel(4,59,1);
	drawPixel(4,60,1);
	drawPixel(4,53,1);
	drawPixel(4,52,1);

	drawPixel(5,54,1);
	drawPixel(5,55,1);
	drawPixel(5,56,1);
	drawPixel(5,57,1);
	drawPixel(5,58,1);
	drawPixel(5,59,1);
	drawPixel(5,60,1);
	drawPixel(5,53,1);

	drawPixel(6,54,1);
	drawPixel(6,55,1);
	drawPixel(6,56,1);
	drawPixel(6,57,1);
	drawPixel(6,58,1);
	drawPixel(6,59,1);
	drawPixel(6,60,1);

	drawPixel(7,55,1);
	drawPixel(7,56,1);
	drawPixel(7,57,1);
	drawPixel(7,58,1);
	drawPixel(7,59,1);
	drawPixel(7,60,1);

	drawPixel(8,56,1);
	drawPixel(8,57,1);
	drawPixel(8,58,1);
	drawPixel(8,59,1);
	drawPixel(8,60,1);

	drawPixel(9,57,1);
	drawPixel(9,58,1);
	drawPixel(9,59,1);
	drawPixel(9,60,1);

	drawPixel(10,58,1);
	drawPixel(10,59,1);
	drawPixel(10,60,1);

	drawPixel(11,59,1);
	drawPixel(11,60,1);

	drawPixel(12,60,1);
}

void drawArrowNW(void){
    distanceloc = 1;
    drawLine(8, 7, 64, 33, 1);
	drawLine(8, 6, 64, 32, 1);
	drawLine(8, 5, 64, 31, 1);
    
	drawPixel(4,2,1);
	drawPixel(4,3,1);
	drawPixel(4,4,1);
	drawPixel(4,5,1);
	drawPixel(4,6,1);
	drawPixel(4,7,1);
	drawPixel(4,8,1);
	drawPixel(4,9,1);
	drawPixel(4,10,1);

	drawPixel(5,2,1);
	drawPixel(5,3,1);
	drawPixel(5,4,1);
	drawPixel(5,5,1);
	drawPixel(5,6,1);
	drawPixel(5,7,1);
	drawPixel(5,8,1);
	drawPixel(5,9,1);

	drawPixel(6,2,1);
	drawPixel(6,3,1);
	drawPixel(6,4,1);
	drawPixel(6,5,1);
	drawPixel(6,6,1);
	drawPixel(6,7,1);
	drawPixel(6,8,1);

	drawPixel(7,2,1);
	drawPixel(7,3,1);
	drawPixel(7,4,1);
	drawPixel(7,5,1);
	drawPixel(7,6,1);
	drawPixel(7,7,1);

	drawPixel(8,2,1);
	drawPixel(8,3,1);
	drawPixel(8,4,1);
	drawPixel(8,5,1);
	drawPixel(8,6,1);

	drawPixel(9,2,1);
	drawPixel(9,3,1);
	drawPixel(9,4,1);
	drawPixel(9,5,1);

	drawPixel(10,2,1);
	drawPixel(10,3,1);
	drawPixel(10,4,1);

	drawPixel(11,2,1);
	drawPixel(11,3,1);

	drawPixel(12,2,1);
}

//char psz_s2;
void writeDistance(char* psz_s2){  //input distance!
    if (distanceloc == 1){
    setCursor(50,48);
	setTextSize(2);
	writeString(psz_s2);   //fix
    }
    else if (distanceloc == 2){
	setCursor(50,10);
	setTextSize(2);
	writeString(psz_s2);   //fix
    }
}

void proximity20(void){   
	setTextSize(1);
	char *line = "Set Proximity(meters)";
    setCursor(1,1);
	writeString(line);
	setTextSize(2);
    setCursor(32,14);
	line = "20 30";
	writeString(line);
	line = "40 50";
	setCursor(32, 40);
	writeString(line);
    drawRect(30, 12, 26, 19, 1);
}

void proximity30(void){   
	setTextSize(1);
	char *line = "Set Proximity(meters)";
    setCursor(1,1);
	writeString(line);
	setTextSize(2);
    setCursor(32,14);
	line = "20 30";
	writeString(line);
	line = "40 50";
	setCursor(32, 40);
	writeString(line);
    drawRect(66, 12, 26, 19, 1);
}

void proximity40(void){   
	setTextSize(1);
	char *line = "Set Proximity(meters)";
    setCursor(1,1);
	writeString(line);
	setTextSize(2);
    setCursor(32,14);
	line = "20 30";
	writeString(line);
	line = "40 50";
	setCursor(32, 40);
	writeString(line);
    drawRect(30, 38, 26, 19, 1);
}

void proximity50(void){   
	setTextSize(1);
	char *line = "Set Proximity(meters)";
    setCursor(1,1);
	writeString(line);
	setTextSize(2);
    setCursor(32,14);
	line = "20 30";
	writeString(line);
	line = "40 50";
	setCursor(32, 40);
	writeString(line);
    drawRect(66, 38, 26, 19, 1);
}

void invertDisplay(uint8_t i) {
  if (i) {
    ssd1306_command(SSD1306_INVERTDISPLAY);
  } else {
    ssd1306_command(SSD1306_NORMALDISPLAY);
  }
}










