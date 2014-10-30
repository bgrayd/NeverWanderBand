#ifndef _NEVERWANDERBAND_H_
#define _NEVERWANDERBAND_H_

typedef struct st_gpsCoordinate{
	uint8_t u8_hemisphereIndicator;
	uint8_t u8_degrees;
	uint8_t u8_minutes;
	uint8_t u8_seconds;
} st_gpsCoordinate;

//This is format of the data for transfering the positions between
//	the modules
typedef struct st_gpsPosition{
	st_gpsCoordinate latitude;
	st_gpsCoordinate longitude;
} st_gpsPosition;


/*********************************************************
*getGpsPosition
*gets the current position from the gps
*@return: the current gps position
*********************************************************/
st_gpsPosition getGpsPosition();

/*********************************************************
*getGpsPosition
*gets the current direction from the gps
*@return: the current direction of travel in degrees
*********************************************************/
uint8_t getDirection();

/*********************************************************
*transmitPosition
*send the gps position
*@gpsPosition: the position to transmit
*@return: none
*********************************************************/
void transmitPosition(st_gpsPosition gpsPosition);

/*********************************************************
*receivePosition
*get the gps position sent to it
*@return: the gps position transmitted
*********************************************************/
st_gpsPosition receivePosition();

/*********************************************************
*calcDistanceMeters
*calculates the distance between two gps positions in meters
*@position1: the first gps position
*@position2: the second gps position
*@return: the distance between the two points in meters
*********************************************************/
uint16_t calcDistanceMeters(st_gpsPosition position1, st_gpsPosition position2);

/*********************************************************
*calcAngleDegrees
*calculates the angle of position2 with respect to position1
*	with 0 being North
*@position1: the first gps position
*@position2: the second gps position
*@return: degrees in the a range of -180 to 180
*********************************************************/
int16_t calcAngleDegrees(st_gpsPosition position1, st_gpsPosition position2);

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
void printCharacters(char* ch_letters, uint16_t color, unit16_t size);

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

#endif  //_NEVERWANDERBAND_H_