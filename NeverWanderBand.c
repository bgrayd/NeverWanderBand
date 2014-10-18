#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"


//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configHeartbeat();
  configUART1(DEFAULT_BAUDRATE);
  configUART2(DEFAULT_BAUDRATE);
  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);
  initScreen();
  //ssd1306_command(0xA5);
  display();
  clearDisplay();
  setTextColor(1);
  setTextSize(2);
  char *newLine = "It is working!!";
  writeString(newLine);
  display();
  ssd1306_command(0x26);
  ssd1306_command(0x2F);
  display();
  	
  while(1){
	ssd1306_command(0x2F);
	DELAY_MS(10);
    doHeartbeat();
  };
}