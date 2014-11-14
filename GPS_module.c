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


/*st_gpsData parseGpsPacket(char *nmea) {
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
        return gpsData;
    }

    return;
}*/

st_gpsData parseGpsPacket(char *psz_s){
    st_gpsData gpsData;

    if((*(psz_s+1)=='G')&&(*(psz_s+2)=='P')&&(*(psz_s+3)=='R')&&(*(psz_s+4)=='M')&&(*(psz_s+5)=='C')){
        //I need to go back and change the magic number is defined constants
        gpsData.u8_hours = ((*(psz_s+7)-48)*10 + (*(psz_s+8)-48));
        gpsData.u8_minutes = ((*(psz_s+9)-48)*10 + (*(psz_s+10)-48));
        gpsData.u8_seconds = ((*(psz_s+11)-48)*10 + (*(psz_s+12)-48));
        gpsData.u8_valid = (*(psz_s+18))=='A';

        if(gpsData.u8_valid == 0){
            gpsData.f_latitude = 0;
            gpsData.f_longitude = 0;

            return gpsData;
        }

        st_gpsCoordinate latitude, longitude;

        latitude.u8_hemisphereIndicator = (*(psz_s+30))=='N';
        latitude.u8_degrees = ((*(psz_s+20)-48)*10 + (*(psz_s+21)-48));
        latitude.u8_minutes = ((*(psz_s+22)-48)*10 + (*(psz_s+23)-48));
        gpsData.f_latitude = ((*(psz_s+25)-48)*600 + (*(psz_s+26)-48)*60 + (*(psz_s+27)-48)*6+(*(psz_s+28)-48)*6/10);   //centiseconds
        outChar1('(');
        outString(uitoa(latitude.u8_degrees));
        outChar1(',');
        outString(uitoa(latitude.u8_minutes));
        outChar1(',');
        outString(uitoa(gpsData.f_latitude/100));
        outChar1(';');


        gpsData.f_latitude = ((gpsData.f_latitude/100.0)/60.0);                                                         //minutes
        gpsData.f_latitude += latitude.u8_minutes;                                                                      //minutes
        gpsData.f_latitude = (gpsData.f_latitude/60.0);                                                                 //degrees
        gpsData.f_latitude += latitude.u8_degrees;                                                                      //degrees
        gpsData.f_latitude *= (latitude.u8_hemisphereIndicator) ? 1:-1;                                                 //degrees

        longitude.u8_hemisphereIndicator = (*(psz_s+43))=='E';
        longitude.u8_degrees = ((*(psz_s+32)-48)*100 + (*(psz_s+33)-48)*10 + (*(psz_s+34)-48));
        longitude.u8_minutes = ((*(psz_s+35)-48)*10 + (*(psz_s+36)-48));
        gpsData.f_longitude = ((*(psz_s+38)-48)*600 + (*(psz_s+39)-48)*60 + (*(psz_s+40)-48)*6+(*(psz_s+41)-48)*6/10);   //centiseconds

        outString(uitoa(longitude.u8_degrees));
        outChar1(',');
        outString(uitoa(longitude.u8_minutes));
        outChar1(',');
        outString(uitoa(gpsData.f_longitude/100));
        outChar1(')');

        gpsData.f_longitude = ((gpsData.f_longitude/100.0)/60.0);                                                         //minutes
        gpsData.f_longitude += longitude.u8_minutes;                                                                      //minutes
        gpsData.f_longitude = (gpsData.f_longitude/60.0);                                                                 //degrees
        gpsData.f_longitude += longitude.u8_degrees;                                                                      //degrees
        gpsData.f_longitude *= (longitude.u8_hemisphereIndicator) ? 1:-1;                                                 //degrees


        uint8_t u8_counter = 43+2;
        while(u8_counter <= 254){
            //loop past the speed over ground
            if(*(psz_s + u8_counter) == ',')
                break;
            u8_counter++;
        }
        u8_counter++;

        gpsData.f_angle = 0;

        //the course has a varying length of whole numbers and a decimal
        while(u8_counter <=254){
            if(*(psz_s + u8_counter) == '.')
                break;
            gpsData.f_angle *= 10;
            gpsData.f_angle += (*(psz_s + u8_counter)-48);
            u8_counter++;
        }

        return gpsData;
    }

    return gpsData;
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