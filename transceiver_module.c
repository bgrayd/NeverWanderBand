#include "pic24_all.h"
#include "transceiver_module.h"
#include "NeverWanderBand.h"

void configUartChild(){
	configUART2(9600);
	CONFIG_RB6_AS_DIG_INPUT();           // RX pin must be digital input
	CONFIG_U2RX_TO_RP(RB6_RP);           // U2RX <- RB8
	CONFIG_RB9_AS_DIG_OUTPUT();           // TX pin must be digital output
	CONFIG_U2TX_TO_RP(RB9_RP);            // U2TX -> RB7
}

void configUartParent(){
	configUART1(9600);
}

void sendUint8Child(uint8_t u8_toBeSent){
	outChar2(u8_toBeSent);
}

uint8_t receiveUint8Child(){
	return inChar2();
}

void getChildPacket(char* psz_buff, uint16_t u16_maxCount){
	uint8_t u8_c;
	uint16_t u16_i;
	outChar('{');
	if (!u16_maxCount) return;
	u16_i = 0;
	for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
		u8_c = receiveUint8Child();
		if (u8_c == '\n' ) break; //terminate loop
		if (u8_c == '\r' ) continue; //ignore carriage return
		*psz_buff = u8_c; //save character
		outUint8(u8_c);
		outChar(';');
		psz_buff++;
	}
	outChar('}');
	outChar('\n');

	*psz_buff = 0;
}

void transmitChildCommand(char *psz_s){
	while (*psz_s) {
		if (*psz_s == '\n') sendUint8Child(0x0D);
		sendUint8Child(*psz_s);
		psz_s++;
	}
}

void getParentPacket(char* psz_buff, uint16_t u16_maxCount){
	uint8_t u8_c;
	uint16_t u16_i;

	if (!u16_maxCount) return;
	u16_i = 0;
	outChar('[');
	for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
		u8_c = inChar1();
		if (u8_c == '\n' ) break; //terminate loop
		if (u8_c == '\r' ) continue; //ignore carriage return
		*psz_buff = u8_c; //save character
		outUint8(u8_c);
		outChar(';');
		psz_buff++;
	}
	outChar(']');
	outChar('\n');

	*psz_buff = 0;
}

uint8_t parentPacketReady(){
	return isCharReady1();
}

uint8_t childPacketReady(){
	return isCharReady2();
}