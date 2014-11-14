#include "pic24_all.h"
#include "GPS_module.h"
#include "NeverWanderBand.h"
#include "string.h"
#include "stdlib.h"


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

// read a Hex value and return the decimal equivalent
uint8_t parseHex(char c) {
    if (c < '0')
      return 0;
    if (c <= '9')
      return c - '0';
    if (c < 'A')
       return 0;
    if (c <= 'F')
       return (c - 'A')+10;
    // if (c > 'F')
    return 0;
}


st_gpsData parseGpsPacket(char *nmea) {
    st_gpsData gpsData;
    // do checksum check
    // first look if we even have one
    if (nmea[strlen(nmea)-4] == '*') {
        uint16_t sum = parseHex(nmea[strlen(nmea)-3]) * 16;
        sum += parseHex(nmea[strlen(nmea)-2]);

        // check checksum
        uint8_t i;
        for (i=1; i < (strlen(nmea)-4); i++) {
            sum ^= nmea[i];
        }
            if (sum != 0) {
            // bad checksum :(
            //return false;
            }
    }
    int32_t degree;
    long minutes;
    char degreebuff[10];
    // look for a few common sentences
    if (strstr(nmea, "$GPGGA")) {
        // found GGA
        char *p = nmea;
        // get time
        p = strchr(p, ',')+1;

        // parse out latitude
        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            strncpy(degreebuff, p, 2);
            p += 2;
            degreebuff[2] = '\0';
            degree = atol(degreebuff) * 10000000;
            strncpy(degreebuff, p, 2); // minutes
            p += 3; // skip decimal point
            strncpy(degreebuff + 2, p, 4);
            degreebuff[6] = '\0';
            minutes = 50 * atol(degreebuff) / 3;
            gpsData.i32_latitudeFixed = degree + minutes;
            gpsData.f_latitude = degree / 100000 + minutes * 0.000006F;
            gpsData.f_latitudeDegrees = (gpsData.f_latitude-100*((int)gpsData.f_latitude/100))/60.0;
            gpsData.f_latitudeDegrees += ((int)gpsData.f_latitude/100);
            }

        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            if (p[0] == 'S') gpsData.f_latitudeDegrees *= -1.0;
            if (p[0] == 'N') gpsData.c_lat = 'N';
            else if (p[0] == 'S') gpsData.c_lat = 'S';
            else if (p[0] == ',') gpsData.c_lat = 0;
        }

        // parse out longitude
        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            strncpy(degreebuff, p, 3);
            p += 3;
            degreebuff[3] = '\0';
            degree = atol(degreebuff) * 10000000;
            strncpy(degreebuff, p, 2); // minutes
            p += 3; // skip decimal point
            strncpy(degreebuff + 2, p, 4);
            degreebuff[6] = '\0';
            minutes = 50 * atol(degreebuff) / 3;
            gpsData.i32_longitudeFixed = degree + minutes;
            gpsData.f_longitude = degree / 100000 + minutes * 0.000006F;
            gpsData.f_longitudeDegrees = (gpsData.f_longitude-100*((int)gpsData.f_longitude/100))/60.0;
            gpsData.f_longitudeDegrees += ((int)gpsData.f_longitude/100);
        }

        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            if (p[0] == 'W') gpsData.f_longitudeDegrees *= -1.0;
            if (p[0] == 'W') gpsData.c_lon = 'W';
            else if (p[0] == 'E') gpsData.c_lon = 'E';
            else if (p[0] == ',') gpsData.c_lon = 0;
        }

        p = strchr(p, ',')+1;
        p = strchr(p, ',')+1;
        p = strchr(p, ',')+1;
        p = strchr(p, ',')+1;
        p = strchr(p, ',')+1;
        p = strchr(p, ',')+1;

        return gpsData;
    }
    if (strstr(nmea, "$GPRMC")) {
        // found RMC
        char *p = nmea;

        // get time
        p = strchr(p, ',')+1;

        p = strchr(p, ',')+1;
        // Serial.println(p);
        if (p[0] == 'A')
            gpsData.u8_valid = 1;
        else if (p[0] == 'V')
            gpsData.u8_valid = 0;

        // parse out latitude
        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            strncpy(degreebuff, p, 2);
            p += 2;
            degreebuff[2] = '\0';
            long degree = atol(degreebuff) * 10000000;
            strncpy(degreebuff, p, 2); // minutes
            p += 3; // skip decimal point
            strncpy(degreebuff + 2, p, 4);
            degreebuff[6] = '\0';
            long minutes = 50 * atol(degreebuff) / 3;
            gpsData.i32_latitudeFixed = degree + minutes;
            gpsData.f_latitude = degree / 100000 + minutes * 0.000006F;
            gpsData.f_latitudeDegrees = (gpsData.f_latitude-100*((int)gpsData.f_latitude/100))/60.0;
            gpsData.f_latitudeDegrees += ((int)gpsData.f_latitude/100);
        }

        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            if (p[0] == 'S') gpsData.f_latitudeDegrees *= -1.0;
            if (p[0] == 'N') gpsData.c_lat = 'N';
            else if (p[0] == 'S') gpsData.c_lat = 'S';
            else if (p[0] == ',') gpsData.c_lat = 0;
        }

        // parse out longitude
        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            strncpy(degreebuff, p, 3);
            p += 3;
            degreebuff[3] = '\0';
            degree = atol(degreebuff) * 10000000;
            strncpy(degreebuff, p, 2); // minutes
            p += 3; // skip decimal point
            strncpy(degreebuff + 2, p, 4);
            degreebuff[6] = '\0';
            minutes = 50 * atol(degreebuff) / 3;
            gpsData.i32_longitudeFixed = degree + minutes;
            gpsData.f_longitude = degree / 100000 + minutes * 0.000006F;
            gpsData.f_longitudeDegrees = (gpsData.f_longitude-100*((int)gpsData.f_longitude/100))/60.0;
            gpsData.f_longitudeDegrees += ((int)gpsData.f_longitude/100);
        }

        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            if (p[0] == 'W') gpsData.f_longitudeDegrees *= -1.0;
            if (p[0] == 'W') gpsData.c_lon = 'W';
            else if (p[0] == 'E') gpsData.c_lon = 'E';
            else if (p[0] == ',') gpsData.c_lon = 0;
        }
        // speed
        p = strchr(p, ',')+1;

        // angle
        p = strchr(p, ',')+1;
        if (',' != *p)
        {
            gpsData.f_angle = atof(p);
        }

        p = strchr(p, ',')+1;
        // we dont parse the remaining, yet!
        return;
    }

    return;
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
        au8_String[u8_digit++] = '0' + (u16_x % 10000) / 1000;
    if (u16_x > 99)
        au8_String[u8_digit++] = '0' + (u16_x % 1000) / 100;
    if (u16_x > 9)
        au8_String[u8_digit++] = '0' + (u16_x % 100) / 10;
    au8_String[u8_digit++] = '0' + (u16_x % 10);
    au8_String[u8_digit] = 0;

    return au8_String;
}