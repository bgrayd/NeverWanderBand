#ifndef _TIMERMODULE_H_
#define _TIMERMODULE_H_

#include "pic24_all.h"
#include "NeverWanderBand.h"

//these should set the timer counter to 0 --toChange
#define resetParentPacketTimer()	1
#define resetChildPacketTimer()		1
#define resetParentMovedTimer()		1

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

/*******************************
--toChange
parentPacketTimer raises u8_fParentPacketTimeOut, u8_fScreenChange
childPacketTimer raises u8_fChildPacketTimeOut, u8_fScreenChange
parentMovedTimer raises u8_fParentStationary
*******************************/


#endif //__TIMERMODULE_H_