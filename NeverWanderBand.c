#include "pic24_all.h"
#include <stdio.h>
#include "NeverWanderBand.h"


//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configHeartbeat();
  configUART1(DEFAULT_BAUDRATE);
  configUART2(DEFAULT_BAUDRATE);

   //Defining Pins
  CONFIG_RB10_AS_DIG_INPUT();           // RX pin must be digital input
  CONFIG_U2RX_TO_RP(RB10_RP);           // U1RX <- RB12
  CONFIG_RB11_AS_DIG_OUTPUT();           // TX pin must be digital output
  CONFIG_U2TX_TO_RP(RB11_RP);            // U1TX -> RB11

  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);

  char c_char;
  c_char = inChar2();
  outChar1(c_char);
  while(1)
    {c_char = inChar2();
        outChar1(c_char);
    };
}