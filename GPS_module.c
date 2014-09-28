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

packetType_t parsePacketType(char* psz_s){
	if((*(psz_s+1)=='G')&&(*(psz_s+2)=='P')&&(*(psz_s+3)=='R')&&(*(psz_s+4)=='M')&&(*(psz_s+5)=='C')){
		return GPRMC;
	}
}		
