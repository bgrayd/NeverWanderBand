#ifndef _ADAFRUIT_GPS_H_
#define _ADAFRUIT_GPS_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"

// different commands to set the update rate from once a second (1 Hz) to 10 times a second (10Hz)
// Note that these only control the rate at which the position is echoed, to actually speed up the
// position fix you must also send one of the position fix rate commands below too.
#define PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ  "$PMTK220,10000*2F\r\n" // Once every 10 seconds, 100 millihertz.
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F\r\n"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C\r\n"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F\r\n"
// Position fix update rate commands.
#define PMTK_API_SET_FIX_CTL_100_MILLIHERTZ  "$PMTK300,10000,0,0,0,0*2C\r\n" // Once every 10 seconds, 100 millihertz.
#define PMTK_API_SET_FIX_CTL_1HZ  "$PMTK300,1000,0,0,0,0*1C\r\n"
#define PMTK_API_SET_FIX_CTL_5HZ  "$PMTK300,200,0,0,0,0*2F\r\n"
// Can't fix position faster than 5 times a second!

#define PMTK_SET_NEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"


#define PMTK_SET_BAUD_57600 "$PMTK251,57600*2C\r\n"
#define PMTK_SET_BAUD_9600 "$PMTK251,9600*17\r\n"


typedef enum{
	GPRMC,
	GPGGA,
	INVALIDPACKET
} _packetType_t;

typedef struct _RMCPacket{
	uint8_t u8_hours;
	uint8_t u8_minutes;
	uint8_t u8_seconds;
	uint8_t u8_valid;
	st_gpsPosition position;
	uint16_t u16_course;
} _RMCPacket;

char CalcCheckSum(char* psz_s, uint8_t u8_size);

_packetType_t parsePacketType(char* psz_s);

_RMCPacket parseRMCPacket(char* psz_s);

void configRMC1Hz();

char * uitoa(uint16_t u16_x);

uint16_t getCourse();

#endif //_ADAFRUIT_GPS_H_