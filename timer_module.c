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
	configTimerQuarterSecond();
}

/*********************************************************
*configTimerParentPacket
*configures the parent packet timeout timer
*@return:none
*********************************************************/
void configTimerParentPacket(){
	T3CON = T3_OFF | T3_IDLE_CON | T3_GATE_OFF | T3_SOURCE_INT | T3_PS_1_256;
	PR3 = PARENTPACKETPERIODS << 2;
	TMR3 = 0;
	_T3IF = 0;
	_T3IP = 1;
	_T3IE = 0;
}

/*********************************************************
*configTimerChildPacket
*configures the child packet timeout timer
*@return:none
*********************************************************/
void configTimerChildPacket(){
	T5CON = T5_OFF | T5_IDLE_CON | T5_GATE_OFF | T5_SOURCE_INT | T5_PS_1_256;
	PR5 = CHILDPACKETPERIODS << 2;
	TMR5 = 0;
	_T5IF = 0;
	_T5IP = 1;
	_T5IE = 0;
}

/*********************************************************
*configTimerParentMoved
*configures the parent moved timer
*@return:none
*********************************************************/
void configTimerParentMoved(){
	T4CON = T4_OFF | T4_IDLE_CON | T4_GATE_OFF | T4_32BIT_MODE_OFF | T4_SOURCE_INT | T4_PS_1_256;
	PR4 = PARENTMOVEDPERIODS << 2;
	TMR4 = 0;
	_T4IF = 0;
	_T4IP = 1;
	_T4IE = 0;
}

/*********************************************************
*configTimerSecond
*configures one second timer
*@return:none
*********************************************************/
void configTimerQuarterSecond(){
	T2CON = T2_OFF | T2_IDLE_CON | T2_GATE_OFF | T2_32BIT_MODE_OFF | T2_SOURCE_INT | T2_PS_1_256;
	PR2 = msToU16Ticks(250, getTimerPrescale(T2CONbits))-1;
	TMR2 = 0;
	_T2IF = 0;
	_T2IP = 1;
	_T2IE = 0;
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
	_T3IE = 1;
	enableTimerQuarterSecond();
}

/*********************************************************
*enableTimerChildPacket
*enables the child packet timeout timer
*@return:none
*********************************************************/
void enableTimerChildPacket(){
	_T5IE = 1;
	enableTimerQuarterSecond();
}

/*********************************************************
*enableTimerParentMoved
*enables the parent moved timer
*@return:none
*********************************************************/
void enableTimerParentMoved(){
	_T4IE = 1;
	enableTimerQuarterSecond();
}

/*********************************************************
*enableTimerSecond
*enables the parent moved timer
*@return:none
*********************************************************/
void enableTimerQuarterSecond(){
	T2CONbits.TON = 1;
	_T2IE = 1;
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
	T3CONbits.TON = 0;
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

//Interrupt Service Routine for Timer3
void _ISR _T3Interrupt(void){
	_T3IF = 0;
        TMR3 = 0;
	u8_fParentTimeOut = 1;
	u8_fScreenChange = 1;
}

//Interrupt Service Routine for Timer5
void _ISR _T5Interrupt(void){
	_T5IF = 0;
        TMR5 = 0;
	u8_fChildTimeOut = 1;
	u8_fScreenChange = 1;
}

//Interrupt Service Routine for Timer4
void _ISR _T4Interrupt(void){
	_T4IF = 0;
        TMR4 = 0;
	u8_fParentStationary = 1;
}

//Interrupt Service Routine for Timer6
void _ISR _T2Interrupt(void){
	_T2IF = 0;
	TMR3++;
	TMR5++;
	TMR4++;
	_T3IF = (PR3 == TMR3);
        _T4IF = (PR4 == TMR4);
        _T5IF = (PR5 == TMR5);
}