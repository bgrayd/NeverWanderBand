#include "pic24_all.h"
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
	T2CON = T2_OFF | T2_IDLE_CON | T2_GATE_OFF | T2_32BIT_MODE_OFF | T2_SOURCE_INT | T2_PS_1_64;
	PR2 = msToU16Ticks(PARENTPACKETPERIODMS, getTimerPrescale(T2CONbits))-1;
	TMR2 = 0;
	_T2IF = 0;
	_T2IP = 1;
	_T2IE = 1;
}

/*********************************************************
*configTimerChildPacket
*configures the child packet timeout timer
*@return:none
*********************************************************/
void configTimerChildPacket(){
	T5CON = T5_OFF | T5_IDLE_CON | T5_GATE_OFF | T5_SOURCE_INT | T5_PS_1_64;
	PR5 = msToU16Ticks(CHILDPACKETPERIODMS, getTimerPrescale(T5CONbits))-1;
	TMR5 = 0;
	_T5IF = 0;
	_T5IP = 1;
	_T5IE = 1;
}

/*********************************************************
*configTimerParentMoved
*configures the parent moved timer
*@return:none
*********************************************************/
void configTimerParentMoved(){
	T4CON = T4_OFF | T4_IDLE_CON | T4_GATE_OFF | T4_32BIT_MODE_OFF | T4_SOURCE_INT | T4_PS_1_64;
	PR4 = msToU16Ticks(PARENTMOVEDPERIODMS, getTimerPrescale(T4CONbits))-1;
	TMR4 = 0;
	_T4IF = 0;
	_T4IP = 1;
	_T4IE = 1;
}

/*********************************************************
*enableTimers
*enables all three timers
*@return:none
*********************************************************/
void enableTimers(){
	enableTimerParentPacket();
	enableTimerChildPacket();
	enableTimerParentMoved();
}

/*********************************************************
*enableTimerParentPacket
*enables the parent packet timeout timer
*@return:none
*********************************************************/
void enableTimerParentPacket(){
	T2CONbits.TON = 1;
}

/*********************************************************
*enableTimerChildPacket
*enables the child packet timeout timer
*@return:none
*********************************************************/
void enableTimerChildPacket(){
	T5CONbits.TON = 1;
}

/*********************************************************
*enableTimerParentMoved
*enables the parent moved timer
*@return:none
*********************************************************/
void enableTimerParentMoved(){
	T4CONbits.TON = 1;
}

/*********************************************************
*disableTimers
*disables all three timers
*@return:none
*********************************************************/
void disableTimers(){
	disableTimerParentPacket();
	disableTimerChildPacket();
	disableTimerParentMoved();
}

/*********************************************************
*disableTimerParentPacket
*disables the parent packet timeout timer
*@return:none
*********************************************************/
void disableTimerParentPacket(){
	T2CONbits.TON = 0;
}

/*********************************************************
*disableTimerChildPacket
*disables the child packet timeout timer
*@return:none
*********************************************************/
void disableTimerChildPacket(){
	T5CONbits.TON = 0;
}

/*********************************************************
*disableTimerParentMoved
*disables the parent moved timer
*@return:none
*********************************************************/
void disableTimerParentMoved(){
	T4CONbits.TON = 0;
}

//Interrupt Service Routine for Timer2
void _ISRFAST _T2Interrupt(void){
	_T2IF = 0;
	u8_fParentTimeOut = 1;
	u8_fScreenChange = 1;
}

//Interrupt Service Routine for Timer5
void _ISRFAST _T5Interrupt(void){
	_T5IF = 0;
	u8_fChildTimeOut = 1;
	u8_fScreenChange = 1;
}

//Interrupt Service Routine for Timer4
void _ISRFAST _T4Interrupt(void){
	_T4IF = 0;
	u8_fParentStationary = 1;
}