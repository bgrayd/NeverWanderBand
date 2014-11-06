#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"
#include "GPS_module.h"
#include "math.h"

#ifndef PARENTBAND
#ifndef CHILDBAND
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
        const char psz_course[9] = "Coursr: ";
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
                            RMCPacket = parseRMCPacket(psz_input);
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
            //writeString(uitoa(RMCPacket.position.latitude.u8_centiseconds));
            write(34);
            write('\n');
            writeString(psz_longitude);
            writeString(uitoa(RMCPacket.position.longitude.u8_degrees));
            write(0xA7);
            write(' ');
            writeString(uitoa(RMCPacket.position.longitude.u8_minutes));
            write(96);
            write(' ');
            //writeString(uitoa(RMCPacket.position.longitude.u8_seconds));
            write(34);
            write('\n');
            writeString(psz_time);
            writeString(uitoa(RMCPacket.u8_hours));
            write(':');
            writeString(uitoa(RMCPacket.u8_minutes));
            write(':');
            writeString(uitoa(RMCPacket.u8_seconds));
            write('\n');
            writeString(psz_course);
            writeString(uitoa(RMCPacket.u16_course));
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
#endif
#endif

#ifdef PARENTBAND

#endif

#ifdef CHILDBAND

#endif


#define PI 3.1415926535

/*********************************************************
*calcDistanceMeters
*calculates the distance between two gps positions in meters
*@position1: the first gps position
*@position2: the second gps position
*@return: the distance between the two points in meters
*********************************************************/
uint16_t calcDistanceMeters(st_gpsPosition position1, st_gpsPosition position2){
    int16_t i16_dLatDeg = 0;
    int16_t i16_dLatMin = 0;
    int32_t i32_dLatCSec = 0;
    int16_t i16_dLonDeg = 0;
    int16_t i16_dLonMin = 0;
    int32_t i32_dLonCSec = 0;

    uint16_t u16_tempcSecHolder = 0;

    i16_dLatDeg = (int16_t)position1.latitude.u8_degrees - (int16_t)position2.latitude.u8_degrees;
    i16_dLatMin = (int16_t)position1.latitude.u8_minutes - (int16_t)position2.latitude.u8_minutes;
    i32_dLatCSec = (int32_t)(((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB);
    u16_tempcSecHolder = ((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB;
    i32_dLatCSec = i32_dLatCSec - ((int32_t) u16_tempcSecHolder);
    i16_dLatMin += (i16_dLatDeg*60);
    i32_dLatCSec += ((int32_t)(i16_dLatMin*60)*100);

    i16_dLonDeg = (int16_t)position1.longitude.u8_degrees - (int16_t)position2.longitude.u8_degrees;
    i16_dLonMin = (int16_t)position1.longitude.u8_minutes - (int16_t)position2.longitude.u8_minutes;
    i32_dLonCSec = (int32_t)(((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB);
    u16_tempcSecHolder = ((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB;
    i32_dLonCSec = i32_dLonCSec - ((int32_t) u16_tempcSecHolder);
    i16_dLonMin += (i16_dLonDeg*60);
    i32_dLonCSec += ((int32_t)(i16_dLonMin*60)*100);

    uint32_t u32_latDis = 0;
    uint32_t u32_lonDis = 0;
    uint32_t u32_dis = 0;
    u32_latDis = (i32_dLatCSec > 0) ? i32_dLatCSec : -i32_dLatCSec;
    u32_lonDis = (i32_dLonCSec > 0) ? i32_dLonCSec : -i32_dLonCSec;
    u32_latDis *= .3102;
    u32_lonDis *= .2680;

    u32_dis = u32_lonDis*u32_lonDis + u32_latDis*u32_latDis;
    u32_dis = sqrt(u32_dis);

    return (uint16_t)u32_dis;
    
    /*double d_lat1 = ((double)position1.latitude.u8_degrees + ((double)position1.latitude.u8_minutes)/60 +((double)((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB)/360000) * PI /180;
    double d_lon1 = ((double)position1.longitude.u8_degrees + ((double)position1.longitude.u8_minutes)/60 +((double)((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB)/360000) * PI /180;
    double d_lat2 = ((double)position2.latitude.u8_degrees + ((double)position2.latitude.u8_minutes)/60 +((double)((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB)/360000) * PI /180;
    double d_lon2 = ((double)position2.longitude.u8_degrees + ((double)position2.longitude.u8_minutes)/60 +((double)((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB)/360000) * PI /180;
    d_lat1 = position1.latitude.u8_hemisphereIndicator ? d_lat1 : -d_lat1;
    d_lon1 = position1.longitude.u8_hemisphereIndicator ? d_lon1 : -d_lon1;
    d_lat2 = position2.latitude.u8_hemisphereIndicator ? d_lat2 : -d_lat2;
    d_lon2 = position2.longitude.u8_hemisphereIndicator ? d_lon2 : -d_lon2;

    double d_dist = acos(sin(d_lat1)*sin(d_lat2)+cos(d_lat1)*cos(d_lat2)*cos(d_lon2-d_lon1))*6371000;

    uint16_t u16_distance = (uint16_t)d_dist;
    return u16_distance;*/
}

/*********************************************************
*calcAngleDegrees
*calculates the angle of position2 with respect to position1
*	with 0 being North
*@position1: the first gps position
*@position2: the second gps position
*@return: degrees in the a range of -180 to 180
*********************************************************/
int16_t calcAngleDegrees(st_gpsPosition position1, st_gpsPosition position2){
    int16_t i16_dLatDeg = 0;
    int16_t i16_dLatMin = 0;
    int32_t i32_dLatCSec = 0;
    int16_t i16_dLonDeg = 0;
    int16_t i16_dLonMin = 0;
    int32_t i32_dLonCSec = 0;

    uint16_t u16_tempcSecHolder = 0;

    i16_dLatDeg = (int16_t)position1.latitude.u8_degrees - (int16_t)position2.latitude.u8_degrees;
    i16_dLatMin = (int16_t)position1.latitude.u8_minutes - (int16_t)position2.latitude.u8_minutes;
    i32_dLatCSec = (int32_t)(((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB);
    u16_tempcSecHolder = ((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB;
    i32_dLatCSec = i32_dLatCSec - ((int32_t) u16_tempcSecHolder);
    i16_dLatMin += (i16_dLatDeg*60);
    i32_dLatCSec += ((int32_t)(i16_dLatMin*60)*100);

    i16_dLonDeg = (int16_t)position1.longitude.u8_degrees - (int16_t)position2.longitude.u8_degrees;
    i16_dLonMin = (int16_t)position1.longitude.u8_minutes - (int16_t)position2.longitude.u8_minutes;
    i32_dLonCSec = (int32_t)(((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB);
    u16_tempcSecHolder = ((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB;
    i32_dLonCSec = i32_dLonCSec - ((int32_t) u16_tempcSecHolder);
    i16_dLonMin += (i16_dLonDeg*60);
    i32_dLonCSec += ((int32_t)(i16_dLonMin*60)*100);

    //double d_dLatRad = (((double) i32_dLatCSec)/360000) *PI/180;
    double d_dLonRad = (((double) i32_dLonCSec)/360000) *PI/180;
    double d_lat1 = ((double)position1.latitude.u8_degrees + ((double)position1.latitude.u8_minutes)/60 +((double)((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB)/360000) * PI /180;
    //double d_lon1 = ((double)position1.longitude.u8_degrees + ((double)position1.longitude.u8_minutes)/60 +((double)((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB)/360000) * PI /180;
    double d_lat2 = ((double)position2.latitude.u8_degrees + ((double)position2.latitude.u8_minutes)/60 +((double)((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB)/360000) * PI /180;
    //double d_lon2 = ((double)position2.longitude.u8_degrees + ((double)position2.longitude.u8_minutes)/60 +((double)((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB)/360000) * PI /180;

    d_lat1 = position1.latitude.u8_hemisphereIndicator ? d_lat1 : -d_lat1;
    d_lat2 = position2.latitude.u8_hemisphereIndicator ? d_lat2 : -d_lat2;

    double d_radDir = atan2(sin(d_dLonRad)*cos(d_lat2),cos(d_lat1)*sin(d_lat2)-sin(d_lat1)*cos(d_lat2)*cos(d_dLonRad));
    int16_t i16_degDir = (int16_t)(d_radDir*180/PI);
    return i16_degDir;
}
