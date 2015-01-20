#ifndef _NEVERWANDERBAND_H_
#define _NEVERWANDERBAND_H_

typedef struct st_gpsCoordinate{
	uint8_t u8_hemisphereIndicator;
	uint8_t u8_degrees;
	uint8_t u8_minutes;
	uint8_t u8_centiSecondsMSB;
    uint8_t u8_centiSecondsLSB;
} st_gpsCoordinate;

//This is format of the data for transferring the positions between
//	the modules
typedef struct st_gpsData{
    uint8_t u8_valid;
    double f_latitude, f_longitude;
    uint16_t u16_angle;
    uint8_t u8_hours, u8_minutes, u8_seconds;
} st_gpsData;

typedef struct gpsDataTuple{
    st_gpsData parentPosition;
    st_gpsData childPosition;
} gpsDataTuple;


static uint8_t u8_fParseParent;			//flag saying a packet from the parent is ready to be parsed
static uint8_t u8_fParseChild;			//flag saying a packet from the child is ready to be parsed
static uint8_t u8_fRecalcNeeded;		//flag saying the distance and direction need updated, raised by the parsers
static uint8_t u8_fRecalcDone;			//flag saying the distance and direction have been updated and to do applicable alerts and displays, raised by the math calcs
static uint8_t u8_fScreenChange;		//flag saying the screen needs to be changed, raised by recalc and timeouts

static uint8_t u8_fParentStationary;	//flag denoting that the parent position stopped changing, so the parent's course might be wrong
static uint8_t u8_fParentPacketInvalid;	//flag denoting the parent packet is invalid, error
static uint8_t u8_fChildPacketInvalid;	//flag denoting the child packet is invalid, error
static uint8_t u8_fChildTimeOut;		//flag denoting a timeout waiting for the child packet, error
static uint8_t u8_fParentTimeOut;		//flag denoting a timeout waiting for the parent packet, error

/*********************************************************
*getGpsPositions
*gets the current position from the gps
*@return: the gps position of the parent and the child
*********************************************************/
gpsDataTuple getGpsPositions();


/*********************************************************
*getGpsDirection
*gets the current direction from the gps
*@return: the current direction of travel in degrees of -180 to 180
*********************************************************/
int16_t getDirection();


/*********************************************************
*calcDistanceMeters
*calculates the distance between two gps positions in meters
*@position1: the first gps position
*@position2: the second gps position
*@return: the distance between the two points in meters
*********************************************************/
uint16_t calcDistanceMeters(st_gpsData position1, st_gpsData position2);

/*********************************************************
*calcAngleDegrees
*calculates the angle of position2 with respect to position1
*	with 0 being North
*@position1: the first gps position
*@position2: the second gps position
*@return: degrees in the a range of -180 to 180
*********************************************************/
int16_t calcAngleDegrees(st_gpsData position1, st_gpsData position2);

/*********************************************************
*displayAngleDegrees
*Displays an arrow on the screen at the specified angle
*@i16_angle: angle to point to, in degrees, between -180 and 180
*@return: nothing
*********************************************************/
void giveAngleDegrees(int16_t i16_angle);

//void giveAngleWords(int16_t i16_angle);

/*********************************************************
*printCharacters
*prints the characters passed to it
*@ch_letters: array of characters to be printed, null terminated
*@return:none
*********************************************************/
void printCharacters(char* ch_letters, uint16_t color, uint16_t size);

/*********************************************************
*clearScreen
*clears the screen
*@return:none
*********************************************************/
void clearScreen();


/*********************************************************
*updateScreen
*will refresh screen and display whatevers in the buffer
*@return:none
*********************************************************/
void updateScreen();

/*********************************************************
*resetCursor
*resets cursor to 0,0
*@return:none
*********************************************************/
void resetCursor();

/*********************************************************
*parentMoveCheck
*compares the current position of the parent with a previous
*  one to determine if the angle is accurate
*@parentPosition: the st_gpsData with the parent position
*@return:0 for not having moved enough, 1 for having moved
*********************************************************/
uint8_t parentMoveCheck(st_gpsData parentPosition);

static uint16_t u16_angle;

#endif  //_NEVERWANDERBAND_H_
