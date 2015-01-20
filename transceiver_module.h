#ifndef _TRANSCEIVER_H_
#define _TRANSCEIVER_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"

void configUartChild();

void configUartParent();

void sendUint8Child(uint8_t u8_toBeSent);

uint8_t receiveUint8Child();

void getChildPacket(char* psz_buff, uint16_t u16_maxCount);

void transmitChildCommand(char *psz_s);

void getParentPacket(char* psz_buff, uint16_t u16_maxCount);

uint8_t parentPacketReady();

uint8_t childPacketReady();

#endif //_TRANSCEIVER_H_