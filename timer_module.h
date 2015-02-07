#ifndef _TIMERMODULE_H_
#define _TIMERMODULE_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"


#define resetParentPacketTimer()	TMR3=0
#define resetChildPacketTimer()		TMR5=0
#define resetParentMovedTimer()		TMR4=0

#define PARENTPACKETPERIODS	3
#define CHILDPACKETPERIODS	3
#define PARENTMOVEDPERIODS	10

/*********************************************************
*configTimers
*configures all three timers
*@return:none
*********************************************************/
void configTimers();

/*********************************************************
*configTimerParentPacket
*configures the parent packet timeout timer
*@return:none
*********************************************************/
void configTimerParentPacket();

/*********************************************************
*configTimerChildPacket
*configures the child packet timeout timer
*@return:none
*********************************************************/
void configTimerChildPacket();

/*********************************************************
*configTimerParentMoved
*configures the parent moved timer
*@return:none
*********************************************************/
void configTimerParentMoved();

/*********************************************************
*configTimerSecond
*configures one second timer
*@return:none
*********************************************************/
void configTimerQuarterSecond();

/*********************************************************
*enableTimers
*enables all three timers
*@return:none
*********************************************************/
void enableTimers();

/*********************************************************
*enableTimerParentPacket
*enables the parent packet timeout timer
*@return:none
*********************************************************/
void enableTimerParentPacket();

/*********************************************************
*enableTimerChildPacket
*enables the child packet timeout timer
*@return:none
*********************************************************/
void enableTimerChildPacket();

/*********************************************************
*enableTimerParentMoved
*enables the parent moved timer
*@return:none
*********************************************************/
void enableTimerParentMoved();

/*********************************************************
*enableTimerSecond
*enables the parent moved timer
*@return:none
*********************************************************/
void enableTimerQuarterSecond();

/*********************************************************
*disableTimers
*disables all three timers
*@return:none
*********************************************************/
void disableTimers();

/*********************************************************
*disableTimerParentPacket
*disables the parent packet timeout timer
*@return:none
*********************************************************/
void disableTimerParentPacket();

/*********************************************************
*disableTimerChildPacket
*disables the child packet timeout timer
*@return:none
*********************************************************/
void disableTimerChildPacket();

/*********************************************************
*disableTimerParentMoved
*disables the parent moved timer
*@return:none
*********************************************************/
void disableTimerParentMoved();

#endif //__TIMERMODULE_H_