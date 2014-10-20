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
	//const char *newLine = "\n";
        const char psz_latitude[11] = "Latitude: ";
        const char psz_longitude[12] = "Longitude: ";
        const char psz_time[7] = "Time: ";
	char sz_buffer[256];
	char *psz_input;
	psz_input = sz_buffer; 
	_RMCPacket RMCPacket;
        setTextColor(1);
        setTextSize(1);
        write('h');
        display();
	while(1){
            clearDisplay();
            setCursor(0,0);
            psz_input = sz_buffer;
            inString(psz_input, 256);
            switch(parsePacketType(psz_input)){
                    case GPRMC:
                            RMCPacket = parseRMCPacket(psz_input);/*
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
                            break;
                    default:
                            break;
            }
            writeString(psz_latitude);
            writeString(uitoa(RMCPacket.position.latitude.u8_degrees));
            write(0xA7);
            write(' ');
            writeString(uitoa(RMCPacket.position.latitude.u8_minutes));
            write(96);
            write(' ');
            writeString(uitoa(RMCPacket.position.latitude.u8_seconds));
            write(34);
            write('\n');
            writeString(psz_longitude);
            writeString(uitoa(RMCPacket.position.longitude.u8_degrees));
            write(0xA7);
            write(' ');
            writeString(uitoa(RMCPacket.position.longitude.u8_minutes));
            write(96);
            write(' ');
            writeString(uitoa(RMCPacket.position.longitude.u8_seconds));
            write(34);
            write('\n');
            writeString(psz_time);
            writeString(uitoa(RMCPacket.u8_hours));
            write(':');
            writeString(uitoa(RMCPacket.u8_minutes));
            write(':');
            writeString(uitoa(RMCPacket.u8_seconds));
            display();
            /*outString(psz_input);
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
            DELAY_MS(10);
	};
}
