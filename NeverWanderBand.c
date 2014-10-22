#include "pic24_all.h"
#include "NeverWanderBand.h"


//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configHeartbeat();
  configUART1(DEFAULT_BAUDRATE);
  configUART2(DEFAULT_BAUDRATE);
  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);
  while(1){};
}