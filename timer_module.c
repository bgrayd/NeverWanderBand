#include "timer_module.h"

/*********************************************************
*configTimers
*configures all three timers
*@return:none
*********************************************************/
void configTimers(){
	configTimerParentPacket();
	configTimerChildPacket();
	configTimerParentMoved();
}

/*********************************************************
*configTimerParentPacket
*configures the parent packet timeout timer
*@return:none
*********************************************************/
void configTimerParentPacket(){

}

/*********************************************************
*configTimerChildPacket
*configures the child packet timeout timer
*@return:none
*********************************************************/
void configTimerChildPacket(){

}

/*********************************************************
*configTimerParentMoved
*configures the parent moved timer
*@return:none
*********************************************************/
void configTimerParentMoved(){

}

/*******************************
--toChange
parentPacketTimer raises u8_fParentPacketTimeOut, u8_fScreenChange
childPacketTimer raises u8_fChildPacketTimeOut, u8_fScreenChange
parentMovedTimer raises u8_fParentStationary
*******************************/