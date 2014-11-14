#include "pic24_all.h"
#include "transceiver_module.h"
#include "NeverWanderBand.h"

void configUartXbee(){
    configUART2(9600);
    CONFIG_RB6_AS_DIG_INPUT();           // RX pin must be digital input
    CONFIG_U2RX_TO_RP(RB6_RP);           // U2RX <- RB8
    CONFIG_RB9_AS_DIG_OUTPUT();           // TX pin must be digital output
    CONFIG_U2TX_TO_RP(RB9_RP);            // U2TX -> RB7
}

void sendUint8Xbee(uint8_t u8_toBeSent){
    outChar2(u8_toBeSent);
}

uint8_t receiveUint8Xbee(){
    return inChar2();
}

void getChildPacket(char* psz_buff, uint16_t u16_maxCount){
  uint8_t u8_c;
  uint16_t u16_i;

  if (!u16_maxCount) return 0;
  u16_i = 0;
  for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
    u8_c = receiveUint8Xbee();
    if (u8_c == '\n' ||u8_c == '\r' ) break; //terminate loop
    *psz_buff = u8_c; //save character
    psz_buff++;
  }

  *psz_buff = 0;
  return(u16_i);
}

void transmitChildCommand(char *psz_s){
    while (*psz_s) {
        if (*psz_s == '\n') sendUint8Xbee(0x0D);
        sendUint8Xbee(*psz_s);
        psz_s++;
    }
}

void getParentPacket(char* psz_buff, uint16_t u16_maxCount){
  uint8_t u8_c;
  uint16_t u16_i;

  if (!u16_maxCount) return 0;
  u16_i = 0;
  for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
    u8_c = inChar1();
    if (u8_c == '\n' ||u8_c == '\r' ) break; //terminate loop
    *psz_buff = u8_c; //save character
    psz_buff++;
  }

  *psz_buff = 0;
  return(u16_i);
}