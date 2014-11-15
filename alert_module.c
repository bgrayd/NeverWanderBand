#include "alert_module.h"
#include "pic24_all.h"

#define config_buzzer_pin() CONFIG_RB4_AS_DIG_OUTPUT()
#define config_vibrat_pin() CONFIG_RA4_AS_DIG_OUTPUT()
#define buzzer _LATB4
#define vibrator _LATA4

#define buzzEn 0x01
#define vibrEn 0x02
#define shiftBuzz 0
#define shiftVibr 1
#define buzzMask 0xFE
#define vibrMask 0xFD


static uint8_t u8_enabledAlerts;

void _ISR _T3Interrupt (void) {
	buzzer = !buzzer;
	_T3IF = 0;                //clear T3 interrupt flag
}

void configTimer3(void) {
	T3CONbits.TON = 0;
	T3CON = T3_PS_1_1 | T3_SOURCE_INT;
	TMR3 = 0;
	PR3 = usToU16Ticks(100, getTimerPrescale(T3CONbits)) - 1;
	_T3IP=7;
	_T3IF=0;
	_T3IE=1;
}

void configBuzzer(){
	configTimer3();
	config_buzzer_pin();
}

void startBuzzer(){
	T3CONbits.TON = 1;
}

void stopBuzzer(){
	T3CONbits.TON = 0; 	//stop the timer
	buzzer = 0;			//also leave the buzzer with zero volts across it
}

void configVibrator(){
	config_vibrat_pin();
}

void startVibrator(){
	vibrator = 1;
}

void stopVibrator(){
	vibrator = 0;
}

/*********************************************************
*configAlerts
*configure alerts to be able to run
*	enables buzzer
*	enables vibrator
*********************************************************/
void configAlerts(){
	configBuzzer();
	configVibrator();
        enableBuzzer();
        enableVibrator();
}

/*********************************************************
*startAlerts
*triggers all enable alerts
*********************************************************/
void startAlerts(){
	if(((u8_enabledAlerts & buzzEn) >> shiftBuzz) == 1){
		startBuzzer();
	}
	if(((u8_enabledAlerts & vibrEn)>> shiftVibr) == 1){
		startVibrator();
	}
}

/*********************************************************
*stopAlerts
*stops all alerts 
*********************************************************/
void stopAlerts(){
	stopBuzzer();
	stopVibrator();
}

/*********************************************************
*enableBuzzer
*enables the buzzer (automatically enabled)
*********************************************************/
void enableBuzzer(){
	u8_enabledAlerts |= buzzEn;
}

/*********************************************************
*disableBuzzer
*disables the buzzer (won't be started by startAlerts)
*********************************************************/
void disableBuzzer(){
	u8_enabledAlerts &= buzzMask;
}

/*********************************************************
*enableVibrator
*enables the vibrator (automatically enabled)
*********************************************************/
void enableVibrator(){
	u8_enabledAlerts |= vibrEn;
}

/*********************************************************
*disableVibrator
*disables the vibrator (won't be started by startAlerts)
*********************************************************/
void disableVibrator(){
	u8_enabledAlerts &= vibrMask;
}