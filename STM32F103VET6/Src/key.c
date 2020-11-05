#include "key.h"
#include "gpio.h"
#include "main.h"
#include "lcd.h"
#include "LCD19264.h"
#include "AT24Cxx.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include	"FILE_SYS.H"
#include "cmsis_os.h"

enum
{
	index_moren_par,
	index_moren_par1,
	//用户
	index_c_dspP02P,
	index_c_dspP02P1,
	index_c_dspP02C,
	index_c_dspP02C1,
	index_c_dspDTP,
	index_c_dspDTP1,
	index_c_dspRTP,
	index_c_dspRTP1,
	
	index_c_vsDC,
	index_c_vsDC1,
	index_c_vsCC,
	index_c_vsCC1,
	index_c_vsSC,
	index_c_vsSC1,
	index_c_vsMC,
	index_c_vsMC1,
	index_c_vsLC,
	index_c_vsLC1,
	index_c_vsDrTQ,
	index_c_vsDrTQ1,
	index_c_vsDTQ,
	index_c_vsDTQ1,
	index_c_vsFTO,
	index_c_vsFTO1,
	index_c_vsDTO,
	index_c_vsDTO1,
	index_c_vsCL,
	index_c_vsCL1,
	index_c_vsCP,
	index_c_vsCP1,
	

	//工厂
	index_f_cpSt,
	index_f_cpSt1,
	index_f_cpHy,
	index_f_cpHy1,
	index_f_cpHyde,
	index_f_cpHyde1,
	index_f_cpLS,
	index_f_cpLS1,
	index_f_cpUS,
	index_f_cpUS1,
	index_f_cpot,
	index_f_cpot1,
	index_f_cpotde,
	index_f_cpotde1,
	index_f_cpP2,
	index_f_cpP21,
	index_f_cpoE,
	index_f_cpoE1,
	index_f_cpoEde,
	index_f_cpoEde1,
	index_f_cpod,
	index_f_cpod1,
	index_f_cpAC,
	index_f_cpAC1,
	index_f_cpCy,
	index_f_cpCy1,
	index_f_cpCn,
	index_f_cpCn1,
	index_f_cpdAd,
	index_f_cpdAd1,
	
	index_f_disPA1,
	index_f_disPA11,
	index_f_disPA2,
	index_f_disPA21,
	index_f_disCF,
	index_f_disCF1,
	index_f_disrE,
	index_f_disrE1,
	index_f_disLd,
	index_f_disLd1,
	index_f_disdy,
	index_f_disdy1,
	index_f_disP31,
	index_f_disP311,
	index_f_disP32,
	index_f_disP321,
	
	index_f_deftd,
	index_f_deftd1,
	index_f_defdE,
	index_f_defdE1,
	index_f_defid,
	index_f_defid1,
	index_f_defMd,
	index_f_defMd1,
	index_f_defdd,
	index_f_defdd1,
	index_f_defdF,
	index_f_defdF1,
	index_f_defdt,
	index_f_defdt1,
	index_f_defdP,
	index_f_defdP1,
	
	index_f_fanFd,
	index_f_fanFd1,
	index_f_fanFS,
	index_f_fanFS1,
	index_f_fanFAd,
	index_f_fanFAd1,
	index_f_fanFn,
	index_f_fanFn1,
	index_f_fanFF,
	index_f_fanFF1,
	index_f_fandAd,
	index_f_fandAd1,
	
	index_f_alAU,
	index_f_alAU1,
	index_f_alAL,
	index_f_alAL1,
	index_f_alAd,
	index_f_alAd1,
	index_f_aldA,
	index_f_aldA1,
	
	index_f_dspP10,
	index_f_dspP101,
	index_f_dspP11,
	index_f_dspP111,
	index_f_dspP13,
	index_f_dspP131,
	index_f_dspP14,
	index_f_dspP141,
	index_f_dspP15,
	index_f_dspP151,
	index_f_dspP16,
	index_f_dspP161,
	index_f_dspP17,
	index_f_dspP171,
	index_f_dspP18,
	index_f_dspP181,
	index_f_dspP19,
	index_f_dspP191,
	index_f_dspP20,
	index_f_dspP201,
	index_f_dspP21,
	index_f_dspP211,
	index_f_dspP22,
	index_f_dspP221,
	index_f_dspP23,
	index_f_dspP231,
	index_f_dspP29,
	index_f_dspP291,
	index_f_dspP30,
	index_f_dspP301,
	index_f_dspT1,
	index_f_dspT11,
	index_f_dspT2,
	index_f_dspT21,
	
	index_delay,
	index_delay1,
	index_delaytt,
	index_delaytt1,
	
	//P31、P32参数
	index_P31_0,
	index_P31_01,
	index_P31_1,
	index_P31_11,
	index_P31_2,
	index_P31_21,
	index_P31_3,
	index_P31_31,
	index_P31_4,
	index_P31_41,
	index_P31_5,
	index_P31_51,
	index_P31_6,
	index_P31_61,
	index_P31_7,
	index_P31_71,
	index_P31_8,
	index_P31_81,
	index_P31_9,
	index_P31_91,
	index_P31_10,
	index_P31_101,
	index_P31_110,
	index_P31_111,
	index_P31_12,
	index_P31_121,
	index_P31_13,
	index_P31_131,
	index_P31_14,
	index_P31_141,
	
	
	index_P32_0,
	index_P32_01,
	index_P32_1,
	index_P32_11,
	index_P32_2,
	index_P32_21,
	index_P32_3,
	index_P32_31,
	index_P32_4,
	index_P32_41,
	index_P32_5,
	index_P32_51,
	index_P32_6,
	index_P32_61,
	index_P32_7,
	index_P32_71,
	index_P32_8,
	index_P32_81,
	index_P32_9,
	index_P32_91,
	index_P32_10,
	index_P32_101,
	index_P32_110,
	index_P32_111,
	index_P32_12,
	index_P32_121,
	index_P32_13,
	index_P32_131,
	index_P32_14,
	index_P32_141,
};


//static uint8_t KeySet = 0;
static uint8_t line = 0;
static int replace = 0;
static float demical0 = 0.0;
static float demical1 = 0.0;
static float demical3 = 0.0;
static float demical4 = 0.0;
static float demical5 = 0.0;
static float demical6 = 0.0;
static int16_t PA1 = 0;
static int16_t PA2 = 0;
static uint8_t Password = 0;
char save[10] = "Save";
volatile uint8_t qiehuan = 0;
uint8_t p31_0 = 0;
uint8_t p31_1 = 0;
uint8_t p31_2 = 0;
uint8_t p31_3 = 0;
uint8_t p31_4 = 0;
uint8_t p31_5 = 0;
uint8_t p31_6 = 0;
uint8_t p31_7 = 0;
uint8_t p31_8 = 0;
uint8_t p31_9 = 0;
uint8_t p31_10 = 0;
uint8_t p31_11 = 0;
uint8_t p31_12 = 0;
uint8_t p31_13 = 0;
uint8_t p31_14 = 0;

uint8_t p32_0 = 0;
uint8_t p32_1 = 0;
uint8_t p32_2 = 0;
uint8_t p32_3 = 0;
uint8_t p32_4 = 0;
uint8_t p32_5 = 0;
uint8_t p32_6 = 0;
uint8_t p32_7 = 0;
uint8_t p32_8 = 0;
uint8_t p32_9 = 0;
uint8_t p32_10 = 0;
uint8_t p32_11 = 0;
uint8_t p32_12 = 0;
uint8_t p32_13 = 0;
uint8_t p32_14 = 0;
uint8_t dash_number0[11] = "0123456789F";
uint8_t dash_number1[13] = "0123456789S.-";
uint8_t dash_number2[12] = "0123456789.-";
uint8_t dash_number3[11] = "0123456789-";
uint16_t test = 0;
uint8_t jiaozhunkey = 0;
void otherdis(uint8_t v)
{
	char buffer[40] = {0};
	char buffer2[40] = {0};
	if(udiskread){
		if(v == 0){
			sprintf(buffer,"Press L to Reset");
			sprintf(buffer2,"Press Exit to Exit");
			Lcm_GotoXY(0,0,1);
			Lcm_Wr_Command(0x01); //显示清屏
			Lcm_GotoXY(0,0,0);
			Lcm_Wr_Command(0x01); //显示清屏
			Lcm_GotoXY(0,0,1);
			Lcm_Disp_String((unsigned char *)buffer);
			Lcm_GotoXY(0,1,1);
			Lcm_Disp_String((unsigned char *)buffer2);
			while(1){
				if(LARGE_SET == RESET){
					Read_Parameter(1);
					sprintf(buffer,"Reset Successful");
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //显示清屏
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char *)buffer);
					HAL_Delay(2000);
					ParamSave();
					break;
				}
				else if(STANDBY == RESET){
					break;
				}
			}
		}
		else{
			if(line == 0){
				sprintf(buffer,"Press L to upLoad");
				sprintf(buffer2,"Press Exit to exit");
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char *)buffer);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char *)buffer2);
				int oo = 0;
				while(1){
					if(LARGE_SET == RESET){
						if(oo == 0){
							oo = 1;
							char ausd[20] = {0};
							sprintf(ausd,"/PARAMTER.TXT");
							CH376FileErase((PUINT8)ausd);
						}
						uint8_t ret = writeUDisk();
						if(ret != 2){
						writeUDisk();
	//					sprintf(buffer,"Press L to continue    ");
	//					Lcm_GotoXY(0,0,1);
	//					Lcm_Disp_String((unsigned char *)buffer);
	//						return;
						HAL_Delay(1000);
						}
						sprintf(buffer,"UpLoad Successful      ");
						Lcm_GotoXY(0,0,1);
						Lcm_Wr_Command(0x01); //显示清屏
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char *)buffer);
						sprintf(buffer,"waitting...            ");
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char *)buffer);
	//					UDiskRemove();
						HAL_Delay(2000);
						break;
					}
					else if(STANDBY == RESET){
						break;
					}
				}
			}
			else{
				sprintf(buffer,"Press L to Format");
				sprintf(buffer2,"Press Exit to Exit");
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char *)buffer);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char *)buffer2);
				while(1){
					if(LARGE_SET == RESET){
						char ausd[20] = {0};
						sprintf(ausd,"/PARAMTER.TXT");
						CH376FileErase((PUINT8)ausd);
						sprintf(buffer,"Formatting Successful");
						Lcm_GotoXY(0,0,1);
						Lcm_Wr_Command(0x01); //显示清屏
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char *)buffer);
						HAL_Delay(2000);
						break;
					}
					else if(STANDBY == RESET){
						break;
					}
				}
			}
		}
	}
	else{
		sprintf(buffer, "Please insert U Disk    ");
		sprintf(buffer2,"Power OFF Then On       ");
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //显示清屏
		Lcm_GotoXY(0,0,0);
		Lcm_Wr_Command(0x01); //显示清屏
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)buffer);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)buffer2);
		osDelay(4000);
	}
}
uint8_t Key_GetState(void)
{
//	Usart3_Printf("优秀%d\r\n",stm32_config.CUSTSelected);
//	
//	Usart3_Printf("%d\r\n",stm32_config.CUSTSelected2);
	volatile uint8_t KeyPress = eKEY_NONE;
	static uint8_t drum_door = 0;
	if(SMALL == GPIO_PIN_RESET){
		osDelay(100);
		if(qiehuan == 0){
			qiehuan = 0;
			return KeyPress;
		}
		//KeyPress = eKEY_ENTER;//进入下一层菜单
		qiehuan--;
		return KeyPress;
	}
	else if(MID == GPIO_PIN_RESET){
		osDelay(100);
		if(qiehuan > 14){
			qiehuan = 14;
			return KeyPress;
		}
		//KeyPress = eKEY_ENTER;//进入下一层菜单
		qiehuan++;
			return KeyPress;
	}
	
	else if(LARGE_SET == GPIO_PIN_RESET){
		//KeyPress = eKEY_SET;//选择
		KeyPress = eKEY_ENTER;//进入下一层菜单
		if(stm32_config.Menu_Tier == 3){
			if(custdsp.Line == 1 && line == 0){
				otherdis(0);
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				KeyPress = eKEY_EXIT;
			}
			else if(factfpr.Line == 1){
				otherdis(1);
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				KeyPress = eKEY_EXIT;
			}
			else if(custdsp.Line == 1 && line == 3){
				char disdrum[48] = {0};
				char disdoor[48] = {0};
				Drum_Motor(On);
				if(test < AdcBuf[3])
					test = AdcBuf[3];
				KeyPress = eKEY_NONE;
				sprintf(disdrum,"T  %d      ",AdcBuf[3]);
				sprintf(disdoor,"P  %d      ",test);
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char *)disdrum);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char *)disdoor);
				drum_door = 1;
			}
			else if(custdsp.Line == 1 && line == 4){
				char disdrum[48] = {0};
				char disdoor[48] = {0};
				DoorOpen_Motor(On);
				if(test < AdcBuf[2])
					test = AdcBuf[2];
				if(HAL_GPIO_ReadPin(dooropen_GPIO_Port,dooropen_Pin)){
					DoorOpen_Motor(Off);
					HAL_Delay(800);
					DoorOpen_Motor(2);
				}
				else{
					if(test < AdcBuf[2])
						test = AdcBuf[2];
				}
				KeyPress = eKEY_NONE;
				sprintf(disdrum,"T  %d      ",AdcBuf[2]);
				sprintf(disdoor,"P  %d      ",test);
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char *)disdrum);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char *)disdoor);
				drum_door = 1;
			}
			else{
				ParamSave();//保存
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,1);
				KeyPress = eKEY_EXIT;
				Lcm_Disp_String((unsigned char *)save);
				HAL_Delay(500);
			}
		}
	}
	
	else if(UP == GPIO_PIN_RESET){
		if(stm32_config.Menu_Tier == 3 || stm32_config.Menu_Tier == 5){
			KeyPress = eKEY_UP;//加
			return KeyPress;
		}
		else if(stm32_config.Menu_Tier == 1){
			stm32_config.CUSTSelected -= 2;
			stm32_config.FACTSelected -= 2;
		}
		else if(stm32_config.Menu_Tier == 2){
			stm32_config.CUSTSelected2 -= 2;
			stm32_config.FACTSelected2 -= 2;
		}
		else if(stm32_config.Menu_Tier == 4){
			stm32_config.Selected -= 2;
		}
		KeyPress = eKEY_SET;
	}

	else if(DOWN == GPIO_PIN_RESET){
		if(stm32_config.Menu_Tier == 3 || stm32_config.Menu_Tier == 5){
			KeyPress = eKEY_DOWN;//减
		}
		else
			KeyPress = eKEY_SET;
	}

	else if(STANDBY == GPIO_PIN_RESET){
		KeyPress = eKEY_EXIT;//退出
		test = 0;
		drum_door = 0;
	}
	else if(LARGE_SET == GPIO_PIN_SET && custdsp.Line == 1 && drum_door){
		char disdrum[48] = {0};
		char disdoor[48] = {0};
		if(line == 3){
			Drum_Motor(2);
			if(test < AdcBuf[3])
				test = AdcBuf[3];
				custdsp.DT_P = test;
			sprintf(disdrum,"T  %d      ",AdcBuf[3]);
			sprintf(disdoor,"P  %d      ",test);
		}
		else if(line == 4){
			if(HAL_GPIO_ReadPin(dooropen_GPIO_Port,dooropen_Pin)){
				DoorOpen_Motor(Off);
				HAL_Delay(800);
				DoorOpen_Motor(2);
				if(test < AdcBuf[2])
					test = AdcBuf[2];
				custdsp.RT_P = test;
				sprintf(disdrum,"T  %d      ",AdcBuf[2]);
				sprintf(disdoor,"P  %d      ",test);
			}
			else{
				if(test < AdcBuf[2])
					test = AdcBuf[2];
				custdsp.RT_P = test;
				sprintf(disdrum,"T  %d      ",AdcBuf[2]);
				sprintf(disdoor,"P  %d      ",test);
			}
		}
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)disdrum);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)disdoor);
	}
	return KeyPress;
}


int Key_Scan(void)
{
	switch(Key_GetState())
	{
		case eKEY_SAVE:
				ParamSave();//保存
				//Usart3_Printf("保存\r\n");
				break;
		case eKEY_ENTER:
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				if(stm32_config.Menu_Tier == 1){
					//Usart3_Printf("进入下一层\r\n");
					stm32_config.Menu_Tier = 2;
					MenuSelectShow();
				}
				else if(stm32_config.Menu_Tier == 2){
					//Usart3_Printf("进入参数设置层\r\n");
					stm32_config.Menu_Tier = 3;
					MenuSelectShow();
				}
				else if(stm32_config.Menu_Tier == 3){
					//提示：已经是最底层了,无法进入下一层菜单了
//					display(0,"我是有底线的","",2);
					//Usart3_Printf("我是有底线的\r\n");
					MenuSelectShow();
				}
				else if(stm32_config.Menu_Tier == 4){
					//Usart3_Printf("进入密码输入层\r\n");
					stm32_config.Menu_Tier = 5;
					MenuSelectShow();
				}
				else if(stm32_config.Menu_Tier == 5){
					if(PA1 == factdis.PA1){
						char errorpassword[14] = "USER ENTER";
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char *)errorpassword);
						HAL_Delay(1000);
						MenuInit();
						stm32_config.Menu_Tier = 1;
						CUST_FACT = 0;
						PA1 = 0;
						Password = 0;
						MenuSelectShow();
					}
					else if(PA2 == factdis.PA2){
						stm32_config.Menu_Tier = 1;
						char errorpassword[14] = "ADMIN ENTER";
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char *)errorpassword);
						HAL_Delay(1000);
						MenuInit();
						CUST_FACT = 1;
						PA2 = 0;
						Password = 0;
						MenuSelectShow();
					}
					else{
						char errorpassword[14] = "PassWord Error";
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char *)errorpassword);
						HAL_Delay(1000);
						MenuSelectShow();
					}
				}
				break;
		case eKEY_SET:
				if(stm32_config.Menu_Tier != 3){
					ParamSelect();//参数选择
					//Usart3_Printf("选择\r\n");
				}
				break;
		case eKEY_UP:
				if(stm32_config.Menu_Tier == 3 || stm32_config.Menu_Tier == 5){
					ParamSettingAdd();//param add++
					//Usart3_Printf("加\r\n");
				}
				break;
		case eKEY_DOWN:
				if(stm32_config.Menu_Tier == 3 || stm32_config.Menu_Tier == 5){
					ParamSettingSub();//param sub--
					//Usart3_Printf("减\r\n");
				}
				break;
		case eKEY_EXIT:
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //显示清屏
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //显示清屏
				if(stm32_config.Menu_Tier == 1){
					Menu = 0;
					jiaozhun = 0;
					TIM3_Enable();
					MenuInit();
//				Lcm12232F_Wr_Command(0x30, 1,1);
//				Lcm12232F_Wr_Command(CLR_SCREN, 1,1); //清屏
					//Usart3_Printf("退出\r\n");
				}
				if(stm32_config.Menu_Tier == 2){
					stm32_config.Menu_Tier = 1;
					stm32_config.CUSTSelected2 = 0;
					stm32_config.FACTSelected2 = 0;
					MenuSelectShow();
					//Usart3_Printf("返回一层\r\n");
				}
				if(stm32_config.Menu_Tier == 3){
					stm32_config.Menu_Tier = 2;
					MenuSelectShow();
					//Usart3_Printf("返回二层\r\n");
				}
				if(stm32_config.Menu_Tier == 4){
					Menu = 0;
					TIM3_Enable();
					MenuInit();
					//Usart3_Printf("退出密码\r\n");
				}
				if(stm32_config.Menu_Tier == 5){
					stm32_config.Menu_Tier = 4;
					MenuSelectShow();
					//Usart3_Printf("返回密码选择\r\n");
				}
				break;
		default :
				break;
	}
  return 0;
}

void ParamSettingAdd(void)
{
//	for(uint j=0;j<14;j++){
//		Usart3_Printf("%c\r\n",dash_number[j]);
//		Usart3_Printf("%s\r\n",dash_number);
//	}
	if(stm32_config.Menu_Tier == 5 && Password == 0)
		PA1++;
	else if(stm32_config.Menu_Tier == 5 && Password == 1)
		PA2++;
	//用户参数
    else if(stm32_config.Menu_Tier == 3 && CUST_FACT == 0){
	    switch(stm32_config.CUSTSelected2)
	    {
			case 0:
					if(custdsp.Line == 1){
						//custdsp.RE++;
					}
					if(custvs.Line == 1){
						//custvs.DC++;
	    			}
					if(custcp.Line == 1){
						custcp.St++;
						factcp.St = custcp.St;
	    			}
					if(custdis.Line == 1){
						custdis.CF++;
						factdis.CF = custdis.CF;
	    			}
					if(custdef.Line == 1){
						custdef.dE++;
						factdef.dE = custdef.dE;
	    			}
					if(custfan.Line == 1){
						custfan.Fd++;
						factfan.Fd = custfan.Fd;
	    			}
					if(custal.Line == 1){
						custal.AU++;
						factal.AU = custal.AU;
	    			}
					break;
			case 1:
					if(custdsp.Line == 1){
						//custdsp.P02_P++;
					}
					if(custvs.Line == 1){
						//custvs.CC++;
	    			}
					if(custcp.Line == 1){
						custcp.Hy += 0.1;
						factcp.Hy = custcp.Hy;
	    			}
					if(custdis.Line == 1){
						custdis.rE++;
						factdis.rE = custdis.rE;
	    			}
					if(custdef.Line == 1){
						custdef.id++;
						factdef.id = custdef.id;
	    			}
					if(custfan.Line == 1){
						custfan.Fn++;
						factfan.Fn = custfan.Fn;
	    			}
					if(custal.Line == 1){
						custal.AL++;
						factal.AL = custal.AL;
	    			}
					break;
			case 2:
					if(custdsp.Line == 1){
						//custdsp.P02_C++;
					}
					if(custvs.Line == 1){
						//custvs.SC++;
	    			}
					if(custcp.Line == 1){
						custcp.ot += 0.1;
						factcp.ot = custcp.ot;
	    			}
					if(custdis.Line == 1){
						custdis.d1++;
						factdis.d1 = custdis.d1;
	    			}
					if(custdef.Line == 1){
						custdef.Md++;
						factdef.Md = custdef.Md;
	    			}
					if(custfan.Line == 1){
						custfan.FF++;
						factfan.FF = custfan.FF;
	    			}
					break;
			case 3:
					if(custdsp.Line == 1){
						//custdsp.DT_P++;
					}
					if(custvs.Line == 1){
						//custvs.MC++;
	    			}
					if(custcp.Line == 1){
						custcp.p2++;
						factcp.P2 = custcp.p2;
	    			}
					if(custdis.Line == 1){
						custdis.d2++;
						factdis.d2 = custdis.d2;
	    			}
					break;
			case 4:
					if(custdsp.Line == 1){
						//custdsp.RT_P++;
					}
					if(custvs.Line == 1){
						//custvs.LC++;
	    			}
					if(custcp.Line == 1){
						custcp.AC++;
						factcp.AC = custcp.AC;
	    			}
					if(custdis.Line == 1){
						custdis.P01++;
						factdis.P01 = custdis.P01;
	    			}
					break;
			case 5:
					if(custvs.Line == 1){
						//custvs.DrTQ++;
	    			}
			case 6:
					if(custvs.Line == 1){
						//custvs.DTQ++;
	    			}
			case 7:
					if(custvs.Line == 1){
						//custvs.FTO++;
	    			}
			case 8:
					if(custvs.Line == 1){
						//custvs.DTO++;
	    			}
			case 9:
					if(custvs.Line == 1){
						//custvs.CC++;
	    			}
			case 10:
					if(custvs.Line == 1){
						//custvs.CP++;
	    			}
	    	default:
	       	 break;
	    }
		//范围检测
		{
			if(PA1 > 250)
				PA1 = 250;
			if(PA2 > 250)
				PA2 = 250;
			if(custcp.St > factcp.US)
				custcp.St = factcp.US;
			if(custcp.Hy > 5)
				custcp.Hy = 5;
			if(custcp.ot > 30)
				custcp.ot = 30;
			if(custcp.p2 > 1)
				custcp.p2 = 1;
			if(custcp.AC > 50)
				custcp.AC = 50;

			if(custdis.CF > 1)
				custdis.CF = 1;
			if(custdis.rE > 1)
				custdis.rE = 1;
			if(custdis.P01 > 4)
				custdis.P01 = 4;

			if(custdef.dE > 320)
				custdef.dE = 320;
			if(custdef.id > 99)
				custdef.id = 99;
			if(custdef.Md > 99)
				custdef.Md = 99;

			if(custfan.F1 > 3)
				custfan.F1 = 3;
			if(custfan.F2 > 3)
				custfan.F2 = 3;
			if(custfan.Fd > 99)
				custfan.Fd = 99;
			if(custfan.FF > 15)
				custfan.FF = 15;

			if(custal.AU > 50)
				custal.AU = 50;
			if(custal.AL > 50)
				custal.AL = 50;
		
			if(factcp.St > factcp.US)
				factcp.St = factcp.US;
			if(factcp.Hy > 5)
				factcp.Hy = 5;
			if(factcp.LS > 302)
				factcp.LS = 302;
			if(factcp.US > 30)
				factcp.US =  30;
			if(factcp.ot > 30)
				factcp.ot = 30;
			if(factcp.P2 > 1)
				factcp.P2 = 1;
			if(factcp.oE > 30)
				factcp.oE = 30;
			if(factcp.od > 99)
				factcp.od = 99;
			if(factcp.AC > 50)
				factcp.AC = 50;
			if(factcp.Cy > 99)
				factcp.Cy = 99;
			if(factcp.Cn > 99)
				factcp.Cn = 99;
			if(factcp.dAd > 255)
				factcp.dAd = 255;

			if(factdis.CF > 1)
				factdis.CF = 1;
			if(factdis.rE > 1)
				factdis.rE = 1;
			if(factdis.Ld > 1)
				factdis.Ld = 1;
			if(factdis.dy > 15)
				factdis.dy = 15;
			if(factdis.P01 > 4)
				factdis.P01 = 4;


			if(factdef.td > 2)
				factdef.td = 2;
			if(factdef.dE > 320)
				factdef.dE = 320;
			if(factdef.id > 99)
				factdef.id = 99;
			if(factdef.Md > 99)
				factdef.Md = 99;
			if(factdef.dd > 99)
				factdef.dd = 99;
			if(factdef.dF > 3)
				factdef.dF = 3;
			if(factdef.dt > 99)
				factdef.dt = 99;
			if(factdef.dP > 1)
				factdef.dP = 1;

			if(factfan.F1 > 3)
				factfan.F1 = 3;
			if(factfan.F2 > 3)
				factfan.F2 = 3;
			if(factfan.Fd > 99)
				factfan.Fd = 99;
			if(factfan.FS > 50)
				factfan.FS = 50;
			if(factfan.FAd > 50)
				factfan.FAd = 50;
			if(factfan.Fn > 15)
				factfan.Fn = 15;
			if(factfan.FF > 15)
				factfan.FF = 15;
			if(factfan.dAd > 255)
				factfan.dAd = 255;

			if(factal.AU > 50)
				factal.AU = 50;
			if(factal.AL > 50)
				factal.AL = 50;
			if(factal.Ad > 99)
				factal.Ad = 99;
			if(factal.dA > 99)
				factal.dA = 99;

			if(factdsp.P10 > 20)
				factdsp.P10 = 20;
			if(factdsp.P11 > 20)
				factdsp.P11 = 20;
			if(factdsp.P13 > 1500)
				factdsp.P13 = 1500;
			if(factdsp.P14 > 1500)
				factdsp.P14 = 1500;
			if(factdsp.P16 > 1500)
				factdsp.P16 = 1600;
			if(factdsp.P17 > 1500)
				factdsp.P17 = 1500;
			if(factdsp.P18 > 1)
				factdsp.P18 = 1;
			if(factdsp.P19 > 1)
				factdsp.P19 = 1;
			if(factdsp.P20 > 1)
				factdsp.P20 = 1;
			if(factdsp.P21 > 100)
				factdsp.P21 = 100;
			if(factdsp.P22 > 100)
				factdsp.P22 = 100;
			if(factdsp.P23 > 100)
				factdsp.P23 = 100;
			if(factdsp.P26 > 3)
				factdsp.P26 = 3;
			if(factdsp.P28 > 1)
				factdsp.P28 = 1;
			if(factdsp.P29 > 100)
				factdsp.P29 = 100;
			if(factdsp.P30 > 100)
				factdsp.P30 = 100;
		}
    }

	//工厂参数
	else if(stm32_config.Menu_Tier == 3 && CUST_FACT == 1){
		switch(stm32_config.FACTSelected2){
			case 0:
				if(factcp.Line == 1){
					factcp.St++;
					custcp.St = factcp.St;
				}
				if(factdis.Line == 1){
					factdis.PA1++;
				}
				if(factdef.Line == 1){
					factdef.td++;
				}
				if(factfan.Line == 1){
//					factfan.F1++;
					factfan.Fd++;
					custfan.Fd = factfan.Fd;
				}
				if(factal.Line == 1){
					factal.AU++;
					custal.AU = factal.AU;
				}
				if(factdsp.Line == 1){
					factdsp.P10++;
				}
				if(factfpr.Line == 1){
					factfpr.UL++;
				}
				break;
			case 1:
				if(factcp.Line == 1){
					factcp.Hy += 0.1;
					custcp.Hy = factcp.Hy;
				}
				if(factdis.Line == 1){
					factdis.PA2++;
				}
				if(factdef.Line == 1){
					factdef.dE++;
					custdef.dE = factdef.dE;
				}
				if(factfan.Line == 1){
//					factfan.F2++;
					factfan.FS++;
				}
				if(factal.Line == 1){
					factal.AL++;
					custal.AL = factal.AL;
				}
				if(factdsp.Line == 1){
					factdsp.P11++;
				}
				if(factfpr.Line == 1){
					factfpr.Fr++;
				}
				break;
			case 2:
				if(factcp.Line == 1){
					factcp.LS++;
				}
				if(factdis.Line == 1){
					factdis.CF++;
					custdis.CF = factdis.CF;
				}
				if(factdef.Line == 1){
					factdef.id++;
					custdef.id = factdef.id;
				}
				if(factfan.Line == 1){
					factfan.FAd++;
				}
				if(factal.Line == 1){
					factal.Ad++;
				}
				if(factdsp.Line == 1){
					factdsp.P13 += 10;
				}
				break;
			case 3:
				if(factcp.Line == 1){
					factcp.US++;
				}
				if(factdis.Line == 1){
					factdis.rE++;
					custdis.rE = factdis.rE;
				}
				if(factdef.Line == 1){
					factdef.Md++;
					custdef.Md = factdef.Md;
				}
				if(factfan.Line == 1){
					factfan.Fn++;
					custfan.Fn = factfan.Fn;
				}
				if(factal.Line == 1){
					factal.dA++;
				}
				if(factdsp.Line == 1){
					factdsp.P14 += 10;
				}
				break;
			case 4:
				if(factcp.Line == 1){
					factcp.ot++;
					custcp.ot = factcp.ot;
				}
				if(factdis.Line == 1){
					factdis.Ld++;
				}
				if(factdef.Line == 1){
					factdef.dd++;
				}
				if(factfan.Line == 1){
					factfan.FF++;
					custfan.FF = factfan.FF;
				}
				if(factdsp.Line == 1){
					factdsp.P15 += 10;
				}
				break;
			case 5:
				if(factcp.Line == 1){
					factcp.P2++;
					custcp.p2 = factcp.P2;
				}
				if(factdis.Line == 1){
					factdis.dy++;
				}
				if(factdef.Line == 1){
					factdef.dF++;
				}
				if(factfan.Line == 1){
					factfan.dAd++;
				}
				if(factdsp.Line == 1){
					factdsp.P16 += 10;
				}
				break;
			case 6:
				if(factcp.Line == 1){
					factcp.oE += 0.1;
				}
				if(factdis.Line == 1){
//					factdis.d1++;
				}
				if(factdef.Line == 1){
					factdef.dt++;
				}
				if(factdsp.Line == 1){
					factdsp.P17 += 10;
				}
				break;
			case 7:
				if(factcp.Line == 1){
					factcp.od++;
				}
				if(factdis.Line == 1){
//					factdis.d2++;
				}
				if(factdef.Line == 1){
					factdef.dP++;
				}
				if(factdsp.Line == 1){
					factdsp.P18++;
				}
				break;
			case 8:
				if(factcp.Line == 1){
					factcp.AC++;
					custcp.AC = factcp.AC;
				}
				if(factdis.Line == 1){
					factdis.P01++;
					custdis.P01 = factdis.P01;
				}
				if(factdsp.Line == 1){
					factdsp.P19++;
				}
				break;
			case 9:
				if(factcp.Line == 1){
					factcp.Cy++;
				}
				if(factdis.Line == 1){
					int8_t i;
					if(qiehuan == 0){
						for(i=0;i<11;i++){
							//Usart3_Printf("%c\r\n",dash_number[i]);
							if(factdis.P31[qiehuan] ==dash_number0[i]){
								Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number1[i]);
								break;
							}
						}
					}
					else if(qiehuan == 1){
						for(i=0;i<13;i++){
							//Usart3_Printf("%c\r\n",dash_number[i]);
							if(factdis.P31[qiehuan] ==dash_number1[i]){
								Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number1[i]);
								break;
							}
						}
					}
					else{
						for(i=0;i<12;i++){
							//Usart3_Printf("%c\r\n",dash_number[i]);
							if(factdis.P31[qiehuan] ==dash_number2[i]){
								Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number1[i]);
								break;
							}
						}
					}
					switch(qiehuan){
						case 0:
							if(i >= 10){
								i = 0;
								factdis.P31[qiehuan] = (char)dash_number0[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number0[i+1];
							break;
						case 1:
							if(i >= 12){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number1[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number1[i+1];
							break;
						case 2:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 3:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 4:
							if(i == 11){
								i=0;
							}
							factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 5:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 6:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 7:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 8:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 9:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 10:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 11:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 12:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 13:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
						case 14:
							if(i == 11){
								i=0;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i+1];
							break;
					}
				}
				if(factdsp.Line == 1){
					factdsp.P21++;
				}
				break;
			case 10:
				if(factcp.Line == 1){
					factcp.Cn++;
				}
				if(factdis.Line == 1){
					int8_t i;
					for(i=0;i<11;i++){
						//Usart3_Printf("%c\r\n",dash_number[i]);
						if(factdis.P32[qiehuan] == dash_number3[i]){
							//Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number[i]);
							break;
						}
					}
					switch(qiehuan){
						case 0:
							if(i >= 10){
								i = 0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 1:
							if(i == 10){
								i = 0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 2:
							if(i == 10){
								i = 0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 3:
							if(i == 10){
								i = 0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 4:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 5:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 6:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 7:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 8:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 9:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 10:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 11:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 12:
							if(i == 10){
							i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 13:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
						case 14:
							if(i == 10){
								i=0;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i+1];
							break;
					}
				}
				if(factdsp.Line == 1){
					factdsp.P22++;
				}
				break;
			case 11:
				if(factcp.Line == 1){
					factcp.dAd++;
				}
				if(factdsp.Line == 1){
					factdsp.P23++;
				}
				break;
			case 12:
				if(factdsp.Line == 1){
					factdsp.P26++;
				}
				break;
			case 13:
				if(factdsp.Line == 1){
					factdsp.P28++;
				}
				break;
			case 14:
				if(factdsp.Line == 1){
					factdsp.P29++;
				}
				break;
			case 15:
				if(factdsp.Line == 1){
					factdsp.P30++;
				}
				break;
			case 16:
				if(factdsp.Line == 1){
					delaytt += 10;
				}
				break;
			case 17:
				if(factdsp.Line == 1){
					delaytt1 += 10;
				}
				break;
			case 18:
				if(factdsp.Line == 1){
					factdsp.T1++;
				}
				break;
			case 19:
				if(factdsp.Line == 1){
					factdsp.T2++;
				}
				break;
			default:
				break;
		}
		//范围检测
		{
			if(PA1 > 250)
				PA1 = 250;
			if(PA2 > 250)
				PA2 = 250;
			if(custcp.St > factcp.US)
				custcp.St = factcp.US;
			if(custcp.Hy > 5)
				custcp.Hy = 5;
			if(custcp.ot > 30)
				custcp.ot = 30;
			if(custcp.p2 > 1)
				custcp.p2 = 1;
			if(custcp.AC > 50)
				custcp.AC = 50;

			if(custdis.CF > 1)
				custdis.CF = 1;
			if(custdis.rE > 1)
				custdis.rE = 1;
			if(custdis.P01 > 4)
				custdis.P01 = 4;

			if(custdef.dE > 320)
				custdef.dE = 320;
			if(custdef.id > 99)
				custdef.id = 99;
			if(custdef.Md > 99)
				custdef.Md = 99;

			if(custfan.F1 > 3)
				custfan.F1 = 3;
			if(custfan.F2 > 3)
				custfan.F2 = 3;
			if(custfan.Fd > 99)
				custfan.Fd = 99;
			if(custfan.FF > 15)
				custfan.FF = 15;

			if(custal.AU > 50)
				custal.AU = 50;
			if(custal.AL > 50)
				custal.AL = 50;
		
			if(factcp.St > factcp.US)
				factcp.St = factcp.US;
			if(factcp.Hy > 5)
				factcp.Hy = 5;
			if(factcp.LS > 302)
				factcp.LS = 302;
			if(factcp.US > 30)
				factcp.US =  30;
			if(factcp.ot > 30)
				factcp.ot = 30;
			if(factcp.P2 > 1)
				factcp.P2 = 1;
			if(factcp.oE > 30)
				factcp.oE = 30;
			if(factcp.od > 99)
				factcp.od = 99;
			if(factcp.AC > 50)
				factcp.AC = 50;
			if(factcp.Cy > 99)
				factcp.Cy = 99;
			if(factcp.Cn > 99)
				factcp.Cn = 99;
			if(factcp.dAd > 255)
				factcp.dAd = 255;

			if(factdis.CF > 1)
				factdis.CF = 1;
			if(factdis.rE > 1)
				factdis.rE = 1;
			if(factdis.Ld > 1)
				factdis.Ld = 1;
			if(factdis.dy > 15)
				factdis.dy = 15;
			if(factdis.P01 > 4)
				factdis.P01 = 4;


			if(factdef.td > 2)
				factdef.td = 2;
			if(factdef.dE > 320)
				factdef.dE = 320;
			if(factdef.id > 99)
				factdef.id = 99;
			if(factdef.Md > 99)
				factdef.Md = 99;
			if(factdef.dd > 99)
				factdef.dd = 99;
			if(factdef.dF > 3)
				factdef.dF = 3;
			if(factdef.dt > 99)
				factdef.dt = 99;
			if(factdef.dP > 1)
				factdef.dP = 1;

			if(factfan.F1 > 3)
				factfan.F1 = 3;
			if(factfan.F2 > 3)
				factfan.F2 = 3;
			if(factfan.Fd > 99)
				factfan.Fd = 99;
			if(factfan.FS > 50)
				factfan.FS = 50;
			if(factfan.FAd > 50)
				factfan.FAd = 50;
			if(factfan.Fn > 15)
				factfan.Fn = 15;
			if(factfan.FF > 15)
				factfan.FF = 15;
			if(factfan.dAd > 255)
				factfan.dAd = 255;

			if(factal.AU > 50)
				factal.AU = 50;
			if(factal.AL > 50)
				factal.AL = 50;
			if(factal.Ad > 99)
				factal.Ad = 99;
			if(factal.dA > 99)
				factal.dA = 99;

			if(factdsp.P10 > 20)
				factdsp.P10 = 20;
			if(factdsp.P11 > 20)
				factdsp.P11 = 20;
			if(factdsp.P13 > 1500)
				factdsp.P13 = 1500;
			if(factdsp.P14 > 1500)
				factdsp.P14 = 1500;
			if(factdsp.P16 > 1500)
				factdsp.P16 = 1600;
			if(factdsp.P17 > 1500)
				factdsp.P17 = 1500;
			if(factdsp.P18 > 1)
				factdsp.P18 = 1;
			if(factdsp.P19 > 1)
				factdsp.P19 = 1;
			if(factdsp.P20 > 1)
				factdsp.P20 = 1;
			if(factdsp.P21 > 100)
				factdsp.P21 = 100;
			if(factdsp.P22 > 100)
				factdsp.P22 = 100;
			if(factdsp.P23 > 100)
				factdsp.P23 = 100;
			if(factdsp.P26 > 3)
				factdsp.P26 = 3;
			if(factdsp.P28 > 1)
				factdsp.P28 = 1;
			if(factdsp.P29 > 100)
				factdsp.P29 = 100;
			if(factdsp.P30 > 100)
				factdsp.P30 = 100;
			if(factdsp.T1 > 999)
				factdsp.T1 = 999;
			if(factdsp.T2 > 999)
				factdsp.T2 = 999;
		}
	}
	
	MenuSelectShow();
}

void ParamSettingSub(void)
{
	if(stm32_config.Menu_Tier == 5 && Password == 0)
		PA1--;
	else if(stm32_config.Menu_Tier == 5 && Password == 1)
		PA2--;
	//用户参数
	else if(stm32_config.Menu_Tier == 3 && CUST_FACT == 0){
		switch(stm32_config.CUSTSelected2)
		{
			case 0:
					if(custdsp.Line == 1){
						//custdsp.RE--;
					}
					if(custvs.Line == 1){
						//custvs.DC--;
	    			}
					if(custcp.Line == 1){
						custcp.St--;
						factcp.St = custcp.St;
	    			}
					if(custdis.Line == 1){
						custdis.CF--;
						factdis.CF = custdis.CF;
	    			}
					if(custdef.Line == 1){
						custdef.dE--;
						factdef.dE = custdef.dE;
	    			}
					if(custfan.Line == 1){
						custfan.Fd--;
						factfan.Fd = custfan.Fd;
	    			}
					if(custal.Line == 1){
						custal.AU--;
						factal.AU = custal.AU;
	    			}
					break;
			case 1:
					if(custdsp.Line == 1){
						//custdsp.P02_P--;
					}
					if(custvs.Line == 1){
						//custvs.CC--;
	    			}
					if(custcp.Line == 1){
						custcp.Hy -= 0.1;
						factcp.Hy = custcp.Hy;
	    			}
					if(custdis.Line == 1){
						custdis.rE--;
						factdis.rE = custdis.rE;
	    			}
					if(custdef.Line == 1){
						custdef.id--;
						factdef.id = custdef.id;
	    			}
					if(custfan.Line == 1){
						custfan.Fn--;
						factfan.Fn = custfan.Fn;
	    			}
					if(custal.Line == 1){
						custal.AL--;
						factal.AL = custal.AL;
	    			}
					break;
			case 2:
					if(custdsp.Line == 1){
						//custdsp.P02_C--;
					}
					if(custvs.Line == 1){
						//custvs.SC--;
	    			}
					if(custcp.Line == 1){
						custcp.ot -= 0.1;
						factcp.ot = custcp.ot;
	    			}
					if(custdis.Line == 1){
//						custdis.d1--;
	    			}
					if(custdef.Line == 1){
						custdef.Md--;
						factdef.Md = custdef.Md;
	    			}
					if(custfan.Line == 1){
						custfan.FF--;
						factfan.FF = custfan.FF;
	    			}
					break;
			case 3:
					if(custdsp.Line == 1){
						//custdsp.DT_P--;
					}
					if(custvs.Line == 1){
						//custvs.MC--;
	    			}
					if(custcp.Line == 1){
						custcp.p2--;
						factcp.P2 = custcp.p2;
	    			}
					if(custdis.Line == 1){
//						custdis.d2--;
	    			}
					break;
			case 4:
					if(custdsp.Line == 1){
						//custdsp.RT_P--;
					}
					if(custvs.Line == 1){
						//custvs.LC--;
	    			}
					if(custcp.Line == 1){
						custcp.AC--;
						factcp.AC = custcp.AC;
	    			}
					if(custdis.Line == 1){
						custdis.P01--;
						factdis.P01 = custdis.P01;
	    			}
					break;
			case 5:
					if(custvs.Line == 1){
						//custvs.DrTQ--;
	    			}
			case 6:
					if(custvs.Line == 1){
						//custvs.DTQ--;
	    			}
			case 7:
					if(custvs.Line == 1){
						//custvs.FTO--;
	    			}
			case 8:
					if(custvs.Line == 1){
						//custvs.DTO--;
	    			}
			case 9:
					if(custvs.Line == 1){
						//custvs.CC--;
	    			}
			case 10:
					if(custvs.Line == 1){
						//custvs.CP--;
	    			}
	    	default:
	       	 break;
		}
		//MenuSelectShow();
		//范围检测
		{
			if(PA1 < 0)
				PA1 = 0;
			if(PA2 < 0)
				PA2 = 0;
			if(custcp.St < factcp.LS)
				custcp.St = factcp.LS;
			if(custcp.Hy < 0.5)
				custcp.Hy = 0.5;
			if(custcp.ot < -30)
				custcp.ot = -30;
			if(custcp.p2 < 0)
				custcp.p2 = 0;
			if(custcp.AC < 0)
				custcp.AC = 0;
			
			if(custdis.CF < 0)
				custdis.CF = 0;
			if(custdis.rE < 0)
				custdis.rE = 0;
			if(custdis.P01 < 0)
				custdis.P01 = 0;

			if(custdef.dE < -67)
				custdef.dE = -67;
			if(custdef.id < 0)
				custdef.id = 0;
			if(custdef.Md < 0)
				custdef.Md = 0;

			if(custfan.F1 < 0)
				custfan.F1 = 0;
			if(custfan.F2 < 0)
				custfan.F2 = 0;
			if(custfan.Fd < 0)
				custfan.Fd = 0;
			if(custfan.Fn < 0)
				custfan.Fn = 0;
			if(custfan.FF <0)
				custfan.FF = 0;
			
			if(factcp.St < factcp.LS)
				factcp.St = factcp.LS;
			if(factcp.Hy < 0.5)
				factcp.Hy = 0.5;
			if(factcp.LS < - 30)
				factcp.LS = -30;
			if(factcp.US < -58)
				factcp.US = -58;
			if(factcp.ot < -30)
				factcp.ot = -30;
			if(factcp.P2 < 0)
				factcp.P2 = 0;
			if(factcp.oE < -30)
				factcp.oE = -30;
			if(factcp.od < 0)
				factcp.od = 0;
			if(factcp.AC < 0)
				factcp.AC = 0;
			if(factcp.Cy < 0)
				factcp.Cy = 0;
			if(factcp.Cn < 0)
				factcp.Cn = 0;
			if(factcp.dAd < 0)
				factcp.dAd = 0;
			
			if(factdis.CF < 0)
				factdis.CF = 0;
			if(factdis.rE < 0)
				factdis.rE = 0;
			if(factdis.Ld < 0)
				factdis.Ld = 0;
			if(factdis.dy < 0)
				factdis.dy = 0;
			if(factdis.P01 < 0)
				factdis.P01 = 0;
			
			if(factdef.td < 0)
				factdef.td = 0;
			if(factdef.dE < -67)
				factdef.dE = -67;
			if(factdef.id < 0)
				factdef.id = 0;
			if(factdef.Md < 0)
				factdef.Md = 0;
			if(factdef.dd < 0)
				factdef.dd = 0;
			if(factdef.dF < 0)
				factdef.dF = 0;
			if(factdef.dt < 0)
				factdef.dt = 0;
			if(factdef.dP < 0)
				factdef.dP = 0;

			if(factfan.F1 < 0)
				factfan.F1 = 0;
			if(factfan.F2 < 0)
				factfan.F2 = 0;
			if(factfan.Fd < 0)
				factfan.Fd = 0;
			if(factfan.FS < -55)
				factfan.FS = -55;
			if(factfan.FAd < 1)
				factfan.FAd = 1;
			if(factfan.Fn < 0)
				factfan.Fn = 0;
			if(factfan.FF < 0)
				factfan.FF = 0;
			if(factfan.dAd < 0)
				factfan.dAd = 0;

			if(factal.AU < -100)
				factal.AU = -100;
			if(factal.AL < - 67)
				factal.AL = -67;
			if(factal.Ad < 0)
				factal.Ad = 0;
			if(factal.dA < 0)
				factal.dA = 0;
			
			if(factdsp.P10 < 1)
				factdsp.P10 = 1;
			if(factdsp.P11 < 1)
				factdsp.P11 = 1;
			if(factdsp.P13 < 10)
				factdsp.P13 = 10;
			if(factdsp.P14 < 10)
				factdsp.P14 = 10;
			if(factdsp.P16 < 10)
				factdsp.P16 = 10;
			if(factdsp.P17 < 10)
				factdsp.P17 = 10;
			if(factdsp.P18 < 0)
				factdsp.P18 = 0;
			if(factdsp.P19 < 0)
				factdsp.P19 = 0;
			if(factdsp.P20 < 0)
				factdsp.P20 = 0;
			if(factdsp.P21 < 50)
				factdsp.P21 = 50;
			if(factdsp.P22 < 50)
				factdsp.P22 = 50;
			if(factdsp.P23 < 50)
				factdsp.P23 = 50;
			if(factdsp.P26 < 1)
				factdsp.P26 = 1;
			if(factdsp.P28 < 0)
				factdsp.P28 = 0;
			if(factdsp.P29 < 25)
				factdsp.P29 = 25;
			if(factdsp.P30 < 25)
				factdsp.P30 = 25;
		}
	}

	//工厂参数
	else if(stm32_config.Menu_Tier == 3 && CUST_FACT == 1){
		switch(stm32_config.FACTSelected2){
			case 0:
				if(factcp.Line == 1){
					factcp.St--;
					custcp.St = factcp.St;
				}
				if(factdis.Line == 1){
					factdis.PA1--;
				}
				if(factdef.Line == 1){
					factdef.td--;
				}
				if(factfan.Line == 1){
					factfan.Fd--;
					custfan.Fd = factfan.Fd;
				}
				if(factal.Line == 1){
					factal.AU--;
					custal.AU = factal.AU;
				}
				if(factdsp.Line == 1){
					factdsp.P10--;
				}
				if(factfpr.Line == 1){
//					factfpr.UL--;
				}
				break;
			case 1:
				if(factcp.Line == 1){
					factcp.Hy -= 0.1;
					custcp.Hy = factcp.Hy;
				}
				if(factdis.Line == 1){
					factdis.PA2--;
				}
				if(factdef.Line == 1){
					factdef.dE--;
					custdef.dE = factdef.dE;
				}
				if(factfan.Line == 1){
					factfan.FS--;
				}
				if(factal.Line == 1){
					factal.AL--;
					custal.AL = factal.AL;
				}
				if(factdsp.Line == 1){
					factdsp.P11--;
				}
				if(factfpr.Line == 1){
//					factfpr.Fr--;
				}
				break;
			case 2:
				if(factcp.Line == 1){
					factcp.LS--;
				}
				if(factdis.Line == 1){
					factdis.CF--;
					custdis.CF = factdis.CF;
				}
				if(factdef.Line == 1){
					factdef.id--;
					custdef.id = factdef.id;
				}
				if(factfan.Line == 1){
					factfan.FAd--;
				}
				if(factal.Line == 1){
					factal.Ad--;
				}
				if(factdsp.Line == 1){
					factdsp.P13 -= 10;
				}
				break;
			case 3:
				if(factcp.Line == 1){
					factcp.US--;
				}
				if(factdis.Line == 1){
					factdis.rE--;
					custdis.rE = factdis.rE;
				}
				if(factdef.Line == 1){
					factdef.Md--;
					custdef.Md = factdef.Md;
				}
				if(factfan.Line == 1){
					factfan.Fn--;
					custfan.Fn = factfan.Fn;
				}
				if(factal.Line == 1){
					factal.dA--;
				}
				if(factdsp.Line == 1){
					factdsp.P14 -= 10;
				}
				break;
			case 4:
				if(factcp.Line == 1){
					factcp.ot--;
					custcp.ot = factcp.ot;
				}
				if(factdis.Line == 1){
					factdis.Ld--;
				}
				if(factdef.Line == 1){
					factdef.dd--;
				}
				if(factfan.Line == 1){
					factfan.FF--;
					custfan.FF = factfan.FF;
				}
				if(factdsp.Line == 1){
					factdsp.P15 -= 10;
				}
				break;
			case 5:
				if(factcp.Line == 1){
					factcp.P2--;
					custcp.p2 = factcp.P2;
				}
				if(factdis.Line == 1){
					factdis.dy--;
				}
				if(factdef.Line == 1){
					factdef.dF--;
				}
				if(factfan.Line == 1){
					factfan.dAd--;
				}
				if(factdsp.Line == 1){
					factdsp.P16 -= 10;
				}
				break;
			case 6:
				if(factcp.Line == 1){
					factcp.oE -= 0.1;
				}
				if(factdis.Line == 1){
//					factdis.d1--;
				}
				if(factdef.Line == 1){
					factdef.dt--;
				}
				if(factdsp.Line == 1){
					factdsp.P17 -= 10;
				}
				break;
			case 7:
				if(factcp.Line == 1){
					factcp.od--;
				}
				if(factdis.Line == 1){
//					factdis.d2--;
				}
				if(factdef.Line == 1){
					factdef.dP--;
				}
				if(factdsp.Line == 1){
					factdsp.P18--;
				}
				break;
			case 8:
				if(factcp.Line == 1){
					factcp.AC--;
					custcp.AC = factcp.AC;
				}
				if(factdis.Line == 1){
					factdis.P01--;
					custdis.P01 = factdis.P01;
				}
				if(factdsp.Line == 1){
					factdsp.P19--;
				}
				break;
			case 9:
				if(factcp.Line == 1){
					factcp.Cy--;
				}
				if(factdis.Line == 1){
					int8_t i;
					if(qiehuan == 0){
						for(i=0;i<11;i++){
							//Usart3_Printf("%c\r\n",dash_number[i]);
							if(factdis.P31[qiehuan] ==dash_number0[i]){
								//Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number[i]);
								break;
							}
						}
					}
					else if(qiehuan == 1){
						for(i=0;i<13;i++){
							//Usart3_Printf("%c\r\n",dash_number[i]);
							if(factdis.P31[qiehuan] ==dash_number1[i]){
								//Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number[i]);
								break;
							}
						}
					}
					else{
						for(i=0;i<12;i++){
							//Usart3_Printf("%c\r\n",dash_number[i]);
							if(factdis.P31[qiehuan] ==dash_number2[i]){
								//Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number[i]);
								break;
							}
						}
					}
					switch(qiehuan){
						case 0:
							if(i == 0){
								i = 10;
								factdis.P31[qiehuan] = (char)dash_number0[i];
							}
							//Usart3_Printf("en%c\r\n",dash_number[i]);
							else
								factdis.P31[qiehuan] = (char)dash_number0[i-1];
							break;
						case 1:
							if(i == 0){
								i = 12;
								factdis.P31[qiehuan] = (char)dash_number1[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number1[i-1];
							break;
						case 2:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 3:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 4:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 5:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 6:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 7:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 8:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 9:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 10:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 11:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 12:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 13:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
						case 14:
							if(i == 0){
								i=11;
								factdis.P31[qiehuan] = (char)dash_number2[i];
							}
							else
								factdis.P31[qiehuan] = (char)dash_number2[i-1];
							break;
					}
				}
				if(factdsp.Line == 1){
					factdsp.P21--;
				}
				break;
			case 10:
				if(factcp.Line == 1){
					factcp.Cn--;
				}
				if(factdis.Line == 1){
					int8_t i;
					for(i=0;i<11;i++){
						//Usart3_Printf("%c\r\n",dash_number[i]);
						if(factdis.P32[qiehuan] ==dash_number3[i]){
							//Usart3_Printf("保存:%c\r\n字符串中:%c\r\n",factdis.P32[qiehuan],dash_number[i]);
							break;
						}
					}
					switch(qiehuan){
						case 0:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 1:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 2:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 3:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 4:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 5:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 6:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 7:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 8:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 9:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 10:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 11:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 12:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 13:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
						case 14:
							if(i == 0){
								i=10;
								factdis.P32[qiehuan] = (char)dash_number3[i];
							}
							else
								factdis.P32[qiehuan] = (char)dash_number3[i-1];
							break;
					}
				}
				if(factdsp.Line == 1){
					factdsp.P22--;
				}
				break;
			case 11:
				if(factcp.Line == 1){
					factcp.dAd--;
				}
				if(factdsp.Line == 1){
					factdsp.P23--;
				}
				break;
			case 12:
				if(factdsp.Line == 1){
					factdsp.P26--;
				}
				break;
			case 13:
				if(factdsp.Line == 1){
					factdsp.P28--;
				}
				break;
			case 14:
				if(factdsp.Line == 1){
					factdsp.P29--;
				}
				break;
			case 15:
				if(factdsp.Line == 1){
					factdsp.P30--;
				}
				break;
			case 16:
				if(factdsp.Line == 1){
					delaytt -= 10;
				}
				break;
			case 17:
				if(factdsp.Line == 1){
					delaytt1 -= 10;
				}
				break;
			case 18:
				if(factdsp.Line == 1){
					factdsp.T1--;
				}
				break;
			case 19:
				if(factdsp.Line == 1){
					factdsp.T2--;
				}
				break;
			default:
				break;
		}
		//范围检测
		{
			if(PA1 < 0)
				PA1 = 0;
			if(PA2 < 0)
				PA2 = 0;
			if(custcp.St < factcp.LS)
				custcp.St = factcp.LS;
			if(custcp.Hy < 0.5)
				custcp.Hy = 0.5;
			if(custcp.ot < -30)
				custcp.ot = -30;
			if(custcp.p2 < 0)
				custcp.p2 = 0;
			if(custcp.AC < 0)
				custcp.AC = 0;
			
			if(custdis.CF < 0)
				custdis.CF = 0;
			if(custdis.rE < 0)
				custdis.rE = 0;
			if(custdis.P01 < 0)
				custdis.P01 = 0;

			if(custdef.dE < -67)
				custdef.dE = -67;
			if(custdef.id < 0)
				custdef.id = 0;
			if(custdef.Md < 0)
				custdef.Md = 0;

			if(custfan.F1 < 0)
				custfan.F1 = 0;
			if(custfan.F2 < 0)
				custfan.F2 = 0;
			if(custfan.Fd < 0)
				custfan.Fd = 0;
			if(custfan.Fn < 0)
				custfan.Fn = 0;
			if(custfan.FF <0)
				custfan.FF = 0;
			
			if(factcp.St < factcp.LS)
				factcp.St = factcp.LS;
			if(factcp.Hy < 0.5)
				factcp.Hy = 0.5;
			if(factcp.LS < - 30)
				factcp.LS = -30;
			if(factcp.US < -58)
				factcp.US = -58;
			if(factcp.ot < -30)
				factcp.ot = -30;
			if(factcp.P2 < 0)
				factcp.P2 = 0;
			if(factcp.oE < -30)
				factcp.oE = -30;
			if(factcp.od < 0)
				factcp.od = 0;
			if(factcp.AC < 0)
				factcp.AC = 0;
			if(factcp.Cy < 0)
				factcp.Cy = 0;
			if(factcp.Cn < 0)
				factcp.Cn = 0;
			if(factcp.dAd < 0)
				factcp.dAd = 0;
			
			if(factdis.CF < 0)
				factdis.CF = 0;
			if(factdis.rE < 0)
				factdis.rE = 0;
			if(factdis.Ld < 0)
				factdis.Ld = 0;
			if(factdis.dy < 0)
				factdis.dy = 0;
			if(factdis.P01 < 0)
				factdis.P01 = 0;
			
			if(factdef.td < 0)
				factdef.td = 0;
			if(factdef.dE < -67)
				factdef.dE = -67;
			if(factdef.id < 0)
				factdef.id = 0;
			if(factdef.Md < 0)
				factdef.Md = 0;
			if(factdef.dd < 0)
				factdef.dd = 0;
			if(factdef.dF < 0)
				factdef.dF = 0;
			if(factdef.dt < 0)
				factdef.dt = 0;
			if(factdef.dP < 0)
				factdef.dP = 0;

			if(factfan.F1 < 0)
				factfan.F1 = 0;
			if(factfan.F2 < 0)
				factfan.F2 = 0;
			if(factfan.Fd < 0)
				factfan.Fd = 0;
			if(factfan.FS < -55)
				factfan.FS = -55;
			if(factfan.FAd < 1)
				factfan.FAd = 1;
			if(factfan.Fn < 0)
				factfan.Fn = 0;
			if(factfan.FF < 0)
				factfan.FF = 0;
			if(factfan.dAd < 0)
				factfan.dAd = 0;

			if(factal.AU < -100)
				factal.AU = -100;
			if(factal.AL < - 67)
				factal.AL = -67;
			if(factal.Ad < 0)
				factal.Ad = 0;
			if(factal.dA < 0)
				factal.dA = 0;
			
			if(factdsp.P10 < 1)
				factdsp.P10 = 1;
			if(factdsp.P11 < 1)
				factdsp.P11 = 1;
			if(factdsp.P13 < 10)
				factdsp.P13 = 10;
			if(factdsp.P14 < 10)
				factdsp.P14 = 10;
			if(factdsp.P16 < 10)
				factdsp.P16 = 10;
			if(factdsp.P17 < 10)
				factdsp.P17 = 10;
			if(factdsp.P18 < 0)
				factdsp.P18 = 0;
			if(factdsp.P19 < 0)
				factdsp.P19 = 0;
			if(factdsp.P20 < 0)
				factdsp.P20 = 0;
			if(factdsp.P21 < 50)
				factdsp.P21 = 50;
			if(factdsp.P22 < 50)
				factdsp.P22 = 50;
			if(factdsp.P23 < 50)
				factdsp.P23 = 50;
			if(factdsp.P26 < 1)
				factdsp.P26 = 1;
			if(factdsp.P28 < 0)
				factdsp.P28 = 0;
			if(factdsp.P29 < 25)
				factdsp.P29 = 25;
			if(factdsp.P30 < 25)
				factdsp.P30 = 25;
			if(delaytt < 0)
				delaytt = 0;
			if(delaytt1 < 0)
				delaytt1 = 0;
			if(factdsp.T1 < 0)
				factdsp.T1 = 0;
			if(factdsp.T2 < 0)
				factdsp.T2 = 0;
		}
	}
	
	
	MenuSelectShow();
}

void ParamSelect(void)
{
	Lcm_GotoXY(0,0,1);
	Lcm_Wr_Command(0x01); //显示清屏
	Lcm_GotoXY(0,0,0);
	Lcm_Wr_Command(0x01); //显示清屏
	if(stm32_config.Menu_Tier == 4){
		stm32_config.Selected++;
		if(stm32_config.Selected > 1)
			stm32_config.Selected = 0;
		if(stm32_config.Selected < 0)
			stm32_config.Selected = 1;
	}
	if(stm32_config.Menu_Tier == 1 && CUST_FACT == 0){
	    stm32_config.CUSTSelected++;
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
			if(stm32_config.CUSTSelected > 6)
					stm32_config.CUSTSelected = 0;
				
			if(stm32_config.CUSTSelected < 0)
				stm32_config.CUSTSelected = 6;
		}
		else{
			if(stm32_config.CUSTSelected > 2)
					stm32_config.CUSTSelected = 0;
				
			if(stm32_config.CUSTSelected < 0)
				stm32_config.CUSTSelected = 2;
		}
	}
	else if(stm32_config.Menu_Tier == 2 && CUST_FACT == 0){
		//DSP
		if(custdsp.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 4){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 4;
		}
		//VS
		if(custvs.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 10){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 10;
		}
		//CP
		if(custcp.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 4){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 4;
		}
		//dis
		if(custdis.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 4){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 4;
		}
		//dEF
		if(custdef.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 2){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 2;
		}
		//FAn
		if(custfan.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 2){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 2;
		}
		//AL
		if(custal.Line == 1){
			stm32_config.CUSTSelected2++;
			if(stm32_config.CUSTSelected2 > 1){
				stm32_config.CUSTSelected2 = 0;
			}
			if(stm32_config.CUSTSelected2 < 0)
				stm32_config.CUSTSelected2 = 1;
		}
	}

	if(stm32_config.Menu_Tier == 1 && CUST_FACT == 1){
		stm32_config.FACTSelected++;
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
			if(stm32_config.FACTSelected > 6){
				stm32_config.FACTSelected = 0;
			}
			if(stm32_config.FACTSelected < 0){
				stm32_config.FACTSelected = 6;
			}
		}
		else{
			if(stm32_config.FACTSelected > 1){
				stm32_config.FACTSelected = 0;
			}
			if(stm32_config.FACTSelected < 0){
				stm32_config.FACTSelected = 1;
			}
		}
	}
	else if(stm32_config.Menu_Tier == 2 && CUST_FACT == 1){
		//CP
		if(factcp.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 11){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 11;
			}
		}
		//dis
		if(factdis.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 10){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 10;
			}
		}
		//dEF
		if(factdef.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 7){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 7;
			}
		}
		//FAn
		if(factfan.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 5){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 5;
			}
		}
		//AL
		if(factal.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 3){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 3;
			}
		}
		//DSP
		if(factdsp.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 19){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 19;
			}
		}
		//FPr
		if(factfpr.Line == 1){
			stm32_config.FACTSelected2++;
			if(stm32_config.FACTSelected2 > 1){
				stm32_config.FACTSelected2 = 0;
			}
			if(stm32_config.FACTSelected2 < 0){
				stm32_config.FACTSelected2 = 1;
			}
		}
	}
	
	MenuSelectShow();
}

int ParamSave(void)
{
	p31_p32();
	//STM32 Param save on EEPROM
	uint8_t WriteBuffer[BufferSize] = {0};
	uint8_t ReadBuffer[BufferSize] = {0};

	memset(WriteBuffer,0,sizeof(WriteBuffer));
	memset(ReadBuffer,0,sizeof(ReadBuffer));
	{
			{
				WriteBuffer[index_moren_par] 					= (uint8_t)(moren_par & 0xff);
				WriteBuffer[index_moren_par1] 				= (uint8_t)((moren_par >> 8) & 0xff);
				WriteBuffer[index_c_dspP02P] 					= (uint8_t)(custdsp.P02_P & 0xff);
				WriteBuffer[index_c_dspP02P1] 				= (uint8_t)((custdsp.P02_P >> 8) & 0xff);
				WriteBuffer[index_c_dspP02C] 					= (uint8_t)(custdsp.P02_C & 0xff);
				WriteBuffer[index_c_dspP02C1] 				= (uint8_t)((custdsp.P02_C >> 8) & 0xff);
				WriteBuffer[index_c_dspDTP] 					= (uint8_t)(custdsp.DT_P & 0xff);
				WriteBuffer[index_c_dspDTP1] 					= (uint8_t)((custdsp.DT_P >> 8) & 0xff);
				WriteBuffer[index_c_dspRTP] 					= (uint8_t)(custdsp.RT_P & 0xff);
				WriteBuffer[index_c_dspRTP1] 					= (uint8_t)((custdsp.RT_P >> 8) & 0xff);
				
				WriteBuffer[index_c_vsDC] 						= (uint8_t)(custvs.DC & 0xff);
				WriteBuffer[index_c_vsDC1] 						= (uint8_t)((custvs.DC >> 8) & 0xff);
				WriteBuffer[index_c_vsCC] 						= (uint8_t)(custvs.CC & 0xff);
				WriteBuffer[index_c_vsCC1] 						= (uint8_t)((custvs.CC >> 8) & 0xff);
				WriteBuffer[index_c_vsSC] 						= (uint8_t)(custvs.SC & 0xff);
				WriteBuffer[index_c_vsSC1] 						= (uint8_t)((custvs.SC >> 8) & 0xff);
				WriteBuffer[index_c_vsMC] 						= (uint8_t)(custvs.MC & 0xff);
				WriteBuffer[index_c_vsMC1] 						= (uint8_t)((custvs.MC >> 8) & 0xff);
				WriteBuffer[index_c_vsLC] 						= (uint8_t)(custvs.LC  & 0xff);
				WriteBuffer[index_c_vsLC1] 						= (uint8_t)((custvs.LC  >> 8) & 0xff);
				WriteBuffer[index_c_vsDrTQ] 					= (uint8_t)(custvs.DrTQ & 0xff);
				WriteBuffer[index_c_vsDrTQ1] 					= (uint8_t)((custvs.DrTQ >> 8) & 0xff);
				WriteBuffer[index_c_vsDTQ] 						= (uint8_t)(custvs.DTQ  & 0xff);
				WriteBuffer[index_c_vsDTQ1] 					= (uint8_t)((custvs.DTQ  >> 8) & 0xff);
				WriteBuffer[index_c_vsFTO] 						= (uint8_t)(custvs.FTO & 0xff);
				WriteBuffer[index_c_vsFTO1] 					= (uint8_t)((custvs.FTO >> 8) & 0xff);
				WriteBuffer[index_c_vsDTO] 						= (uint8_t)(custvs.DTO & 0xff);
				WriteBuffer[index_c_vsDTO1] 					= (uint8_t)((custvs.DTO >> 8) & 0xff);
				WriteBuffer[index_c_vsCL] 						= (uint8_t)(custvs.CL & 0xff);
				WriteBuffer[index_c_vsCL1] 					= (uint8_t)((custvs.CL >> 8) & 0xff);
				WriteBuffer[index_c_vsCP] 						= (uint8_t)(custvs.CP & 0xff);
				WriteBuffer[index_c_vsCP1] 						= (uint8_t)((custvs.CP >> 8) & 0xff);
			}
			
			{
				WriteBuffer[index_f_cpSt] 						= (uint8_t)(factcp.St & 0xff);
				WriteBuffer[index_f_cpSt1] 						= (uint8_t)((factcp.St >> 8) & 0xff);
				WriteBuffer[index_f_cpHy] 						= (uint8_t)((int)factcp.Hy & 0xff);
				WriteBuffer[index_f_cpHy1] 						= (uint8_t)(((int)factcp.Hy >> 8) & 0xff);
				WriteBuffer[index_f_cpHyde] 						= (uint8_t)((int)((factcp.Hy - (int)factcp.Hy) *10) & 0xff);
				WriteBuffer[index_f_cpHyde1] 						= (uint8_t)(((int)((factcp.Hy - (int)factcp.Hy) *10) >> 8) & 0xff);
				WriteBuffer[index_f_cpLS] 						= (uint8_t)(factcp.LS & 0xff);
				WriteBuffer[index_f_cpLS1] 						= (uint8_t)((factcp.LS >> 8) & 0xff);
				WriteBuffer[index_f_cpUS] 						= (uint8_t)(factcp.US & 0xff);
				WriteBuffer[index_f_cpUS1] 						= (uint8_t)((factcp.US >> 8) & 0xff);
				WriteBuffer[index_f_cpot] 						= (uint8_t)((int)factcp.ot & 0xff);
				WriteBuffer[index_f_cpot1] 						= (uint8_t)(((int)factcp.ot >> 8) & 0xff);
				WriteBuffer[index_f_cpotde] 						= (uint8_t)((int)((factdef.dE - (int)factdef.dE) * 10) & 0xff);
				WriteBuffer[index_f_cpotde1] 					=(uint8_t)(((int)((factdef.dE - (int)factdef.dE) * 10) >> 8) & 0xff);
				WriteBuffer[index_f_cpP2] 						= (uint8_t)(factcp.P2 & 0xff);
				WriteBuffer[index_f_cpP21] 						= (uint8_t)((factcp.P2 >> 8) & 0xff);
				WriteBuffer[index_f_cpoE] 						= (uint8_t)((int)factcp.oE & 0xff);
				WriteBuffer[index_f_cpoE1] 						= (uint8_t)(((int)factcp.oE >> 8) & 0xff);
				WriteBuffer[index_f_cpoEde] 						= (uint8_t)((int)((factcp.oE - (int)factcp.oE) *10) & 0xff);
				WriteBuffer[index_f_cpoEde1] 						= (uint8_t)(((int)((factcp.oE - (int)factcp.oE) *10) >> 8) & 0xff);
				WriteBuffer[index_f_cpod] 						= (uint8_t)(factcp.od & 0xff);
				WriteBuffer[index_f_cpod1] 						= (uint8_t)((factcp.od >> 8) & 0xff);
				WriteBuffer[index_f_cpAC] 						= (uint8_t)(factcp.AC & 0xff);
				WriteBuffer[index_f_cpAC1] 						= (uint8_t)((factcp.AC >> 8) & 0xff);
				WriteBuffer[index_f_cpCy] 						= (uint8_t)(factcp.Cy & 0xff);
				WriteBuffer[index_f_cpCy1] 						= (uint8_t)((factcp.Cy >> 8) & 0xff);
				WriteBuffer[index_f_cpCn] 						= (uint8_t)(factcp.Cn & 0xff);
				WriteBuffer[index_f_cpCn1] 						= (uint8_t)((factcp.Cn >> 8) & 0xff);
				WriteBuffer[index_f_cpdAd] 						= (uint8_t)(factcp.dAd & 0xff);
				WriteBuffer[index_f_cpdAd1] 						= (uint8_t)((factcp.dAd >> 8) & 0xff);
				
				
				WriteBuffer[index_f_disPA1] 						= (uint8_t)(factdis.PA1 & 0xff);
				WriteBuffer[index_f_disPA11] 						= (uint8_t)((factdis.PA1 >> 8) & 0xff);
				WriteBuffer[index_f_disPA2] 						= (uint8_t)(factdis.PA2 & 0xff);
				WriteBuffer[index_f_disPA21] 						= (uint8_t)((factdis.PA2 >> 8) & 0xff);
				WriteBuffer[index_f_disCF] 						= (uint8_t)(factdis.CF & 0xff);
				WriteBuffer[index_f_disCF1] 						= (uint8_t)((factdis.CF >> 8) & 0xff);
				WriteBuffer[index_f_disCF] 						= (uint8_t)(factdis.CF & 0xff);
				WriteBuffer[index_f_disCF1] 						= (uint8_t)((factdis.CF >> 8) & 0xff);
				WriteBuffer[index_f_disrE] 						= (uint8_t)((int)factdis.rE & 0xff);
				WriteBuffer[index_f_disrE1] 						= (uint8_t)(((int)factdis.rE >> 8) & 0xff);
//					WriteBuffer[index_f_disrEde] 						= (uint8_t)((int)((factdis.rE - (int)factdis.rE) *10) & 0xff);
//					WriteBuffer[index_f_disrEde1] 						= (uint8_t)(((int)((factdis.rE - (int)factdis.rE) *10) >> 8) & 0xff);
				WriteBuffer[index_f_disLd] 						= (uint8_t)(factdis.Ld & 0xff);
				WriteBuffer[index_f_disLd1] 						= (uint8_t)((factdis.Ld >> 8) & 0xff);
				WriteBuffer[index_f_disdy] 						= (uint8_t)(factdis.dy & 0xff);
				WriteBuffer[index_f_disdy1] 						= (uint8_t)((factdis.dy >> 8) & 0xff);
//					WriteBuffer[index_f_disd1] 						= (uint8_t)(factdis.d1 & 0xff);
//					WriteBuffer[index_f_disd11] 						= (uint8_t)((factdis.d1 >> 8) & 0xff);
//					WriteBuffer[index_f_disd2] 						= (uint8_t)(factdis.d2 & 0xff);
//					WriteBuffer[index_f_disd21] 						= (uint8_t)((factdis.d2 >> 8) & 0xff);
//					WriteBuffer[index_f_disP01] 						= (uint8_t)(factdis.P01 & 0xff);
//					WriteBuffer[index_f_disP011] 						= (uint8_t)((factdis.P01 >> 8) & 0xff);
				
				WriteBuffer[index_f_deftd] 						= (uint8_t)(factdef.td & 0xff);
				WriteBuffer[index_f_deftd1] 						= (uint8_t)((factdef.td >> 8) & 0xff);
				WriteBuffer[index_f_defdE] 						= (uint8_t)(factdef.dE & 0xff);
				WriteBuffer[index_f_defdE1] 						= (uint8_t)((factdef.dE >> 8) & 0xff);
				WriteBuffer[index_f_defid] 						= (uint8_t)(factdef.id & 0xff);
				WriteBuffer[index_f_defid1] 						= (uint8_t)((factdef.id >> 8) & 0xff);
				WriteBuffer[index_f_defMd] 						= (uint8_t)(factdef.Md & 0xff);
				WriteBuffer[index_f_defMd1] 						= (uint8_t)((factdef.Md >> 8) & 0xff);
				WriteBuffer[index_f_defdd] 						= (uint8_t)(factdef.dd & 0xff);
				WriteBuffer[index_f_defdd1] 						= (uint8_t)((factdef.dd >> 8) & 0xff);
				WriteBuffer[index_f_defdF] 						= (uint8_t)(factdef.dF & 0xff);
				WriteBuffer[index_f_defdF1] 						= (uint8_t)((factdef.dF >> 8) & 0xff);
				WriteBuffer[index_f_defdt] 						= (uint8_t)(factdef.dt & 0xff);
				WriteBuffer[index_f_defdt1] 						= (uint8_t)((factdef.dt >> 8) & 0xff);
				WriteBuffer[index_f_defdP] 						= (uint8_t)(factdef.dP & 0xff);
				WriteBuffer[index_f_defdP1] 						= (uint8_t)((factdef.dP >> 8) & 0xff);
				
//					WriteBuffer[index_f_fanF1] 						= (uint8_t)(factfan.F1 & 0xff);
//					WriteBuffer[index_f_fanF11] 						= (uint8_t)((factfan.F1 >> 8) & 0xff);
//					WriteBuffer[index_f_fanF2] 						= (uint8_t)(factfan.F2 & 0xff);
//					WriteBuffer[index_f_fanF21] 						= (uint8_t)((factfan.F2 >> 8) & 0xff);
				WriteBuffer[index_f_fanFd] 						= (uint8_t)(factfan.Fd & 0xff);
				WriteBuffer[index_f_fanFd1] 						= (uint8_t)((factfan.Fd >> 8) & 0xff);
				WriteBuffer[index_f_fanFS] 						= (uint8_t)(factfan.FS & 0xff);
				WriteBuffer[index_f_fanFS1] 						= (uint8_t)((factfan.FS >> 8) & 0xff);
				WriteBuffer[index_f_fanFAd] 						= (uint8_t)(factfan.FAd & 0xff);
				WriteBuffer[index_f_fanFAd1] 						= (uint8_t)((factfan.FAd >> 8) & 0xff);
				WriteBuffer[index_f_fanFn] 						= (uint8_t)(factfan.Fn & 0xff);
				WriteBuffer[index_f_fanFn1] 						= (uint8_t)((factfan.Fn >> 8) & 0xff);
				WriteBuffer[index_f_fanFF] 						= (uint8_t)(factfan.FF & 0xff);
				WriteBuffer[index_f_fanFF1] 						= (uint8_t)((factfan.FF >> 8) & 0xff);
				WriteBuffer[index_f_fandAd] 						= (uint8_t)(factfan.dAd & 0xff);
				WriteBuffer[index_f_fandAd1] 						= (uint8_t)((factfan.dAd >> 8) & 0xff);
				
				WriteBuffer[index_f_alAU] 						= (uint8_t)(factal.AU & 0xff);
				WriteBuffer[index_f_alAU1] 						= (uint8_t)((factal.AU >> 8) & 0xff);
				WriteBuffer[index_f_alAL] 						= (uint8_t)(factal.AL & 0xff);
				WriteBuffer[index_f_alAL1] 						= (uint8_t)((factal.AL >> 8) & 0xff);
				WriteBuffer[index_f_alAd] 						= (uint8_t)(factal.Ad & 0xff);
				WriteBuffer[index_f_alAd1] 						= (uint8_t)((factal.Ad >> 8) & 0xff);
				WriteBuffer[index_f_aldA] 						= (uint8_t)(factal.dA & 0xff);
				WriteBuffer[index_f_aldA1] 						= (uint8_t)((factal.dA >> 8) & 0xff);
				
				WriteBuffer[index_f_dspP10] 						= (uint8_t)(factdsp.P10 & 0xff);
				WriteBuffer[index_f_dspP101] 						= (uint8_t)((factdsp.P10 >> 8) & 0xff);
				WriteBuffer[index_f_dspP11] 						= (uint8_t)(factdsp.P11 & 0xff);
				WriteBuffer[index_f_dspP111] 						= (uint8_t)((factdsp.P11 >> 8) & 0xff);
				WriteBuffer[index_f_dspP13] 						= (uint8_t)(factdsp.P13 & 0xff);
				WriteBuffer[index_f_dspP131] 						= (uint8_t)((factdsp.P13 >> 8) & 0xff);
				WriteBuffer[index_f_dspP14] 						= (uint8_t)(factdsp.P14 & 0xff);
				WriteBuffer[index_f_dspP141] 						= (uint8_t)((factdsp.P14 >> 8) & 0xff);
				WriteBuffer[index_f_dspP15] 						= (uint8_t)(factdsp.P15 & 0xff);
				WriteBuffer[index_f_dspP151] 						= (uint8_t)((factdsp.P15 >> 8) & 0xff);
				WriteBuffer[index_f_dspP16] 						= (uint8_t)(factdsp.P16 & 0xff);
				WriteBuffer[index_f_dspP161] 						= (uint8_t)((factdsp.P16 >> 8) & 0xff);
				WriteBuffer[index_f_dspP17] 						= (uint8_t)(factdsp.P17 & 0xff);
				WriteBuffer[index_f_dspP171] 						= (uint8_t)((factdsp.P17 >> 8) & 0xff);
				WriteBuffer[index_f_dspP18] 						= (uint8_t)(factdsp.P18 & 0xff);
				WriteBuffer[index_f_dspP181] 						= (uint8_t)((factdsp.P18 >> 8) & 0xff);
				WriteBuffer[index_f_dspP19] 						= (uint8_t)(factdsp.P19 & 0xff);
				WriteBuffer[index_f_dspP191] 						= (uint8_t)((factdsp.P19 >> 8) & 0xff);
				WriteBuffer[index_f_dspP20] 						= (uint8_t)(factdsp.P20 & 0xff);
				WriteBuffer[index_f_dspP201] 						= (uint8_t)((factdsp.P20 >> 8) & 0xff);
				WriteBuffer[index_f_dspP21] 						= (uint8_t)(factdsp.P21 & 0xff);
				WriteBuffer[index_f_dspP211] 						= (uint8_t)((factdsp.P21 >> 8) & 0xff);
				WriteBuffer[index_f_dspP22] 						= (uint8_t)(factdsp.P22 & 0xff);
				WriteBuffer[index_f_dspP221] 						= (uint8_t)((factdsp.P22 >> 8) & 0xff);
				WriteBuffer[index_f_dspP23] 						= (uint8_t)(factdsp.P23 & 0xff);
				WriteBuffer[index_f_dspP231] 						= (uint8_t)((factdsp.P23 >> 8) & 0xff);
//					WriteBuffer[index_f_dspP26] 						= (uint8_t)(factdsp.P26 & 0xff);
//					WriteBuffer[index_f_dspP261] 						= (uint8_t)((factdsp.P26 >> 8) & 0xff);
//					WriteBuffer[index_f_dspP28] 						= (uint8_t)(factdsp.P28 & 0xff);
//					WriteBuffer[index_f_dspP281] 						= (uint8_t)((factdsp.P28 >> 8) & 0xff);
				WriteBuffer[index_f_dspP29] 						= (uint8_t)(factdsp.P29 & 0xff);
				WriteBuffer[index_f_dspP291] 						= (uint8_t)((factdsp.P29 >> 8) & 0xff);
				WriteBuffer[index_f_dspP30] 						= (uint8_t)(factdsp.P30 & 0xff);
				WriteBuffer[index_f_dspP301] 						= (uint8_t)((factdsp.P30 >> 8) & 0xff);
				
				WriteBuffer[index_delay] 						= (uint8_t)(delaytt & 0xff);
				WriteBuffer[index_delay1] 						= (uint8_t)((delaytt >> 8) & 0xff);
				WriteBuffer[index_delaytt] 						= (uint8_t)(delaytt1 & 0xff);
				WriteBuffer[index_delaytt1] 						= (uint8_t)((delaytt1 >> 8) & 0xff);
				WriteBuffer[index_f_dspT1] 						= (uint8_t)(factdsp.T1 & 0xff);
				WriteBuffer[index_f_dspT11] 						= (uint8_t)((factdsp.T1 >> 8) & 0xff);
				WriteBuffer[index_f_dspT2] 						= (uint8_t)(factdsp.T2 & 0xff);
				WriteBuffer[index_f_dspT21] 						= (uint8_t)((factdsp.T2 >> 8) & 0xff);
//					WriteBuffer[index_f_fprUL] 						= (uint8_t)(factfpr.UL & 0xff);
//					WriteBuffer[index_f_fprUL1] 						= (uint8_t)((factfpr.UL >> 8) & 0xff);
//					WriteBuffer[index_f_fprFr] 						= (uint8_t)(factfpr.Fr & 0xff);
//					WriteBuffer[index_f_fprFr1] 						= (uint8_t)((factfpr.Fr >> 8) & 0xff);
			}
			{
				WriteBuffer[index_P31_0] 						= (uint8_t)(p31_0 & 0xff);
				WriteBuffer[index_P31_01] 						= (uint8_t)((p31_0 >> 8) & 0xff);
				WriteBuffer[index_P31_1] 						= (uint8_t)(p31_1 & 0xff);
				WriteBuffer[index_P31_11] 						= (uint8_t)((p31_1 >> 8) & 0xff);
				WriteBuffer[index_P31_2] 						= (uint8_t)(p31_2 & 0xff);
				WriteBuffer[index_P31_21] 						= (uint8_t)((p31_2 >> 8) & 0xff);
				WriteBuffer[index_P31_3] 						= (uint8_t)(p31_3 & 0xff);
				WriteBuffer[index_P31_31] 						= (uint8_t)((p31_3 >> 8) & 0xff);
				WriteBuffer[index_P31_4] 						= (uint8_t)(p31_4 & 0xff);
				WriteBuffer[index_P31_41] 						= (uint8_t)((p31_4 >> 8) & 0xff);
				WriteBuffer[index_P31_5] 						= (uint8_t)(p31_5 & 0xff);
				WriteBuffer[index_P31_51] 						= (uint8_t)((p31_5 >> 8) & 0xff);
				WriteBuffer[index_P31_6] 						= (uint8_t)(p31_6 & 0xff);
				WriteBuffer[index_P31_61] 						= (uint8_t)((p31_6 >> 8) & 0xff);
				WriteBuffer[index_P31_7] 						= (uint8_t)(p31_7 & 0xff);
				WriteBuffer[index_P31_71] 						= (uint8_t)((p31_7 >> 8) & 0xff);
				WriteBuffer[index_P31_8] 						= (uint8_t)(p31_8 & 0xff);
				WriteBuffer[index_P31_81] 						= (uint8_t)((p31_8 >> 8) & 0xff);
				WriteBuffer[index_P31_9] 						= (uint8_t)(p31_9 & 0xff);
				WriteBuffer[index_P31_91] 						= (uint8_t)((p31_9 >> 8) & 0xff);
				WriteBuffer[index_P31_10] 						= (uint8_t)(p31_10 & 0xff);
				WriteBuffer[index_P31_101] 						= (uint8_t)((p31_10 >> 8) & 0xff);
				WriteBuffer[index_P31_110] 						= (uint8_t)(p31_11 & 0xff);
				WriteBuffer[index_P31_111] 						= (uint8_t)((p31_11 >> 8) & 0xff);
				WriteBuffer[index_P31_12] 						= (uint8_t)(p31_12 & 0xff);
				WriteBuffer[index_P31_121] 						= (uint8_t)((p31_12 >> 8) & 0xff);
				WriteBuffer[index_P31_13] 						= (uint8_t)(p31_13 & 0xff);
				WriteBuffer[index_P31_131] 						= (uint8_t)((p31_13 >> 8) & 0xff);
				WriteBuffer[index_P31_14] 						= (uint8_t)(p31_14 & 0xff);
				WriteBuffer[index_P31_141] 						= (uint8_t)((p31_14 >> 8) & 0xff);
				WriteBuffer[index_P32_0] 						= (uint8_t)(p32_0 & 0xff);
				WriteBuffer[index_P32_01] 						= (uint8_t)((p32_0 >> 8) & 0xff);
				WriteBuffer[index_P32_1] 						= (uint8_t)(p32_1 & 0xff);
				WriteBuffer[index_P32_11] 						= (uint8_t)((p32_1 >> 8) & 0xff);
				WriteBuffer[index_P32_2] 						= (uint8_t)(p32_2 & 0xff);
				WriteBuffer[index_P32_21] 						= (uint8_t)((p32_2 >> 8) & 0xff);
				WriteBuffer[index_P32_3] 						= (uint8_t)(p32_3 & 0xff);
				WriteBuffer[index_P32_31] 						= (uint8_t)((p32_3 >> 8) & 0xff);
				WriteBuffer[index_P32_4] 						= (uint8_t)(p32_4 & 0xff);
				WriteBuffer[index_P32_41] 						= (uint8_t)((p32_4 >> 8) & 0xff);
				WriteBuffer[index_P32_5] 						= (uint8_t)(p32_5 & 0xff);
				WriteBuffer[index_P32_51] 						= (uint8_t)((p32_5 >> 8) & 0xff);
				WriteBuffer[index_P32_6] 						= (uint8_t)(p32_6 & 0xff);
				WriteBuffer[index_P32_61] 						= (uint8_t)((p32_6 >> 8) & 0xff);
				WriteBuffer[index_P32_7] 						= (uint8_t)(p32_7 & 0xff);
				WriteBuffer[index_P32_71] 						= (uint8_t)((p32_7 >> 8) & 0xff);
				WriteBuffer[index_P32_8] 						= (uint8_t)(p32_8 & 0xff);
				WriteBuffer[index_P32_81] 						= (uint8_t)((p32_8 >> 8) & 0xff);
				WriteBuffer[index_P32_9] 						= (uint8_t)(p32_9 & 0xff);
				WriteBuffer[index_P32_91] 						= (uint8_t)((p32_9 >> 8) & 0xff);
				WriteBuffer[index_P32_10] 						= (uint8_t)(p32_10 & 0xff);
				WriteBuffer[index_P32_101] 						= (uint8_t)((p32_10 >> 8) & 0xff);
				WriteBuffer[index_P32_110] 						= (uint8_t)(p32_11 & 0xff);
				WriteBuffer[index_P32_111] 						= (uint8_t)((p32_11 >> 8) & 0xff);
				WriteBuffer[index_P32_12] 						= (uint8_t)(p32_12 & 0xff);
				WriteBuffer[index_P32_121] 						= (uint8_t)((p32_12 >> 8) & 0xff);
				WriteBuffer[index_P32_13] 						= (uint8_t)(p32_13 & 0xff);
				WriteBuffer[index_P32_131] 						= (uint8_t)((p32_13 >> 8) & 0xff);
				WriteBuffer[index_P32_14] 						= (uint8_t)(p32_14 & 0xff);
				WriteBuffer[index_P32_141] 						= (uint8_t)((p32_14 >> 8) & 0xff);
			}
	}
		//Usart3_Printf("整数:%d\r\n小数:%d\r\n",(uint8_t)((int)((custcp.Hy - (int)custcp.Hy) * 10) & 0xff),(uint8_t)(((int)((custcp.Hy -(int)custcp.Hy) * 10) >> 8) & 0xff));
		AT24Cxx_Write(WriteBuffer);
	AT24Cxx_Read(ReadBuffer);
	static uint8_t SaveFailed = 0;

	if(memcmp(WriteBuffer, ReadBuffer, BufferSize) == 0 ) // check date 
	{
		SaveFailed = 0;
		//if(stm32_config.iSetting == 1)
		if(1)
		{
			//display(0, "Saved", "",1);
		}
		//TIM3_Enable();
		//HAL_Delay(2000);
				//Usart3_Printf("保存成功啊啊啊啊啊啊啊啊啊\r\n");
	}
	else
	{
		if(SaveFailed < 3)
		{
			SaveFailed++;
		   // config->iSetting = 1;
			char str[15] = {0};
			sprintf(str,"Try Again,%d",SaveFailed);
			//display(0, "Save Failed", str,1);
			HAL_Delay(1000);
		}
		else
		{
			SaveFailed = 0;
			//config->iSetting = 0;
			TIM3_Enable();
			//display(0, "Save Failed", "Error...",1);
			//HAL_Delay(2000);
		}
				
				//Usart3_Printf("保存失败啊啊啊啊啊啊啊啊啊\r\n");
	}
    return 0;
}

int ParamRead(void)
{
	
    uint8_t ReadBuffer[BufferSize] = {0};
    int ret = AT24Cxx_Read(ReadBuffer);

    if(ret != 0)
    {
        //display(0, "Read Param", "Failed",2);
        return 1;
    }
    else
    {
//        display(0, "Read Successful", "",2);
//				HAL_Delay(500);
    }

	{
//		demical0 = ReadBuffer[index_c_cpHyde] | (ReadBuffer[index_c_cpHyde1] << 8);
		demical0 = demical0 / 10;
//		demical1 = ReadBuffer[index_c_cpotde] | (ReadBuffer[index_c_cpotde1] << 8);
		demical1 = demical1 / 10;
	//	demical2 = ReadBuffer[index_c_disrEde] | (ReadBuffer[index_c_disrEde1] << 8);
	//	demical2 = demical2 / 10;
//		demical3 = ReadBuffer[index_c_defdEde] | (ReadBuffer[index_c_defdEde1] << 8);
		demical3 = demical3 / 10;
		demical4 = ReadBuffer[index_f_cpHyde] | (ReadBuffer[index_f_cpHyde1] << 8);
		demical4 = demical4 / 10;
		demical5 = ReadBuffer[index_f_cpoEde] | (ReadBuffer[index_f_cpoEde1] << 8);
		demical5 = demical5 / 10;
		demical6 = ReadBuffer[index_f_cpotde] | (ReadBuffer[index_f_cpotde1] << 8);
		demical6 = demical6 / 10;
		//工厂
		factcp.St = ReadBuffer[index_f_cpSt] | (ReadBuffer[index_f_cpSt1] << 8);
		factcp.Hy = (ReadBuffer[index_f_cpHy] | (ReadBuffer[index_f_cpHy1] << 8)) + demical4;
		factcp.LS = ReadBuffer[index_f_cpLS] | (ReadBuffer[index_f_cpLS1] << 8);
		factcp.US = ReadBuffer[index_f_cpUS] | (ReadBuffer[index_f_cpUS1] << 8);
		factcp.ot = (ReadBuffer[index_f_cpot] | (ReadBuffer[index_f_cpot1] << 8)) + demical6;
		factcp.P2 = ReadBuffer[index_f_cpP2] | (ReadBuffer[index_f_cpP21] << 8);
		factcp.oE = (ReadBuffer[index_f_cpoE] | (ReadBuffer[index_f_cpoE1] << 8)) + demical5;
		factcp.od = ReadBuffer[index_f_cpod] | (ReadBuffer[index_f_cpod1] << 8);
		factcp.AC = ReadBuffer[index_f_cpAC] | (ReadBuffer[index_f_cpAC1] << 8);
		factcp.Cy = ReadBuffer[index_f_cpCy] | (ReadBuffer[index_f_cpCy1] << 8);
		factcp.Cn = ReadBuffer[index_f_cpCn] | (ReadBuffer[index_f_cpCn1] << 8);
		factcp.dAd = ReadBuffer[index_f_cpdAd] | (ReadBuffer[index_f_cpdAd1] << 8);
	
		factdis.PA1 = ReadBuffer[index_f_disPA1] | (ReadBuffer[index_f_disPA11] << 8);
		factdis.PA2 = ReadBuffer[index_f_disPA2] | (ReadBuffer[index_f_disPA21] << 8);
		factdis.CF = ReadBuffer[index_f_disCF] | (ReadBuffer[index_f_disCF] << 8);
		factdis.rE = (ReadBuffer[index_f_disrE] | (ReadBuffer[index_f_disrE] << 8));
		//factdis.rE = (ReadBuffer[index_f_disrE] | (ReadBuffer[index_f_disrE] << 8)) + demical6;
		factdis.Ld = ReadBuffer[index_f_disLd] | (ReadBuffer[index_f_disLd1] << 8);
		factdis.dy = ReadBuffer[index_f_disdy] | (ReadBuffer[index_f_disdy1] << 8);
//		factdis.d1 = ReadBuffer[index_f_disd1] | (ReadBuffer[index_f_disd11] << 8);
//		factdis.d2 = ReadBuffer[index_f_disd2] | (ReadBuffer[index_f_disd21] << 8);
//		factdis.P01 = ReadBuffer[index_f_disP01] | (ReadBuffer[index_f_disP011] << 8);
//		factdis.P31 = ReadBuffer[index_f_disP31] | (ReadBuffer[index_f_disP311] << 8);
//		factdis.P32 = ReadBuffer[index_f_disP32] | (ReadBuffer[index_f_disP321] << 8);

		factdef.td = ReadBuffer[index_f_deftd] | (ReadBuffer[index_f_deftd1] << 8);
		factdef.dE = ReadBuffer[index_f_defdE] | (ReadBuffer[index_f_defdE1] << 8);
		factdef.id = ReadBuffer[index_f_defid] | (ReadBuffer[index_f_defid1] << 8);
		factdef.Md = ReadBuffer[index_f_defMd] | (ReadBuffer[index_f_defMd1] << 8);
		factdef.dd = ReadBuffer[index_f_defdd] | (ReadBuffer[index_f_defdd1] << 8);
		factdef.dF = ReadBuffer[index_f_defdF] | (ReadBuffer[index_f_defdF1] << 8);
		factdef.dt = ReadBuffer[index_f_defdt] | (ReadBuffer[index_f_defdt1] << 8);
		factdef.dP = ReadBuffer[index_f_defdP] | (ReadBuffer[index_f_defdP1] << 8);

//		factfan.F1 = ReadBuffer[index_f_fanF1] | (ReadBuffer[index_f_fanF11] << 8);
//		factfan.F2 = ReadBuffer[index_f_fanF2] | (ReadBuffer[index_f_fanF21] << 8);
		factfan.Fd = ReadBuffer[index_f_fanFd] | (ReadBuffer[index_f_fanFd1] << 8);
		factfan.FS = ReadBuffer[index_f_fanFS] | (ReadBuffer[index_f_fanFS1] << 8);
		factfan.FAd = ReadBuffer[index_f_fanFAd] | (ReadBuffer[index_f_fanFAd1] << 8);
		factfan.Fn = ReadBuffer[index_f_fanFn] | (ReadBuffer[index_f_fanFn1] << 8);
		factfan.FF = ReadBuffer[index_f_fanFF] | (ReadBuffer[index_f_fanFF1] << 8);
		factfan.dAd = ReadBuffer[index_f_fandAd] | (ReadBuffer[index_f_fandAd1] << 8);

		factal.AU = ReadBuffer[index_f_alAU] | (ReadBuffer[index_f_alAU1] << 8);
		factal.AL = ReadBuffer[index_f_alAL] | (ReadBuffer[index_f_alAL1] << 8);
		factal.Ad = ReadBuffer[index_f_alAd] | (ReadBuffer[index_f_alAd1] << 8);
		factal.dA = ReadBuffer[index_f_aldA] | (ReadBuffer[index_f_aldA1] << 8);

		factdsp.P10 = ReadBuffer[index_f_dspP10] | (ReadBuffer[index_f_dspP101] << 8);
		factdsp.P11 = ReadBuffer[index_f_dspP11] | (ReadBuffer[index_f_dspP111] << 8);
		factdsp.P13 = ReadBuffer[index_f_dspP13] | (ReadBuffer[index_f_dspP131] << 8);
		factdsp.P14 = ReadBuffer[index_f_dspP14] | (ReadBuffer[index_f_dspP141] << 8);
		factdsp.P15 = ReadBuffer[index_f_dspP15] | (ReadBuffer[index_f_dspP151] << 8);
		factdsp.P16 = ReadBuffer[index_f_dspP16] | (ReadBuffer[index_f_dspP161] << 8);
		factdsp.P17 = ReadBuffer[index_f_dspP17] | (ReadBuffer[index_f_dspP171] << 8);
		factdsp.P18 = ReadBuffer[index_f_dspP18] | (ReadBuffer[index_f_dspP181] << 8);
		factdsp.P19 = ReadBuffer[index_f_dspP19] | (ReadBuffer[index_f_dspP191] << 8);
		factdsp.P20 = ReadBuffer[index_f_dspP20] | (ReadBuffer[index_f_dspP201] << 8);
		factdsp.P21 = ReadBuffer[index_f_dspP21] | (ReadBuffer[index_f_dspP211] << 8);
		factdsp.P22 = ReadBuffer[index_f_dspP22] | (ReadBuffer[index_f_dspP221] << 8);
		factdsp.P23 = ReadBuffer[index_f_dspP23] | (ReadBuffer[index_f_dspP231] << 8);
//		factdsp.P26 = ReadBuffer[index_f_dspP26] | (ReadBuffer[index_f_dspP261] << 8);
//		factdsp.P28 = ReadBuffer[index_f_dspP28] | (ReadBuffer[index_f_dspP28] << 8);
		factdsp.P29 = ReadBuffer[index_f_dspP29] | (ReadBuffer[index_f_dspP291] << 8);
		factdsp.P30 = ReadBuffer[index_f_dspP30] | (ReadBuffer[index_f_dspP301] << 8);

		delaytt     = ReadBuffer[index_delay] | (ReadBuffer[index_delay1] << 8);
		delaytt1     = ReadBuffer[index_delaytt] | (ReadBuffer[index_delaytt1] << 8);
		factdsp.T1     = ReadBuffer[index_f_dspT1] | (ReadBuffer[index_f_dspT11] << 8);
		factdsp.T2     = ReadBuffer[index_f_dspT2] | (ReadBuffer[index_f_dspT21] << 8);
//		factfpr.UL = ReadBuffer[index_f_fprUL] | (ReadBuffer[index_f_fprUL1] << 8);
//		factfpr.Fr = ReadBuffer[index_f_fprFr] | (ReadBuffer[index_f_fprFr1] << 8);
	}
	{
		//用户
		moren_par     = ReadBuffer[index_moren_par] | (ReadBuffer[index_moren_par1] << 8);
		custdsp.P02_P = ReadBuffer[index_c_dspP02P] | (ReadBuffer[index_c_dspP02P1] << 8);
		custdsp.P02_C = ReadBuffer[index_c_dspP02C] | (ReadBuffer[index_c_dspP02C1] << 8);
		custdsp.DT_P = ReadBuffer[index_c_dspDTP] | (ReadBuffer[index_c_dspDTP1] << 8);
		custdsp.RT_P = ReadBuffer[index_c_dspRTP] | (ReadBuffer[index_c_dspRTP1] << 8);

		custvs.DC = ReadBuffer[index_c_vsDC] | (ReadBuffer[index_c_vsDC1] << 8);
		custvs.CC = ReadBuffer[index_c_vsCC] | (ReadBuffer[index_c_vsCC1] << 8);
		custvs.SC = ReadBuffer[index_c_vsSC] | (ReadBuffer[index_c_vsSC1] << 8);
		custvs.MC = ReadBuffer[index_c_vsMC] | (ReadBuffer[index_c_vsMC1] << 8);
		custvs.LC = ReadBuffer[index_c_vsLC] | (ReadBuffer[index_c_vsLC1] << 8);
		custvs.DrTQ = ReadBuffer[index_c_vsDrTQ] | (ReadBuffer[index_c_vsDrTQ1] << 8);
		custvs.DTQ = ReadBuffer[index_c_vsDTQ] | (ReadBuffer[index_c_vsDTQ1] << 8);
		custvs.FTO = ReadBuffer[index_c_vsFTO] | (ReadBuffer[index_c_vsFTO1] << 8);
		custvs.DTO = ReadBuffer[index_c_vsDTO] | (ReadBuffer[index_c_vsDTO] << 8);
		custvs.CL = ReadBuffer[index_c_vsCL] | (ReadBuffer[index_c_vsCL1] << 8);
		custvs.CP = ReadBuffer[index_c_vsCP] | (ReadBuffer[index_c_vsCP1] << 8);
		
		custcp.St = factcp.St;
		custcp.Hy = factcp.Hy;
		custcp.ot = factcp.ot;
		custcp.p2 = factcp.P2;
		custcp.AC = factcp.AC;

		custdis.CF = factdis.CF;
		custdis.rE = factdis.rE;
		
		custdef.dE = factdef.dE;
		custdef.id = factdef.id;
		custdef.Md = factdef.Md;
		
		custfan.Fd = factfan.Fd;
		custfan.Fn = factfan.Fn;
		custfan.FF = factfan.FF;
		
		custal.AU = factal.AU;
		custal.AL = factal.AL;
	}
	{
		p31_0  = ReadBuffer[index_P31_0]   | (ReadBuffer[index_P31_01] << 8);
		p31_1  = ReadBuffer[index_P31_1]   | (ReadBuffer[index_P31_11] << 8);
		p31_2  = ReadBuffer[index_P31_2]   | (ReadBuffer[index_P31_21] << 8);
		p31_3  = ReadBuffer[index_P31_3]   | (ReadBuffer[index_P31_31] << 8);
		p31_4  = ReadBuffer[index_P31_4]   | (ReadBuffer[index_P31_41] << 8);
		p31_5  = ReadBuffer[index_P31_5]   | (ReadBuffer[index_P31_51] << 8);
		p31_6  = ReadBuffer[index_P31_6]   | (ReadBuffer[index_P31_61] << 8);
		p31_7  = ReadBuffer[index_P31_7]   | (ReadBuffer[index_P31_71] << 8);
		p31_8  = ReadBuffer[index_P31_8]   | (ReadBuffer[index_P31_81] << 8);
		p31_9  = ReadBuffer[index_P31_9]   | (ReadBuffer[index_P31_91] << 8);
		p31_10 = ReadBuffer[index_P31_10]  | (ReadBuffer[index_P31_101] << 8);
		p31_11 = ReadBuffer[index_P31_110] | (ReadBuffer[index_P31_111] << 8);
		p31_12 = ReadBuffer[index_P31_12]  | (ReadBuffer[index_P31_121] << 8);
		p31_13 = ReadBuffer[index_P31_13]  | (ReadBuffer[index_P31_131] << 8);
		p31_14 = ReadBuffer[index_P31_14]  | (ReadBuffer[index_P31_141] << 8);
		
		p32_0  = ReadBuffer[index_P32_0] | (ReadBuffer[index_P32_01] << 8);
		p32_1  = ReadBuffer[index_P32_1] | (ReadBuffer[index_P32_11] << 8);
		p32_2  = ReadBuffer[index_P32_2] | (ReadBuffer[index_P32_21] << 8);
		p32_3  = ReadBuffer[index_P32_3] | (ReadBuffer[index_P32_31] << 8);
		p32_4  = ReadBuffer[index_P32_4] | (ReadBuffer[index_P32_41] << 8);
		p32_5  = ReadBuffer[index_P32_5] | (ReadBuffer[index_P32_51] << 8);
		p32_6  = ReadBuffer[index_P32_6] | (ReadBuffer[index_P32_61] << 8);
		p32_7  = ReadBuffer[index_P32_7] | (ReadBuffer[index_P32_71] << 8);
		p32_8  = ReadBuffer[index_P32_8] | (ReadBuffer[index_P32_81] << 8);
		p32_9  = ReadBuffer[index_P32_9] | (ReadBuffer[index_P32_91] << 8);
		p32_10 = ReadBuffer[index_P32_10] | (ReadBuffer[index_P32_101] << 8);
		p32_11 = ReadBuffer[index_P32_110] | (ReadBuffer[index_P32_111] << 8);
		p32_12 = ReadBuffer[index_P32_12] | (ReadBuffer[index_P32_121] << 8);
		p32_13 = ReadBuffer[index_P32_13] | (ReadBuffer[index_P32_131] << 8);
		p32_14 = ReadBuffer[index_P32_14] | (ReadBuffer[index_P32_141] << 8);
		factdis.P31[0]  = dash_number0[p31_0];
		factdis.P31[1]  = dash_number1[p31_1];
		factdis.P31[2]  = dash_number2[p31_2];
		factdis.P31[3]  = dash_number2[p31_3];
		factdis.P31[4]  = dash_number2[p31_4];
		factdis.P31[5]  = dash_number2[p31_5];
		factdis.P31[6]  = dash_number2[p31_6];
		factdis.P31[7]  = dash_number2[p31_7];
		factdis.P31[8]  = dash_number2[p31_8];
		factdis.P31[9]  = dash_number2[p31_9];
		factdis.P31[10] = dash_number2[p31_10];
		factdis.P31[11] = dash_number2[p31_11];
		factdis.P31[12] = dash_number2[p31_12];
		factdis.P31[13] = dash_number2[p31_13];
		factdis.P31[14] = dash_number2[p31_14];
		
		
		factdis.P32[0]  = dash_number3[p32_0];
		factdis.P32[1]  = dash_number3[p32_1];
		factdis.P32[2]  = dash_number3[p32_2];
		factdis.P32[3]  = dash_number3[p32_3];
		factdis.P32[4]  = dash_number3[p32_4];
		factdis.P32[5]  = dash_number3[p32_5];
		factdis.P32[6]  = dash_number3[p32_6];
		factdis.P32[7]  = dash_number3[p32_7];
		factdis.P32[8]  = dash_number3[p32_8];
		factdis.P32[9]  = dash_number3[p32_9];
		factdis.P32[10] = dash_number3[p32_10];
		factdis.P32[11] = dash_number3[p32_11];
		factdis.P32[12] = dash_number3[p32_12];
		factdis.P32[13] = dash_number3[p32_13];
		factdis.P32[14] = dash_number3[p32_14];
	}
	return 0;
}

void MenuSelectShow(void)
{
	char str1[48] = {0};
	char str2[48] = {0};
	char str3[48] = {0};
	char str4[48] = {0};
	//选择进入用户还是工厂
	if(stm32_config.Menu_Tier == 4){
		//MenuInit();
		switch(stm32_config.Selected){
			case 0:
				sprintf(str1,"PA1 : user  password  →");
				sprintf(str2,"PA2 : admin password    ");
				sprintf(str3,"Press ↑↓ to select");
				sprintf(str4,"Enter               Exit");
				Password = 0;
				break;
			case 1:
				sprintf(str1,"PA1 : user  password    ");
				sprintf(str2,"PA2 : admin password  →");
				sprintf(str3,"Press ↑↓ to select");
				sprintf(str4,"Enter               Exit");
				Password = 1;
				break;
			default:
				break;
		}
		//display_smg(str3);
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
		HAL_Delay(500);
		return;
	}
	else if(stm32_config.Menu_Tier == 5){
		sprintf(str1,"Enter Password    ");
		if(Password == 0){
			//Usart3_Printf("卧槽了  %d\r\n",PA1);
			sprintf(str2,"%d     ",PA1);
			sprintf(str3,"Press Up/Down to change");
			sprintf(str4,"Enter  Up    Down   Exit");
			Lcm_GotoXY(0,0,1);
			Lcm_Disp_String((unsigned char *)str1);
			Lcm_GotoXY(0,1,1);
			Lcm_Disp_String((unsigned char *)str2);
			Lcm_GotoXY(0,0,0);
			Lcm_Disp_String((unsigned char *)str3);
			Lcm_GotoXY(0,1,0);
			Lcm_Disp_String((unsigned char *)str4);
		}
		else if(Password == 1){
			//Usart3_Printf("你好菜啊   %d\r\n",PA2);
			sprintf(str2,"%d     ",PA2);
			sprintf(str3,"Press Up/Down to change");
			sprintf(str4,"Enter  Up    Down   Exit");
			Lcm_GotoXY(0,0,1);
			Lcm_Disp_String((unsigned char *)str1);
			Lcm_GotoXY(0,1,1);
			Lcm_Disp_String((unsigned char *)str2);
			Lcm_GotoXY(0,0,0);
			Lcm_Disp_String((unsigned char *)str3);
			Lcm_GotoXY(0,1,0);
			Lcm_Disp_String((unsigned char *)str4);
		}
	}
	else if(stm32_config.Menu_Tier == 1 && CUST_FACT == 0){
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
			switch(stm32_config.CUSTSelected){
				case DSP:
					sprintf(str1,"DSP  :   Dispense     →");
					sprintf(str2,"VS   :   Statistics     ");
					sprintf(str3,"CP   :   Compressor     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					//分配参数菜单层
					custdsp.Line = 1;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case VS:
					sprintf(str1,"DSP  :   Dispense       ");
					sprintf(str2,"VS   :   Statistics   →");
					sprintf(str3,"CP   :   Compressor     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					//统计菜单层
					custdsp.Line = 0;
					custvs.Line  = 1;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case CP:
					sprintf(str1,"DSP  :   Dispense       ");
					sprintf(str2,"VS   :   Statistics     ");
					sprintf(str3,"CP   :   Compressor   →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					//压缩机菜单层
					custdsp.Line = 0;
					custvs.Line  = 0;
					custcp.Line  = 1;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case dis:
					sprintf(str1,"dis   :  Display      →");
					sprintf(str2,"dEF   :  Defrost        ");
					sprintf(str3,"FAn   :  Fan            ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					//显示菜单层
					custdsp.Line = 0;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 1;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case dEF:
					sprintf(str1,"dis   :  Display        ");
					sprintf(str2,"dEF   :  Defrost      →");
					sprintf(str3,"FAn   :  Fan            ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					//化霜菜单层
					custdsp.Line = 0;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 1;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case FAn:
					sprintf(str1,"dis   :  Display        ");
					sprintf(str2,"dEF   :  Defrost        ");
					sprintf(str3,"FAn   :  Fan          →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					//风扇菜单层
					custdsp.Line = 0;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 1;
					custal.Line  = 0;
					break;
				case AL:
					sprintf(str1,"AL    :   Alarm       →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					//报警菜单层
					custdsp.Line = 0;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 1;
					break;
				default:
					break;
			}
		}
		else{
			switch(stm32_config.CUSTSelected){
				case DSP:
					sprintf(str1,"DSP   :   Dispense    →");
					sprintf(str2,"VS    :   Statistics    ");
					sprintf(str3,"dis   :   Display       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					//分配参数菜单层
					custdsp.Line = 1;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case VS:
					sprintf(str1,"DSP   :   Dispense      ");
					sprintf(str2,"VS    :   Statistics  →");
					sprintf(str3,"dis   :   Display       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					//统计菜单层
					custdsp.Line = 0;
					custvs.Line  = 1;
					custcp.Line  = 0;
					custdis.Line = 0;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				case CP:
					sprintf(str1,"DSP   :   Dispense      ");
					sprintf(str2,"VS    :   Statistics    ");
					sprintf(str3,"dis   :   Display     →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					//压缩机菜单层
					custdsp.Line = 0;
					custvs.Line  = 0;
					custcp.Line  = 0;
					custdis.Line = 1;
					custdef.Line = 0;
					custfan.Line = 0;
					custal.Line  = 0;
					break;
				default:
					break;
			}
		}
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
		factcp.Line = 0;
		factdis.Line = 0;
		factdef.Line = 0;
		factfan.Line = 0;
		factal.Line = 0;
		factdsp.Line = 0;
	}
	else if(stm32_config.Menu_Tier == 2 && CUST_FACT == 0){
		if(custdsp.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"RE    :  Restore      →");
					sprintf(str2,"P02_P :  PreLoad        ");
					sprintf(str3,"P02_C :  Large Load     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"RE    :  Restore        ");
					sprintf(str2,"P02_P :  PreLoad      →");
					sprintf(str3,"P02_C :  Large Load     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"RE    :  Restore        ");
					sprintf(str2,"P02_P :  PreLoad        ");
					sprintf(str3,"P02_C :  Large Load   →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"DT    :  Drum Motor   →");
					sprintf(str2,"RT    :  Door Motor     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"DT    :  Drum Motor     ");
					sprintf(str2,"RT    :  Door Motor   →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				default:
					break;
			}
		}
		if(custvs.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"DC   : Dispense  cycle→");
					sprintf(str2,"CC   : Calibrate cycle  ");
					sprintf(str3,"SC   : Dispense  small  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"DC   : Dispense  cycle  ");
					sprintf(str2,"CC   : Calibrate cycle→");
					sprintf(str3,"SC   : Dispense  small  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"DC   : Dispense  cycle  ");
					sprintf(str2,"CC   : Calibrate cycle  ");
					sprintf(str3,"SC   : Dispense  small→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"MC   : Dispense  mid  →");
					sprintf(str2,"LC   : Dispense  large  ");
					sprintf(str3,"DrTQ : Drum    over     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"MC   : Dispense  mid    ");
					sprintf(str2,"LC   : Dispense  large→");
					sprintf(str3,"DrTQ : Drum    over     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				case 5:
					sprintf(str1,"MC   : Dispense  mid    ");
					sprintf(str2,"LC   : Dispense  large  ");
					sprintf(str3,"DrTQ : Drum    over   →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 5;
					break;
				case 6:
					sprintf(str1,"DTQ :  Door    over   →");
					sprintf(str2,"FTO :  Fill  time-outs  ");
					sprintf(str3,"DTO :  Door  time-outs  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 6;
					break;
				case 7:
					sprintf(str1,"DTQ :  Door    over     ");
					sprintf(str2,"FTO :  Fill  time-outs→");
					sprintf(str3,"DTO :  Door  time-outs  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 7;
					break;
				case 8:
					sprintf(str1,"DTQ :  Door    over     ");
					sprintf(str2,"FTO :  Fill  time-outs  ");
					sprintf(str3,"DTO :  Door  time-outs→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 8;
					break;
				case 9:
					sprintf(str1,"CL : Calibrate large  →");
					sprintf(str2,"CP : Calibrate preload  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 9;
					break;
				case 10:
					sprintf(str1,"CL : Calibrate large    ");
					sprintf(str2,"CP : Calibrate preload→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 10;
					break;
				default:
					break;
			}
		}
		if(custcp.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"St  :  Temp Set       →");
					sprintf(str2,"Hy  :  Differeential    ");
					sprintf(str3,"ot  :  Calibrate prb1   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"St  :  Temp Set         ");
					sprintf(str2,"Hy  :  Differeential  →");
					sprintf(str3,"ot  :  Calibrate prb1   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"St  :  Temp Set         ");
					sprintf(str2,"Hy  :  Differeential    ");
					sprintf(str3,"ot  :  Calibrate prb1 →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"P2  :  Evpa.Probe2    →");
					sprintf(str2,"AC  :  Frequent comp    ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"P2  :  Evpa.Probe2      ");
					sprintf(str2,"AC  :  Frequent comp  →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				default:
					break;
			}
		}
		if(custdis.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"CF  :  Temp Unit      →");
					sprintf(str2,"rE  :  Decimal point    ");
					sprintf(str3,"d1  :  Room Temp        ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"CF  :  Temp Unit        ");
					sprintf(str2,"rE  :  Decimal point  →");
					sprintf(str3,"d1  :  Room Temp        ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"CF  :  Temp Unit        ");
					sprintf(str2,"rE  :  Decimal point    ");
					sprintf(str3,"d1  :  Room Temp      →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"d2  :  Evap Temp      →");
					sprintf(str2,"P01 :  Language         ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"d2  :  Evap Temp        ");
					sprintf(str2,"P01 :  Language       →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				default:
					break;
			}
		}
		if(custdef.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"dE : Def end temp     →");
					sprintf(str2,"id : Def cycles time    ");
					sprintf(str3,"Md : Def max time       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"dE : Def end temp       ");
					sprintf(str2,"id : Def cycles time  →");
					sprintf(str3,"Md : Def max time       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"dE : Def end temp       ");
					sprintf(str2,"id : Def cycles time    ");
					sprintf(str3,"Md : Def max time     →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				default:
					break;
			}
		}
		if(custfan.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"Fd : Delay after def  →");
					sprintf(str2,"Fn : Fans ON time       ");
					sprintf(str3,"FF : Fans Off time      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"Fd : Delay after def    ");
					sprintf(str2,"Fn : Fans ON time     →");
					sprintf(str3,"FF : Fans Off time      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"Fd : Delay after def    ");
					sprintf(str2,"Fn : Fans ON time       ");
					sprintf(str3,"FF : Fans Off time    →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				default:
					break;
			}
		}
		if(custal.Line == 1){
			switch(stm32_config.CUSTSelected2){
				case 0:
					sprintf(str1,"AU  :  Max temp alarm →");
					sprintf(str2,"AL  :  Min temp alarm   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"AU  :  Max temp alarm   ");
					sprintf(str2,"AL  :  Min temp alarm →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				default:
					break;
			}
		}
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
	}
	else if(stm32_config.Menu_Tier == 3 && CUST_FACT == 0){
		sprintf(str2,"");
		//sprintf(str3,"Save and Exit");
		sprintf(str3,"Press up/down to change");
		sprintf(str4,"Save    Up    Down  Exit");
		if(custdsp.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"Reset All Parameter");
					sprintf(str3,"Press L to continue");
					sprintf(str4,"");
					break;
				case 1:
					sprintf(str1," %d    ",custdsp.P02_P);
					if(Downjiaozhun == 3 || Downjiaozhun == 4){
						sprintf(str2,"Waitting...              ");
						sprintf(str3,"                        ");
						sprintf(str4,"                        ");
					}
					else if(Downjiaozhun == 0){
						sprintf(str2,"Pre-Load   Successful   ");
						sprintf(str3,"Exit and choose P02_C   ");
						sprintf(str4,"Save                Exit");
					}
					jiaozhunkey = 1;
					break;
				case 2:
					sprintf(str1," %d    ",custdsp.P02_C);
					sprintf(str2,"Large Load Successful   ");
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					jiaozhunkey = 2;
					break;
				case 3:
					sprintf(str1,"T  %d      ",AdcBuf[3]);
					sprintf(str2,"P  %d      ",test);
					sprintf(str3,"Drum Motor Test");
					sprintf(str4,"Press L to Run Motor");
					break;
				case 4:
					sprintf(str1,"T  %d      ",AdcBuf[2]);
					sprintf(str2,"P  %d      ",test);
					sprintf(str3,"Door Motor Test");
					sprintf(str4,"Press L to Run Motor");
					break;
				default:
					break;
			}
		}
		if(custvs.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",custvs.DC);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 1:
					sprintf(str1,"%d",custvs.CC);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 2:
					sprintf(str1,"%d",custvs.SC);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 3:
					sprintf(str1,"%d",custvs.MC);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 4:
					sprintf(str1,"%d",custvs.LC);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 5:
					sprintf(str1,"%d",custvs.DrTQ);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 6:
					sprintf(str1,"%d",custvs.DTQ);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 7:
					sprintf(str1,"%d",custvs.FTO);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 8:
					sprintf(str1,"%d",custvs.DTO);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 9:
					sprintf(str1,"%d",custvs.CL);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 10:
					sprintf(str1,"%d",custvs.CP);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				default:
					break;
			}
		}
		if(custcp.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",custcp.St);
					break;
				case 1:
					sprintf(str1,"%.1f",custcp.Hy);
					break;
				case 2:
					sprintf(str1,"%.1f",custcp.ot);
					break;
				case 3:
					replace = custcp.p2;
				//Usart3_Printf("p2:%d replace:%d\r\n",custcp.p2,replace);
					if(replace)
							sprintf(str1,"y");
					else
							sprintf(str1,"n");
					break;
				case 4:
					sprintf(str1,"%d",custcp.AC);
					break;
				default:
					break;
			}
//			if(line == 3)
//				return;
		}
		if(custdis.Line == 1){
			switch(line){
				case 0:
					replace = custdis.CF;
					if(replace)
							sprintf(str1,"°F");
					else
							sprintf(str1,"°C");
					break;
				case 1:
					replace = custdis.rE;
					if(replace)
							sprintf(str1,"in");
					else
							sprintf(str1,"dE");
					break;
				case 2:
					if(custdis.CF == 1)
						sprintf(str1,"%d F",Case_T_HSD);
					else
						sprintf(str1,"%.1f C",Case_T);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 3:
					if(custdis.CF == 1)
						sprintf(str1,"%d F",Vapor_T_HSD);
					else
						sprintf(str1,"%.1f C",Vapor_T);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 4:
					sprintf(str1,"English");
					break;
				default:
					break;
			}
//			if(line == 0 || line == 1)
//				return;
		}
		if(custdef.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",custdef.dE);
					break;
				case 1:
					sprintf(str1,"%d",custdef.id);
					break;
				case 2:
					sprintf(str1,"%d",custdef.Md);
					break;
				default:
					break;
			}
		}
		if(custfan.Line == 1){
			switch(line){
//				case 0:
//					sprintf(str1,"%d",custfan.F1);
//					break;
//				case 1:
//					sprintf(str1,"%d",custfan.F2);
//					break;
				case 0:
					sprintf(str1,"%d",custfan.Fd);
					break;
				case 1:
					sprintf(str1,"%d",custfan.Fn);
					break;
				case 2:
					sprintf(str1,"%d",custfan.FF);
					break;
				default:
					break;
			}
		}
		if(custal.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",custal.AU);
					break;
				case 1:
					sprintf(str1,"%d",custal.AL);
					break;
				default:
					break;
			}
		}
		
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //显示清屏
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
	}

	else if(stm32_config.Menu_Tier == 1 && CUST_FACT == 1){
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
			switch(stm32_config.FACTSelected){
				case DSP:
					sprintf(str1,"CP   :   Compressor   →");
					sprintf(str2,"dis  :   Display        ");
					sprintf(str3,"dEF  :   Defrost        ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					factcp.Line = 1;
					factdis.Line = 0;
					factdef.Line = 0;
					factfan.Line = 0;
					factal.Line = 0;
					factdsp.Line = 0;
					factfpr.Line = 0;
					break;
				case VS:
					sprintf(str1,"CP   :   Compressor     ");
					sprintf(str2,"dis  :   Display      →");
					sprintf(str3,"dEF  :   Defrost        ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					factcp.Line = 0;
					factdis.Line = 1;
					factdef.Line = 0;
					factfan.Line = 0;
					factal.Line = 0;
					factdsp.Line = 0;
					factfpr.Line = 0;
					break;
				case CP:
					sprintf(str1,"CP   :   Compressor     ");
					sprintf(str2,"dis  :   Display        ");
					sprintf(str3,"dEF  :   Defrost      →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					factcp.Line = 0;
					factdis.Line = 0;
					factdef.Line = 1;
					factfan.Line = 0;
					factal.Line = 0;
					factdsp.Line = 0;
					factfpr.Line = 0;
					break;
				case dis:
					sprintf(str1,"FAn  :   Fan          →");
					sprintf(str2,"AL   :   Alarm          ");
					sprintf(str3,"DSP  :   Dispense       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					factcp.Line = 0;
					factdis.Line = 0;
					factdef.Line = 0;
					factfan.Line = 1;
					factal.Line = 0;
					factdsp.Line = 0;
					factfpr.Line = 0;
					break;
				case dEF:
					sprintf(str1,"FAn  :   Fan            ");
					sprintf(str2,"AL   :   Alarm        →");
					sprintf(str3,"DSP  :   Dispense       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					factcp.Line = 0;
					factdis.Line = 0;
					factdef.Line = 0;
					factfan.Line = 0;
					factal.Line = 1;
					factdsp.Line = 0;
					factfpr.Line = 0;
					break;
				case FAn:
					sprintf(str1,"FAn  :   Fan            ");
					sprintf(str2,"AL   :   Alarm          ");
					sprintf(str3,"DSP  :   Dispense     →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					factcp.Line = 0;
					factdis.Line = 0;
					factdef.Line = 0;
					factfan.Line = 0;
					factal.Line = 0;
					factdsp.Line = 1;
					factfpr.Line = 0;
					break;
				case AL:
					sprintf(str1,"FPr  :   Format       →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					factcp.Line = 0;
					factdis.Line = 0;
					factdef.Line = 0;
					factfan.Line = 0;
					factal.Line = 0;
					factdsp.Line = 0;
					factfpr.Line = 1;
					break;
				default:
					break;
			}
		}
		else{
			switch(stm32_config.FACTSelected){
				case DSP:
						sprintf(str1,"dis  :   Display      →");
						sprintf(str2,"DSP  :   Dispense       ");
						sprintf(str4,"Set     Up    Down  Exit");
						line = 1;
						factcp.Line = 0;
						factdis.Line = 1;
						factdef.Line = 0;
						factfan.Line = 0;
						factal.Line = 0;
						factdsp.Line = 0;
						factfpr.Line = 0;
						break;
					case VS:
						sprintf(str1,"dis  :   Display        ");
						sprintf(str2,"DSP  :   Dispense     →");
						sprintf(str4,"Set     Up    Down  Exit");
						line = 2;
						factcp.Line = 0;
						factdis.Line = 0;
						factdef.Line = 0;
						factfan.Line = 0;
						factal.Line = 0;
						factdsp.Line = 1;
						factfpr.Line = 0;
						break;
					default:
						break;
				}
		}
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
		custdsp.Line = 0;
		custvs.Line = 0;
		custcp.Line = 0;
		custdis.Line = 0;
		custdef.Line = 0;
		custfan.Line = 0;
		custal.Line = 0;
	}
	else if(stm32_config.Menu_Tier == 2 && CUST_FACT == 1){
		if(factcp.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"St  :  Temp Set       →");
					sprintf(str2,"Hy  :  Differeential    ");
					sprintf(str3,"LS  :  Min Temp Set     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"St  :  Temp Set         ");
					sprintf(str2,"Hy  :  Differeential  →");
					sprintf(str3,"LS  :  Min Temp Set     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"St  :  Temp Set         ");
					sprintf(str2,"Hy  :  Differeential    ");
					sprintf(str3,"LS  :  Min Temp Set   →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"US  :  Max Temp Set   →");
					sprintf(str2,"ot  :  Calibrate prb1   ");
					sprintf(str3,"P2  :  Evpa.Probe2      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"US  :  Max Temp Set     ");
					sprintf(str2,"ot  :  Calibrate prb1 →");
					sprintf(str3,"P2  :  Evpa.Probe2      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				case 5:
					sprintf(str1,"US  :  Max Temp Set     ");
					sprintf(str2,"ot  :  Calibrate prb1   ");
					sprintf(str3,"P2  :  Evpa.Probe2    →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 5;
					break;
				case 6:
					sprintf(str1,"oE  : Calibrate probe2→");
					sprintf(str2,"od  : Com relay         ");
					sprintf(str3,"AC  : Frequent comp     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 6;
					break;
				case 7:
					sprintf(str1,"oE  : Calibrate probe2  ");
					sprintf(str2,"od  : Com relay       →");
					sprintf(str3,"AC  : Frequent comp     ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 7;
					break;
				case 8:
					sprintf(str1,"oE  : Calibrate probe2  ");
					sprintf(str2,"od  : Com relay         ");
					sprintf(str3,"AC  : Frequent comp   →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 8;
					break;
				case 9:
					sprintf(str1,"Cy  : Probe fail run  →");
					sprintf(str2,"Cn  : Probe fail off    ");
					sprintf(str3,"dAd : Delay output off  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 9;
					break;
				case 10:
					sprintf(str1,"Cy  : Probe fail run    ");
					sprintf(str2,"Cn  : Probe fail off  →");
					sprintf(str3,"dAd : Delay output off  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 10;
					break;
				case 11:
					sprintf(str1,"Cy  : Probe fail run    ");
					sprintf(str2,"Cn  : Probe fail off    ");
					sprintf(str3,"dAd : Delay output off→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 11;
					break;
				default :
						break;
			}
		}
		if(factdis.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"PA1  : User password  →");
					sprintf(str2,"PA2  : Admin password   ");
					sprintf(str3,"CF   : Temp Unit        ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"PA1  : User password    ");
					sprintf(str2,"PA2  : Admin password →");
					sprintf(str3,"CF   : Temp Unit        ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"PA1  : User password    ");
					sprintf(str2,"PA2  : Admin password   ");
					sprintf(str3,"CF   : Temp Unit      →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"rE  :  Decimal point  →");
					sprintf(str2,"Ld  :  Default panel    ");
					sprintf(str3,"dy  :  Display delay    ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"rE  :  Decimal point    ");
					sprintf(str2,"Ld  :  Default panel  →");
					sprintf(str3,"dy  :  Display delay    ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				case 5:
					sprintf(str1,"rE  :  Decimal point    ");
					sprintf(str2,"Ld  :  Default panel    ");
					sprintf(str3,"dy  :  Display delay  →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 5;
					break;
				case 6:
					sprintf(str1,"d1  :  Room Temp      →");
					sprintf(str2,"d2  :  Evap Temp        ");
					sprintf(str3,"P01 :  Language         ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 6;
					break;
				case 7:
					sprintf(str1,"d1  :  Room Temp        ");
					sprintf(str2,"d2  :  Evap Temp      →");
					sprintf(str3,"P01 :  Language         ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 7;
					break;
				case 8:
					sprintf(str1,"d1  :  Room Temp        ");
					sprintf(str2,"d2  :  Evap Temp        ");
					sprintf(str3,"P01 :  Language       →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 8;
					break;
				case 9:
					sprintf(str1,"P31 :  Part Numebrt   →");
					sprintf(str2,"P32 :  Serial Numebrt   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 9;
					break;
				case 10:
					sprintf(str1,"P31 :  Part Numebrt     ");
					sprintf(str2,"P32 :  Serial Numebrt →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 10;
					break;
				default :
						break;
			}
		}
		if(factdef.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"td  :  Drfrost type   →");
					sprintf(str2,"dE  :  Def end temp     ");
					sprintf(str3,"id  :  Def cycles time  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"td  :  Drfrost type     ");
					sprintf(str2,"dE  :  Def end temp   →");
					sprintf(str3,"id  :  Def cycles time  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"td  :  Drfrost type     ");
					sprintf(str2,"dE  :  Def end temp     ");
					sprintf(str3,"id  :  Def cycles time→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"Md  :  Def max time   →");
					sprintf(str2,"dd  :  Def start delay  ");
					sprintf(str3,"dF  :  Temp dis in def  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"Md  :  Def max time     ");
					sprintf(str2,"dd  :  Def start delay→");
					sprintf(str3,"dF  :  Temp dis in def  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				case 5:
					sprintf(str1,"Md  :  Def max time     ");
					sprintf(str2,"dd  :  Def start delay  ");
					sprintf(str3,"dF  :  Temp dis in def→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 5;
					break;
				case 6:
					sprintf(str1,"dt  :  Dripping time  →");
					sprintf(str2,"dP  :  Def allowed      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 6;
					break;
				case 7:
					sprintf(str1,"dt  :  Dripping time    ");
					sprintf(str2,"dP  :  Def allowed    →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 7;
					break;
				default :
						break;
			}
		}
		if(factfan.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"Fd : Delay after def  →");
					sprintf(str2,"FS : Fan Stop Temp      ");
					sprintf(str3,"FAd: Fan Stop diff      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"Fd : Delay after def    ");
					sprintf(str2,"FS : Fan Stop Temp    →");
					sprintf(str3,"FAd  Fan Stop diff      ");
					line = 1;
					break;
				case 2:
					sprintf(str1,"Fd : Delay after def    ");
					sprintf(str2,"FS : Fan Stop Temp      ");
					sprintf(str3,"FAd: Fan Stop diff    →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"Fn : Fans ON time     →");
					sprintf(str2,"FF : Fans Off time      ");
					sprintf(str3,"dAd: Delay output off   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"Fn : Fans ON time       ");
					sprintf(str2,"FF : Fans Off time    →");
					sprintf(str3,"dAd: Delay output off   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				case 5:
					sprintf(str1,"Fn : Fans ON time       ");
					sprintf(str2,"FF : Fans Off time      ");
					sprintf(str3,"dAd: Delay output off →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 5;
					break;
				default :
						break;
			}
		}
		if(factal.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"AU  :  Max temp alarm →");
					sprintf(str2,"AL  :  Min temp alarm   ");
					sprintf(str3,"Ad  :  Temp AL delay    ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"AU  :  Max temp alarm   ");
					sprintf(str2,"AL  :  Min temp alarm →");
					sprintf(str3,"Ad  :  Temp AL delay    ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"AU  :  Max temp alarm   ");
					sprintf(str2,"AL  :  Min temp alarm   ");
					sprintf(str3,"Ad  :  Temp AL delay  →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"dA : AL delay Power on→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				default :
						break;
			}
		}
		if(factdsp.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"P10 :  Down Shift LM  →");
					sprintf(str2,"P11 :  Down Shift MS    ");
					sprintf(str3,"P13 :  Drum Torq Thres  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"P10 :  Down Shift LM    ");
					sprintf(str2,"P11 :  Down Shift MS  →");
					sprintf(str3,"P13 :  Drum Torq Thres  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				case 2:
					sprintf(str1,"P10 :  Down Shift LM    ");
					sprintf(str2,"P11 :  Down Shift MS    ");
					sprintf(str3,"P13 :  Drum Torq Thres→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 2;
					break;
				case 3:
					sprintf(str1,"P14 :  Door Torq Thres→");
					sprintf(str2,"P15 :  Lift Torq Thres  ");
					sprintf(str3,"P16 :  Basket In Time   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 3;
					break;
				case 4:
					sprintf(str1,"P14 :  Door Torq Thres  ");
					sprintf(str2,"P15 :  Lift Torq Thres→");
					sprintf(str3,"P16 :  Basket In Time   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 4;
					break;
				case 5:
					sprintf(str1,"P14 :  Door Torq Thres  ");
					sprintf(str2,"P15 :  Lift Torq Thres  ");
					sprintf(str3,"P16 :  Basket In Time →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 5;
					break;
				case 6:
					sprintf(str1,"P17 :  Basket Out Time→");
					sprintf(str2,"P18 :  Low Product      ");
					sprintf(str3,"P19 :  Hi Accuracy      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 6;
					break;
				case 7:
					sprintf(str1,"P17 :  Basket Out Time  ");
					sprintf(str2,"P18 :  Low Product    →");
					sprintf(str3,"P19 :  Hi Accuracy      ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 7;
					break;
				case 8:
					sprintf(str1,"P17 :  Basket Out Time  ");
					sprintf(str2,"P18 :  Low Product      ");
					sprintf(str3,"P19 :  Hi Accuracy    →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 8;
					break;
				case 9:
					sprintf(str1,"P21 :  Large Fill Pct →");
					sprintf(str2,"P22 :  Mid   Fill Pct   ");
					sprintf(str3,"P23 :  Small Fill Pct   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 9;
					break;
				case 10:
					sprintf(str1,"P21 :  Large Fill Pct   ");
					sprintf(str2,"P22 :  Mid   Fill Pct →");
					sprintf(str3,"P23 :  Small Fill Pct   ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 10;
					break;
				case 11:
					sprintf(str1,"P21 :  Large Fill Pct   ");
					sprintf(str2,"P22 :  Mid   Fill Pct   ");
					sprintf(str3,"P23 :  Small Fill Pct →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 11;
					break;
				case 12:
					sprintf(str1,"P26 :  Dual Lang  Rate→");
					sprintf(str2,"P28 :  Backdoor Type    ");
					sprintf(str3,"P29 :  Mid Factor       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 12;
					break;
				case 13:
					sprintf(str1,"P26 :  Dual Lang  Rate  ");
					sprintf(str2,"P28 :  Backdoor Type  →");
					sprintf(str3,"P29 :  Mid Factor       ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 13;
					break;
				case 14:
					sprintf(str1,"P26 :  Dual Lang  Rate  ");
					sprintf(str2,"P28 :  Backdoor Type    ");
					sprintf(str3,"P29 :  Mid Factor     →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 14;
					break;
				case 15:
					sprintf(str1,"P30  :Small Factor    →");
					sprintf(str2,"Run  :Inching Run Time  ");
					sprintf(str3,"Stop :Inching StopTime  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 15;
					break;
				case 16:
					sprintf(str1,"P30  :Small Factor      ");
					sprintf(str2,"Run  :Inching Run Time→");
					sprintf(str3,"Stop :Inching StopTime  ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 16;
					break;
				case 17:
					sprintf(str1,"P30  :Small Factor      ");
					sprintf(str2,"Run  :Inching Run Time  ");
					sprintf(str3,"Stop :Inching StopTime→");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 17;
					break;
				case 18:
					sprintf(str1,"T1   :Positive  Time  →");
					sprintf(str2,"T2   :Reversing Time    ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 18;
					break;
				case 19:
					sprintf(str1,"T1   :Positive  Time    ");
					sprintf(str2,"T2   :Reversing Time  →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 19;
					break;
				default :
						break;
			}
		}
		if(factfpr.Line == 1){
			switch(stm32_config.FACTSelected2){
				case 0:
					sprintf(str1,"UL  :  Up Load        →");
					sprintf(str2,"Fr  :  Format           ");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 0;
					break;
				case 1:
					sprintf(str1,"UL  :  Up Load          ");
					sprintf(str2,"Fr  :  Format         →");
					sprintf(str4,"Set     Up    Down  Exit");
					line = 1;
					break;
				default :
						break;
			}
		}
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
	}
	else if(stm32_config.Menu_Tier == 3 && CUST_FACT == 1){
		sprintf(str2,"");
		//sprintf(str3,"Save and Exit");
		sprintf(str3,"Press up/down to change");
		sprintf(str4,"Save    Up    Down  Exit");
		if(factcp.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",factcp.St);
					break;
				case 1:
					sprintf(str1,"%.1f",factcp.Hy);
					break;
				case 2:
					sprintf(str1,"%d",factcp.LS);
					break;
				case 3:
					sprintf(str1,"%d",factcp.US);
					break;
				case 4:
					sprintf(str1,"%.1f",factcp.ot);
					break;
				case 5:
					replace = factcp.P2;
					if(replace)
							sprintf(str1,"y");
					else
							sprintf(str1,"n");
					break;
				case 6:
					sprintf(str1,"%.1f",factcp.oE);
					break;
				case 7:
					sprintf(str1,"%d",factcp.od);
					break;
				case 8:
					sprintf(str1,"%d",factcp.AC);
					break;
				case 9:
					sprintf(str1,"%d",factcp.Cy);
					break;
				case 10:
					sprintf(str1,"%d",factcp.Cn);
					break;
				case 11:
					sprintf(str1,"%d",factcp.dAd);
					break;
				default :
						break;
			}
//			if(line == 5)
//				return;
		}
		if(factdis.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",factdis.PA1);
					break;
				case 1:
					sprintf(str1,"%d",factdis.PA2);
					break;
				case 2:
					replace = factdis.CF;
					if(replace)
							sprintf(str1,"°F");
					else
							sprintf(str1,"°C");
					break;
				case 3:
					replace = factdis.rE;
					if(replace)
							sprintf(str1,"in");
					else
							sprintf(str1,"dE");
					break;
				case 4:
					replace = factdis.Ld;
					if(replace)
							sprintf(str1,"P2");
					else
							sprintf(str1,"P1");
					break;
				case 5:
					sprintf(str1,"%d",factdis.dy);
					break;
				case 6:
					if(custdis.CF == 1)
						sprintf(str1,"%d F",Case_T_HSD);
					else
						sprintf(str1,"%.1f C",Case_T);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 7:
					if(custdis.CF == 1)
						sprintf(str1,"%d F",Vapor_T_HSD);
					else
						sprintf(str1,"%.1f C",Vapor_T);
					sprintf(str3,"                        ");
					sprintf(str4,"Save                Exit");
					break;
				case 8:
					if(factdis.P01 == 1)
						sprintf(str1,"English       ");
					else if(factdis.P01 == 2)
						sprintf(str1,"Germen        ");
					else if(factdis.P01 == 3)
						sprintf(str1,"Spain         ");
					else if(factdis.P01 == 4)
						sprintf(str1,"French        ");
					else if(factdis.P01 == 5)
						sprintf(str1,"French/English");
					break;
				case 9:
					sprintf(str1,"%s",factdis.P31);
					break;
				case 10:
					sprintf(str1,"%s",factdis.P32);
					break;
				default :
						break;
			}
//			if(line == 2 || line == 3 || line == 4)
//				return;
		}
		if(factdef.Line == 1){
			switch(line){
				case 0:
					replace = factdef.td;
					if(replace == 0)
							sprintf(str1,"EL");
					else if(replace == 1)
							sprintf(str1,"in");
					else
							sprintf(str1,"Ar");
					break;
				case 1:
					sprintf(str1,"%d",factdef.dE);
					break;
				case 2:
					sprintf(str1,"%d",factdef.id);
					break;
				case 3:
					sprintf(str1,"%d",factdef.Md);
					break;
				case 4:
					sprintf(str1,"%d",factdef.dd);
					break;
				case 5:
					replace = factdef.dF;
					if(replace == 0)
							sprintf(str1,"rt");
					else if(replace == 1)
							sprintf(str1,"it");
					else if(replace == 2)
							sprintf(str1,"SP");
					else if(replace == 3)
							sprintf(str1,"dE");
					break;
				case 6:
					sprintf(str1,"%d",factdef.dt);
					break;
				case 7:
					replace = factdef.dP;
					if(replace)
						sprintf(str1,"n");
					else
						sprintf(str1,"y");
					break;
			}
//			if(line == 0 || line == 5 || line == 7)
//				return;
		}
		if(factfan.Line == 1){
			switch(line){
//				case 0:
//					sprintf(str1,"%d",factfan.F1);
//					replace = factfan.F1;
//					break;
//				case 1:
//					sprintf(str1,"%d",factfan.F2);
//					break;
				case 0:
					sprintf(str1,"%d",factfan.Fd);
					break;
				case 1:
					sprintf(str1,"%d",factfan.FS);
					break;
				case 2:
					sprintf(str1,"%d",factfan.FAd);
					break;
				case 3:
					sprintf(str1,"%d",factfan.Fn);
					break;
				case 4:
					sprintf(str1,"%d",factfan.FF);
					break;
				case 5:
					sprintf(str1,"%d",factfan.dAd);
					break;
				default :
						break;
			}
		}
		if(factal.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"%d",factal.AU);
					break;
				case 1:
					sprintf(str1,"%d",factal.AL);
					break;
				case 2:
					sprintf(str1,"%d",factal.Ad);
					break;
				case 3:
					sprintf(str1,"%d",factal.dA);
					break;
				default :
						break;
			}
		}
		if(factdsp.Line == 1){
			switch(line){
				case 0:
					replace = factdsp.P10;
					if(replace == 20)
						sprintf(str1,"OFF");
					else
						sprintf(str1,"%d",factdsp.P10);
					break;
				case 1:
					replace = factdsp.P11;
					if(replace == 20)
							sprintf(str1,"OFF");
					else
						sprintf(str1,"%d",factdsp.P11);
					break;
				case 2: 
					sprintf(str1,"%d",factdsp.P13);
					break;
				case 3:
					sprintf(str1,"%d",factdsp.P14);
					break;
				case 4:
					sprintf(str1,"%d",factdsp.P15);
					break;
				case 5:
					sprintf(str1,"%d",factdsp.P16);
					break;
				case 6:
					sprintf(str1,"%d",factdsp.P17);
					break;
				case 7:
					replace = factdsp.P18;
					if(replace)
						sprintf(str1,"ON");
					else
						sprintf(str1,"OFF");
					break;
				case 8:
					replace = factdsp.P19;
					if(replace)
						sprintf(str1,"ON");
					else
						sprintf(str1,"OFF");
					break;
				case 9:
					sprintf(str1,"%d",factdsp.P21);
					break;
				case 10:
					sprintf(str1,"%d",factdsp.P22);
					break;
				case 11:
					sprintf(str1,"%d",factdsp.P23);
					break;
				case 12:
					if(factdsp.P26 == 1)
						sprintf(str1,"Close   ");
					else if(factdsp.P26 == 2)
						sprintf(str1,"Slow    ");
					else if(factdsp.P26 == 3)
						sprintf(str1,"Mid     ");
					else if(factdsp.P26 == 4)
						sprintf(str1,"Fast    ");
					break;
				case 13:
					if(factdsp.P28 == 0)
						sprintf(str1,"English    ");
					else if(factdsp.P28)
						sprintf(str1,"Numeric    ");
					break;
				case 14:
					sprintf(str1,"%d",factdsp.P29);
					break;
				case 15:
					sprintf(str1,"%d",factdsp.P30);
					break;
				case 16:
					sprintf(str1,"%d  ms",delaytt);
					break;
				case 17:
					sprintf(str1,"%d  ms",delaytt1);
					break;
				case 18:
					sprintf(str1,"%d  s",factdsp.T1);
					break;
				case 19:
					sprintf(str1,"%d  s",factdsp.T2);
					break;
				default :
						break;
			}
		}
		if(factfpr.Line == 1){
			switch(line){
				case 0:
					sprintf(str1,"Up Load");
					sprintf(str3,"Press L to continue");
					sprintf(str4,"");
					break;
				case 1:
					sprintf(str1,"Formatting");
					sprintf(str3,"Press L to continue");
					sprintf(str4,"");
					break;
				default :
						break;
			}
		}
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //显示清屏
		HAL_Delay(10);
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str2);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str3);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str4);
	}
}

void MenuInit(void)
{
	stm32_config.Selected = 0;
	stm32_config.CUSTSelected = DSP;// = 0
	stm32_config.CUSTSelected2 = 0;
	
	stm32_config.FACTSelected = DSP;// = 0
	stm32_config.FACTSelected2 = 0;
}

void p31_p32(void)
{
	uint8_t j = 0;
	
	//P31
	{
		for(j=0;j<11;j++){
			if(factdis.P31[0] == dash_number0[j])
				break;
		}
		p31_0 = j;
		
		for(j=0;j<13;j++){
			if(factdis.P31[1] == dash_number1[j])
				break;
		}
		p31_1 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[2] == dash_number2[j])
				break;
		}
		p31_2 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[3] == dash_number2[j])
				break;
		}
		p31_3 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[4] == dash_number2[j])
				break;
		}
		p31_4 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[5] == dash_number2[j])
				break;
		}
		p31_5 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[6] == dash_number2[j])
				break;
		}
		p31_6 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[7] == dash_number2[j])
				break;
		}
		p31_7 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[8] == dash_number2[j])
				break;
		}
		p31_8 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[9] == dash_number2[j])
				break;
		}
		p31_9 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[10] == dash_number2[j])
				break;
		}
		p31_10 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[11] == dash_number2[j])
				break;
		}
		p31_11 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[12] == dash_number2[j])
				break;
		}
		p31_12 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[13] == dash_number2[j])
				break;
		}
		p31_13 = j;
		
		for(j=0;j<12;j++){
			if(factdis.P31[14] == dash_number2[j])
				break;
		}
		p31_14 = j;
	}
	
	//P32
	{
		for(j=0;j<11;j++){
			if(factdis.P32[0] == dash_number3[j])
				break;
		}
		p32_0 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[1] == dash_number3[j])
				break;
		}
		p32_1 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[2] == dash_number3[j])
				break;
		}
		p32_2 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[3] == dash_number3[j])
				break;
		}
		p32_3 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[4] == dash_number3[j])
				break;
		}
		p32_4 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[5] == dash_number3[j])
				break;
		}
		p32_5 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[6] == dash_number3[j])
				break;
		}
		p32_6 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[7] == dash_number3[j])
				break;
		}
		p32_7 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[8] == dash_number3[j])
				break;
		}
		p32_8 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[9] == dash_number3[j])
				break;
		}
		p32_9 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[10] == dash_number3[j])
				break;
		}
		p32_10 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[11] == dash_number3[j])
				break;
		}
		p32_11 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[12] == dash_number3[j])
				break;
		}
		p32_12 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[13] == dash_number3[j])
				break;
		}
		p32_13 = j;
		
		for(j=0;j<11;j++){
			if(factdis.P32[14] == dash_number3[j])
				break;
		}
		p32_14 = j;
	}
}


