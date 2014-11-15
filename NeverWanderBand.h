#ifndef _NEVERWANDERBAND_H_
#define _NEVERWANDERBAND_H_

typedef struct st_gpsCoordinate{
	uint8_t u8_hemisphereIndicator;
	uint8_t u8_degrees;
	uint8_t u8_minutes;
	uint8_t u8_centiSecondsMSB;
        uint8_t u8_centiSecondsLSB;
} st_gpsCoordinate;

//This is format of the data for transfering the positions between
//	the modules
typedef struct st_gpsData{
    uint8_t u8_valid;
    double f_latitude, f_longitude;
    float f_angle;
    uint8_t u8_hours, u8_minutes, u8_seconds;
} st_gpsData;

typedef struct gpsDataTuple{
    st_gpsData parentPosition;
    st_gpsData childPosition;
} gpsDataTuple;

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

static float f_angle;

#endif  //_NEVERWANDERBAND_H_
