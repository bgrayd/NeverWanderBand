#pragma once


/*********************************************************
*configAlerts
*configure alerts to be able to run
*	enables buzzer
*	enables vibrator
*********************************************************/
void configAlerts();

/*********************************************************
*startAlerts
*triggers all enable alerts
*********************************************************/
void startAlerts();

/*********************************************************
*stopAlerts
*stops all alerts 
*********************************************************/
void stopAlerts();

/*********************************************************
*enableBuzzer
*enables the buzzer (automatically enabled)
*********************************************************/
void enableBuzzer();

/*********************************************************
*disableBuzzer
*disables the buzzer (won't be started by startAlerts)
*********************************************************/
void disableBuzzer();

/*********************************************************
*enableVibrator
*enables the vibrator (automatically enabled)
*********************************************************/
void enableVibrator();

/*********************************************************
*disableVibrator
*disables the vibrator (won't be started by startAlerts)
*********************************************************/
void disableVibrator();