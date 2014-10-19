#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"
#include "GPS_module.h"

/*
//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configHeartbeat();
  configUART1(DEFAULT_BAUDRATE);
  configUART2(DEFAULT_BAUDRATE);
  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);
  initScreen();
  //ssd1306_command(0xA5);
  display();
  clearDisplay();
  setTextColor(1);
  setTextSize(2);
  char *newLine = "It is working!!";
  writeString(newLine);
  display();
  ssd1306_command(0x26);
  ssd1306_command(0x2F);
  display();
  	
  while(1){
	ssd1306_command(0x2F);
	DELAY_MS(10);
    doHeartbeat();
  };
}
}*/

int main(void){
	configClock();
	configHeartbeat();
	configDefaultUART(9600);
	//printResetCause();       //print statement about what caused reset
	outString(HELLO_MSG);
	configRMC1Hz();
        initScreen();
	const char *newLine = "\n";
	char sz_buffer[256];
	char *psz_input;
	psz_input = sz_buffer; 
	_RMCPacket RMCPacket;
	while(1){
            //clearDisplay();
            setTextColor(1);
            write('h');
		psz_input = sz_buffer;
		inString(psz_input, 256);
		//outString(newLine);
		switch(parsePacketType(psz_input)){
			case GPRMC:
				/*RMCPacket = parseRMCPacket(psz_input);
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
                                writeString(psz_input);
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
