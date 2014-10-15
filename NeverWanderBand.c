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
CONFIG_RB14_AS_DIG_OUTPUT();
  outString(HELLO_MSG);
_LATB14=0;
  initScreen();
_LATB14 = 1;
  ssd1306_command(0xA5);
  while(1){_LATB14 = !_LATB14;; ssd1306_command(0xA5);};
}