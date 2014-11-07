#include "pic24_all.h"
#include "transceiver_module.h"
#include "NeverWanderBand.h"

void configUartXbee(){
    #if (NUM_UART_MODS == 1)
    configUART1(9600);
    CONFIG_RB8_AS_DIG_INPUT();           // RX pin must be digital input
    CONFIG_U1RX_TO_RP(RB8_RP);           // U1RX <- RB8
    CONFIG_RB9_AS_DIG_OUTPUT();           // TX pin must be digital output
    CONFIG_U1TX_TO_RP(RB9_RP);            // U1TX -> RB9
    #else
    configUART2(9600);
    CONFIG_RB8_AS_DIG_INPUT();           // RX pin must be digital input
    CONFIG_U2RX_TO_RP(RB8_RP);           // U1RX <- RB8
    CONFIG_RB9_AS_DIG_OUTPUT();           // TX pin must be digital output
    CONFIG_U2TX_TO_RP(RB9_RP);            // U1TX -> RB9
    #endif
}

void sendUint8Xbee(uint8_t u8_toBeSent){
    #if (NUM_UART_MODS == 1)
    outChar1(u8_toBeSent);
    #else
    outChar2(u8_toBeSent);
    #endif

}

uint8_t receiveUint8Xbee(){
    #if (NUM_UART_MODS == 1)
    return inChar1();
    #else
    return inChar2();
    #endif
}