#include "pic24_all.h"
#include "GPS_module.h"
#include "NeverWanderBand.h"

char CalcCheckSum(char* psz_s, uint8_t u8_size){
	char c_runChecksum;	//the running checksum
	uint8_t u8_count = 2;
	c_runChecksum = *(psz_s +1);
	while(u8_count <= u8_size){
		//if it is the star, that is the end of the checksum part
		if(*(psz_s+u8_count)=='*'){
			break;
		}
		c_runChecksum ^= *(psz_s + u8_count);
		u8_count++;
	}
	return c_runChecksum;	
}

_packetType_t parsePacketType(char* psz_s){
	if((*(psz_s+1)=='G')&&(*(psz_s+2)=='P')&&(*(psz_s+3)=='R')&&(*(psz_s+4)=='M')&&(*(psz_s+5)=='C')){
		return GPRMC;
	}
	return INVALIDPACKET;
}

_RMCPacket parseRMCPacket(char* psz_s){
	_RMCPacket st_rmcPacket;
	
	//I need to go back and change the magic number is defined constants
	st_rmcPacket.u8_hours = ((*(psz_s+7)-48)*10 + (*(psz_s+8)-48));
	st_rmcPacket.u8_minutes = ((*(psz_s+9)-48)*10 + (*(psz_s+10)-48));
	st_rmcPacket.u8_seconds = ((*(psz_s+11)-48)*10 + (*(psz_s+12)-48));
	st_rmcPacket.u8_valid = (*(psz_s+18))=='A';
	
	if(st_rmcPacket.u8_valid == 0){
		st_rmcPacket.position.latitude.u8_hemisphereIndicator = 0;
		st_rmcPacket.position.latitude.u8_degrees = 0;
		st_rmcPacket.position.latitude.u8_minutes = 0;
		st_rmcPacket.position.latitude.u8_seconds = 0;
	
		st_rmcPacket.position.longitude.u8_hemisphereIndicator = 0;
		st_rmcPacket.position.longitude.u8_degrees = 0;
		st_rmcPacket.position.longitude.u8_minutes = 0;
		st_rmcPacket.position.longitude.u8_seconds = 0;
		
		st_rmcPacket.u16_course = 0;
		
		return st_rmcPacket;
	}	
	
	st_rmcPacket.position.latitude.u8_hemisphereIndicator = (*(psz_s+30))=='N';
	st_rmcPacket.position.latitude.u8_degrees = ((*(psz_s+20)-48)*10 + (*(psz_s+21)-48));
	st_rmcPacket.position.latitude.u8_minutes = ((*(psz_s+22)-48)*10 + (*(psz_s+23)-48));
	st_rmcPacket.position.latitude.u8_seconds = ((*(psz_s+25)-48)*6 + (*(psz_s+26)-48)*6/10);
	
	st_rmcPacket.position.longitude.u8_hemisphereIndicator = (*(psz_s+43))=='E';
	st_rmcPacket.position.longitude.u8_degrees = ((*(psz_s+32)-48)*100 + (*(psz_s+33)-48)*10 + (*(psz_s+34)-48));
	st_rmcPacket.position.longitude.u8_minutes = ((*(psz_s+35)-48)*10 + (*(psz_s+36)-48));
	st_rmcPacket.position.longitude.u8_seconds = ((*(psz_s+38)-48)*6 + (*(psz_s+39)-48)*6/10);
	
	uint8_t u8_counter = 43+2;
	while(u8_counter <= 254){
		//loop past the speed over ground
		if(*(psz_s + u8_counter) == ',')
			break;
		u8_counter++;
	}
	u8_counter++;
	
	st_rmcPacket.u16_course = 0;
	
	//the course has a varying length of whole numbers and a decimal
	while(u8_counter <=254){
		if(*(psz_s + u8_counter) == '.')
			break;
		st_rmcPacket.u16_course *= 10;
		st_rmcPacket.u16_course += (*(psz_s + u8_counter)-48);
		u8_counter++;
	}	
	
	
	return st_rmcPacket;
}	

void configRMC1Hz(){
	//DELAY_MS(100);
	const char *message = PMTK_SET_NEA_OUTPUT_RMCONLY;
	const char *message2 = PMTK_SET_NMEA_UPDATE_1HZ;
	outString(message);
	outString(message2);
}


char * uitoa(uint16_t u16_x) {
    static uint8_t au8_String[8];
    static uint8_t u8_digit;

    u8_digit = 0;
    if (u16_x > 9999)
        au8_String[u8_digit++] = '0' + u16_x / 10000;
    if (u16_x > 999)
        au8_String[u8_digit++] = '0' + u16_x / 1000;
    if (u16_x > 99)
        au8_String[u8_digit++] = '0' + u16_x / 100;
    if (u16_x > 9)
        au8_String[u8_digit++] = '0' + (u16_x % 100) / 10;
    au8_String[u8_digit++] = '0' + (u16_x % 10);
    au8_String[u8_digit] = 0;

    return au8_String;
}