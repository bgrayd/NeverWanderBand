#ifndef _TRANSCEIVER_H_
#define _TRANSCEIVER_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"

void configUartXbee();

void sendUint8Xbee(uint8_t u8_toBeSent);

uint8_t receiveUint8Xbee();

void getChildPacket(char* psz_buff, uint16_t u16_maxCount);

void transmitChildCommand(char *psz_s);

void getParentPacket(char* psz_buff, uint16_t u16_maxCount);

#endif //_TRANSCEIVER_H_