#ifndef __key_H
#define __key_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//下面的方式是通过直接操作HAL库函数方式读取IO
#define SMALL     		HAL_GPIO_ReadPin(KEY_6_GPIO_Port,KEY_6_Pin)
#define MID      		HAL_GPIO_ReadPin(KEY_5_GPIO_Port,KEY_5_Pin)
#define LARGE_SET      	HAL_GPIO_ReadPin(KEY_4_GPIO_Port,KEY_4_Pin)
#define UP     			HAL_GPIO_ReadPin(KEY_3_GPIO_Port,KEY_3_Pin)	
#define DOWN     		HAL_GPIO_ReadPin(KEY_2_GPIO_Port,KEY_2_Pin)	
#define STANDBY     	HAL_GPIO_ReadPin(KEY_1_GPIO_Port,KEY_1_Pin)		

typedef enum
{
	eKEY_NONE = 0,
	eKEY_SAVE,
	eKEY_ENTER,
	eKEY_SET,
	eKEY_UP,
	eKEY_DOWN,
	eKEY_EXIT,
} KEY_TypeDef;


typedef enum
{
	DSP = 0,
	VS,
	CP,
	dis,
	dEF,
	FAn,
	AL,
} MenuSelect;


extern uint8_t jiaozhunkey;
extern uint8_t dash_number[14];
void    Key_Init(void);
int 	Key_Scan(void);
uint8_t Key_GetState(void);
void 	ParamSettingAdd(void);
void 	ParamSettingSub(void);
void    ParamSelect(void);
extern int 	ParamSave(void);
int 	ParamRead(void);
void    MenuSelectShow(void);
extern void    MenuInit(void);
void otherdis(uint8_t v);
void p31_p32(void);
#ifdef __cplusplus
}
#endif
#endif
