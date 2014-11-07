#ifndef _TRANSCEIVER_H_
#define _TRANSCEIVER_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"

void configUartXbee();

void sendUint8Xbee(uint8_t u8_toBeSent);

uint8_t receiveUint8Xbee();

#endif //_TRANSCEIVER_H_