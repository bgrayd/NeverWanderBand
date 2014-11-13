#include "pic24_all.h"
#include "transceiver_module.h"
#include "NeverWanderBand.h"

void configUartXbee(){
    configUART2(9600);
    CONFIG_RB6_AS_DIG_INPUT();           // RX pin must be digital input
    CONFIG_U2RX_TO_RP(RB6_RP);           // U2RX <- RB8
    CONFIG_RB9_AS_DIG_OUTPUT();           // TX pin must be digital output
    CONFIG_U2TX_TO_RP(RB9_RP);            // U2TX -> RB7
}

void sendUint8Xbee(uint8_t u8_toBeSent){
    outChar2(u8_toBeSent);
    outChar1(uitoa(u8_toBeSent));
    outChar1(';');
}

uint8_t receiveUint8Xbee(){

    return inChar2();
}