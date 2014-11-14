#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"
#include "GPS_module.h"
#include "transceiver_module.h"
#include <math.h>

#ifndef PARENTBAND
#ifndef CHILDBAND
int main(void){
	configClock();
	configHeartbeat();
	configUART1(9600);
        configUartXbee();
	//printResetCause();       //print statement about what caused reset
	outString(HELLO_MSG);
	configRMC1Hz();
        initScreen();
	//const char *newLine = "\n";
        const char psz_latitude[11] = "Latitude:";
        const char psz_longitude[12] = "Longitude:";
        const char psz_time[7] = "Time:";
        const char psz_course[9] = "Course:";
	char sz_buffer[256];
	char *psz_input;
	psz_input = sz_buffer; 
	_RMCPacket RMCPacket;
        setTextColor(1);
        setTextSize(1);
       // display();
	while(1){
            clearDisplay();
            setCursor(0,0);
            /*psz_input = sz_buffer;
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
            //write(' ');
            writeString(uitoa(RMCPacket.position.latitude.u8_minutes));
            write(96);
            //write(' ');
            uint16_t u16_seconds = (((uint16_t)RMCPacket.position.latitude.u8_centiSecondsMSB<<8)&0xFF00) + (((uint16_t)RMCPacket.position.latitude.u8_centiSecondsLSB)&0x00FF);
            //writeString(uitoa(u16_seconds));
            char* pc_seconds = uitoa(u16_seconds);
            write(*(pc_seconds+0));
            write(*(pc_seconds+1));
            write('.');
            write(*(pc_seconds+2));
            write(*(pc_seconds+3));
            write(34);
            write('\n');
            writeString(psz_longitude);
            writeString(uitoa(RMCPacket.position.longitude.u8_degrees));
            write(0xA7);
            //write(' ');
            writeString(uitoa(RMCPacket.position.longitude.u8_minutes));
            write(96);
            //write(' ');
            u16_seconds = ((uint16_t)RMCPacket.position.longitude.u8_centiSecondsMSB<<8) + ((uint16_t)RMCPacket.position.longitude.u8_centiSecondsLSB);
            //writeString(uitoa(u16_seconds));
            pc_seconds = uitoa(u16_seconds);
            write(*(pc_seconds+0));
            write(*(pc_seconds+1));
            write('.');
            write(*(pc_seconds+2));
            write(*(pc_seconds+3));
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
            DELAY_MS(10);*/
            //write(receiveUint8Xbee());
            //display();
            sendUint8Xbee('1');
            char c_temp;
            c_temp = receiveUint8Xbee();
            outChar1(c_temp);
            DELAY_MS(10);
	};
}
#endif //CHILDBAND
#endif //PARENTBAND


#ifdef PARENTBAND
int main(void){
	configClock();
	configHeartbeat();
	configUART1(9600);
        configUartXbee();
	//printResetCause();       //print statement about what caused reset
	outString(HELLO_MSG);
	configRMC1Hz();
        initScreen();
        const char *meters = "meters";
        const char *invalidParent = "Parent Invalid Location\n";
        const char *invalidChild = "Child Invalid Location\n";
        st_gpsData parentGpsPosition, childGpsPosition;
        uint16_t u16_distance;
        int16_t i16_angleNorth, i16_angleChild;
        updateScreen();
        while(1){
            clearScreen();
            resetCursor();
            parentGpsPosition = getParentGpsPosition();
            childGpsPosition = getChildGpsPosition();
            if(!parentGpsPosition.u8_valid){
                printCharacters(invalidParent,1,1);
            }
            if(!childGpsPosition.u8_valid){
                printCharacters(invalidChild,1,1);
            }
            //printf("(%f;%f)",parentGpsPosition.f_latitudeDegrees,parentGpsPosition.f_latitude);
            u16_distance = calcDistanceMeters(parentGpsPosition, childGpsPosition);
            //i16_angleNorth = getDirection();
            i16_angleChild = calcAngleDegrees(parentGpsPosition, childGpsPosition);
            
            giveAngleDegrees(i16_angleNorth - i16_angleChild);
            printCharacters(uitoa(u16_distance),1,1);
            printCharacters(meters,1,1);
            outString(uitoa(u16_distance));
            outString(meters);
            updateScreen();
        }
}
#endif //PARENTBAND

#ifdef CHILDBAND
int main(void){
	configClock();
	configHeartbeat();
	configUART1(9600);
	//printResetCause();       //print statement about what caused reset
	outString(HELLO_MSG);
	configRMC1Hz();
        configUartXbee();
        st_gpsPosition childGpsPosition;
        while(1){
            childGpsPosition = getGpsPosition();
            transmitPosition(childGpsPosition);
        }
}
#endif //CHILDBAND


#define PI 3.1415926535
//#define radians PI/180.0
#define radians 0.01745329251



void configChildRMC1Hz(){
	//DELAY_MS(100);
	const char *message = PMTK_SET_NEA_OUTPUT_RMCONLY;
	const char *message2 = PMTK_SET_NMEA_UPDATE_1HZ;
	transmitChildCommand(message);
	transmitChildCommand(message2);
}


/*********************************************************
*calcDistanceMeters
*calculates the distance between two gps positions in meters
*@position1: the first gps position
*@position2: the second gps position
*@return: the distance between the two points in meters
*********************************************************/
uint16_t calcDistanceMeters(st_gpsData position1, st_gpsData position2){
    /*int16_t i16_dLatDeg = 0;
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

    return (uint16_t)u32_dis;*/

    double f_distCalc=0;
    double f_distCalc2=0;
    double f_distLat=0;
    double f_distLon=0;
    double f_lat1;
    double f_lat2;

    outString(uitoa(position1.f_longitude-position2.f_longitude));

    f_distLat=radians*(position2.f_latitudeDegrees/10000000.0 - position1.f_latitudeDegrees/10000000.0);
    f_lat1=radians*(position1.f_latitudeDegrees/10000000.0);
    f_lat2=radians*(position2.f_latitudeDegrees/10000000.0);
    f_distLon=radians*((position2.f_longitudeDegrees/10000000.0)-(position1.f_longitudeDegrees/10000000.0));

    f_distCalc = (sin(f_distLat/2.0)*sin(f_distLat/2.0));
    f_distCalc2= cos(position1.f_latitudeDegrees/10000000.0);
    f_distCalc2*=cos(position2.f_latitudeDegrees/10000000.0);
    f_distCalc2*=sin(f_distLon/2.0);
    f_distCalc2*=sin(f_distLon/2.0);
    f_distCalc +=f_distCalc2;

    f_distCalc=(2*atan2(sqrt(f_distCalc),sqrt(1.0-f_distCalc)));

    f_distCalc*=6371000.0; //Converting to meters
    outChar1('f');
    uint16_t u16_toBeReturned = ((uint16_t)f_distCalc);
    return u16_toBeReturned;

    
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
int16_t calcAngleDegrees(st_gpsData position1, st_gpsData position2){

    //double d_sinDLon = sin(position1.)

    //double d_radDir = atan2(sin(d_dLonRad)*cos(d_lat2),cos(d_lat1)*sin(d_lat2)-sin(d_lat1)*cos(d_lat2)*cos(d_dLonRad));
    //int16_t i16_degDir = (int16_t)(d_radDir*180/PI);
    //return i16_degDir;
    //printf("(%f;%f)",position1.f_latitudeDegrees,position1.f_latitude);
    return 1;
}


/*********************************************************
*getGpsPosition
*gets the current position from the gps
*@return: the current gps position
*********************************************************/
st_gpsData getParentGpsPosition(){
    char sz_buffer[256];
    char *psz_input;
    psz_input = sz_buffer;
    st_gpsData gpsPosition;
    inString(psz_input, 256);
    //outString(psz_input);
    gpsPosition = parseGpsPacket(psz_input);
    f_angle = gpsPosition.f_angle;
    return gpsPosition;
};


/*********************************************************
*getChildGpsPosition
*gets the current position from the Child gps from the xbee
*@return: the current gps position
*********************************************************/
st_gpsData getChildGpsPosition(){
    char sz_buffer[256];
    char *psz_input;
    psz_input = sz_buffer;
    st_gpsData gpsPosition;
    getChildPacket(psz_input, 256);
    outString(psz_input);
    gpsPosition = parseGpsPacket(psz_input);
    return gpsPosition;
}

/*********************************************************
*getGpsDirection
*gets the current direction from the gps
*@return: the current direction of travel in degrees of -180 to 180
*********************************************************/
int16_t getDirection(){
   int16_t i16_toBeReturned;
   uint16_t u16_course;
   //u16_course = getCourse();
    if(u16_course > 180){
        i16_toBeReturned = u16_course -360;
    }
    else{
        i16_toBeReturned = u16_course;
    }
    return i16_toBeReturned;// return 0;
};


void printCharacters(char* ch_letters, uint16_t color, uint16_t size){
    setTextColor(color);
    setTextSize(size);
	writeString(ch_letters);
}

void clearScreen(){
	clearDisplay();
}

void updateScreen(){
	display();
}

void resetCursor(){
	setCursor(0, 0);
}

void giveAngleDegrees(int16_t i16_angle){
	if (i16_angle >= -23 && i16_angle <= 23){
		drawArrowN();
        }
	else if (i16_angle > 23 && i16_angle <= 68){
		drawArrowNE();
	}
	else if (i16_angle > 68 && i16_angle <= 113){
		drawArrowE();
	}
	else if (i16_angle > 113 && i16_angle <= 158){
		drawArrowSE();
	}
	else if (i16_angle > 158 || i16_angle <= -158){
		drawArrowS();
	}
	else if (i16_angle >= -68 && i16_angle < -23){
		drawArrowNW();
	}
	else if (i16_angle >= -113 && i16_angle < -68){
		drawArrowW();
	}
	else if (i16_angle > -158 && i16_angle < -113){
		drawArrowSW();
	}
	
}
