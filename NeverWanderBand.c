#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "GPS_module.h"

/*
//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configPinsForLowPower();
  configHeartbeat();
  configDefaultUART(DEFAULT_BAUDRATE);
  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);
}*/

int main(void){
	configClock();
	configPinsForLowPower();
	configHeartbeat();
	configDefaultUART(9600);
	//printResetCause();       //print statement about what caused reset
	outString(HELLO_MSG);
	configRMC1Hz();
	const char *newLine = "\n";
	char sz_buffer[256];
	char *psz_input;
	psz_input = sz_buffer; 
	_RMCPacket RMCPacket;
	while(1){
		psz_input = sz_buffer;
		inString(psz_input, 256);
		outString(newLine);
		switch(parsePacketType(psz_input)){
			case GPRMC:
				RMCPacket = parseRMCPacket(psz_input);
				outString(psz_input);
				outUint8(RMCPacket.u8_hours);
				outUint8(RMCPacket.u8_minutes);
				WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
				outUint8(RMCPacket.u8_seconds);
				outUint8(RMCPacket.u8_valid);
				outUint8(RMCPacket.position.latitude.u8_hemisphereIndicator);
				outUint8(RMCPacket.position.latitude.u8_degrees);
				WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
				outUint8(RMCPacket.position.latitude.u8_minutes);
				outUint8(RMCPacket.position.latitude.u8_seconds);
				outUint8(RMCPacket.position.longitude.u8_hemisphereIndicator);
				outUint8(RMCPacket.position.longitude.u8_degrees);
				WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
				outUint8(RMCPacket.position.longitude.u8_minutes);
				outUint8(RMCPacket.position.longitude.u8_seconds);
				outUint16(RMCPacket.u16_course);
				WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
				outString(newLine);
				break;
			default:
				break;
		}/*
		outString(psz_input);
		outUint8(RMCPacket.u8_hours);
		outUint8(RMCPacket.u8_minutes);
		WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
		outUint8(RMCPacket.u8_seconds);
		outUint8(RMCPacket.u8_valid);
		outUint8(RMCPacket.position.latitude.u8_hemisphereIndicator);
		outUint8(RMCPacket.position.latitude.u8_degrees);
		WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
		outUint8(RMCPacket.position.latitude.u8_minutes);
		outUint8(RMCPacket.position.latitude.u8_seconds);
		outUint8(RMCPacket.position.longitude.u8_hemisphereIndicator);
		outUint8(RMCPacket.position.longitude.u8_degrees);
		WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
		outUint8(RMCPacket.position.longitude.u8_minutes);
		outUint8(RMCPacket.position.longitude.u8_seconds);
		outUint16(RMCPacket.u16_course);
		WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
		outString(newLine);*/
	};
}
