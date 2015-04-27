#include "pic24_all.h"
#include "NeverWanderBand.h"
#include "screen_module.h"
#include "GPS_module.h"
#include "transceiver_module.h"
#include "timer_module.h"
#include "alert_module.h"
#include <math.h>

uint8_t u8_fParseParent;			//flag saying a packet from the parent is ready to be parsed
uint8_t u8_fParseChild;			//flag saying a packet from the child is ready to be parsed
uint8_t u8_fRecalcNeeded;		//flag saying the distance and direction need updated, raised by the parsers
uint8_t u8_fRecalcDone;			//flag saying the distance and direction have been updated and to do applicable alerts and displays, raised by the math calcs
uint8_t u8_fScreenChange;		//flag saying the screen needs to be changed, raised by recalc and timeouts

uint8_t u8_fParentStationary;            //flag denoting that the parent position stopped changing, so the parent's course might be wrong
uint8_t u8_fParentPacketInvalid;	//flag denoting the parent packet is invalid, error
uint8_t u8_fChildPacketInvalid;	//flag denoting the child packet is invalid, error
uint8_t u8_fChildTimeOut;		//flag denoting a timeout waiting for the child packet, error
uint8_t u8_fParentTimeOut;		//flag denoting a timeout waiting for the parent packet, error

#define clearFlags() do{u8_fParseParent=0; u8_fParseChild=0; u8_fRecalcNeeded=0; u8_fRecalcDone=0; u8_fParentStationary=0;\
						u8_fParentPacketInvalid=0; u8_fChildPacketInvalid=0; u8_fChildTimeOut=0; u8_fParentTimeOut=0; u8_fScreenChange = 0; }while(0)

enum states { 
    proximity2, proximity3, proximity4,proximity5
};

uint16_t u16_alertDist;

int main(void){
	configClock();
	configHeartbeat();
	configUartParent();
    configUartChild();
    configRMC1Hz();
    configChildRMC1Hz();
	//printResetCause();       //print statement about what caused reset
	outString(HELLO_MSG);
	configAlerts();
	configUI();
	configTimers();
	clearFlags();
	enableTimers();
	initScreen();
	const char *meters = "meters";
	const char *invalidParent = "Parent Invalid Location\n";
	const char *invalidChild = "Child Invalid Location\n";
	
	char ac_parentBuffer[256] = "$GPRMC,2213014.82,V,0,N,0,W,0,,,A*75";
    char ac_childBuffer[256] = "$GPRMC,2213014.82,V,0,N,0,W,0,,,A*75";

	st_gpsData parentGpsPosition, childGpsPosition;
	gpsDataTuple st_gpsTuple;
	uint16_t u16_distance;
	int16_t i16_angleNorth, i16_angleChild;

	enum states state = proximity2;
	u16_alertDist = 20;
	updateScreen();

	while(1){
		//check the parent UART buffer, getting all the packets and keeping the most recent
		while(parentPacketReady()){
			getParentPacket(ac_parentBuffer,256);
			resetParentPacketTimer();
			u8_fParentTimeOut = 0;
			
			u8_fParseParent = 1;
		}
		
		//check the child UART buffer, getting all the packets and keeping the most recent
		while(childPacketReady()){
			getChildPacket(ac_childBuffer,256);
			resetChildPacketTimer();
			u8_fChildTimeOut = 0;
			
			u8_fParseChild = 1;
		}

		if(SETTINGSMODE){
			state = settingsModeCycle(state);
		}
		
		//Parse the new parent packet
		if(u8_fParseParent && !SETTINGSMODE){
			u8_fParseParent = 0;
			parentGpsPosition = parseGpsPacket(ac_parentBuffer);
			
			if(parentGpsPosition.u8_valid){
				u8_fRecalcNeeded = 1;
				u8_fParentPacketInvalid = 0;
				if((parentMoveCheck(parentGpsPosition))==1){
					resetParentMovedTimer();
					u8_fParentStationary = 0;
				}
			}
			else{
				u8_fParentPacketInvalid = 1;
			}
		}
		
		//Parse the new child packet
		if(u8_fParseChild && !SETTINGSMODE){
			u8_fParseChild = 0;
			childGpsPosition = parseGpsPacket(ac_childBuffer);
			
			if(childGpsPosition.u8_valid){
				u8_fRecalcNeeded = 1;
				u8_fChildPacketInvalid = 0;
			}
			else{
				u8_fChildPacketInvalid = 1;
			}
		}
		
		//A position is new, recalculate the distance and direction
		if(u8_fRecalcNeeded && !SETTINGSMODE){
			u8_fRecalcNeeded = 0;
			u8_fRecalcDone = 1;
			
			u16_distance = calcDistanceMeters(parentGpsPosition, childGpsPosition);
			i16_angleNorth = normalizeAngle(parentGpsPosition.u16_angle);
			i16_angleChild = calcAngleDegrees(parentGpsPosition, childGpsPosition);
		}
		
		//The recalculations were finished
		if(u8_fRecalcDone && !SETTINGSMODE){
			u8_fRecalcDone = 0;
			u8_fScreenChange = 1;
			
			if((u16_distance > u16_alertDist)&&(!ERROROCCURRED)){
				startAlerts();
			}
			else {
				stopAlerts();
			}
		}
		
		//Something cause the screen to need to change outside of settings mode
		if((u8_fScreenChange || ERROROCCURRED) && !SETTINGSMODE){
			u8_fScreenChange = 0;
                        clearScreen();
                        resetCursor();
			
			//Did an error occur?
			if(ERROROCCURRED){
                            stopAlerts();
                            const char *errorMsg = "An Error has occured!!";
                            printCharacters(errorMsg,1,1);
                            if(u8_fParentPacketInvalid){
                                const char *invParMsg = "\nThe parent packet is invalid.";
                                printCharacters(invParMsg,1,1);
                            }
                            
                            if(u8_fChildPacketInvalid){
                                const char *invChiMsg = "\nThe child packet is invalid.";
                                printCharacters(invChiMsg,1,1);
                            }

                            if(u8_fChildTimeOut){
                                const char *chiTimeOMsg = "\nTimeout from the Child GPS";
                                printCharacters(chiTimeOMsg,1,1);
                            }

                            if(u8_fParentTimeOut){
                                const char *parTimeOMsg = "\nTimeout from the Parent GPS";
                                printCharacters(parTimeOMsg,1,1);
                            }
			}
			
			//Did the parent stop moving (making their direction from the gps wrong)
			else if(u8_fParentStationary){
				printCharacters(uitoa(u16_distance),1,1);
				printCharacters(meters,1,1);
                                giveAngleLetters(i16_angleChild);
				updateScreen();
			}
			
			//Everything is fine, act normal
			else{
				giveAngleDegrees(normalizeAngle(i16_angleChild - i16_angleNorth));
				printCharacters(uitoa(u16_distance),1,1);
				printCharacters(meters,1,1);
				updateScreen();
			}
                        updateScreen();
		}
		
	}
}


#define PI 3.1415926535

void configChildRMC1Hz(){
	const char *message = PMTK_SET_NEA_OUTPUT_RMCONLY;
	const char *message2 = PMTK_SET_NMEA_UPDATE_1HZ;
	transmitChildCommand(message);
	transmitChildCommand(message2);
}

void configChildRMC5Hz(){
	const char *message = PMTK_SET_NEA_OUTPUT_RMCONLY;
	const char *message2 = PMTK_SET_NMEA_UPDATE_5HZ;
	transmitChildCommand(message);
	transmitChildCommand(message2);
}


uint16_t calcDistanceMetersInternal(st_gpsData position1, st_gpsData position2){

    double d_diffLat = position1.f_latitude-position2.f_latitude;
    double d_diffLon = position1.f_longitude-position2.f_longitude;

    d_diffLat *= 111194.9267;  //meters per degree latititude for Starkville
    d_diffLon *= 92774.9406;   //meters per degree longitude for Starkville

    double d_calc = d_diffLat*d_diffLat + d_diffLon*d_diffLon;
    d_calc = sqrt(d_calc);

    uint16_t toBeReturned = ((uint16_t)d_calc);

    return toBeReturned;
}

/*********************************************************
*calcDistanceMeters
*calculates the distance between two gps positions in meters
*@position1: the first gps position
*@position2: the second gps position
*@return: the distance between the two points in meters
*********************************************************/
uint16_t calcDistanceMeters(st_gpsData position1, st_gpsData position2){
    uint16_t u16_firstReturn = calcDistanceMetersInternal(position1, position2);
    uint16_t u16_secondReturn = calcDistanceMetersInternal(position1, position2);

    if(u16_firstReturn != u16_secondReturn){
        return calcDistanceMeters(position1, position2);
    }
    return u16_firstReturn;
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

    double d_sinDLon = sin((position2.f_longitude - position1.f_longitude)*PI/180.0);
    double d_cosLat2 = cos((position2.f_latitude)*PI/180.0);

    double d_cosLat1 = cos((position1.f_latitude)*PI/180.0);
    double d_sinLat2 = sin((position2.f_latitude)*PI/180.0);
    double d_sinLat1 = sin((position1.f_latitude)*PI/180.0);
    double d_cosDLon = cos((position2.f_longitude - position1.f_longitude)*PI/180.0);

    double d_radDir = atan2(d_sinDLon*d_cosLat2, d_cosLat1*d_sinLat2 - d_sinLat1*d_cosLat2*d_cosDLon);

    int16_t i16_degDir = (int16_t)(d_radDir*180/PI);
    return i16_degDir;
}


//remove in future --toChange
/*********************************************************
*getGpsPositions
*gets the current position from the gps
*@return: the gps position of the parent and the child
*********************************************************/
gpsDataTuple getGpsPositions(){
    gpsDataTuple st_gpsPositions;
    char ac_parentBuffer[256] = "$GPRMC,2213014.82,V,0,N,0,W,0,,,A*75";
    char ac_childBuffer[256] = "$GPRMC,2213014.82,V,0,N,0,W,0,,,A*75";

    getParentPacket(ac_parentBuffer,256);
    getChildPacket(ac_childBuffer,256);

    st_gpsPositions.parentPosition = parseGpsPacket(ac_parentBuffer);
    st_gpsPositions.childPosition = parseGpsPacket(ac_childBuffer);

    u16_angle = st_gpsPositions.parentPosition.u16_angle;

    return st_gpsPositions;
}

int16_t normalizeAngle(int16_t i16_angle){
   int16_t i16_toBeReturned;

    if(i16_angle > 180){
        i16_toBeReturned = i16_angle - 360;
    }
    if(i16_angle < -180){
        i16_toBeReturned = i16_angle + 360;
    }
    else{
        i16_toBeReturned = i16_angle;
    }
    return i16_toBeReturned;
}


/*********************************************************
*getGpsDirection
*gets the current direction from the gps
*@return: the current direction of travel in degrees of -180 to 180
*********************************************************/
int16_t getDirection(){
   int16_t i16_toBeReturned;
   uint16_t u16_course;
   u16_course = u16_angle;
    if(u16_course > 180){
        i16_toBeReturned = u16_course -360;
    }
    else{
        i16_toBeReturned = u16_course;
    }
    return i16_toBeReturned;
};

/*********************************************************
*parentMoveCheck
*compares the current position of the parent with a previous
*  one to determine if the angle is accurate
*@parentPosition: the st_gpsData with the parent position
*@return:0 for not having moved enough, 1 for having moved
*********************************************************/
static st_gpsData previousPosition;
uint8_t parentMoveCheck(st_gpsData parentPosition){
        if((fabs(parentPosition.f_latitude - previousPosition.f_latitude) < 0.0000455) && (fabs(parentPosition.f_longitude - previousPosition.f_longitude) < .00005389)){
            return 0;
        }
        else{
            previousPosition = parentPosition;
            return 1;
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

/*********************************************************
*displayAngleLetters
*Displays letters on the screen at the specified angle
*@i16_angle: angle to point to, in degrees, between -180 and 180
*@return: nothing
*********************************************************/
void giveAngleLetters(int16_t i16_angle){
        setCursor(64,32);
        
	if (i16_angle >= -68 && i16_angle <= 68){
            char *c_N = "N";
            printCharacters(c_N , 1, 4);
        }
        else if (i16_angle > 113 || i16_angle <= -113){
            char *c_S = "S";
            printCharacters(c_S , 1, 4);
	}
        
        if (i16_angle > 23 && i16_angle <= 158){
            char *c_E = "E";
            printCharacters(c_E , 1, 4);
	}
        else if (i16_angle >= -158 && i16_angle < -23){
            char *c_W = "W";
            printCharacters(c_W , 1, 4);
	}
}

/*********************************************************
*displayAngleDegrees
*Displays an arrow on the screen at the specified angle
*@i16_angle: angle to point to, in degrees, between -180 and 180
*@return: nothing
*********************************************************/
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

enum states settingsModeCycle(enum states state){
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
			else if (BUTTON2_PRESSED) {
				DELAY_US(50);
				if BUTTON2_RELEASED{
					invertDisplay(1);
					u16_alertDist = 20;
					DELAY_MS(500);
					invertDisplay(0);
				}
			}
			else{
				clearDisplay();
				proximity20();
				display();
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
			else if BUTTON2_PRESSED{
				DELAY_US(50);
				if BUTTON2_RELEASED {
					invertDisplay(1);
					u16_alertDist = 30;
					DELAY_MS(500);
					invertDisplay(0);
				}
			}
			else{
				clearDisplay();
				proximity30();
				display();
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
			else if BUTTON2_PRESSED{
				DELAY_US(50);
				if BUTTON2_RELEASED{
					invertDisplay(1);
					u16_alertDist = 40;
					DELAY_MS(500);
					invertDisplay(0);
				}
			}
			else{
				clearDisplay();
				proximity40();
				display();
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
			else if BUTTON2_PRESSED{
				DELAY_US(50);
				if BUTTON2_RELEASED{
					invertDisplay(1);
					u16_alertDist = 50;
					DELAY_MS(500);
					invertDisplay(0);
				}
			}
			else{
				clearDisplay();
				proximity50();
				display();
			}
		break;
	
		default:
			state = proximity2;
			clearDisplay();
			proximity20();
			display();
		break;
	}
        return state;
}
