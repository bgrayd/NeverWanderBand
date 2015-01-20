#ifndef _TIMERMODULE_H_
#define _TIMERMODULE_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"


#define resetParentPacketTimer()	TMR2=0
#define resetChildPacketTimer()		TMR5=0
#define resetParentMovedTimer()		TMR4=0

#define PARENTPACKETPERIODMS	2000
#define CHILDPACKETPERIODMS		2000
#define PARENTMOVEDPERIODMS		10000

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