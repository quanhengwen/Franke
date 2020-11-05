#ifndef __esp32_H
#define __esp32_H
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
extern void ESP32_Test(void);
extern void ESP32_WIFI(void);
extern void ESP32_BLE(void);
extern void StringCompare(char *s);
extern void StringCompare_s(char *s);
extern void Send_Data(int16_t weight,uint16_t i);

extern uint8_t BLEStatus;
extern uint8_t WIFIStatus;
extern float send_temp;
extern float St2;
extern float Hy2;//0.1~25℃
extern int16_t LS2 ;//-55℃~Set
extern int8_t US2 ;//SET~99℃
extern float ot2;//-9.9~9.9℃
extern int8_t P22 ;
extern float oE2;//-9.9~9.9℃
extern int8_t od2 ;//0~99分钟
extern int8_t AC2 ;//0~50分钟
extern int8_t Cy2 ;//0~99分钟
extern int8_t Cn2 ;//0~99分钟
extern int16_t dAd2 ;//0~255分钟
extern uint16_t PA12;
extern uint16_t PA22;
extern int8_t CF2 ;//℃/℉
extern int8_t rE2 ;
extern int8_t Ld2 ;
extern int8_t dy2 ;
extern uint8_t d12 ;
extern uint8_t d22 ;
extern int8_t P012 ;//语言
extern char P312[30];//????
extern char P322[30];
extern int8_t td2 ;
extern int16_t dE2 ;//-55~50℃
extern int8_t id2 ;//0~99小时
extern int8_t Md2 ;//0~99分钟
extern int8_t dd2 ;//0~99分钟
extern int8_t dF2 ;//融霜期间的温度显示
extern int8_t dt2 ;//0~99分钟
extern int8_t dP2 ;//上电融霜
extern int8_t F12 ;
extern int8_t F22 ;
extern int8_t Fd2 ;//0~99min
extern int8_t FS2 ;//-55/50℃  -67/99℃
extern uint8_t FAd2 ;//1~50
extern int8_t Fn2 ;//	0/15(min.)
extern int8_t FF2 ;//	0/15(min.)
extern int16_t dad2 ;//0~255分钟
extern int8_t AU2 ;//ALL~99℃
extern int8_t AL2 ;//-55℃~ALU
extern int8_t Ad2 ;//0~99分钟
extern int8_t dA2 ;//0~99分钟
extern uint8_t P102 ;
extern uint8_t P112 ;
extern uint16_t P132 ;
extern uint16_t P142 ;
extern uint16_t P162 ;
extern uint16_t P172 ;
extern int8_t P182 ;
extern int8_t P192 ;
extern int8_t P202 ;
extern uint8_t P212 ;
extern uint8_t P222 ;
extern uint8_t P232 ;
extern uint8_t P262 ;
extern int8_t P282 ;
extern uint8_t P292 ;
extern uint8_t P302 ;
#ifdef __cplusplus
}
#endif
#endif
