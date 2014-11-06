#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"


//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configPinsForLowPower();
  configHeartbeat();
  configDefaultUART(DEFAULT_BAUDRATE);
  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);
  initScreen();
  //ssd1306_command(0xA5);
  display();
  clearDisplay();
  setTextColor(1);
  setTextSize(1);
//  char *newLine = "It is working! But not really.";
//  writeString(newLine);

  //ssd1306_command(0xA3);
  //ssd1306_command(0x2F);
  //display();
  	
  while(1){
	//ssd1306_command(0x2F);
	//DELAY_MS(10);
  drawArrowN();
  display();
  clearDisplay();
  DELAY_MS(2000);
  drawArrowNE();
  display();
  clearDisplay();
  DELAY_MS(2000);	
  drawArrowE();
  display();
  clearDisplay();
  DELAY_MS(2000);
  drawArrowSE();
  display();
  clearDisplay();
  DELAY_MS(2000);
  drawArrowS();
  display();
  clearDisplay();
  DELAY_MS(2000);
  drawArrowSW();
  display();
  clearDisplay();
  DELAY_MS(2000);
  drawArrowW();
  display();
  clearDisplay();
  DELAY_MS(2000);
  drawArrowNW();
  display();
  clearDisplay();
  DELAY_MS(2000);
    doHeartbeat();
  };
};

void printCharacters(char* ch_letters, uint16_t color, uint16_t size){
    setTextColor(color);
    setTextSize(size);
	writeString(ch_letters);
}

void clearScreen(){
	clearDisplay();
}

void updateScreen(){
	display();
}

void resetCursor(){
	setCursor(0, 0);
}

void giveAngleDegrees(int16_t i16_angle){
	if (i16_angle >= -23 && i16_angle <= 23){
		drawArrowN();
        }
	else if (i16_angle > 23 && i16_angle <= 68){
		drawArrowNE();
	}
	else if (i16_angle > 68 && i16_angle <= 113){
		drawArrowE();
	}
	else if (i16_angle > 113 && i16_angle <= 158){
		drawArrowSE();
	}
	else if (i16_angle > 158 || i16_angle <= -158){
		drawArrowS();
	}
	else if (i16_angle >= -68 && i16_angle < -23){
		drawArrowNW();
	}
	else if (i16_angle >= -113 && i16_angle < -68){
		drawArrowW();
	}
	else if (i16_angle > -158 && i16_angle < -113){
		drawArrowSW();
	}
	
}