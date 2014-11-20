#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"
#include "GPS_module.h"
#include "math.h"



//This is for testing different modules and will call the functions the way the parent or child will call them
int main(void) {
  configClock();
  configHeartbeat();
  configUART1(DEFAULT_BAUDRATE);
  CONFIG_RB0_AS_DIG_INPUT();
  CONFIG_RB1_AS_DIG_INPUT();
  CONFIG_RB14_AS_DIG_INPUT();
  //configUART2(DEFAULT_BAUDRATE);
  printResetCause();       //print statement about what caused reset
  outString(HELLO_MSG);
  initScreen();
  //ssd1306_command(0xA5);
  //display();
  //DELAY_MS(5000);
  //clearDisplay();
  //setTextColor(1);
  //setTextSize(1);
  //char *newLine = "30 m";
  //ssd1306_command(0xA3);
  //ssd1306_command(0x2F);
  //display();
  
 	//enum states { 
  	//proximity2, proximity3, proximity4,proximity5
//	};

	//enum states state = proximity2;
	//proximity20();
	//display();	

	while(1) {
	if SWITCH1_UP { 

	  switch(state) {
	  case proximity2:
		if (BUTTON1_PRESSED) {
			DELAY_US(50);
			if (BUTTON1_RELEASED) {
				state = proximity3;
				clearDisplay();
				proximity30();
				display();
			}
		}
		if (BUTTON2_PRESSED) {
			DELAY_US(50);
			if BUTTON2_RELEASED{
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}
	    break;
	  case proximity3:
		if BUTTON1_PRESSED{
			DELAY_US(50);
			if BUTTON1_RELEASED{
				state = proximity4;
				clearDisplay();
				proximity40();
				display();
			}
		}
		if BUTTON2_PRESSED{
			DELAY_US(50);
			if BUTTON2_RELEASED {
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}
	    break;
	  case proximity4:
		if BUTTON1_PRESSED{
			DELAY_US(50);
			if BUTTON1_RELEASED{
				state = proximity5;
				clearDisplay();
				proximity50();
				display();
			}
		}
		if BUTTON2_PRESSED{
			DELAY_US(50);
			if BUTTON2_RELEASED{
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}

	    break;
	  case proximity5:
		if BUTTON1_PRESSED{
			DELAY_US(50);
			if BUTTON1_RELEASED{
				state = proximity2;
				clearDisplay();
				proximity20();
				display();
			}
		}
		if BUTTON2_PRESSED{
			DELAY_US(50);
			if BUTTON2_RELEASED{
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}

	    break;
	  }
	}
	else{ 
		giveAngleDegrees(90);
		writeDistance(newLine);
		display();	
		clearDisplay();
		if SWITCH1_UP{
			proximity20();
			display();
		}
	}
	doHeartbeat();
  };
};

void movedRecently( uint8 u8_movedRecently){
}


void normalMode(char* distance, int16_t i16_angle){   //remember to add in error statements
	giveAngleDegrees(i16_angle);
	writeDistance(distance);
}

void settingsMode(){
	enum states { 
  	proximity20, proximity30, proximity40,proximity50
	};

	enum states state = proximity20;

	while(1) {
	  switch(state) {
	  case proximity20:
		if (BUTTON1_PRESSED) {
			DELAY_US(50);
			if (BUTTON1_RELEASED) {
				state = proximity30;
			}
		}
		if (BUTTON2_PRESSED) {
			DELAY_US(50);
			if BUTTON2_RELEASED{
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}
	    break;
	  case proximity30:
		if BUTTON1_PRESSED{
			DELAY_US(50);
			if BUTTON1_RELEASED{
				state = proximity40;
			}
		}
		if BUTTON2_PRESSED{
			DELAY_US(50);
			if BUTTON2_RELEASED {
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}
	    break;
	  case proximity40:
		if BUTTON1_PRESSED{
			DELAY_US(50);
			if BUTTON1_RELEASED{
				state = proximity50;
			}
		}
		if BUTTON2_PRESSED{
			DELAY_US(50);
			if BUTTON2_RELEASED{
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}

	    break;
	  case proximity50:
		if BUTTON1_PRESSED{
			DELAY_US(50);
			if BUTTON1_RELEASED{
				state = proximity20;
			}
		}
		if BUTTON2_PRESSED{
			DELAY_US(50);
			if BUTTON2_RELEASED{
			invertDisplay(1);
			DELAY_MS(500);
			invertDisplay(0);
			}
		}

	    break;
	  }
	}
}

void checkSwitch(void){
	if (SWITCH1_DOWN) {
	//	normalMode(distance,i16_angle);
	}
	else if (SWITCH1_UP){
		settingsMode();
	}
	else {
		char *error1 = "Error in Switch Position!";
		writeString(error1);
	}
}

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

void arrowAndDistance(int16_t i16_angle, uint16_t u16_distance){

}

void flashingScreen(){ 			//flashes for 5 seconds
	invertDisplay(1);
	DELAY_MS(1000);
	invertDisplay(0);
	DELAY_MS(1000);
	invertDisplay(1);
	DELAY_MS(1000);
	invertDisplay(0);
	DELAY_MS(1000);
	invertDisplay(1);
	DELAY_MS(1000);
	invertDisplay(0);
}


/*int main(void){
	configClock();
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
            st_gpsPosition position1, position2;
            position1.latitude.u8_degrees = 33;
            position1.latitude.u8_minutes = 27;
            position1.latitude.u8_centiSecondsMSB = 0x03;
            position1.latitude.u8_centiSecondsLSB = 0x3A;
            position1.latitude.u8_hemisphereIndicator = 1;
            position1.longitude.u8_degrees = 88;
            position1.longitude.u8_minutes = 47;
            position1.longitude.u8_centiSecondsMSB = 0x05;
            position1.longitude.u8_centiSecondsLSB = 0xA4;
            position1.longitude.u8_hemisphereIndicator = 0;

            position2.latitude.u8_degrees = 34;
            position2.latitude.u8_minutes = 27;
            position2.latitude.u8_centiSecondsMSB = 0x03;
            position2.latitude.u8_centiSecondsLSB = 0x3A;
            position2.latitude.u8_hemisphereIndicator = 1;
            position2.longitude.u8_degrees = 88;
            position2.longitude.u8_minutes = 47;
            position2.longitude.u8_centiSecondsMSB = 0x05;
            position2.longitude.u8_centiSecondsLSB = 0xA4;
            position2.longitude.u8_hemisphereIndicator = 0;
            uint16_t returned = calcDistanceMeters(position1, position2);
            outUint16(returned);
            returned = calcAngleDegrees(position1, position2);
            outString(newLine);
            outUint16(returned);
            while(1){doHeartbeat();};
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
				outUint8(RMCPacket.position.latitude.u8_centiSecondsMSB);
                                outUint8(RMCPacket.position.latitude.u8_centiSecondsLSB);
				outUint8(RMCPacket.position.longitude.u8_hemisphereIndicator);
				outUint8(RMCPacket.position.longitude.u8_degrees);
				WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
				outUint8(RMCPacket.position.longitude.u8_minutes);
				outUint8(RMCPacket.position.longitude.u8_centiSecondsMSB);
                                outUint8(RMCPacket.position.longitude.u8_centiSecondsLSB);
				outUint16(RMCPacket.u16_course);
				WAIT_UNTIL_TRANSMIT_COMPLETE_UART1();
				outString(newLine);
				break;
			default:
				break;
		}*/
//	};
//}



//#define PI 3.1415926535
//
///*********************************************************
//*calcDistanceMeters
//*calculates the distance between two gps positions in meters
//*@position1: the first gps position
//*@position2: the second gps position
//*@return: the distance between the two points in meters
//*********************************************************/
//uint16_t calcDistanceMeters(st_gpsPosition position1, st_gpsPosition position2){
//    int16_t i16_dLatDeg = 0;
//    int16_t i16_dLatMin = 0;
//    int32_t i32_dLatCSec = 0;
//    int16_t i16_dLonDeg = 0;
//    int16_t i16_dLonMin = 0;
//    int32_t i32_dLonCSec = 0;
//
//    uint16_t u16_tempcSecHolder = 0;
//
//    i16_dLatDeg = (int16_t)position1.latitude.u8_degrees - (int16_t)position2.latitude.u8_degrees;
//    i16_dLatMin = (int16_t)position1.latitude.u8_minutes - (int16_t)position2.latitude.u8_minutes;
//    i32_dLatCSec = (int32_t)(((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB);
//    u16_tempcSecHolder = ((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB;
//    i32_dLatCSec = i32_dLatCSec - ((int32_t) u16_tempcSecHolder);
//    i16_dLatMin += (i16_dLatDeg*60);
//    i32_dLatCSec += ((int32_t)(i16_dLatMin*60)*100);
//
//    i16_dLonDeg = (int16_t)position1.longitude.u8_degrees - (int16_t)position2.longitude.u8_degrees;
//    i16_dLonMin = (int16_t)position1.longitude.u8_minutes - (int16_t)position2.longitude.u8_minutes;
//    i32_dLonCSec = (int32_t)(((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB);
//    u16_tempcSecHolder = ((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB;
//    i32_dLonCSec = i32_dLonCSec - ((int32_t) u16_tempcSecHolder);
//    i16_dLonMin += (i16_dLonDeg*60);
//    i32_dLonCSec += ((int32_t)(i16_dLonMin*60)*100);
//
//    uint32_t u32_latDis = 0;
//    uint32_t u32_lonDis = 0;
//    uint32_t u32_dis = 0;
//    u32_latDis = (i32_dLatCSec > 0) ? i32_dLatCSec : -i32_dLatCSec;
//    u32_lonDis = (i32_dLonCSec > 0) ? i32_dLonCSec : -i32_dLonCSec;
//    u32_latDis *= .3102;
//    u32_lonDis *= .2680;
//
//    u32_dis = u32_lonDis*u32_lonDis + u32_latDis*u32_latDis;
//    u32_dis = sqrt(u32_dis);
//
//    return (uint16_t)u32_dis;
//    
//    /*double d_lat1 = ((double)position1.latitude.u8_degrees + ((double)position1.latitude.u8_minutes)/60 +((double)((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB)/360000) * PI /180;
//    double d_lon1 = ((double)position1.longitude.u8_degrees + ((double)position1.longitude.u8_minutes)/60 +((double)((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB)/360000) * PI /180;
//    double d_lat2 = ((double)position2.latitude.u8_degrees + ((double)position2.latitude.u8_minutes)/60 +((double)((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB)/360000) * PI /180;
//    double d_lon2 = ((double)position2.longitude.u8_degrees + ((double)position2.longitude.u8_minutes)/60 +((double)((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB)/360000) * PI /180;
//    d_lat1 = position1.latitude.u8_hemisphereIndicator ? d_lat1 : -d_lat1;
//    d_lon1 = position1.longitude.u8_hemisphereIndicator ? d_lon1 : -d_lon1;
//    d_lat2 = position2.latitude.u8_hemisphereIndicator ? d_lat2 : -d_lat2;
//    d_lon2 = position2.longitude.u8_hemisphereIndicator ? d_lon2 : -d_lon2;
//
//    double d_dist = acos(sin(d_lat1)*sin(d_lat2)+cos(d_lat1)*cos(d_lat2)*cos(d_lon2-d_lon1))*6371000;
//
//    uint16_t u16_distance = (uint16_t)d_dist;
//    return u16_distance;*/
//}
//
///*********************************************************
//*calcAngleDegrees
//*calculates the angle of position2 with respect to position1
//*	with 0 being North
//*@position1: the first gps position
//*@position2: the second gps position
//*@return: degrees in the a range of -180 to 180
//*********************************************************/
//int16_t calcAngleDegrees(st_gpsPosition position1, st_gpsPosition position2){
//    int16_t i16_dLatDeg = 0;
//    int16_t i16_dLatMin = 0;
//    int32_t i32_dLatCSec = 0;
//    int16_t i16_dLonDeg = 0;
//    int16_t i16_dLonMin = 0;
//    int32_t i32_dLonCSec = 0;
//
//    uint16_t u16_tempcSecHolder = 0;
//
//    i16_dLatDeg = (int16_t)position1.latitude.u8_degrees - (int16_t)position2.latitude.u8_degrees;
//    i16_dLatMin = (int16_t)position1.latitude.u8_minutes - (int16_t)position2.latitude.u8_minutes;
//    i32_dLatCSec = (int32_t)(((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB);
//    u16_tempcSecHolder = ((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB;
//    i32_dLatCSec = i32_dLatCSec - ((int32_t) u16_tempcSecHolder);
//    i16_dLatMin += (i16_dLatDeg*60);
//    i32_dLatCSec += ((int32_t)(i16_dLatMin*60)*100);
//
//    i16_dLonDeg = (int16_t)position1.longitude.u8_degrees - (int16_t)position2.longitude.u8_degrees;
//    i16_dLonMin = (int16_t)position1.longitude.u8_minutes - (int16_t)position2.longitude.u8_minutes;
//    i32_dLonCSec = (int32_t)(((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB);
//    u16_tempcSecHolder = ((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB;
//    i32_dLonCSec = i32_dLonCSec - ((int32_t) u16_tempcSecHolder);
//    i16_dLonMin += (i16_dLonDeg*60);
//    i32_dLonCSec += ((int32_t)(i16_dLonMin*60)*100);
//
//    //double d_dLatRad = (((double) i32_dLatCSec)/360000) *PI/180;
//    double d_dLonRad = (((double) i32_dLonCSec)/360000) *PI/180;
//    double d_lat1 = ((double)position1.latitude.u8_degrees + ((double)position1.latitude.u8_minutes)/60 +((double)((uint16_t)position1.latitude.u8_centiSecondsMSB<<8) + position1.latitude.u8_centiSecondsLSB)/360000) * PI /180;
//    //double d_lon1 = ((double)position1.longitude.u8_degrees + ((double)position1.longitude.u8_minutes)/60 +((double)((uint16_t)position1.longitude.u8_centiSecondsMSB<<8) + position1.longitude.u8_centiSecondsLSB)/360000) * PI /180;
//    double d_lat2 = ((double)position2.latitude.u8_degrees + ((double)position2.latitude.u8_minutes)/60 +((double)((uint16_t)position2.latitude.u8_centiSecondsMSB<<8) + position2.latitude.u8_centiSecondsLSB)/360000) * PI /180;
//    //double d_lon2 = ((double)position2.longitude.u8_degrees + ((double)position2.longitude.u8_minutes)/60 +((double)((uint16_t)position2.longitude.u8_centiSecondsMSB<<8) + position2.longitude.u8_centiSecondsLSB)/360000) * PI /180;
//
//    d_lat1 = position1.latitude.u8_hemisphereIndicator ? d_lat1 : -d_lat1;
//    d_lat2 = position2.latitude.u8_hemisphereIndicator ? d_lat2 : -d_lat2;
//
//    double d_radDir = atan2(sin(d_dLonRad)*cos(d_lat2),cos(d_lat1)*sin(d_lat2)-sin(d_lat1)*cos(d_lat2)*cos(d_dLonRad));
//    int16_t i16_degDir = (int16_t)(d_radDir*180/PI);
//    return i16_degDir;
//}


