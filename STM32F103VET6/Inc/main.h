/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Load_Cell_Sensor_in_Pin GPIO_PIN_0
#define Load_Cell_Sensor_in_GPIO_Port GPIOC
#define Lift_Motor_Sensor_in_Pin GPIO_PIN_1
#define Lift_Motor_Sensor_in_GPIO_Port GPIOC
#define DoorOpen_Motor_Sensor_in_Pin GPIO_PIN_2
#define DoorOpen_Motor_Sensor_in_GPIO_Port GPIOC
#define Drum_Motor_Sensor_in_Pin GPIO_PIN_3
#define Drum_Motor_Sensor_in_GPIO_Port GPIOC
#define Case_Sensor_in_Pin GPIO_PIN_0
#define Case_Sensor_in_GPIO_Port GPIOA
#define Vapor_Sensor_in_Pin GPIO_PIN_1
#define Vapor_Sensor_in_GPIO_Port GPIOA
#define Power_Sensor_in_Pin GPIO_PIN_2
#define Power_Sensor_in_GPIO_Port GPIOA
#define Outside_DoorOpen_Pin GPIO_PIN_3
#define Outside_DoorOpen_GPIO_Port GPIOA
#define Lift_Motor_en_Pin GPIO_PIN_5
#define Lift_Motor_en_GPIO_Port GPIOC
#define Lift_Motor_in2_Pin GPIO_PIN_0
#define Lift_Motor_in2_GPIO_Port GPIOB
#define Lift_Motor_in1_Pin GPIO_PIN_1
#define Lift_Motor_in1_GPIO_Port GPIOB
#define basket_on_Pin GPIO_PIN_7
#define basket_on_GPIO_Port GPIOE
#define dooropen_Pin GPIO_PIN_8
#define dooropen_GPIO_Port GPIOE
#define lowproduct_Pin GPIO_PIN_9
#define lowproduct_GPIO_Port GPIOE
#define DoorOpen_motor_en_Pin GPIO_PIN_10
#define DoorOpen_motor_en_GPIO_Port GPIOE
#define DoorOpen_motor_in2_Pin GPIO_PIN_11
#define DoorOpen_motor_in2_GPIO_Port GPIOE
#define DoorOpen_motor_in1_Pin GPIO_PIN_12
#define DoorOpen_motor_in1_GPIO_Port GPIOE
#define Drum_motor_en_Pin GPIO_PIN_13
#define Drum_motor_en_GPIO_Port GPIOE
#define Drum_motor_in2_Pin GPIO_PIN_14
#define Drum_motor_in2_GPIO_Port GPIOE
#define Drum_motor_in1_Pin GPIO_PIN_15
#define Drum_motor_in1_GPIO_Port GPIOE
#define SCL2_Pin GPIO_PIN_10
#define SCL2_GPIO_Port GPIOB
#define SDA2_Pin GPIO_PIN_11
#define SDA2_GPIO_Port GPIOB
#define LCD_CLK2_Pin GPIO_PIN_12
#define LCD_CLK2_GPIO_Port GPIOB
#define LCD_CLK_Pin GPIO_PIN_13
#define LCD_CLK_GPIO_Port GPIOB
#define LCD_SIO_Pin GPIO_PIN_14
#define LCD_SIO_GPIO_Port GPIOB
#define LCD_Reset_Pin GPIO_PIN_15
#define LCD_Reset_GPIO_Port GPIOB
#define DEBUG_UART3_TX_Pin GPIO_PIN_8
#define DEBUG_UART3_TX_GPIO_Port GPIOD
#define DEBUG_UART3_RX_Pin GPIO_PIN_9
#define DEBUG_UART3_RX_GPIO_Port GPIOD
#define LCD_STB_Pin GPIO_PIN_10
#define LCD_STB_GPIO_Port GPIOD
#define KEY_6_Pin GPIO_PIN_13
#define KEY_6_GPIO_Port GPIOD
#define KEY_5_Pin GPIO_PIN_14
#define KEY_5_GPIO_Port GPIOD
#define KEY_4_Pin GPIO_PIN_15
#define KEY_4_GPIO_Port GPIOD
#define KEY_3_Pin GPIO_PIN_6
#define KEY_3_GPIO_Port GPIOC
#define KEY_2_Pin GPIO_PIN_7
#define KEY_2_GPIO_Port GPIOC
#define KEY_1_Pin GPIO_PIN_8
#define KEY_1_GPIO_Port GPIOC
#define Defrosting_Relay_Pin GPIO_PIN_8
#define Defrosting_Relay_GPIO_Port GPIOA
#define Vaporization_Relay_Pin GPIO_PIN_9
#define Vaporization_Relay_GPIO_Port GPIOA
#define Compressor_Relay_Pin GPIO_PIN_10
#define Compressor_Relay_GPIO_Port GPIOA
#define USB_INT_Pin GPIO_PIN_11
#define USB_INT_GPIO_Port GPIOA
#define USB_Reset_Pin GPIO_PIN_12
#define USB_Reset_GPIO_Port GPIOA
#define MCU_UART4_TX_Pin GPIO_PIN_10
#define MCU_UART4_TX_GPIO_Port GPIOC
#define MCU_UART4_RX_Pin GPIO_PIN_11
#define MCU_UART4_RX_GPIO_Port GPIOC
#define MCU_UART5_TX_Pin GPIO_PIN_12
#define MCU_UART5_TX_GPIO_Port GPIOC
#define Master_Slave_Pin GPIO_PIN_1
#define Master_Slave_GPIO_Port GPIOD
#define MCU_UART5_RX_Pin GPIO_PIN_2
#define MCU_UART5_RX_GPIO_Port GPIOD
#define MCU_UART2_TX_Pin GPIO_PIN_5
#define MCU_UART2_TX_GPIO_Port GPIOD
#define MCU_UART2_RX_Pin GPIO_PIN_6
#define MCU_UART2_RX_GPIO_Port GPIOD
#define WB_DOWNLOAD_Pin GPIO_PIN_7
#define WB_DOWNLOAD_GPIO_Port GPIOD
#define ESP32_S_EN__Pin GPIO_PIN_3
#define ESP32_S_EN__GPIO_Port GPIOB
#define LoRa_HostWake_Pin GPIO_PIN_5
#define LoRa_HostWake_GPIO_Port GPIOB
#define LoRa_UART1_TX_Pin GPIO_PIN_6
#define LoRa_UART1_TX_GPIO_Port GPIOB
#define LoRa_UART1_RX_Pin GPIO_PIN_7
#define LoRa_UART1_RX_GPIO_Port GPIOB
#define LoRa_nReload_Pin GPIO_PIN_8
#define LoRa_nReload_GPIO_Port GPIOB
#define LoRa_nRST_Pin GPIO_PIN_9
#define LoRa_nRST_GPIO_Port GPIOB
#define LoRa_wakeup_Pin GPIO_PIN_0
#define LoRa_wakeup_GPIO_Port GPIOE
#define WIRELESS_STATE_Pin GPIO_PIN_1
#define WIRELESS_STATE_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
#define DIANZU0 	188.2
#define DIANZU1 	178.3
#define DIANZU2 	169.0
#define DIANZU3 	160.2
#define DIANZU4 	151.9
#define DIANZU5 	144.1
#define DIANZU6 	136.7
#define DIANZU7 	129.8
#define DIANZU8 	123.2
#define DIANZU9 	117.0
#define DIANZU10 	111.2
#define DIANZU11 	105.7
#define DIANZU12 	100.5
#define DIANZU13 	95.53
#define DIANZU14 	90.87
#define DIANZU15 	86.46
#define DIANZU16 	82.29
#define DIANZU17 	78.34
#define DIANZU18 	74.61
#define DIANZU19 	71.07
#define DIANZU20 	67.72
#define DIANZU21 	64.55
#define DIANZU22 	61.54
#define DIANZU23 	58.69
#define DIANZU24 	55.98
#define DIANZU25 	53.42
#define DIANZU26 	50.98
#define DIANZU27 	48.67
#define DIANZU28 	46.48
#define DIANZU29 	44.40
#define DIANZU30	42.42
#define DIANZU31 	40.54
#define DIANZU32 	38.75
#define DIANZU33 	37.05
#define DIANZU34 	35.44
#define DIANZU35 	33.90
#define DIANZU36 	32.44
#define DIANZU37 	31.05
#define DIANZU38 	29.73
#define DIANZU39 	28.47
#define DIANZU40 	27.27
#define DIANZU41 	26.12
#define DIANZU42 	25.03
#define DIANZU43 	24.00
#define DIANZU44 	23.01
#define DIANZU45 	22.06
#define DIANZU46 	21.16
#define DIANZU47 	20.30
#define DIANZU48 	19.48
#define DIANZU49 	18.70
#define DIANZU50 	17.95
#define DIANZU51 	17.24
#define DIANZU52 	16.56
#define DIANZU53 	15.91
#define DIANZU54	15.29
#define DIANZU55 	14.69
#define DIANZU56 	14.13
#define DIANZU57 	13.58
#define DIANZU58 	13.06
#define DIANZU59 	12.57
#define DIANZU60 	12.09
#define DIANZU61 	11.64
#define DIANZU62 	11.20
#define DIANZU63 	10.78
#define DIANZU64 	10.38
#define DIANZU65 	10.00
#define DIANZU66 	9.633
#define DIANZU67 	9.282
#define DIANZU68 	8.945
#define DIANZU69 	8.622
#define DIANZU70 	8.313
#define DIANZU71 	8.016
#define DIANZU72 	7.731
#define DIANZU73 	7.458
#define DIANZU74 	7.196
#define DIANZU75 	6.944
#define DIANZU76 	6.702
#define DIANZU77 	6.470
#define DIANZU78 	6.247
#define DIANZU79 	6.033
#define DIANZU80 	5.828
#define DIANZU81 	5.630
#define DIANZU82 	5.440
#define DIANZU83 	5.258
#define DIANZU84 	5.082
#define DIANZU85 	4.913
#define DIANZU86 	4.751
#define DIANZU87 	4.595
#define DIANZU88 	4.444
#define DIANZU89 	4.300
#define DIANZU90 	4.160
#define DIANZU91 	4.026
#define DIANZU92 	3.897
#define DIANZU93 	3.773
#define DIANZU94 	3.653
#define DIANZU95 	3.538
#define DIANZU96 	3.427
#define DIANZU97 	3.320
#define DIANZU98 	3.216
#define DIANZU99 	3.117
#define DIANZU100 3.021
#define DIANZU101 2.982
#define DIANZU102 2.839
#define DIANZU103 2.753
#define DIANZU104 2.670
#define DIANZU105 2.590
#define DIANZU106 2.512
#define DIANZU107 2.438
#define DIANZU108 2.365
#define DIANZU109 2.296
#define DIANZU110 2.229
#define DIANZU111 2.164
#define DIANZU112 2.101
#define DIANZU113 2.040
#define DIANZU114 1.982
#define DIANZU115 1.925
#define DIANZU116 1.870
#define DIANZU117 1.817
#define DIANZU118 1.766
#define DIANZU119 1.716
#define DIANZU120 1.669
#define DIANZU121 1.622
#define DIANZU122 1.577
#define DIANZU123 1.534
#define DIANZU124 1.492
#define DIANZU125 1.451
#define DIANZU126 1.412
#define DIANZU127 1.374
#define DIANZU128 1.337
#define DIANZU129 1.301
#define DIANZU130 1.267
#define DIANZU131 1.233
#define DIANZU132 1.201
#define DIANZU133 1.169
#define DIANZU134 1.139
#define DIANZU135 1.109
#define DIANZU136 1.080
#define DIANZU137 1.052
#define DIANZU138 1.026
#define DIANZU139 0.9993
#define DIANZU140 0.9740
#define DIANZU141 0.9493
#define DIANZU142 0.9254
#define DIANZU143 0.9023
#define DIANZU144 0.8798
#define DIANZU145 0.8579
#define DIANZU146 0.8367
#define DIANZU147 0.8161
#define DIANZU148 0.7961
#define DIANZU149 0.7767
#define DIANZU150 0.7579
#define DIANZU151 0.7395
#define DIANZU152 0.7217
#define DIANZU153 0.7044
#define DIANZU154 0.6876
#define DIANZU155 0.6713
#define DIANZU156 0.6554
#define DIANZU157 0.6400
#define DIANZU158 0.6250
#define DIANZU159 0.6104
#define DIANZU160 0.5962

typedef struct _CUSTDSP
{
	uint8_t Line;
	char RE[20];
	uint16_t P02_P;
	uint16_t P02_C;
	uint8_t DT_T;
	uint8_t DT_P;
	uint16_t RT_T;
	uint16_t RT_P;
}CUSTDSP;//用户DSP(分配菜单层)菜单层

typedef struct _CUSTVS
{
	uint8_t Line;
	uint16_t DC;
	uint16_t CC;//校准次数报告
	uint16_t SC;
	uint16_t MC;
	uint16_t LC;
	uint16_t DrTQ;
	uint16_t DTQ;
	uint16_t FTO;
	uint16_t DTO;
	uint16_t CL;//称重大份校准值
	uint16_t CP;
}CUSTVS;//用户VS(统计)菜单层

typedef struct _CUSTCP
{
	uint8_t Line;
	int16_t St;//范围LS~US
	float Hy;//0.1~25℃
	float ot;//-9.9~9.9℃
	int8_t p2;//n-y
	int8_t AC;//0~50分钟
}CUSTCP;//用户压缩机菜单层

typedef struct _CUSTdis
{
	uint8_t Line;
	int8_t CF;//℃/℉
	int8_t rE;//dE-in
	int8_t d1;//库温探头读数
	int8_t d2;//蒸发器探头读数
	int8_t P01;//语言
}CUSTdis;//用户显示菜单层

typedef struct _CUSTdEF
{
	uint8_t Line;
	int16_t dE;//-55~50℃
	int8_t id;//0~99小时
	int8_t Md;//0~99分钟
}CUSTdEF;//用户化霜菜单层

typedef struct _CUSTFAn
{
	uint8_t Line;
	int8_t F1;//风机运行模式
	int8_t F2;
	int8_t Fd;//融霜后风扇启动延时 0~99min
	int8_t Fn;//0/15(min)
	int8_t FF;//0/15(min)
}CUSTFAn;//用户风扇菜单层

typedef struct _CUSTAL
{
	uint8_t Line;
	int8_t AU;//ALL~99℃
	int8_t	AL;//-55℃~ALU
}CUSTAL;//用户报警菜单层


typedef struct _FACTCP
{
	uint8_t Line;
	int16_t St;//LS~US
	float Hy;//0.1~25℃
	int16_t LS;//-55℃~Set
	int8_t US;//SET~99℃
	float ot;//-9.9~9.9℃
	int8_t P2;
	float oE;//-9.9~9.9℃
	int8_t od;//0~99分钟
	int8_t AC;//0~50分钟
	int8_t Cy;//0~99分钟
	int8_t Cn;//0~99分钟
	int16_t dAd;//0~255分钟
}FACTCP;//工厂压缩机菜单层

typedef struct _FACTdis
{
	uint8_t Line;
	uint16_t PA1;
	uint16_t PA2;
	int8_t CF;//℃/℉
	int8_t rE;
	int8_t Ld;
	int8_t dy;
	int16_t d1;
	int16_t d2;
	int8_t P01;//语言
	char P31[30];//????
	char P32[30];
}FACTdis;//工厂显示菜单层

typedef struct _FACTdEF
{
	uint8_t Line;
	int8_t td;
	int16_t dE;//-55~50℃
	int8_t id;//0~99小时
	int8_t Md;//0~99分钟
	int8_t dd;//0~99分钟
	int8_t dF;//融霜期间的温度显示
	int8_t dt;//0~99分钟
	int8_t dP;//上电融霜
}FACTdEF;//工厂化霜菜单层

typedef struct _FACTFAn
{
	uint8_t Line;
	int8_t F1;
	int8_t F2;
	int8_t Fd;//0~99min
	int8_t FS;//-55/50℃  -67/99℃
	uint8_t FAd;//1~50
	int8_t Fn;//	0/15(min.)
	int8_t FF;//	0/15(min.)
	int16_t dAd;//0~255分钟
}FACTFAn;//工厂风扇菜单层

typedef struct _FACTAL
{
	uint8_t Line;
	int8_t AU;//ALL~99℃
	int8_t AL;//-55℃~ALU
	int8_t Ad;//0~99分钟
	int8_t dA;//0~99分钟
}FACTAL;//工厂报警菜单层

typedef struct _FACTDSP
{
	uint8_t Line;
	uint8_t P10;
	uint8_t P11;
	uint16_t P13;
	uint16_t P14;
	uint16_t P15;
	uint16_t P16;
	uint16_t P17;
	int8_t P18;
	int8_t P19;
	int8_t P20;
	uint8_t P21;
	uint8_t P22;
	uint8_t P23;
	uint8_t P26;
	int8_t P28;
	uint8_t P29;
	uint8_t P30;
	uint16_t T1;
	uint16_t T2;
	uint16_t A;
}FACTDSP;//工厂分配参数菜单层

typedef struct _FACTFpr
{
	uint8_t Line;
	uint8_t UL;//上传
	uint8_t Fr;//格式
}FACTFpr;//工厂分配参数菜单层

typedef struct _STM32_Config
{
	uint16_t S;
	uint16_t M;
	uint16_t LSet;
	uint8_t UP;
	uint8_t DOWN;
	uint8_t STANDBY;
	uint8_t Menu_Tier;
	int8_t CUSTSelected;
	int8_t CUSTSelected2;
	int8_t FACTSelected;
	int8_t FACTSelected2;
	int8_t Selected;
}STM32_Config;

typedef struct _TIME
{
    uint8_t Year;
    uint8_t Month;
    uint8_t Date;
    uint8_t WeekDay;

    uint8_t Hours;
    uint8_t Minutes;
    uint8_t Seconds;
} TIME;

enum
{
    false = 0,
    true
};

#define On	1
#define Off 0
#define Start 1
#define Stop  0

#define	ERR_MISS_FILE		0x42			/* 指定路径的文件没有找到,可能是文件名称错误 */
#define	USB_INT_SUCCESS		0x14			/* USB事务或者传输操作成功 */
#define	CMD11_CHECK_EXIST	0x06			/* 测试通讯接口和工作状态 */
#define	ERR_DISK_DISCON		0x82			/* 磁盘尚未连接,可能磁盘已经断开 */
extern CUSTDSP custdsp;
extern CUSTVS	custvs;
extern CUSTCP custcp;
extern CUSTdis custdis;
extern CUSTdEF custdef;
extern CUSTFAn custfan;
extern CUSTAL custal;

extern FACTCP factcp;
extern FACTdis factdis;
extern FACTdEF factdef;
extern FACTFAn factfan;
extern FACTAL factal;
extern FACTDSP factdsp;
extern FACTFpr factfpr;

extern STM32_Config stm32_config;
extern int8_t Menu;
extern uint8_t CUST_FACT;
extern uint8_t bSystemInitOk;
extern int weight;
extern int16_t Small;
extern int16_t Standby;
extern int16_t Up;
extern int16_t Down;
extern uint8_t Test_Mark;
extern float Vapor_T;
extern float Case_T;
extern int Vapor_T_HSD;
extern int Case_T_HSD;
extern uint8_t Drum_door_status;
extern uint8_t Ref_door_status;
extern uint8_t Compressor_status;
extern uint8_t Vapor_status;
extern uint8_t Defrost_status;
extern uint8_t Record_High_Temp;
extern uint8_t Record_Low_Temp;
extern uint8_t Record_Evap_Probe_alarm;
extern uint8_t Record_Refri_Probe_alarm;
extern uint8_t Record_Door_Opening_alarm;
extern uint8_t jiaozhun;
extern uint8_t dataa;
extern uint16_t delaytt;
extern uint16_t delaytt1;
extern volatile uint8_t Down_finish;
extern uint16_t AdcBuf[7];//存储Adc值

extern uint8_t Downjiaozhun;
extern uint8_t udiskread;
extern uint8_t moren_par;
void task_RX_TX(void *paramter);
void task_TempShow(void *paramter);
void task_Freeze(void *paramter);
void task_Defrost(void *paramter);
void task_DeviceCheck(void * paramter);

void TIM3_Enable(void);
void TIM3_Disable(void);
void TIM4_Enable(void);
void TIM4_Disable(void);

uint8_t Test(void);
void Switching_Value(void);

void Read_Parameter(uint8_t save);																	//参数默认设置
void Compressor_Relay(uint8_t State);														//压缩机
void Vaporization_Relay(uint8_t State);														//蒸发机
void Defrosting_Relay(uint8_t State);														//融霜
void DoorOpen_Motor(uint8_t State);															//开门电机
void Drum_Motor(uint8_t State);																//下料电机
void Lift_Motor(uint8_t State);																//升降电机
float Ohm_Temp(float dianzu);																	//电阻表
extern void Calibration(void);
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

uint8_t writeUDisk(void);												//写U盘
void readUdisk(void);
int16_t GetUdiskFreeSpace(void);											//查询U盘剩余空间
void UDiskRemove(void);
void usb_test(void);
uint8_t Check_Ch376sUart2Connect_(void);
void Uart_RX_TX(void);																		//串口数据收发
void Temperature_Alarm(void);															//温度报警
void ShowTemp(void);																		//显示温度
void Freeze(void);																			//冷冻模式
void Defrost(void);																			//融霜模式
void Fan(void);																				//风扇运作

extern void Scan(void);																			//按键检测
void Allocation(uint8_t copies);																		//分配功能

void DeviceCheck(void);																		//设备自检

void RTCTimeUpdate(void);												//更新时间
void GetRTCTimer(TIME *time);																//获取时间
void DiffTimeCalc(TIME *StartTime, TIME *StopTime, uint32_t *diffTime);						//时间差计算
uint32_t GetDiffTime(TIME *StartTime, uint8_t *bStartTime);									//获取时间差

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
