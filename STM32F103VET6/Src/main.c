/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "freertos.h"
#include "lcd.h"
#include "bsp_EEPROM.h"
#include "Number.h"
//#include "tools.h"
#include "key.h"
#include "AT24Cxx.h"
#include "esp32.h"
#include "LCD19264.h"
#include "HAL.h"
#include "HOST.h"
#include "FILE_SYS.h"
#define STM32_USART_EN	1
#define BUFFSIZE 500
#define	AGING_TEST	1

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
CUSTDSP custdsp;
CUSTVS	custvs;
CUSTCP custcp;
CUSTdis custdis;
CUSTdEF custdef;
CUSTFAn custfan;
CUSTAL custal;

FACTCP factcp;
FACTdis factdis;
FACTdEF factdef;
FACTFAn factfan;
FACTAL factal;
FACTDSP factdsp;
FACTFpr factfpr;

STM32_Config stm32_config;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint16_t AdcBuf[7] = {0};//¥Ê¥¢Adc÷µ
uint8_t bSystemInitOk = false;
int weight = 0;
int16_t Down = 0;
int16_t Up = 0;
int16_t Small = 0;
static int16_t Mid = 0;
static int16_t Large_Set = 0;
int16_t Standby = 0;
int8_t Menu = 0;
uint8_t CUST_FACT = 0; // 0 ¥˙±Ì”√ªß£¨1¥˙±Ìπ§≥ß
uint32_t DiffTime = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
float Measuing = 0.0;	//≤‚¡ø µº ÷ÿ¡ø÷µ
uint8_t jiaozhun = 0;
//static float CaseV = 0.0;
//static float VaporV = 0.0;
static float OhmCase = 0.0;
static float OhmVapor = 0.0;
float Vapor_T = 0.0;
float Case_T = 0.0;
int Case_T_HSD = 0;
int Vapor_T_HSD = 0;

//static uint16_t Com_Delay = 0;
static uint8_t  bCom_Delay = true;
static uint32_t Compressor_Time = 0;
static uint32_t Often_Time = 0;
static uint8_t  bOften_Start = true;
static uint8_t bDoor_Open = true;
static uint32_t Door_Time = 0;
static uint8_t  bProbe_Com = true;
static uint32_t Probe_Com_Time = 0;
static uint8_t flag1 = 1;
static uint8_t flag2 = 0;
static uint8_t bDefrost_Delay = true;
static uint32_t Defrost_Delay_Time = 0;
static uint8_t bDefrost_Delay0 = true;
static uint32_t Defrost_Delay0_Time = 0;
static uint8_t bFan_Delay = true;
static uint32_t Fan_Delay_Time = 0;
static uint8_t bAlarm = true;
static uint8_t bAlarm_Delay = true;
static uint8_t Alarm_3 = 0;
static uint8_t Door_Sign = 0;
static uint8_t bDoorOpen = true;
static uint32_t DoorOpen_Time = 0;
static uint8_t bfan = true;
static uint32_t fan_time = 0;
static uint8_t bDown_Time = true;
static uint32_t Down_Time = 0;
static uint8_t bFill = true;
static uint32_t Fill_Time = 0;
uint8_t Drum_door_status = 0;
uint8_t Ref_door_status = 0;
uint8_t Compressor_status = 0;
uint8_t Vapor_status = 0;
uint8_t Defrost_status = 0;
uint8_t Record_High_Temp = 0;
uint8_t Record_Low_Temp = 0;
uint8_t Record_Evap_Probe_alarm = 0;
uint8_t Record_Refri_Probe_alarm = 0;
uint8_t Record_Door_Opening_alarm = 0;
volatile uint8_t Down_finish = 6;
static uint8_t bdrip = true;
static uint32_t drip_time = 0;
static uint8_t bdrip2 = true;
static uint32_t drip_time2 = 0;
static uint8_t bTemp = true;
static uint32_t Temp_Time = 0;
static uint8_t time_out = 0;
static uint8_t smalla = 0;
static uint8_t wendtime = 0;
static uint8_t cell = 0;
static uint8_t lp = 0;
static uint8_t f_timeout = 0;
volatile uint8_t chongxin = 0;
volatile uint8_t bedefrost = 0;
static float defrost_temp = 0.0; 
volatile uint8_t afterdefrost = 0;
static uint32_t AlarmTime_Delay = 0;
volatile uint8_t alarmsign = 0;
volatile int liftadc = 200;
volatile int aadsl1 = 239;
volatile uint8_t whiledown = 0;
volatile uint16_t delaytime = 300;
volatile uint16_t adcdoor = 1000;
static uint8_t close_time = 9;
static uint16_t minadc = 336;
static uint16_t lifttime = 3000;
//static uint16_t liftweight = 5263;
static uint16_t liftweight = 3000;
static uint16_t delaysd = 950;
static uint16_t delaysd1 = 1500;
static uint16_t delaysd_2 = 950;
static uint16_t delaysd1_2 = 1500;
//static uint8_t TempError = 0;
static uint16_t yuanbenw = 0;
float smallwei = 0.0;
//float midwei = 0.0;
//float largewei = 0.0;
uint16_t delaytt = 100;
uint16_t delaytt1 = 1600;//45%
static uint16_t no_load = 0;
static uint8_t bdownfinish_0 = true;
static uint32_t downfinish_0 = 0;
static uint8_t zerofinish = 0;
//static uint8_t bdoor_outside = true;
//static uint32_t door_outside_time = 0;
uint8_t Downjiaozhun = 4;
static uint8_t fanqidong = 0;
static uint16_t chengzADC = 4096;
static uint8_t defrostsign = 0;
static uint8_t defrostsign_nokey = 0;
uint16_t Case_mean_value[100] = {0};
uint16_t Vapor_mean_value[100] = {0};
static uint16_t chavalue = 20;
static uint16_t haltime = 1500;
static float realweight = 0;
static uint8_t load_cell_error = 0;
static uint8_t vaporerror = 0;
static uint8_t drum = 0;
static uint8_t opendoor = 0;
static uint8_t closedoor = 0;
static uint8_t errorcode_0 = 0;
static uint8_t drumover = 0 ;
static uint8_t liftover = 0;
uint8_t udiskread = 0;
static uint8_t berror_code = 0;
static uint8_t highalarm = 0;
static uint8_t lowalarm = 0;
static int weisig = 15;
static uint8_t binching = true;
static uint32_t inchingtime= 0;
static int deletewarn = 0;
static uint8_t doorlock = 0;
static int errordelete = 0;
uint8_t ssada = 0;
uint8_t sensordoor = 0;
uint8_t nodoor = 0;
uint8_t outdoor = 0;
uint8_t c_sensor = 0;
uint8_t v_sensor = 0;
uint8_t moren_par = 0;
	static uint16_t drumtime = 100;
/* USER CODE END PFP */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t Systemconfig = 0;
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

    //¥Æø⁄≥ı ºªØ
//	HAL_UART_Receive_DMA(&huart5, UsartReceiveType5.RX_pData, UART5_RX_LEN);
//	__HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart4, UsartReceiveType4.RX_pData, UART4_RX_LEN);
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
//	HAL_UART_Receive_DMA(&huart3, UsartReceiveType3.RX_pData, USART3_RX_LEN);
//	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart2, (uint8_t *)UsartReceiveType2.RX_pData, USART2_RX_LEN);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1, UsartReceiveType1.RX_pData, USART1_RX_LEN);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);

	//AT24C02≥ı ºªØ
	Systemconfig = EEPROM_CheckOk();
	char str1[48] = {0};
	while(Systemconfig != 1)
	{
		//AT24C02≥ı ºªØ ß∞‹
		sprintf(str1,"Please Restart ");
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,1,1);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char *)str1);
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char *)str1);
		HAL_Delay(100);
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		Lcm_GotoXY(0,0,0);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		HAL_Delay(100);
	}
	//ø™∆ÙADC–£◊º
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)AdcBuf, 7);
	Lift_Motor(2);
	Drum_Motor(2);
	DoorOpen_Motor(2);
	//∂¡»°≤Œ ˝≈‰÷√
	Read_Parameter(0);
	if(moren_par > 0)
		Read_Parameter(1);
	MenuInit();
	//∂® ±∆˜ø™∆Ù
	TIM3_Enable();
//	TIM4_Enable();
	Lcm_Init();
	weight = 100;
	// ‰≥ˆ–≈œ¢“‘≤Èø¥
	HAL_GPIO_WritePin(ESP32_S_EN__GPIO_Port,ESP32_S_EN__Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(WB_DOWNLOAD_GPIO_Port,WB_DOWNLOAD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(USB_INT_GPIO_Port,USB_INT_Pin,GPIO_PIN_RESET);
	printf("11111\r\n");
	//Usart2_Printf("22222\r\n");
//	Usart3_Printf("œ»«∞P31:%s\r\n",P31);
//	Usart3_Printf("Menu:%d\r\n≤Àµ•≤„:%d\r\n”√ªßπ§≥ß:%d\r\nŒ¬∂»≤Œ ˝:%d\r\nP31:%s\r\nP32:%s\r\n",Menu,stm32_config.Menu_Tier,CUST_FACT,custcp.St,factdis.P31,factdis.P32);
//	Uart4_Printf("44444\r\n");
//	Uart5_Printf("55555\r\n");
//	int i = Test();
//	while(i !=1){
//		Lcm_GotoXY(0,0,1);
//		char xianshi[48] = {0};
//		sprintf(xianshi,"Trun off the machine            Check the equipment");
//		Lcm_Disp_String((unsigned char*)xianshi);
//	}
  /* USER CODE END 2 */
//	DoorOpen_Motor(On);
//	Drum_Motor(On);
//	Lift_Motor(On);
	bSystemInitOk = true;
	usb_test();
	HAL_Delay(1000);
	if(udiskread)
		readUdisk();
	/* Call init function for freertos objects (in freertos.c) */
	MX_FREERTOS_Init(); 

	/* Start scheduler */
	osKernelStart();
  
	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
	/* USER CODE END WHILE */
	/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
unsigned char *GetNum(uint8_t num)
{
    switch(num)
    {
    case 0:
        return Num0;
    case 1:
        return Num1;
    case 2:
        return Num2;
    case 3:
        return Num3;
    case 4:
        return Num4;
    case 5:
        return Num5;
    case 6:
        return Num6;
    case 7:
        return Num7;
    case 8:
        return Num8;
    case 9:
        return Num9;
    }
		return 0;
}

void Read_Parameter(uint8_t save)
{
	if(save == 1){
		
		{
			//”√ªß
			sprintf(custdsp.RE,"Reset");
			moren_par = 0;
			custdsp.P02_P = 2900;
			custdsp.P02_C = 665;
			custdsp.DT_T = 0;
			custdsp.DT_P = 0;
			custdsp.RT_T = 0;
			custdsp.RT_P = 0;

			custvs.DC = 0;
			custvs.CC = 0;
			custvs.SC = 0;
			custvs.MC = 0;
			custvs.LC = 0;
			custvs.DrTQ = 0;
			custvs.DTQ = 0;
			custvs.FTO = 0;
			custvs.DTO = 0;
			custvs.CL = 665;
			custvs.CP = 2900;

			custcp.St = -12;
			custcp.Hy = 2.5;
			custcp.ot = 0.0;
			custcp.p2 = 0;
			custcp.AC = 2;

			custdis.CF = 1;
			custdis.rE = 0;
			custdis.d1 = 1;
			custdis.d2 = 1;
			custdis.P01 = 1;

			custdef.dE = 60;
			custdef.id = 3;
			custdef.Md = 30;

			custfan.F1 = 2;
			custfan.F2 = 0;
			custfan.Fd = 5;
			custfan.Fn = 1;
			custfan.FF = 3;

			custal.AU = 40;
			custal.AL = -50;
		}

		{
			//π§≥ß
			factcp.St = -12;
			factcp.Hy = 2.5;
			factcp.LS = -15;
			factcp.US = 10;
			factcp.ot = 0.0;
			factcp.P2 = 0;
			factcp.oE = 0.0;
			factcp.od = 2;
			factcp.AC = 2;
			factcp.Cy = 20;
			factcp.Cn = 10;
			factcp.dAd = 5;

			factdis.PA1 = 14;
			factdis.PA2 = 15;
			factdis.CF = 1;
			factdis.rE = 0;
			factdis.Ld = 0;
			factdis.dy = 1;
			factdis.d1 = 1;
			factdis.d2 = 1;
			factdis.P01 = 1;
			sprintf(factdis.P31,"000000000000000");
			sprintf(factdis.P32,"000000000000000");
//			sprintf(factdis.P31,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],\
//																														(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],\
//																															(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0]);
//			sprintf(factdis.P32,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",(char*)dash_number[10],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],\
//																														(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],\
//																															(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0],(char*)dash_number[0]);
			factdef.td = 0;
			factdef.dE = 60;
			factdef.id = 3;
			factdef.Md = 30;
			factdef.dd = 0;
			factdef.dF = 0;
			factdef.dt = 5;
			factdef.dP = 1;

			factfan.F1 = 2;
			factfan.F2 = 0;
			factfan.Fd = 5;
			factfan.FS = 50;
			factfan.FAd = 2;
			factfan.Fn = 1;
			factfan.FF = 3;
			factfan.dAd = 5;

			factal.AU = 40;
			factal.AL = -50;
			factal.Ad = 15;
			factal.dA = 90;

			factdsp.P10 = 4;
			factdsp.P11 = 20;
			factdsp.P13 = 4050;
			factdsp.P14 = 4050;
			factdsp.P15 = 4050;
			factdsp.P16 = 150;
			factdsp.P17 = 50;
			factdsp.P18 = 1;
			factdsp.P19 = 0;
			factdsp.P20 = 1;
			factdsp.P21 = 90;
			factdsp.P22 = 89;
			factdsp.P23 = 88;
			factdsp.P26 = 3;
			factdsp.P28 = 0;
			factdsp.P29 = 67;
			factdsp.P30 = 50;
			factdsp.T1 = 999;
			factdsp.T2 = 5;
			factdsp.A = 4050;

			factfpr.UL = 1;
			factfpr.Fr = 1;
		}
		
		
		delaytt = 100;
		delaytt1 = 1600;
		ParamSave();
	}
	else{
		ParamRead();
	}
	{
		stm32_config.S = 100;
		stm32_config.M = 200;
		stm32_config.LSet = 300;
	}
	Usart3_Printf("ƒ„ «÷Ì:%d\r\nenen:%.1f\r\n√‹¬Î¢Ÿ:%d\r\n√‹¬Î¢⁄:%d\r\n",custdsp.P02_P,custcp.Hy,factdis.PA1,factdis.PA2);
}

uint8_t Test(void)
{
	return 1;
}
void Compressor_Relay(uint8_t State)
{
	//—πÀıª˙
	if(State == 1){
		HAL_GPIO_WritePin(Compressor_Relay_GPIO_Port,Compressor_Relay_Pin, GPIO_PIN_SET);
	}

	else if(State == 0){
		HAL_GPIO_WritePin(Compressor_Relay_GPIO_Port,Compressor_Relay_Pin, GPIO_PIN_RESET);
	}
	
}

void Vaporization_Relay(uint8_t State)
{
	if(Case_T >= factfan.FS + factfan.FAd){
		HAL_GPIO_WritePin(Vaporization_Relay_GPIO_Port,Vaporization_Relay_Pin, GPIO_PIN_RESET);
		Usart3_Printf("Œ¬∂»π˝∏ﬂ£¨πÿ±’∑Á…»\r\n");
		return;
	}
	//’Ù∑¢∆˜
	else if(State == 1){
			HAL_GPIO_WritePin(Vaporization_Relay_GPIO_Port,Vaporization_Relay_Pin, GPIO_PIN_SET);
	}
	
	else if(State == 0){
		HAL_GPIO_WritePin(Vaporization_Relay_GPIO_Port,Vaporization_Relay_Pin, GPIO_PIN_RESET);
	}
}

void Defrosting_Relay(uint8_t State)
{
	//»⁄À™
	if(State == 1){
//		static TIME DefrostDelay;
//		Defrost_Delay_Time = GetDiffTime(&DefrostDelay,&bDefrost_Delay);
//		if(Defrost_Delay_Time >= factdef.dd)
			HAL_GPIO_WritePin(Defrosting_Relay_GPIO_Port,Defrosting_Relay_Pin, GPIO_PIN_SET);
	}
	
	else if(State == 0){
		HAL_GPIO_WritePin(Defrosting_Relay_GPIO_Port,Defrosting_Relay_Pin, GPIO_PIN_RESET);
	}
}

void DoorOpen_Motor(uint8_t State)
{
	//≤ª◊™
	if(State == 2){
		HAL_GPIO_WritePin(DoorOpen_motor_en_GPIO_Port,DoorOpen_motor_en_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DoorOpen_motor_in1_GPIO_Port,DoorOpen_motor_in1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DoorOpen_motor_in2_GPIO_Port,DoorOpen_motor_in2_Pin, GPIO_PIN_RESET);
	}
	//’˝◊™
	else if(State == 1){
		HAL_GPIO_WritePin(DoorOpen_motor_en_GPIO_Port,DoorOpen_motor_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DoorOpen_motor_in1_GPIO_Port,DoorOpen_motor_in1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DoorOpen_motor_in2_GPIO_Port,DoorOpen_motor_in2_Pin, GPIO_PIN_RESET);
	}
	//∑¥◊™
	else if(State == 0){
		HAL_GPIO_WritePin(DoorOpen_motor_en_GPIO_Port,DoorOpen_motor_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DoorOpen_motor_in1_GPIO_Port,DoorOpen_motor_in1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DoorOpen_motor_in2_GPIO_Port,DoorOpen_motor_in2_Pin, GPIO_PIN_SET);
	}
}

void Drum_Motor(uint8_t State)
{
	if(State == 2){
		HAL_GPIO_WritePin(Drum_motor_en_GPIO_Port,Drum_motor_en_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Drum_motor_in1_GPIO_Port,Drum_motor_in1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Drum_motor_in2_GPIO_Port,Drum_motor_in2_Pin, GPIO_PIN_RESET);
	}
	
	else if(State == 1){
		HAL_GPIO_WritePin(Drum_motor_en_GPIO_Port,Drum_motor_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Drum_motor_in2_GPIO_Port,Drum_motor_in2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Drum_motor_in1_GPIO_Port,Drum_motor_in1_Pin, GPIO_PIN_SET);
		
	}
	
	else if(State == 0){
		HAL_GPIO_WritePin(Drum_motor_en_GPIO_Port,Drum_motor_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Drum_motor_in1_GPIO_Port,Drum_motor_in1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Drum_motor_in2_GPIO_Port,Drum_motor_in2_Pin, GPIO_PIN_SET);
	}
	//HAL_Delay(drumtime);
}
	
void Lift_Motor(uint8_t State)
{
	if(State == 2){
		HAL_GPIO_WritePin(Lift_Motor_en_GPIO_Port,Lift_Motor_en_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Lift_Motor_in1_GPIO_Port,Lift_Motor_in1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Lift_Motor_in2_GPIO_Port,Lift_Motor_in2_Pin, GPIO_PIN_RESET);
	}
	
	else if(State == 1){
		HAL_GPIO_WritePin(Lift_Motor_en_GPIO_Port,Lift_Motor_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Lift_Motor_in1_GPIO_Port,Lift_Motor_in1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Lift_Motor_in2_GPIO_Port,Lift_Motor_in2_Pin, GPIO_PIN_RESET);
	}
	
	else if(State == 0){
		HAL_GPIO_WritePin(Lift_Motor_en_GPIO_Port,Lift_Motor_en_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Lift_Motor_in1_GPIO_Port,Lift_Motor_in1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Lift_Motor_in2_GPIO_Port,Lift_Motor_in2_Pin, GPIO_PIN_SET);
	}
}
void GetRTCTimer(TIME *time)
{
    /* Get the RTC current Time ,must get time first*/
    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

    memset(time, 0, sizeof(TIME));

    time->Year = currentDate.Year;
    time->Month = currentDate.Month;
    time->Date = currentDate.Date;
    time->WeekDay = currentDate.WeekDay;

    time->Hours = currentTime.Hours;
    time->Minutes = currentTime.Minutes;
    time->Seconds = currentTime.Seconds;
}

void RTCTimeUpdate(void)
{
    /* Get the RTC current Time ,must get time first*/
    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

    /* Display date Format : yy/mm/dd */
//    printf("%02d/%02d/%02d\t", 2000 + currentDate.Year, currentDate.Month, currentDate.Date);
//    /* Display time Format : hh:mm:ss */
//    printf("%02d:%02d:%02d\t", currentTime.Hours, currentTime.Minutes, currentTime.Seconds);
//    printf("Temp: %d\tHum: %d\r\n", stm32_config.iCurrentTemper,stm32_config.iCurrentHum);
}


void DiffTimeCalc(TIME *StartTime, TIME *StopTime, uint32_t *diffTime)
{
//    uint32_t start = StartTime->Hours * 60 + StartTime->Minutes;
//    uint32_t stop = StopTime->Hours * 60 + StopTime->Minutes;
		uint32_t start = StartTime->Hours * 60 * 60 + StartTime->Minutes * 60 +StartTime->Seconds;
		uint32_t stop = StopTime->Hours * 60 * 60 + StopTime->Minutes * 60 + StopTime->Seconds;
    *diffTime = 0;

    if(StartTime->Date != StopTime->Date)// ±÷”‘À––µΩµ⁄∂˛ÃÏ
    {
        stop += 24 * 60 * 60; //º”…œ24–° ±
    }

    if(StartTime > StopTime)
    {
      //  *diffTime = (start - stop)/60;
			*diffTime = start - stop;
    }
    else
    {
       // *diffTime = (stop - start)/60;
			*diffTime = stop - start;
    }
}

uint32_t GetDiffTime(TIME *StartTime, uint8_t *bStartTime)
{
    //º∆À„ ±º‰≤Ó
    if(*bStartTime)
    {
        *bStartTime = false;
        GetRTCTimer(StartTime);
    }

    TIME StopTime;
    GetRTCTimer(&StopTime);

    uint32_t DiffTime = 0;
    DiffTimeCalc(StartTime, &StopTime, &DiffTime);

//    if(DiffTime > 999 * 60)
//        DiffTime = 0;
    return DiffTime;
}

void Uart_RX_TX(void)
{
	if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
		static TIME bletime;
		static uint8_t bbletime = true;
		static uint32_t bletimes = 0;
		bletimes = GetDiffTime(&bletime,&bbletime);
		if(Down == 0){
			if(bletimes >= 20)
				Down++;
		}
	}
	ESP32_Test();
}

void Temperature_Alarm(void)
{
	static TIME Alarm;
	uint32_t AlarmTime = GetDiffTime(&Alarm,&bAlarm);
	if(AlarmTime >= factal.dA * 60){
		//ø‚Œ¬±®æØ,º¥œ‰Œ¬
		if(Case_T_HSD >= custal.AU){
			Alarm_3 = 1;
		}
		else if(Case_T_HSD <= custal.AL){
			Alarm_3 = 1;
		}
		else{
			if(Alarm_3)
				berror_code = 0;
			Alarm_3 = 0;
			bAlarm_Delay = true;
			highalarm = 0;
			lowalarm = 0;
		}
	}
	if(Alarm_3){
		static TIME Alarm_Delay;
		AlarmTime_Delay = GetDiffTime(&Alarm_Delay,&bAlarm_Delay);
		if(AlarmTime_Delay > factal.Ad * 60){
			//±®æØ
			if(Case_T_HSD > custal.AU){
				alarmsign = 1;
				highalarm = 1;
			}
			else if (Case_T_HSD < custal.AL){
				alarmsign = 2;
				lowalarm = 1;
			}
		}
	}
}
void ShowTemp(void)
{
	static float comcase  = 0;
	static float comvapor = 0;
	if(comcase < Case_T && comvapor < Vapor_T){
		comcase  = Case_T;
		comvapor = Vapor_T;
	}
	else if(comcase >= Case_T && factdis.Ld == 0){
		OhmCase = (50 / ((AdcBuf[4] * 3.3 / 4096) / 0.66)) - 10;
		OhmVapor = (50 / ((AdcBuf[5] * 3.3 / 4096) / 0.66)) - 10;
		Vapor_T = Ohm_Temp(OhmVapor);
		Vapor_T_HSD = Vapor_T * 1.8 + 32;//ª™ œ∂»
		Case_T = Ohm_Temp(OhmCase);
		Case_T_HSD  = Case_T * 1.8 + 32;//ª™ œ∂»
		custdis.d1 = factdis.d1 = comcase  = Case_T;
		custdis.d2 = factdis.d2 = comvapor = Vapor_T;
		bTemp = true;
	}
	else if(comvapor >= Case_T && factdis.Ld){
		OhmCase = (50 / ((AdcBuf[4] * 3.3 / 4096) / 0.66)) - 10;
		OhmVapor = (50 / ((AdcBuf[5] * 3.3 / 4096) / 0.66)) - 10;
		Vapor_T = Ohm_Temp(OhmVapor);
		Vapor_T_HSD = Vapor_T * 1.8 + 32;//ª™ œ∂»
		Case_T = Ohm_Temp(OhmCase);
		Case_T_HSD  = Case_T * 1.8 + 32;//ª™ œ∂»
		custdis.d1 = factdis.d1 = comcase  = Case_T;
		custdis.d2 = factdis.d2 = comvapor = Vapor_T;
		bTemp = true;
	}
	else{
		static TIME temp_time;
		Temp_Time = GetDiffTime(&temp_time,&bTemp);
		//Usart3_Printf("%d\r\n, µº  ±º‰%d\r\n",factdis.dy,Temp_Time);
		if(Temp_Time <= factdis.dy * 60){
			return;
		}
		else{
			bTemp = true;
			Temp_Time = 0;
			OhmCase = (50 / ((AdcBuf[4] * 3.3 / 4096) / 0.66)) - 10;
			OhmVapor = (50 / ((AdcBuf[5] * 3.3 / 4096) / 0.66)) - 10;
			Vapor_T = Ohm_Temp(OhmVapor);
			Vapor_T_HSD = Vapor_T * 1.8 + 32;//ª™ œ∂»
			Case_T = Ohm_Temp(OhmCase);
			Case_T_HSD  = Case_T * 1.8 + 32;//ª™ œ∂»
			custdis.d1 = factdis.d1 = comcase  = Case_T;
			custdis.d2 = factdis.d2 = comvapor = Vapor_T;
		}
	}
}

float Ohm_Temp(float dianzu)
{
	float wendu = 0.0;
	char display[20] = {0};
	//µÁ◊Ë±Ì
	if(dianzu >= DIANZU160 && dianzu <= DIANZU0){
		if(dianzu > DIANZU1 && dianzu <= DIANZU0){
			sprintf(display,"-40");
			wendu = -40 + ((DIANZU0 - dianzu) / ((DIANZU0 - DIANZU1) / 10)) / 10 - 8.3;
		}
		else if(dianzu > DIANZU2 && dianzu <= DIANZU1){
			sprintf(display,"-39");
			wendu = -39 + ((DIANZU1 - dianzu) / ((DIANZU1 - DIANZU2) / 10)) / 10 - 8.1;
		}
		else if(dianzu > DIANZU3 && dianzu <= DIANZU2){
			sprintf(display,"-38");
			wendu = -38 + ((DIANZU2 - dianzu) / ((DIANZU2 - DIANZU3) / 10)) / 10 - 7.9;
		}
		else if(dianzu > DIANZU4 && dianzu <= DIANZU3){
			sprintf(display,"-37");
			wendu = -37 + ((DIANZU3 - dianzu) / ((DIANZU3 - DIANZU4) / 10)) / 10 - 7.7;
		}
		else if(dianzu > DIANZU5 && dianzu <= DIANZU4){
			sprintf(display,"-36");
			wendu = -36 + ((DIANZU4 - dianzu) / ((DIANZU4 - DIANZU5) / 10)) / 10 - 7.5;
		}
		else if(dianzu > DIANZU6 && dianzu <= DIANZU5){
			sprintf(display,"-35");
			wendu = -35 + ((DIANZU5 - dianzu) / ((DIANZU5 - DIANZU6) / 10)) / 10 - 7.3;
		}
		else if(dianzu > DIANZU7 && dianzu <= DIANZU6){
			sprintf(display,"-34");
			wendu = -34 + ((DIANZU6 - dianzu) / ((DIANZU6 - DIANZU7) / 10)) / 10 - 7.1;
		}
		else if(dianzu > DIANZU8 && dianzu <= DIANZU7){
			sprintf(display,"-33");
			wendu = -33 + ((DIANZU7 - dianzu) / ((DIANZU7 - DIANZU8) / 10)) / 10 - 6.9;
		}
		else if(dianzu > DIANZU9 && dianzu <= DIANZU8){
			sprintf(display,"-32");
			wendu = -32 + ((DIANZU8 - dianzu) / ((DIANZU8 - DIANZU9) / 10)) / 10 - 6.7;
		}
		else if(dianzu > DIANZU10 && dianzu <= DIANZU9){
			sprintf(display,"-31");
			wendu = -31 + ((DIANZU9 - dianzu) / ((DIANZU9 - DIANZU10) / 10)) / 10 - 6.5;
		}
		else if(dianzu > DIANZU11 && dianzu <= DIANZU10){
			sprintf(display,"-30");
			wendu = -30 + ((DIANZU10 - dianzu) / ((DIANZU10 - DIANZU11) / 10)) / 10 - 6.3;
		}
		else if(dianzu > DIANZU12 && dianzu <= DIANZU11){
			sprintf(display,"-29");
			wendu = -29 + ((DIANZU11 - dianzu) / ((DIANZU11 - DIANZU12) / 10)) / 10 - 6.1;
		}
		else if(dianzu > DIANZU13 && dianzu <= DIANZU12){
			sprintf(display,"-28");
			wendu = -28 + ((DIANZU12 - dianzu) / ((DIANZU12 - DIANZU13) / 10)) / 10 - 5.9;
		}
		else if(dianzu > DIANZU14 && dianzu <= DIANZU13){
			sprintf(display,"-27");
			wendu = -27 + ((DIANZU13 - dianzu) / ((DIANZU13 - DIANZU14) / 10)) / 10 - 5.7;
		}
		else if(dianzu > DIANZU15 && dianzu <= DIANZU14){
			sprintf(display,"-26");
			wendu = -26 + ((DIANZU14 - dianzu) / ((DIANZU14 - DIANZU15) / 10)) / 10 - 10.5;
		}
		else if(dianzu > DIANZU16 && dianzu <= DIANZU15){
			sprintf(display,"-25");
			wendu = -25 + ((DIANZU15 - dianzu) / ((DIANZU15 - DIANZU16) / 10)) / 10 - 10.7;//-35.7
		}
		else if(dianzu > DIANZU17 && dianzu <= DIANZU16){
			sprintf(display,"-24");
			wendu = -24 + ((DIANZU16 - dianzu) / ((DIANZU16 - DIANZU17) / 10)) / 10 - 10;//–ﬁ∏ƒÕÌ…œ-34
		}
		else if(dianzu > DIANZU18 && dianzu <= DIANZU17){
			sprintf(display,"-23");
			wendu = -23 + ((DIANZU17 - dianzu) / ((DIANZU17 - DIANZU18) / 10)) / 10 - 9.2;//-32.2
		}
		else if(dianzu > DIANZU19 && dianzu <= DIANZU18){
			sprintf(display,"-22");
			wendu = -22 + ((DIANZU18 - dianzu) / ((DIANZU18 - DIANZU19) / 10)) / 10 - 8.5;//-30.5
		}
		else if(dianzu > DIANZU20 && dianzu <= DIANZU19){
			sprintf(display,"-21");
			wendu = -21 + ((DIANZU19 - dianzu) / ((DIANZU19 - DIANZU20) / 10)) / 10 - 7.9;//-28.9
		}
		else if(dianzu > DIANZU21 && dianzu <= DIANZU20){
			sprintf(display,"-20");
			wendu = -20 + ((DIANZU20 - dianzu) / ((DIANZU20 - DIANZU21) / 10)) / 10 - 7.5;//-27.5
		}
		else if(dianzu > DIANZU22 && dianzu <= DIANZU21){
			sprintf(display,"-19");
			wendu = -19 + ((DIANZU21 - dianzu) / ((DIANZU21 - DIANZU22) / 10)) / 10 - 6.9;//-25.9
		}
		else if(dianzu > DIANZU23 && dianzu <= DIANZU22){
			sprintf(display,"-18");
			wendu = -18 + ((DIANZU22 - dianzu) / ((DIANZU22 - DIANZU23) / 10)) / 10 - 6.4;//-24.4
		}
		else if(dianzu > DIANZU24 && dianzu <= DIANZU23){
			sprintf(display,"-17");
			wendu = -17 + ((DIANZU23 - dianzu) / ((DIANZU23 - DIANZU24) / 10)) / 10 - 6;//-23
		}
		else if(dianzu > DIANZU25 && dianzu <= DIANZU24){
			sprintf(display,"-16");
			wendu = -16 + ((DIANZU24 - dianzu) / ((DIANZU24 - DIANZU25) / 10)) / 10 - 5.7;//-21,7
		}
		else if(dianzu > DIANZU26 && dianzu <= DIANZU25){
			sprintf(display,"-15");
			wendu = -15 + ((DIANZU25 - dianzu) / ((DIANZU25 - DIANZU26) / 10)) / 10 - 5.2;//-20.3
		}
		else if(dianzu > DIANZU27 && dianzu <= DIANZU26){
			sprintf(display,"-14");
			wendu = -14 + ((DIANZU26 - dianzu) / ((DIANZU26 - DIANZU27) / 10)) / 10 - 5;//-18.3
		}
		else if(dianzu > DIANZU28 && dianzu <= DIANZU27){
			sprintf(display,"-13");
			wendu = -13 + ((DIANZU27 - dianzu) / ((DIANZU27 - DIANZU28) / 10)) / 10 - 4.1;//17.1
		}
		else if(dianzu > DIANZU29 && dianzu <= DIANZU28){
			sprintf(display,"-12");
			wendu = -12 + ((DIANZU28 - dianzu) / ((DIANZU28 - DIANZU29) / 10)) / 10 - 3.8;//-15.8
		}
		else if(dianzu > DIANZU30 && dianzu <= DIANZU29){
			sprintf(display,"-11");
			wendu = -11 + ((DIANZU29 - dianzu) / ((DIANZU29 - DIANZU30) / 10)) / 10 - 3.4;//-14.4
		}
		else if(dianzu > DIANZU31 && dianzu <= DIANZU30){
			sprintf(display,"-10");
			wendu = (-10 + ((DIANZU30 - dianzu) / ((DIANZU30 - DIANZU31) / 10)) / 10 - 3.1);//-13.1“‘…œ---∂‘µƒ
		}
		else if(dianzu > DIANZU32 && dianzu <= DIANZU31){
			sprintf(display," -9");
			wendu = (-9 + ((DIANZU31 - dianzu) / ((DIANZU31 - DIANZU32) / 10)) / 10 - 2.7);//-11.7“‘…œ
		}
		else if(dianzu > DIANZU33 && dianzu <= DIANZU32){
			sprintf(display," -8");
			wendu = (-8 + ((DIANZU32 - dianzu) / ((DIANZU32 - DIANZU33) / 10)) / 10 - 2.5);//-10.5“‘…œ
		}
		else if(dianzu > DIANZU34 && dianzu <= DIANZU33){
			sprintf(display," -7");
			wendu = (-7 + ((DIANZU33 - dianzu) / ((DIANZU33 - DIANZU34) / 10)) / 10 - 2.3);//-9.3
		}
		else if(dianzu > DIANZU35 && dianzu <= DIANZU34){
			sprintf(display," -6");
			wendu = (-6 + ((DIANZU34 - dianzu) / ((DIANZU34 - DIANZU35) / 10)) / 10 - 2.1);//-8.1
		}
		else if(dianzu > DIANZU36 && dianzu <= DIANZU35){
			sprintf(display," -5");
			wendu = (-5 + ((DIANZU35 - dianzu) / ((DIANZU35 - DIANZU36) / 10)) / 10 - 1.8);//-6.8
		}
		else if(dianzu > DIANZU37 && dianzu <= DIANZU36){
			sprintf(display," -4");
			wendu = (-4 + ((DIANZU36 - dianzu) / ((DIANZU36 - DIANZU37) / 10)) / 10 - 1.5);//-5.5
		}
		else if(dianzu > DIANZU38 && dianzu <= DIANZU37){
			sprintf(display," -3");
			wendu = (-3 + ((DIANZU37 - dianzu) / ((DIANZU37 - DIANZU38) / 10)) / 10 - 1.2);//-4.2
		}
		else if(dianzu > DIANZU39 && dianzu <= DIANZU38){
			sprintf(display," -2");
			wendu = -2 + ((DIANZU38 - dianzu) / ((DIANZU38 - DIANZU39) / 10)) / 10 - 0.9;//-2.9
		}
		else if(dianzu > DIANZU40 && dianzu <= DIANZU39){
			sprintf(display," -1");
			wendu = -1 + ((DIANZU39 - dianzu) / ((DIANZU39 - DIANZU40) / 10)) / 10 - 0.7;//-1.7
		}
		else if(dianzu > DIANZU41 && dianzu <= DIANZU40){
			sprintf(display,"  0");
			wendu = 0 + ((DIANZU40 - dianzu) / ((DIANZU40 - DIANZU41) / 10)) / 10 - 0.8;//-0.8“‘…œ
		}
		else if(dianzu > DIANZU42 && dianzu <= DIANZU41){
			sprintf(display,"  1");
			wendu = 1 + ((DIANZU41 - dianzu) / ((DIANZU41 - DIANZU42) / 10)) / 10 - 0.9;//0.1“‘…œ
		}
		else if(dianzu > DIANZU43 && dianzu <= DIANZU42){
			sprintf(display,"  2");
			wendu = 2 + ((DIANZU42 - dianzu) / ((DIANZU42 - DIANZU43) / 10)) / 10 - 0.7;//1.3
		}
		else if(dianzu > DIANZU44 && dianzu <= DIANZU43){
			sprintf(display,"  3");
			wendu = 3 + ((DIANZU43 - dianzu) / ((DIANZU43 - DIANZU44) / 10)) / 10 - 0.4;
		}
		else if(dianzu > DIANZU45 && dianzu <= DIANZU44){
			sprintf(display,"  4");
			wendu = 4 + ((DIANZU44 - dianzu) / ((DIANZU44 - DIANZU45) / 10)) / 10 - 0.2;
		}
		else if(dianzu > DIANZU46 && dianzu <= DIANZU45){
			sprintf(display,"  5");
			wendu = 5 + ((DIANZU45 - dianzu) / ((DIANZU45 - DIANZU46) / 10)) / 10;
		}
		else if(dianzu > DIANZU47 && dianzu <= DIANZU46){
			sprintf(display,"  6");
			wendu = 6 + ((DIANZU46 - dianzu) / ((DIANZU46 - DIANZU47) / 10)) / 10 + 0.1;
		}
		else if(dianzu > DIANZU48 && dianzu <= DIANZU47){
			sprintf(display,"  7");
			wendu = 7 + ((DIANZU47 - dianzu) / ((DIANZU47 - DIANZU48) / 10)) / 10 + 0.3;
		}
		else if(dianzu > DIANZU49 && dianzu <= DIANZU48){
			sprintf(display,"  8");
			wendu = 8 + ((DIANZU48 - dianzu) / ((DIANZU48 - DIANZU49) / 10)) / 10 + 0.5;
		}
		else if(dianzu > DIANZU50 && dianzu <= DIANZU49){
			sprintf(display,"  9");
			wendu = 9 + ((DIANZU49 - dianzu) / ((DIANZU49 - DIANZU50) / 10)) / 10 + 0.8;
		}
		else if(dianzu > DIANZU51 && dianzu <= DIANZU50){
			sprintf(display," 10");
			wendu = 10 + ((DIANZU50 - dianzu) / ((DIANZU50 - DIANZU51) / 10)) / 10 + 1.2;
		}
		else if(dianzu > DIANZU52 && dianzu <= DIANZU51){
			sprintf(display," 11");
			wendu = 11 + ((DIANZU51 - dianzu) / ((DIANZU51 - DIANZU52) / 10)) / 10 + 1.3;
		}
		else if(dianzu > DIANZU53 && dianzu <= DIANZU52){
			sprintf(display," 12");
			wendu = 12 + ((DIANZU52 - dianzu) / ((DIANZU52 - DIANZU53) / 10)) / 10 + 1.6;
		}
		else if(dianzu > DIANZU54 && dianzu <= DIANZU53){
			sprintf(display," 13");
			wendu = 13 + ((DIANZU53 - dianzu) / ((DIANZU53 - DIANZU54) / 10)) / 10 + 1.7;
		}
		else if(dianzu > DIANZU55 && dianzu <= DIANZU54){
			sprintf(display," 14");
			wendu = 14 + ((DIANZU54 - dianzu) / ((DIANZU54 - DIANZU55) / 10)) / 10 + 1.9;
		}
		else if(dianzu > DIANZU56 && dianzu <= DIANZU55){
			sprintf(display," 15");
			wendu = 15 + ((DIANZU55 - dianzu) / ((DIANZU55 - DIANZU56) / 10)) / 10 + 2.2;
		}
		else if(dianzu > DIANZU57 && dianzu <= DIANZU56){
			sprintf(display," 16");
			wendu = 16 + ((DIANZU56 - dianzu) / ((DIANZU56 - DIANZU57) / 10)) / 10 + 2.4;
		}
		else if(dianzu > DIANZU58 && dianzu <= DIANZU57){
			sprintf(display," 17");
			wendu = 17 + ((DIANZU57 - dianzu) / ((DIANZU57 - DIANZU58) / 10)) / 10 + 2.7;
		}
		else if(dianzu > DIANZU59 && dianzu <= DIANZU58){
			sprintf(display," 18");
			wendu = 18 + ((DIANZU58 - dianzu) / ((DIANZU58 - DIANZU59) / 10)) / 10 + 2.9;
		}
		else if(dianzu > DIANZU60 && dianzu <= DIANZU59){
			sprintf(display," 19");
			wendu = 19 + ((DIANZU59 - dianzu) / ((DIANZU59 - DIANZU60) / 10)) / 10 + 3.2;
		}
		else if(dianzu > DIANZU61 && dianzu <= DIANZU60){
			sprintf(display," 20");
			wendu = 20 + ((DIANZU60 - dianzu) / ((DIANZU60 - DIANZU61) / 10)) / 10 + 3.3;
		}
		else if(dianzu > DIANZU62 && dianzu <= DIANZU61){
			sprintf(display," 21");
			wendu = 21 + ((DIANZU61 - dianzu) / ((DIANZU61 - DIANZU62) / 10)) / 10 + 3.5;
		}
		else if(dianzu > DIANZU63 && dianzu <= DIANZU62){
			sprintf(display," 22");
			wendu = 22 + ((DIANZU62 - dianzu) / ((DIANZU62 - DIANZU63) / 10)) / 10 + 3.7;
		}
		else if(dianzu > DIANZU64 && dianzu <= DIANZU63){
			sprintf(display," 23");
			wendu = 23 + ((DIANZU63 - dianzu) / ((DIANZU63 - DIANZU64) / 10)) / 10 + 3.9;
		}
		else if(dianzu > DIANZU65 && dianzu <= DIANZU64){
			sprintf(display," 24");
			wendu = 24 + ((DIANZU64 - dianzu) / ((DIANZU64 - DIANZU65) / 10)) / 10 + 4.2;
		}
		else if(dianzu > DIANZU66 && dianzu <= DIANZU65){
			sprintf(display," 25");
			wendu = 25 + ((DIANZU65 - dianzu) / ((DIANZU65 - DIANZU66) / 10)) / 10 + 4.5;
		}
		else if(dianzu > DIANZU67 && dianzu <= DIANZU66){
			sprintf(display," 26");
			wendu = 26 + ((DIANZU66 - dianzu) / ((DIANZU66 - DIANZU67) / 10)) / 10 + 4.8;
		}
		else if(dianzu > DIANZU68 && dianzu <= DIANZU67){
			sprintf(display," 27");
			wendu = 27 + ((DIANZU67 - dianzu) / ((DIANZU67 - DIANZU68) / 10)) / 10 + 5.1;
		}
		else if(dianzu > DIANZU69 && dianzu <= DIANZU68){
			sprintf(display," 28");
			wendu = 28 + ((DIANZU68 - dianzu) / ((DIANZU68 - DIANZU69) / 10)) / 10 + 5.4;
		}
		else if(dianzu > DIANZU70 && dianzu <= DIANZU69){
			sprintf(display," 29");
			wendu = 29 + ((DIANZU69 - dianzu) / ((DIANZU69 - DIANZU70) / 10)) / 10 + 5.8;
		}
		else if(dianzu > DIANZU71 && dianzu <= DIANZU70){
			sprintf(display," 30");
			wendu = 30 + ((DIANZU70 - dianzu) / ((DIANZU70 - DIANZU71) / 10)) / 10 + 6.1;
		}
		else if(dianzu > DIANZU72 && dianzu <= DIANZU71){
			sprintf(display," 31");
			wendu = 31 + ((DIANZU71 - dianzu) / ((DIANZU71 - DIANZU72) / 10)) / 10 + 6.4;
		}
		else if(dianzu > DIANZU73 && dianzu <= DIANZU72){
			sprintf(display," 32");
			wendu = 32 + ((DIANZU72 - dianzu) / ((DIANZU72 - DIANZU73) / 10)) / 10 + 6.8;
		}
		else if(dianzu > DIANZU74 && dianzu <= DIANZU73){
			sprintf(display," 33");
			wendu = 33 + ((DIANZU73 - dianzu) / ((DIANZU73 - DIANZU74) / 10)) / 10 + 7.2;
		}
		else if(dianzu > DIANZU75 && dianzu <= DIANZU74){
			sprintf(display," 34");
			wendu = 34 + ((DIANZU74 - dianzu) / ((DIANZU74 - DIANZU75) / 10)) / 10 + 7.5;
		}
		else if(dianzu > DIANZU76 && dianzu <= DIANZU75){
			sprintf(display," 35");
			wendu = 35 + ((DIANZU75 - dianzu) / ((DIANZU75 - DIANZU76) / 10)) / 10 + 7.8;
		}
		else if(dianzu > DIANZU77 && dianzu <= DIANZU76){
			sprintf(display," 36");
			wendu = 36 + ((DIANZU76 - dianzu) / ((DIANZU76 - DIANZU77) / 10)) / 10 + 8.2;
		}
		else if(dianzu > DIANZU78 && dianzu <= DIANZU77){
			sprintf(display," 37");
			wendu = 37 + ((DIANZU77 - dianzu) / ((DIANZU77 - DIANZU78) / 10)) / 10 + 8.6;
		}
		else if(dianzu > DIANZU79 && dianzu <= DIANZU78){
			sprintf(display," 38");
			wendu = 38 + ((DIANZU78 - dianzu) / ((DIANZU78 - DIANZU79) / 10)) / 10 + 9;
		}
		else if(dianzu > DIANZU80 && dianzu <= DIANZU79){
			sprintf(display," 39");
			wendu = 39 + ((DIANZU79 - dianzu) / ((DIANZU79 - DIANZU80) / 10)) / 10 + 9.3;
		}
		else if(dianzu > DIANZU81 && dianzu <= DIANZU80){
			sprintf(display," 40");
			wendu = 40 + ((DIANZU80 - dianzu) / ((DIANZU80 - DIANZU81) / 10)) / 10 + 9.7;
		}
		else if(dianzu > DIANZU82 && dianzu <= DIANZU81){
			sprintf(display," 41");
			wendu = 41 + ((DIANZU81 - dianzu) / ((DIANZU81 - DIANZU82) / 10)) / 10 + 10.2;
		}
		else if(dianzu > DIANZU83 && dianzu <= DIANZU82){
			sprintf(display," 42");
			wendu = 42 + ((DIANZU82 - dianzu) / ((DIANZU82 - DIANZU83) / 10)) / 10 + 10.6;
		}
		else if(dianzu > DIANZU84 && dianzu <= DIANZU83){
			sprintf(display," 43");
			wendu = 43 + ((DIANZU83 - dianzu) / ((DIANZU83 - DIANZU84) / 10)) / 10 + 11.1;
		}
		else if(dianzu > DIANZU85 && dianzu <= DIANZU84){
			sprintf(display," 44");
			wendu = 44 + ((DIANZU84 - dianzu) / ((DIANZU84 - DIANZU85) / 10)) / 10 + 11.7;
		}
		else if(dianzu > DIANZU86 && dianzu <= DIANZU85){
			sprintf(display," 45");
			wendu = 45 + ((DIANZU85 - dianzu) / ((DIANZU85 - DIANZU86) / 10)) / 10 + 12.2;
		}
		else if(dianzu > DIANZU87 && dianzu <= DIANZU86){
			sprintf(display," 46");
			wendu = 46 + ((DIANZU86 - dianzu) / ((DIANZU86 - DIANZU87) / 10)) / 10 + 12.8;
		}
		else if(dianzu > DIANZU88 && dianzu <= DIANZU87){
			sprintf(display," 47");
			wendu = 47 + ((DIANZU87 - dianzu) / ((DIANZU87 - DIANZU88) / 10)) / 10 + 13.3;
		}
		else if(dianzu > DIANZU89 && dianzu <= DIANZU88){
			sprintf(display," 48");
			wendu = 48 + ((DIANZU88 - dianzu) / ((DIANZU88 - DIANZU89) / 10)) / 10 + 14;
		}
		else if(dianzu > DIANZU90 && dianzu <= DIANZU89){
			sprintf(display," 49");
			wendu = 49 + ((DIANZU89 - dianzu) / ((DIANZU89 - DIANZU90) / 10)) / 10 + 14.7;
		}
		else if(dianzu > DIANZU91 && dianzu <= DIANZU90){
			sprintf(display," 50");
			wendu = 50 + ((DIANZU90 - dianzu) / ((DIANZU90 - DIANZU91) / 10)) / 10 + 15.5;
		}
		else if(dianzu > DIANZU92 && dianzu <= DIANZU91){
			sprintf(display," 51");
			wendu = 51 + ((DIANZU91 - dianzu) / ((DIANZU91 - DIANZU92) / 10)) / 10 + 16.2;
		}
		else if(dianzu > DIANZU93 && dianzu <= DIANZU92){
			sprintf(display," 52");
			wendu = 52 + ((DIANZU92 - dianzu) / ((DIANZU92 - DIANZU93) / 10)) / 10 + 16.8;
		}
		else if(dianzu > DIANZU94 && dianzu <= DIANZU93){
			sprintf(display," 53");
			wendu = 53 + ((DIANZU93 - dianzu) / ((DIANZU93 - DIANZU94) / 10)) / 10 + 17.7;
		}
		else if(dianzu > DIANZU95 && dianzu <= DIANZU94){
			sprintf(display," 54");
			wendu = 54 + ((DIANZU94 - dianzu) / ((DIANZU94 - DIANZU95) / 10)) / 10 + 18.7;
		}
		else if(dianzu > DIANZU96 && dianzu <= DIANZU95){
			sprintf(display," 55");
			wendu = 55 + ((DIANZU95 - dianzu) / ((DIANZU95 - DIANZU96) / 10)) / 10 + 19.5;
		}
		else if(dianzu > DIANZU97 && dianzu <= DIANZU96){
			sprintf(display," 56");
			wendu = 56 + ((DIANZU96 - dianzu) / ((DIANZU96 - DIANZU97) / 10)) / 10 + 20.5;
		}
		else if(dianzu > DIANZU98 && dianzu <= DIANZU97){
			sprintf(display," 57");
			wendu = 57 + ((DIANZU97 - dianzu) / ((DIANZU97 - DIANZU98) / 10)) / 10 + 21.5;
		}
		else if(dianzu > DIANZU99 && dianzu <= DIANZU98){
			sprintf(display," 58");
			wendu = 58 + ((DIANZU98 - dianzu) / ((DIANZU98 - DIANZU99) / 10)) / 10 + 22.6;
		}
		else if(dianzu > DIANZU100 && dianzu <= DIANZU99){
			sprintf(display," 59");
			wendu = 59 + ((DIANZU99 - dianzu) / ((DIANZU99 - DIANZU100) / 10)) / 10 + 23.7;
		}
		else if(dianzu > DIANZU101 && dianzu <= DIANZU100){
			sprintf(display," 60");
			wendu = 60 + ((DIANZU100 - dianzu) / ((DIANZU100 - DIANZU101) / 10)) / 10 + 24.2;
		}
		else if(dianzu > DIANZU102 && dianzu <= DIANZU101){
			sprintf(display," 61");
			wendu = 61 + ((DIANZU101 - dianzu) / ((DIANZU101 - DIANZU102) / 10)) / 10 + 25.5;
		}
		else if(dianzu > DIANZU103 && dianzu <= DIANZU102){
			sprintf(display," 62");
			wendu = 62 + ((DIANZU102 - dianzu) / ((DIANZU102 - DIANZU103) / 10)) / 10 + 27.8;
		}
		else if(dianzu > DIANZU104 && dianzu <= DIANZU103){
			sprintf(display," 63");
			wendu = 63 + ((DIANZU103 - dianzu) / ((DIANZU103 - DIANZU104) / 10)) / 10 + 29.3;
		}
		else if(dianzu > DIANZU105 && dianzu <= DIANZU104){
			sprintf(display," 64");
			wendu = 64 + ((DIANZU104 - dianzu) / ((DIANZU104 - DIANZU105) / 10)) / 10 + 31.3;
		}
		else if(dianzu > DIANZU106 && dianzu <= DIANZU105){
			sprintf(display," 65");
			wendu = 65 + ((DIANZU105 - dianzu) / ((DIANZU105 - DIANZU106) / 10)) / 10 + 32.6;
		}
		else if(dianzu > DIANZU107 && dianzu <= DIANZU106){
			sprintf(display," 66");
			wendu = 66 + ((DIANZU106 - dianzu) / ((DIANZU106 - DIANZU107) / 10)) / 10 + 33.7;
		}
		else if(dianzu > DIANZU108 && dianzu <= DIANZU107){
			sprintf(display," 67");
			wendu = 67 + ((DIANZU107 - dianzu) / ((DIANZU107 - DIANZU108) / 10)) / 10 + 35.7;
		}
		else if(dianzu > DIANZU109 && dianzu <= DIANZU108){
			sprintf(display," 68");
			wendu = 68 + ((DIANZU108 - dianzu) / ((DIANZU108 - DIANZU109) / 10)) / 10;
		}
		else if(dianzu > DIANZU110 && dianzu <= DIANZU109){
			sprintf(display," 69");
			wendu = 69 + ((DIANZU109 - dianzu) / ((DIANZU109 - DIANZU110) / 10)) / 10;
		}
		else if(dianzu > DIANZU111 && dianzu <= DIANZU110){
			sprintf(display," 70");
			wendu = 70 + ((DIANZU110 - dianzu) / ((DIANZU110 - DIANZU111) / 10)) / 10;
		}
		else if(dianzu > DIANZU112 && dianzu <= DIANZU111){
			sprintf(display," 71");
			wendu = 71 + ((DIANZU111 - dianzu) / ((DIANZU111 - DIANZU112) / 10)) / 10;
		}
		else if(dianzu > DIANZU113 && dianzu <= DIANZU112){
			sprintf(display," 72");
			wendu = 72 + ((DIANZU112 - dianzu) / ((DIANZU112 - DIANZU113) / 10)) / 10;
		}
		else if(dianzu > DIANZU114 && dianzu <= DIANZU113){
			sprintf(display," 73");
			wendu = 73 + ((DIANZU113 - dianzu) / ((DIANZU113 - DIANZU114) / 10)) / 10;
		}
		else if(dianzu > DIANZU115 && dianzu <= DIANZU114){
			sprintf(display," 74");
			wendu = 74 + ((DIANZU114 - dianzu) / ((DIANZU114 - DIANZU115) / 10)) / 10;
		}
		else if(dianzu > DIANZU116 && dianzu <= DIANZU115){
			sprintf(display," 75");
			wendu = 75 + ((DIANZU115 - dianzu) / ((DIANZU115 - DIANZU116) / 10)) / 10;
		}
		else if(dianzu > DIANZU117 && dianzu <= DIANZU116){
			sprintf(display," 76");
			wendu = 76 + ((DIANZU116 - dianzu) / ((DIANZU116 - DIANZU117) / 10)) / 10;
		}
		else if(dianzu > DIANZU118 && dianzu <= DIANZU117){
			sprintf(display," 77");
			wendu = 77 + ((DIANZU117 - dianzu) / ((DIANZU117 - DIANZU118) / 10)) / 10;
		}
		else if(dianzu > DIANZU119 && dianzu <= DIANZU118){
			sprintf(display," 78");
			wendu = 78 + ((DIANZU118 - dianzu) / ((DIANZU118 - DIANZU119) / 10)) / 10;
		}
		else if(dianzu > DIANZU120 && dianzu <= DIANZU119){
			sprintf(display," 79");
			wendu = 79 + ((DIANZU119 - dianzu) / ((DIANZU119 - DIANZU120) / 10)) / 10;
		}
		else if(dianzu > DIANZU121 && dianzu <= DIANZU120){
			sprintf(display," 80");
			wendu = 80 + ((DIANZU120 - dianzu) / ((DIANZU120 - DIANZU121) / 10)) / 10;
		}
		else if(dianzu > DIANZU122 && dianzu <= DIANZU121){
			sprintf(display," 81");
			wendu = 81 + ((DIANZU121 - dianzu) / ((DIANZU121 - DIANZU122) / 10)) / 10;
		}
		else if(dianzu > DIANZU123 && dianzu <= DIANZU122){
			sprintf(display," 82");
			wendu = 82 + ((DIANZU122 - dianzu) / ((DIANZU122 - DIANZU123) / 10)) / 10;
		}
		else if(dianzu > DIANZU124 && dianzu <= DIANZU123){
			sprintf(display," 83");
			wendu = 83 + ((DIANZU123 - dianzu) / ((DIANZU123 - DIANZU124) / 10)) / 10;
		}
		else if(dianzu > DIANZU125 && dianzu <= DIANZU124){
			sprintf(display," 84");
			wendu = 84 + ((DIANZU124 - dianzu) / ((DIANZU124 - DIANZU125) / 10)) / 10;
		}
		else if(dianzu > DIANZU126 && dianzu <= DIANZU125){
			sprintf(display," 85");
			wendu = 85 + ((DIANZU125 - dianzu) / ((DIANZU125 - DIANZU126) / 10)) / 10;
		}
		else if(dianzu > DIANZU127 && dianzu <= DIANZU126){
			sprintf(display," 86");
			wendu = 86 + ((DIANZU126 - dianzu) / ((DIANZU126 - DIANZU127) / 10)) / 10;
		}
		else if(dianzu > DIANZU128 && dianzu <= DIANZU127){
			sprintf(display," 87");
			wendu = 87 + ((DIANZU127 - dianzu) / ((DIANZU127 - DIANZU128) / 10)) / 10;
		}
		else if(dianzu > DIANZU129 && dianzu <= DIANZU128){
			sprintf(display," 88");
			wendu = 88 + ((DIANZU128 - dianzu) / ((DIANZU128 - DIANZU129) / 10)) / 10;
		}
		else if(dianzu > DIANZU130 && dianzu <= DIANZU129){
			sprintf(display," 89");
			wendu = 89 + ((DIANZU129 - dianzu) / ((DIANZU129 - DIANZU130) / 10)) / 10;
		}
		else if(dianzu > DIANZU131 && dianzu <= DIANZU130){
			sprintf(display," 90");
			wendu = 90 + ((DIANZU130 - dianzu) / ((DIANZU130 - DIANZU131) / 10)) / 10;
		}
		else if(dianzu > DIANZU132 && dianzu <= DIANZU131){
			sprintf(display," 91");
			wendu = 91 + ((DIANZU131 - dianzu) / ((DIANZU131 - DIANZU132) / 10)) / 10;
		}
		else if(dianzu > DIANZU133 && dianzu <= DIANZU132){
			sprintf(display," 92");
			wendu = 92 + ((DIANZU132 - dianzu) / ((DIANZU132 - DIANZU133) / 10)) / 10;
		}
		else if(dianzu > DIANZU134 && dianzu <= DIANZU133){
			sprintf(display," 93");
			wendu = 93 + ((DIANZU133 - dianzu) / ((DIANZU133 - DIANZU134) / 10)) / 10;
		}
		else if(dianzu > DIANZU135 && dianzu <= DIANZU134){
			sprintf(display," 94");
			wendu = 94 + ((DIANZU134 - dianzu) / ((DIANZU134 - DIANZU135) / 10)) / 10;
		}
		else if(dianzu > DIANZU136 && dianzu <= DIANZU135){
			sprintf(display," 95");
			wendu = 95 + ((DIANZU135 - dianzu) / ((DIANZU135 - DIANZU136) / 10)) / 10;
		}
		else if(dianzu > DIANZU137 && dianzu <= DIANZU136){
			sprintf(display," 96");
			wendu = 96 + ((DIANZU136 - dianzu) / ((DIANZU136 - DIANZU137) / 10)) / 10;
		}
		else if(dianzu > DIANZU138 && dianzu <= DIANZU137){
			sprintf(display," 97");
			wendu = 97 + ((DIANZU137 - dianzu) / ((DIANZU137 - DIANZU138) / 10)) / 10;
		}
		else if(dianzu > DIANZU139 && dianzu <= DIANZU138){
			sprintf(display," 98");
			wendu = 98 + ((DIANZU138 - dianzu) / ((DIANZU138 - DIANZU139) / 10)) / 10;
		}
		else if(dianzu > DIANZU140 && dianzu <= DIANZU139){
			sprintf(display," 99");
			wendu = 99 + ((DIANZU139 - dianzu) / ((DIANZU139 - DIANZU140) / 10)) / 10;
		}
		else if(dianzu > DIANZU141 && dianzu <= DIANZU140){
			sprintf(display,"100");
			wendu = 100 + ((DIANZU140 - dianzu) / ((DIANZU140 - DIANZU141) / 10)) / 10;
		}
		else if(dianzu > DIANZU142 && dianzu <= DIANZU141){
			sprintf(display,"101");
			wendu = 101 + ((DIANZU141 - dianzu) / ((DIANZU141 - DIANZU142) / 10)) / 10;
		}
		else if(dianzu > DIANZU143 && dianzu <= DIANZU142){
			sprintf(display,"102");
			wendu = 102 + ((DIANZU142 - dianzu) / ((DIANZU142 - DIANZU143) / 10)) / 10;
		}
		else if(dianzu > DIANZU144 && dianzu <= DIANZU143){
			sprintf(display,"103");
			wendu = 103 + ((DIANZU143 - dianzu) / ((DIANZU143 - DIANZU144) / 10)) / 10;
		}
		else if(dianzu > DIANZU145 && dianzu <= DIANZU144){
			sprintf(display,"104");
			wendu = 104 + ((DIANZU144 - dianzu) / ((DIANZU144 - DIANZU145) / 10)) / 10;
		}
		else if(dianzu > DIANZU146 && dianzu <= DIANZU145){
			sprintf(display,"105");
			wendu = 105 + ((DIANZU145 - dianzu) / ((DIANZU145 - DIANZU146) / 10)) / 10;
		}
		else if(dianzu > DIANZU147 && dianzu <= DIANZU146){
			sprintf(display,"106");
			wendu = 106 + ((DIANZU146 - dianzu) / ((DIANZU146 - DIANZU147) / 10)) / 10;
		}
		else if(dianzu > DIANZU148 && dianzu <= DIANZU147){
			sprintf(display,"107");
			wendu = 107 + ((DIANZU147 - dianzu) / ((DIANZU147 - DIANZU148) / 10)) / 10;
		}
		else if(dianzu > DIANZU149 && dianzu <= DIANZU148){
			sprintf(display,"108");
			wendu = 108 + ((DIANZU148 - dianzu) / ((DIANZU148 - DIANZU149) / 10)) / 10;
		}
		else if(dianzu > DIANZU150 && dianzu <= DIANZU149){
			sprintf(display,"109");
			wendu = 109 + ((DIANZU149 - dianzu) / ((DIANZU149 - DIANZU150) / 10)) / 10;
		}
		else if(dianzu > DIANZU151 && dianzu <= DIANZU150){
			sprintf(display,"110");
			wendu = 110 + ((DIANZU150 - dianzu) / ((DIANZU150 - DIANZU151) / 10)) / 10;
		}
		else if(dianzu > DIANZU152 && dianzu <= DIANZU151){
			sprintf(display,"111");
			wendu = 111 + ((DIANZU151 - dianzu) / ((DIANZU151 - DIANZU152) / 10)) / 10;
		}
		else if(dianzu > DIANZU153 && dianzu <= DIANZU152){
			sprintf(display,"112");
			wendu = 112 + ((DIANZU152 - dianzu) / ((DIANZU152 - DIANZU153) / 10)) / 10;
		}
		else if(dianzu > DIANZU154 && dianzu <= DIANZU153){
			sprintf(display,"113");
			wendu = 113 + ((DIANZU153 - dianzu) / ((DIANZU153 - DIANZU154) / 10)) / 10;
		}
		else if(dianzu > DIANZU155 && dianzu <= DIANZU154){
			sprintf(display,"114");
			wendu = 114 + ((DIANZU154 - dianzu) / ((DIANZU154 - DIANZU155) / 10)) / 10;
		}
		else if(dianzu > DIANZU156 && dianzu <= DIANZU155){
			sprintf(display,"115");
			wendu = 115 + ((DIANZU155 - dianzu) / ((DIANZU155 - DIANZU156) / 10)) / 10;
		}
		else if(dianzu > DIANZU157 && dianzu <= DIANZU156){
			sprintf(display,"116");
			wendu = 116 + ((DIANZU156 - dianzu) / ((DIANZU156 - DIANZU157) / 10)) / 10;
		}
		else if(dianzu > DIANZU158 && dianzu <= DIANZU157){
			sprintf(display,"117");
			wendu = 117 + ((DIANZU157 - dianzu) / ((DIANZU157 - DIANZU158) / 10)) / 10;
		}
		else if(dianzu > DIANZU159 && dianzu <= DIANZU158){
			sprintf(display,"118");
			wendu = 118 + ((DIANZU158 - dianzu) / ((DIANZU158 - DIANZU159) / 10)) / 10;
		}
		else if(dianzu > DIANZU160 && dianzu <= DIANZU159){
			sprintf(display,"119");
			wendu = 119 + ((DIANZU159 - dianzu) / ((DIANZU159 - DIANZU160) / 10)) / 10;
		}
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)display);
//		sprintf(display,"%.1f",wendu);
//		Lcm_GotoXY(0,1,1);
//		Lcm_Disp_String((unsigned char*)display);
//		HAL_Delay(100);
		return wendu;
	}
	else
		return 0;
}


void display(uint8_t asd)
{
//	if(asd == 0){
//		uint8_t cc1[] = "∫ÍÏ«µÁ◊””–œﬁπ´Àæ";
//		Lcm_GotoXY(0,0,1);
//		Lcm_Disp_String(cc1);
//	}
//	else if(asd == 1){
//		uint8_t cc1[] = "LP";
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String(cc1);
//	}
//	else if(asd == 2){
//		uint8_t cc1[] = "Fill Time Out";
//		Lcm_GotoXY(0,1,0);
//		Lcm_Disp_String(cc1);
//	}
//	else if(asd == 3){
//	
//	}
//	else if(asd == 4){
//	
//	}
//	else if(asd == 5){
//	
//	}
//	else if(asd == 6){
//	
//	}
//	else if(asd == 7){
//	
//	}

}
void Freeze(void)
{
	//ø™√≈—” ±πÿ±’∏∫‘ÿ
	if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin)){
		//√≈¥Úø™¡Àø™ ºº∆À„ ±º‰
		static TIME Door_Oepn;
		Door_Time = GetDiffTime(&Door_Oepn,&bDoor_Open);
		if(Door_Time >= factcp.dAd * 60){
			Compressor_Relay(Off);
			Vaporization_Relay(Off);
			Defrosting_Relay(Off);
			Door_Sign = 1;
			bOften_Start = true;
			bDefrost_Delay0 = true;
			bdrip = true;
			bDefrost_Delay = true;
			bdrip2 = true;
			bFan_Delay = true;
			bfan = true;
			return;
		}
	}
	else{
		Door_Sign = 0;
		bDoor_Open = true;// ±º‰«Â0
	}
	static TIME Com_Time;
	Compressor_Time = GetDiffTime(&Com_Time,&bCom_Delay);
	if(Compressor_Time >= factcp.od *60){	
		if(Door_Sign == 0){
			//º∆À„ ±º‰£¨≥¨π˝…Ë∂®÷µ£¨≤≈ø™ º‘À––
			//factcp.St  —πÀıª˙
			//ÃΩÕ∑¥ÌŒÛ —πÀıª˙‘À◊™øÿ÷∆
			//œ‰Œ¬ÃΩÕ∑¥ÌŒÛ
			if(AdcBuf[4] <= 223 || AdcBuf[5] <= 273){
				chongxin = 1;
				static TIME Probe_Com;
				Probe_Com_Time = GetDiffTime(&Probe_Com, &bProbe_Com);
				if(Probe_Com_Time <= factcp.Cy * 60){
					Compressor_Relay(On);
					//Usart3_Printf("ÃΩÕ∑¥ÌŒÛ‘À◊™ ±º‰:%d\r\n",Probe_Com_Time);
				}
				if(Probe_Com_Time > factcp.Cy * 60 && Probe_Com_Time <= (factcp.Cn + factcp.Cy) * 60){
					Compressor_Relay(Off);
					Usart3_Printf("ÃΩÕ∑¥ÌŒÛÕ£÷π ±º‰:%d\r\n",Probe_Com_Time);
				}
				if(Probe_Com_Time > (factcp.Cn + factcp.Cy) *60)
					bProbe_Com = true;
				Vaporization_Relay(Off);
				Defrosting_Relay(Off);
				return;
			}
			else{
				if(chongxin == 1)
					Compressor_Relay(Off);
				chongxin = 0;
				bProbe_Com = true;
			}
			
			
			if(factdef.dP == 0)
				return;
			else if(Defrost_Delay_Time >= custdef.id * 3600 + factdef.dd * 60)
				return;
			if(flag1 == 1){
				//®Hµƒº∆À„
				//if(custdis.CF){
					if((Case_T_HSD + custcp.ot) > (custcp.St)){
						Compressor_Relay(On);
						//Usart3_Printf("Œ¬∂»£∫%f\r\n%d\r\n",Case,__LINE__);
						flag2 = 1;
					}
					else{
						Compressor_Relay(Off);
						flag1 = 0;
						flag2 = 1;
						Usart3_Printf("Œ¬∂»µÕ£¨—πÀıª˙πÿ±’\r\n");
					}
				//}
				//°Êµƒº∆À„
				/*else{
					if(((Case + (custcp.ot - 32) * 5) / 9) > (((custcp.St - 32) * 5) / 9 + ((custcp.Hy - 32) * 5) / 9)){
						Compressor_Relay(On);
						//Usart3_Printf("Œ¬∂»£∫%f\r\n%d\r\n",Case,__LINE__);
						flag2 = 1;
						//Usart3_Printf("Œ¬∂»∏ﬂ£¨—πÀıª˙¥Úø™\r\n");
					}
					else{
						Compressor_Relay(Off);
						flag1 = 0;
						flag2 = 1;
						Usart3_Printf("Œ¬∂»µÕ£¨—πÀıª˙πÿ±’\r\n");
					}
				}*/
			}
			if((Case_T_HSD + custcp.ot) > (custcp.St + custcp.Hy) && flag2 == 1 && HAL_GPIO_ReadPin(Compressor_Relay_GPIO_Port,Compressor_Relay_Pin) == 0){
				static TIME Often_Start;
				Often_Time = GetDiffTime(&Often_Start,&bOften_Start);
				if(Often_Time >= custcp.AC * 60){
					flag1 = 1;
					flag2 = 0;
					//bCom_Delay = true;
					bOften_Start = true;
					Usart3_Printf(" ±º‰◊„πª\r\n");
				}
				//Usart3_Printf("∑¿∆µ∑±∆Ù∂Ø ±º‰º∆À„:%d\r\n",Often_Time);
			}
		}
	}
}

void Defrost(void)
{
	//»⁄À™ƒ£ Ω---dEF---FAn
	//»⁄À™ÃΩÕ∑£®’Ù∑¢∆˜£©ºÏ≤‚µƒ÷µ «∑Ò‘⁄…Ë∂®÷µ∑∂Œßƒ⁄
	// «	 ∑¢»»π‹°¢∑Áª˙Õ£÷π
	//∑Ò ∑¢»»π‹°¢∑Áª˙‘À◊™
	//œ‰Œ¬ÃΩÕ∑¥ÌŒÛ
	if(AdcBuf[4] <= 223 || AdcBuf[5] <= 273){
		if(AdcBuf[5] <= 273){
			if(vaporerror == 0){
				vaporerror = 1;
				Record_Evap_Probe_alarm++;
			}
		}
		return;
	}
	else{
		if(factdef.dP == 0 && Door_Sign == 0){
			if((Vapor_T_HSD + factcp.oE) < custdef.dE && defrostsign == 0){
				static TIME DefrostDelay0;
				Defrost_Delay0_Time = GetDiffTime(&DefrostDelay0,&bDefrost_Delay0);
				if(Defrost_Delay0_Time >= factdef.dd){
					//—” ±◊„πª
					//ø™∆Ù»⁄À™
					//beforeVapor_T = Vapor_T;
					//Defrosting_Relay(On);
//					bdrip = true;
					if(bedefrost == 0){
						bedefrost = 1;
						if(custdis.CF)
							defrost_temp = Vapor_T_HSD;
						else if(custdis.CF == 0 && custdis.rE)
							defrost_temp = (int)Vapor_T;
						else if(custdis.CF == 0 && custdis.rE == 0)
							defrost_temp = Vapor_T;
					}
					if(factdef.td == 1){
						Defrosting_Relay(On);
						Compressor_Relay(On);
						Vaporization_Relay(Off);
					}
					else if(factdef.td == 0){
						Defrosting_Relay(On);
						Compressor_Relay(Off);
						Vaporization_Relay(Off);
					}
					else{
						Defrosting_Relay(Off);
						Compressor_Relay(Off);
						Vaporization_Relay(On);
					}
					/*if(factdef.dF == 0){
					//œ‘ æø‚Œ¬
						Usart3_Printf("%.1f\r\n",Vapor_T);
	//					Lcm_GotoXY(0,1,1);
	//					char xianshi[20] = {0};
	//					if(custdis.CF)
	//						sprintf(xianshi,"%.0f F",Vapor);
	//					else if(custdis.CF == 0 && custdis.rE)
	//						sprintf(xianshi,"%.0f C",Vapor);
	//					else
	//						sprintf(xianshi,"%.1f C",Vapor);
	//					Lcm_Disp_String((unsigned char*)xianshi);
					}
					else if(factdef.dF == 1){
						char xianshi[10] = {0};
						if(custdis.CF)
							sprintf(xianshi,"%.0f F",defrost_temp);
						else if(custdis.CF == 0 && custdis.rE)
							sprintf(xianshi,"%.0f C",defrost_temp);
						else
							sprintf(xianshi,"%.1f C",defrost_temp);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)xianshi);
						//œ‘ æ∆Ù∂Ø»⁄À™«∞Œ¬∂»
						//Usart3_Printf("»⁄À™∆Ù∂Ø«∞Œ¬∂»:.1f\r\n",beforeVapor_T);
					}
					else if(factdef.dF == 2){
						Lcm_GotoXY(0,1,1);
						char xianshi[10] = {0};
						sprintf(xianshi,"%d F",custdef.dE);
						Lcm_Disp_String((unsigned char*)xianshi);
						//œ‘ æ…Ë∂®Œ¬∂»÷µ
						Usart3_Printf("…Ë∂®Œ¬∂»÷µ:%.1f\r\n",custdef.dE);
					}
					else if(factdef.dF == 3){
						Lcm_GotoXY(0,1,1);
						char xianshi[10] = {0};
						sprintf(xianshi,"dE");
						Lcm_Disp_String((unsigned char*)xianshi);
						//œ‘ ædE
						Usart3_Printf("œ‘ ædE◊÷—˘:dE dE dE\r\n");
					}*/
					if(Defrost_Delay0_Time > (custdef.Md + factdef.dd) * 60){
						//µŒÀÆ ±º‰
						Defrosting_Relay(Off);
						Compressor_Relay(Off);
						Vaporization_Relay(Off);
						if(Defrost_Delay0_Time > (factdef.dt + custdef.Md + factdef.dd)  * 60){
							//µŒÀÆΩ· ¯
							bDefrost_Delay0 = true;
							factdef.dP = 1;
							defrostsign = 1;
						}
					}
				}
			}
			else if((Vapor_T_HSD + factcp.oE) > custdef.dE && defrostsign == 0){
				if(factdef.td == 0)
					Defrosting_Relay(Off);
				else if(factdef.td == 1)	
					Compressor_Relay(Off);
				else
					Vaporization_Relay(Off);
				defrostsign = 1;
				Usart3_Printf("Œ¬∂»Ã´∏ﬂ¿≤£¨πÿ±’»⁄À™\r\n");
				bedefrost = 0;
				Compressor_Relay(Off);
				Defrosting_Relay(Off);
				Vaporization_Relay(Off);
				Usart3_Printf("µŒÀÆ÷–£¨πÿ±’À˘”– ‰≥ˆ\r\n");
				
			}
			else if(defrostsign == 1){
				static TIME driptime;
				drip_time = GetDiffTime(&driptime,&bdrip);
				if(drip_time > factdef.dt * 60){
					bdrip = true;
					factdef.dP = 1;
					fanqidong = 1;
					defrostsign = 0;
					bDefrost_Delay = true;
					bDefrost_Delay0 = true;
				}
			}
		}
		else if(factdef.dP && Door_Sign == 0){
			static TIME DefrostDelay;
			Defrost_Delay_Time = GetDiffTime(&DefrostDelay,&bDefrost_Delay);
			if(Defrost_Delay_Time > custdef.id * 3600){
				if((Vapor_T_HSD + factcp.oE) < custdef.dE && defrostsign_nokey == 0){
					if(Defrost_Delay_Time >= factdef.dd * 60 + custdef.id * 3600){
						//—” ±◊„πª
						//ø™∆Ù»⁄À™
						//Defrosting_Relay(On);
//						bdrip = true;
						if(bedefrost == 0){
							bedefrost = 1;
							if(custdis.CF)
								defrost_temp = Vapor_T_HSD;
							else if(custdis.CF == 0 && custdis.rE)
								defrost_temp = (int)Vapor_T;
							else if(custdis.CF == 0 && custdis.rE == 0)
								defrost_temp = Vapor_T;
						}
						if(factdef.td == 1){
							Defrosting_Relay(On);
							Compressor_Relay(On);
							Vaporization_Relay(Off);
						}
						else if(factdef.td == 0){
							Defrosting_Relay(On);
							Compressor_Relay(Off);
							Vaporization_Relay(Off);
						}
						else{
							Defrosting_Relay(Off);
							Compressor_Relay(Off);
							Vaporization_Relay(On);
						}
						/*if(factdef.dF == 0){
						//œ‘ æø‚Œ¬
							Usart3_Printf("%.1f\r\n",Vapor_T);
		//					Lcm_GotoXY(0,1,1);
		//					char xianshi[20] = {0};
		//					if(custdis.CF)
		//						sprintf(xianshi,"%.0f F",Vapor);
		//					else if(custdis.CF == 0 && custdis.rE)
		//						sprintf(xianshi,"%.0f C",Vapor);
		//					else
		//						sprintf(xianshi,"%.1f C",Vapor);
		//					Lcm_Disp_String((unsigned char*)xianshi);
						}
						else if(factdef.dF == 1){
							char xianshi[10] = {0};
							if(custdis.CF)
								sprintf(xianshi,"%.0f F",defrost_temp);
							else if(custdis.CF == 0 && custdis.rE)
								sprintf(xianshi,"%.0f C",defrost_temp);
							else
								sprintf(xianshi,"%.1f C",defrost_temp);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)xianshi);
							//œ‘ æ∆Ù∂Ø»⁄À™«∞Œ¬∂»
							//Usart3_Printf("»⁄À™∆Ù∂Ø«∞Œ¬∂»:.1f\r\n",beforeVapor_T);
						}
						else if(factdef.dF == 2){
							Lcm_GotoXY(0,1,1);
							char xianshi[10] = {0};
							sprintf(xianshi,"%d F",custdef.dE);
							Lcm_Disp_String((unsigned char*)xianshi);
							//œ‘ æ…Ë∂®Œ¬∂»÷µ
							Usart3_Printf("…Ë∂®Œ¬∂»÷µ:%.1f\r\n",custdef.dE);
						}
						else if(factdef.dF == 3){
							Lcm_GotoXY(0,1,1);
							char xianshi[10] = {0};
							sprintf(xianshi,"dE");
							Lcm_Disp_String((unsigned char*)xianshi);
							//œ‘ ædE
							Usart3_Printf("œ‘ ædE◊÷—˘:dE dE dE\r\n");
						}*/
						if(Defrost_Delay_Time > (custdef.Md + factdef.dd) * 60 + custdef.id * 3600){
							//µŒÀÆ ±º‰
							Defrosting_Relay(Off);
							Compressor_Relay(Off);
							Vaporization_Relay(Off);
							if(Defrost_Delay_Time > ((factdef.dt + custdef.Md + factdef.dd) * 60 + custdef.id * 3600)){
								//µŒÀÆΩ· ¯
								factdef.dP = 1;
								defrostsign_nokey = 1;
							}
						}
					}
				}
				else if((Vapor_T_HSD + factcp.oE) > custdef.dE && defrostsign_nokey == 0){
					if(factdef.td == 0)
						Defrosting_Relay(Off);
					else if(factdef.td == 1)	
						Compressor_Relay(Off);
					else
						Vaporization_Relay(Off);
					Usart3_Printf("Œ¬∂»Ã´∏ﬂ¿≤£¨πÿ±’»⁄À™\r\n");
					bedefrost = 0;
					defrostsign_nokey = 1;
					Compressor_Relay(Off);
					Defrosting_Relay(Off);
					Vaporization_Relay(Off);
					Usart3_Printf("µŒÀÆ÷–£¨πÿ±’À˘”– ‰≥ˆ\r\n");
					}
			}
			if(defrostsign_nokey == 1){
					static TIME driptime2;
					drip_time2 = GetDiffTime(&driptime2,&bdrip2);
					if(drip_time2 > factdef.dt * 60){
						bdrip2 = true;
						//factdef.dP = 1;
						bDefrost_Delay = true;
						fanqidong = 1;
						defrostsign_nokey = 0;
					}
			}
		}
		vaporerror = 0;
	}
}

void Fan(void)
{
	if(factdef.dP == 0)
		return;
	else if(Defrost_Delay_Time >= custdef.id * 3600 + factdef.dd * 60)
		return;
	if(fanqidong == 1){
		static TIME FanTime;
		Fan_Delay_Time = GetDiffTime(&FanTime,&bFan_Delay);
		if(Fan_Delay_Time >= custfan.Fd * 60){
			fanqidong = 0;
			bFan_Delay = true;
		}
	}
	if(AdcBuf[4] <= 223 || AdcBuf[5] <= 273){
		return;
	}
	if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin) || Vapor_T_HSD >= factfan.FS + factfan.FAd){
		Vaporization_Relay(Off);
	}
	else{
		if(Door_Sign == 0 && fanqidong == 0){
			if(HAL_GPIO_ReadPin(Compressor_Relay_GPIO_Port,Compressor_Relay_Pin) == 0){
				static TIME fantime;
				fan_time = GetDiffTime(&fantime,&bfan);
				if(fan_time <= custfan.Fn * 60){
					Vaporization_Relay(On);
				}
				else if(fan_time <= (custfan.Fn + custfan.FF) * 60 && fan_time >= custfan.Fn * 60){
					Vaporization_Relay(Off);
				}
				else if(fan_time > (custfan.Fn + custfan.FF) * 60){
					bfan = true;
					Vaporization_Relay(Off);
				}
			}
			else{
				Vaporization_Relay(On);
				bfan = true;
			}
		}
		
	}
	if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin)){
		static TIME DoorOpen;
		DoorOpen_Time = GetDiffTime(&DoorOpen,&bDoorOpen);
		if(DoorOpen_Time >= factfan.dAd * 60){
			Compressor_Relay(Off);
			Defrosting_Relay(Off);
			Vaporization_Relay(Off);
			bOften_Start = true;
			bDefrost_Delay0 = true;
			bdrip = true;
			bDefrost_Delay = true;
			bdrip2 = true;
			bFan_Delay = true;
			bfan = true;
		}
	}
	else
		bDoorOpen = true;
}
void Scan(void)
{
	static char durmerror[40] = {0};
	static char durmerror1[40] = {0};
	static char durmerror2[40] = {0};
	/*if(door == 0){
		if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin)){
			Usart3_Printf("√≈≥¨ ±\r\n");
			Outside_door++;	
			custvs.DTO++;
			door = 1;
		}
	}
	else if(door == 1){
		if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin) == 0){
			door = 0;
		}
	}*/
	if(weight != 100 && Measuing < 80){
		Usart3_Printf("÷ÿ¡ø£∫%d\r\n",weight);
		static TIME Down_weight;
		Down_Time = GetDiffTime(&Down_weight,&bDown_Time);
		if(weight == 300){
			if(Down_Time >= factdsp.P10 * 60 && factdsp.P10 != 20){
					weight = 200;
//					Usart3_Printf("Ωµ÷¡÷–∑›\r\n");
					bDown_Time = true;
			}
		}
		else if(weight == 200){
			if(Down_Time >= factdsp.P11 * 60 && factdsp.P11 != 20){
				weight = 100;
//				Usart3_Printf("Ωµ÷¡–°∑›\r\n");
				bDown_Time = true;
			}
		}
	}
	else if(weight == 100)
		bDown_Time = true;
	//if(factdsp.P18){
		/*if(Down_finish == 1){
			if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
				//œ‘ æ»±¡œ£∫LP
				if(yuanbenw == 0)
					yuanbenw = weight;
				if(time_out == 0){
					f_timeout = 0;
					char low[48] = {0};
					sprintf(low,"Low Product Add Food");
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
					lp = 1;
					Lcm_Disp_String((unsigned char *)low);
//					Usart3_Printf("%s\r\n",low);
					HAL_Delay(500);
				}
				TIM3_Disable();
				
				static TIME filltime;
				Fill_Time = GetDiffTime(&filltime,&bFill);
				if(Fill_Time >= 60){
					time_out = 1;
					//º”‘ÿ≥¨ ±
					Usart3_Printf("º”¡œ≥¨ ±\r\n ¥ÌŒÛ¥˙¬Î£∫Err04A\r\n");
					char timeout[48] = {0};
					sprintf(timeout,"ERR-04A               LP");
					if(f_timeout == 0){
						f_timeout = 1;
						TIM3_Disable();
						custvs.FTO++;
					}
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
					Lcm_Disp_String((unsigned char *)timeout);
//					Usart3_Printf("%s\r\n",timeout);
					
					char explain[48] = {0};
					sprintf(explain,"Fill Time Out    ");
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char *)explain);
					sprintf(explain,"Press L to Reset ");
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char *)explain);
					HAL_Delay(500);
					if(LARGE_SET == GPIO_PIN_RESET){
						time_out = 0;
						bFill = true;
						Large_Set = 0;
//						Usart3_Printf("π˛π˛π˛");
						Lcm_GotoXY(0,0,0);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						weight = yuanbenw;
						yuanbenw = 0;
						TIM3_Enable();
					}
				}
			}
			if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 0){
				if(lp){
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					f_timeout = 0;
					TIM3_Enable();
					lp = 0;
				}
				if(f_timeout){
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					f_timeout = 0;
					TIM3_Enable();
				}
				bFill = true;
				Fill_Time = 0;
				if(drum == 0 && opendoor == 0 && closedoor == 0){
					Allocation(weight / 100);
				}
				else if(drum == 1 || opendoor || closedoor){
					if(drum == 1){
						sprintf(durmerror,"Err-05");
						sprintf(durmerror1,"Drum Torque Err");
						sprintf(durmerror2,"Press L to Reset");
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char*)durmerror);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)durmerror1);
						Lcm_GotoXY(0,0,0);
						Lcm_Disp_String((unsigned char*)durmerror2);
						drum = 2;
						TIM3_Disable();
					}
					else if(opendoor == 1){
						sprintf(durmerror,"Err-07-2");
						sprintf(durmerror1,"Door Torque Err Open");
						sprintf(durmerror2,"Press L to Reset");
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char*)durmerror);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)durmerror1);
						Lcm_GotoXY(0,0,0);
						Lcm_Disp_String((unsigned char*)durmerror2);
						closedoor = 2;
						TIM3_Disable();
					}
					else if(closedoor == 1){
						sprintf(durmerror,"Err-08");
						sprintf(durmerror1,"Door Torque Err Close");
						sprintf(durmerror2,"Press L to Reset");
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char*)durmerror);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)durmerror1);
						Lcm_GotoXY(0,0,0);
						Lcm_Disp_String((unsigned char*)durmerror2);
						drum = 2;
						TIM3_Disable();
					}
				}
				else if(drum == 2 || opendoor == 2 || closedoor == 2){
					if(drum == 2){
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char*)durmerror);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)durmerror1);
						Lcm_GotoXY(0,0,0);
						Lcm_Disp_String((unsigned char*)durmerror2);
						HAL_Delay(500);
						Lcm_GotoXY(0,0,0);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						Lcm_GotoXY(0,0,1);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						HAL_Delay(100);
					}
					else if(opendoor == 2){
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char*)durmerror);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)durmerror1);
						Lcm_GotoXY(0,0,0);
						Lcm_Disp_String((unsigned char*)durmerror2);
						HAL_Delay(500);
						Lcm_GotoXY(0,0,0);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						Lcm_GotoXY(0,0,1);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						HAL_Delay(100);
					}
					else if(closedoor == 2){
						Lcm_GotoXY(0,0,1);
						Lcm_Disp_String((unsigned char*)durmerror);
						Lcm_GotoXY(0,1,1);
						Lcm_Disp_String((unsigned char*)durmerror1);
						Lcm_GotoXY(0,0,0);
						Lcm_Disp_String((unsigned char*)durmerror2);
						HAL_Delay(500);
						Lcm_GotoXY(0,0,0);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						Lcm_GotoXY(0,0,1);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						HAL_Delay(100);
					}
					else if(LARGE_SET == GPIO_PIN_RESET){
						drum = 0;
						opendoor = 0;
						closedoor = 0;
						Lcm_GotoXY(0,0,0);
						Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					}
				}
			}
		}*/
		//else{
			if(drum == 0 && opendoor == 0 && closedoor == 0){
				if(Down_finish == 6 && errordelete == 0)
					TIM3_Enable();
				Allocation(weight / 100);
			}
			else if(drum == 1 || opendoor == 1 || closedoor == 1){
				TIM3_Disable();
				TIM4_Enable();
				if(drum == 1){
					sprintf(durmerror,"Err-05");
					sprintf(durmerror1,"Drum Torque Err");
					sprintf(durmerror2,"Press L to Reset");
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					drum = 2;
					TIM3_Disable();
				}
				else if(opendoor == 1){
					sprintf(durmerror,"Err-07-2");
					sprintf(durmerror1,"Door Torque Err Open");
					sprintf(durmerror2,"Press L to Reset");
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					opendoor = 2;
					TIM3_Disable();
				}
				else if(closedoor == 1){
					sprintf(durmerror,"Err-08");
					sprintf(durmerror1,"Door Torque Err Close");
					sprintf(durmerror2,"Press L to Reset");
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					closedoor = 2;
					TIM3_Disable();
				}
			}
			else if(drum == 2 || opendoor == 2 || closedoor == 2){
				if(deletewarn >= 1){
					TIM4_Disable();
					TIM3_Enable();
					while(1){
						DoorOpen_Motor(On);
						if(HAL_GPIO_ReadPin(dooropen_GPIO_Port,dooropen_Pin)){
							DoorOpen_Motor(Off);
							HAL_Delay(800);
							DoorOpen_Motor(2);
							Down_finish = 4;
							break;
						}
					}
					drum = 0;
					opendoor = 0;
					closedoor = 0;
					deletewarn = 0;
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				}
				else if(drum == 2){
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
				else if(opendoor == 2){
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
				else if(closedoor == 2){
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
				
			}
		//}
	//}
	/*else{
		if(lp){
			Lcm_GotoXY(0,0,0);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			f_timeout = 0;
			TIM3_Enable();
			lp = 0;
		}
		if(f_timeout){
			Lcm_GotoXY(0,0,0);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			f_timeout = 0;
			TIM3_Enable();
		}
		bFill = true;
		Fill_Time = 0;
		if(drum == 0 && opendoor == 0 && closedoor == 0){
			Allocation(weight / 100);
		}
		else if(drum == 1 || opendoor || closedoor){
			if(drum == 1){
				sprintf(durmerror,"Err-05");
				sprintf(durmerror1,"Drum Torque Err");
				sprintf(durmerror2,"Press L to Reset");
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)durmerror);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char*)durmerror1);
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)durmerror2);
				drum = 2;
			}
			else if(opendoor == 1){
				sprintf(durmerror,"Err-07-2");
				sprintf(durmerror1,"Door Torque Err Open");
				sprintf(durmerror2,"Press L to Reset");
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)durmerror);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char*)durmerror1);
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)durmerror2);
				closedoor = 2;
			}
			else if(closedoor == 1){
				sprintf(durmerror,"Err-08");
				sprintf(durmerror1,"Door Torque Err Close");
				sprintf(durmerror2,"Press L to Reset");
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)durmerror);
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char*)durmerror1);
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)durmerror2);
				drum = 2;
			}
		}
		else if(drum == 2 || opendoor == 2 || closedoor == 2){
				if(drum == 2){
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
				else if(opendoor == 2){
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
				else if(closedoor == 2){
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)durmerror);
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)durmerror1);
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)durmerror2);
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
				else if(LARGE_SET == GPIO_PIN_RESET){
					drum = 0;
					opendoor = 0;
					closedoor = 0;
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				}
		}
	}*/
	
}

void Allocation(uint8_t copies)
{
	//Œ¬∂»“ª÷±œ‘ æ
	char heavy[50] = {0};
	static int doorzzz = 0;
	static uint8_t diandong = 0;
	static uint8_t drum_motor_roration = 1;//œ¬¡œµÁª˙◊™œÚ±Í ∂  1’˝◊™ 0∑¥◊™
	static uint8_t roration_time = 0;
	static uint8_t roration = 0;
	static uint8_t broration = TRUE;
//	static uint8_t disweight = 0;°§
//	static uint8_t disweight1 = 0;
//	static uint8_t weightfenshu = 0;
//	static uint8_t weightfenshu1 = 0;
	
	if(berror_code == 0){
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
			if(factdis.Ld){
				if(factdef.dF == 0){
					if(custdis.CF){
						if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
							sprintf(heavy,"              %d F    ",Vapor_T_HSD);
						else if(Down_finish == 0)
							sprintf(heavy,"Filling       %d F    ",Vapor_T_HSD);
						else if(Down_finish == 1)
							sprintf(heavy,"Ready         %d F    ",Vapor_T_HSD);
						else if(Down_finish == 2)
							sprintf(heavy,"Filled        %d F    ",Vapor_T_HSD);
					}
					else if(custdis.CF == 0 && custdis.rE == 0){
						if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
							sprintf(heavy,"             %.1f C    ",Vapor_T);
						else if(Down_finish == 0)
							sprintf(heavy,"Filling      %.1f C    ",Vapor_T);
						else if(Down_finish == 1)
							sprintf(heavy,"Ready        %.1f C    ",Vapor_T);
						else if(Down_finish == 2)
							sprintf(heavy,"Filled       %.1f C    ",Vapor_T);
					}
					else if(custdis.CF == 0 && custdis.rE == 1){
						if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
							sprintf(heavy,"              %.0f C    ",Vapor_T);
						else if(Down_finish == 0)
							sprintf(heavy,"Filling       %.0f C    ",Vapor_T);
						else if(Down_finish == 1)
							sprintf(heavy,"Ready         %.0f C    ",Vapor_T);
						else if(Down_finish == 2)
							sprintf(heavy,"Filled        %.0f C    ",Vapor_T);
					}
				}
				else if(factdef.dF == 1){
					if(custdis.CF){
						if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
							sprintf(heavy,"              %.0f F    ",defrost_temp);
						else if(Down_finish == 0)
							sprintf(heavy,"Filling       %.0f F    ",defrost_temp);
						else if(Down_finish == 1)
							sprintf(heavy,"Ready         %.0f F    ",defrost_temp);
						else if(Down_finish == 2)
							sprintf(heavy,"Filled        %.0f F    ",defrost_temp);
					}
					else if(custdis.CF == 0 && custdis.rE == 0){
						if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
							sprintf(heavy,"             %.1f C    ",defrost_temp);
						else if(Down_finish == 0)
							sprintf(heavy,"Filling      %.1f C    ",defrost_temp);
						else if(Down_finish == 1)
							sprintf(heavy,"Ready        %.1f C    ",defrost_temp);
						else if(Down_finish == 2)
							sprintf(heavy,"Filled       %.1f C    ",defrost_temp);
					}
					else if(custdis.CF == 0 && custdis.rE == 1){
						if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
							sprintf(heavy,"             %.1f C    ",defrost_temp);
						else if(Down_finish == 0)
							sprintf(heavy,"Filling      %.1f C    ",defrost_temp);
						else if(Down_finish == 1)
							sprintf(heavy,"Ready        %.1f C    ",defrost_temp);
						else if(Down_finish == 2)
							sprintf(heavy,"Filled       %.1f C    ",defrost_temp);
					}
				}
				else if(factdef.dF == 2){
					if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
						sprintf(heavy,"             %d F    ",custdef.dE);
					else if(Down_finish == 0)
						sprintf(heavy,"Filling      %d F    ",custdef.dE);
					else if(Down_finish == 1)
						sprintf(heavy,"Ready        %d F    ",custdef.dE);
					else if(Down_finish == 2)
						sprintf(heavy,"Filled       %d F    ",custdef.dE);
				}
				else{
					if(Down_finish == 4 || Down_finish == 3)
						sprintf(heavy,"             dE    ");
					else if(Down_finish == 0)
						sprintf(heavy,"Filling      dE    ");
					else if(Down_finish == 1)
						sprintf(heavy,"Ready        dE    ");
					else if(Down_finish == 2)
						sprintf(heavy,"Filled       dE    ");
				}
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)heavy);
			}
			else{
				if(custdis.CF){
					if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
						sprintf(heavy,"             %d F    ",Case_T_HSD);
					else if(Down_finish == 0)
						sprintf(heavy,"Filling      %d F    ",Case_T_HSD);
					else if(Down_finish == 1)
						sprintf(heavy,"Ready        %d F    ",Case_T_HSD);
					else if(Down_finish == 2)
						sprintf(heavy,"Filled       %d F    ",Case_T_HSD);
				}
				else if(custdis.CF == 0 && custdis.rE == 0){
					if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
						sprintf(heavy,"             %.1f C    ",Case_T);
					else if(Down_finish == 0)
						sprintf(heavy,"Filling      %.1f C    ",Case_T);
					else if(Down_finish == 1)
						sprintf(heavy,"Ready        %.1f C    ",Case_T);
					else if(Down_finish == 2)
						sprintf(heavy,"Filled       %.1f C    ",Case_T);
				}
				else if(custdis.CF == 0 && custdis.rE == 1){
					if(Down_finish == 4 || Down_finish == 3 || Down_finish == 6)
						sprintf(heavy,"             %.0f C    ",Case_T);
					else if(Down_finish == 0)
						sprintf(heavy,"Filling      %.0f C    ",Case_T);
					else if(Down_finish == 1)
						sprintf(heavy,"Ready        %.0f C    ",Case_T);
					else if(Down_finish == 2)
						sprintf(heavy,"Filled       %.0f C    ",Case_T);
				}
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)heavy);
			}
			if(Down_finish != 6){
//				disweight = 1;
				if(weight == 100){
					sprintf(heavy,"Small                   ");
//						weightfenshu = 1;
				}
				else if(weight == 200){
					sprintf(heavy,"Mid                     ");
//						weightfenshu = 2;
				}
				else if(weight == 300){
						sprintf(heavy,"Large                   ");
//						weightfenshu = 3;
					}
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)heavy);
			}
			/*else if(Down_finish == 1 && disweight == 1){
				if(weightfenshu == 1)
					sprintf(heavy,"Small       wei:%.1f g",realweight);
				else if(weightfenshu == 2)
					sprintf(heavy,"Mid         wei:%.1f g",realweight);
				else if(weightfenshu == 3)
					sprintf(heavy,"Large       wei:%.1f g",realweight);
				if(weightfenshu == 1)
					sprintf(heavy,"Small                   ");
				else if(weightfenshu == 2)
					sprintf(heavy,"Mid                     ");
				else if(weightfenshu == 3)
					sprintf(heavy,"Large                   ");
				disweight = 1;
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)heavy);
			}*/
			else if(Down_finish == 6){
				sprintf(heavy,"                        ");
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)heavy);
			}
		}
		else{
			//µ⁄“ª––
			if(Down_finish == 4 || Down_finish == 3)
				sprintf(heavy,"                        ");
			else if(Down_finish == 0)
				sprintf(heavy,"Filling                 ");
			else if(Down_finish == 1)
				sprintf(heavy,"Ready                   ");
			else if(Down_finish == 2)
				sprintf(heavy,"Filled                  ");
			else if(Down_finish == 6)
				sprintf(heavy,"                        ");
			Lcm_GotoXY(0,0,1);
			Lcm_Disp_String((unsigned char*)heavy);
			
			//µ⁄∂˛––
			if(Down_finish != 6){
//				disweight1 = 1;
				if(weight == 100){
					sprintf(heavy,"Small                   ");
//					weightfenshu1 = 1;
				}
				else if(weight == 200){
					sprintf(heavy,"Mid                     ");
//					weightfenshu1 = 2;
				}
				else if(weight == 300){
					sprintf(heavy,"Large                   ");
//					weightfenshu1 = 3;
				}
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)heavy);
			}
			/*else if(Down_finish == 1 && disweight1 == 1){
				if(weightfenshu1 == 1)
					sprintf(heavy,"Small       wei:%.1f g",realweight);
				else if(weightfenshu1 == 2)
					sprintf(heavy,"Mid         wei:%.1f g",realweight);
				else if(weightfenshu1 == 3)
					sprintf(heavy,"Large       wei:%.1f g",realweight);
				if(weightfenshu1 == 1)
					sprintf(heavy,"Small                   ");
				else if(weightfenshu1 == 2)
					sprintf(heavy,"Mid                     ");
				else if(weightfenshu1 == 3)
					sprintf(heavy,"Large                   ");
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)heavy);
			}*/
			else if(Down_finish == 6){
				sprintf(heavy,"                        ");
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)heavy);
			}
		}
	}
	//smallwei = (float)(factdsp.P23 - 37) / 100;
	smallwei = 0.5;
//	midwei = (float)factdsp.P22 / 100;
//	largewei = (float)factdsp.P21 / 100;
	//…˝ΩµµÁª˙
	if(Down_finish == 4){
		Lift_Motor(2);
		HAL_Delay(100);
		Lift_Motor(On);
		HAL_Delay(100);
		while(1){
			Measuing = AdcBuf[0] * 10000 * 3.3 / chengzADC / 3;
			/*if(AdcBuf[1] >= liftadc)
				smalla = 1;
			if(smalla == 0){
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				smalla = 1;
				if(weight == 100)
					sprintf(heavy,"Small  %d",(int)(factdsp.P30 * custvs.CL) / 100);
				else if(weight == 200)
					sprintf(heavy,"Mid  %d",(int)(factdsp.P29 * custvs.CL) / 100);
				else
					sprintf(heavy,"Large  %d",custvs.CL);
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)heavy);
			}
			else if(smalla){
	//			sprintf(danhao, "            °ˆ    °ˆ");
	//			sprintf(danhao2,"          °ˆ  °ˆ  °ˆ");
	//			sprintf(danhao3,"          °ˆ°ˆ°ˆ  °ˆ");
	//			sprintf(danhao4,"          °ˆ  °ˆ  °ˆ°ˆ");
	//			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			}*/
			if(Measuing >= liftweight){
				HAL_Delay(delaysd);
				Lift_Motor(2);
				Down_finish = 3;
				Measuing = 0;
				HAL_Delay(haltime);
				break;
			}
			else{
				if(liftover >= 5){
					if(AdcBuf[1] >= factdsp.P15){
						Lift_Motor(2);
						char lifterror[48] = {0};
						char lifterror1[48] = {0};
						char lifterror2[48] = {0};
						sprintf(lifterror,"Err-05");
						sprintf(lifterror1,"Lift Torque Err");
						sprintf(lifterror2,"Press L to Reset");
						TIM3_Disable();
						while(1){
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)lifterror);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)lifterror1);
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)lifterror2);
							HAL_Delay(500);
							if(LARGE_SET == GPIO_PIN_RESET){
								Lcm_GotoXY(0,0,0);
								Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
								Lcm_GotoXY(0,0,1);
								Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
								Lift_Motor(On);
								break;
							}
						}
					}
					liftover = 0;
				}
				else{
					//…˝ΩµµÁª˙¡¶æÿ
					if(AdcBuf[1] >= factdsp.P15){
						liftover++;
						HAL_Delay(100);
					}
					else{
						liftover = 0;
						Lift_Motor(On);
					}
				}
			}
			/*else if(AdcBuf[1] <= liftadc){
				if(smalla){
					HAL_Delay(delaysd1);
					Lift_Motor(2);
					Down_finish = 3;
					Measuing = 0;
					HAL_Delay(haltime);
					break;
				}
			}*/
		}
	}
	else if(Down_finish == 3){
		int16_t he[100] = {0};
		uint16_t junzhi = 0;
		int zongshu = 0;
		while(1){
			he[junzhi++] = AdcBuf[0];
			HAL_Delay(1);
			if(junzhi == 100){
				junzhi = 0;
				for	(uint16_t i=0;i<100-1;i++){
					for(uint16_t j=0;j<100-i-1;j++){
						if(he[j] > he[j+1]){
							int asd = he[j+1];
							he[j+1] = he[j];
							he[j] = asd;
						}
					}
				}
				for(uint16_t i=20;i<80;i++){
					zongshu += he[i];
				}
				zongshu = zongshu / 60;
				no_load = zongshu * 11000 / chengzADC ;
				break;
			}
		}
		if(no_load <= 5500 && no_load >= 1000){
			TIM3_Disable();
			while(1){
				TIM4_Enable();
				Measuing = AdcBuf[0] * 10000 * 3.3 / chengzADC / 3;
				char errorcode[40] = {0};
				if(cell == 0){
					Lift_Motor(On);//…œ…˝
//					HAL_Delay(lifttime);
					HAL_Delay(1500);
					Lift_Motor(2);
					if(Measuing <= 100)
						cell = 1;
					else
						return;
				}
				if(deletewarn >= 1){
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					cell = 0;
					Down_finish = 4;
//					disweight = 0;
					if(weight == 100)
						weight = 100;
					else if(weight == 200)
						weight = 200;
//					TIM3_Enable();
					TIM4_Disable();
					break;
				}
				else{
					sprintf(errorcode,"ERR-02           ");
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)errorcode);
					sprintf(errorcode,"No Bucket        ");
					Lcm_GotoXY(0,1,1);
					Lcm_Disp_String((unsigned char*)errorcode);
					sprintf(errorcode,"Press L to Reset ");
					Lcm_GotoXY(0,0,0);
					Lcm_Disp_String((unsigned char*)errorcode);
					TIM3_Disable();
					HAL_Delay(500);
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
				}
			}
		}
		else if(no_load < 1000){
			TIM3_Disable();
			while(1){
				char errorcode[40] = {0};
				if(load_cell_error == 0){
					Lift_Motor(On);//…œ…˝
//					HAL_Delay(lifttime);
					HAL_Delay(1500);
					Lift_Motor(2);
					load_cell_error = 1;
				}
				/*sprintf(errorcode,"ERR-01           ");
				Lcm_GotoXY(0,0,1);
				Lcm_Disp_String((unsigned char*)errorcode);
				sprintf(errorcode,"Load Cell Error  ");
				Lcm_GotoXY(0,1,1);
				Lcm_Disp_String((unsigned char*)errorcode);
				sprintf(errorcode,"Press L to Reset ");
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char*)errorcode);
				TIM3_Disable();
				HAL_Delay(500);
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				HAL_Delay(100);*/
				/*if(LARGE_SET == GPIO_PIN_RESET){
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					load_cell_error = 0;
					Down_finish = 4;
//					disweight = 0;
					no_load = 0;
//					TIM3_Enable();
					break;
				}*/
				load_cell_error = 0;
				Down_finish = 4;
				no_load = 0;
				break;
			}
		}
		else{
			if(cell || load_cell_error){
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				cell = 0;
				load_cell_error = 0;
			}
			Down_finish = 0;
		}
		return;
	}
	else if(Down_finish == 0){
		TIM3_Disable();
		//–°∑›
		if(copies == 1){
			int16_t he[80] = {0};
			uint16_t junzhi = 0;
			int zongshu = 0;
			int frybridge = 0;
			int lowproduct = 0;
			while(Measuing < factdsp.P30 * custvs.CL / 100 + no_load  - chavalue){
				static TIME downfinishtime;
				downfinish_0 = GetDiffTime(&downfinishtime,&bdownfinish_0);
				if(downfinish_0 <= 6 || diandong == 1){
					//if(downfinish_0 >= 0){
						if(Measuing <= smallwei * factdsp.P30 * custvs.CL / 100 + no_load - chavalue){
							if(drumover >= 5){
								if(AdcBuf[3] >= factdsp.P13){
									
									//±®æØ»°œ˚£¨ªª≥…’˝∑¥œÚ◊™
									/*custvs.DrTQ++;
									drum = 1;
									Lift_Motor(On);//…œ…˝
//									HAL_Delay(lifttime);
									HAL_Delay(1500);
									Lift_Motor(2);*/
									
									//’˝∑¥œÚ◊™
									if(factdsp.T1 == 999){
										Drum_Motor(Off);
										HAL_Delay(factdsp.T2 * 1000);
										drumover = 0;
									}
									else{
										if(drum_motor_roration){
											drum_motor_roration = 0;
											Drum_Motor(0);
											HAL_Delay(drumtime);
										}
										else{
											drum_motor_roration = 1;
											Drum_Motor(1);
											HAL_Delay(drumtime);
										}
										//HAL_Delay(10);
									}
								}
								drumover = 0;
							}
							else{
								if(AdcBuf[3] >= factdsp.P13){
									drumover++;
									//Drum_Motor(2);
								}
								else
									drumover = 0;
							}
						}
					//}
					//TIM3_Disable();
					he[junzhi++] = AdcBuf[0];
					HAL_Delay(1);
					if(junzhi == 80){
						for	(uint16_t i=0;i<80-1;i++){
							for(uint16_t j=0;j<80-i-1;j++){
								if(he[j] > he[j+1]){
									int asd = he[j+1];
									he[j+1] = he[j];
									he[j] = asd;
								}
							}
						}
						for(uint16_t i=20;i<60;i++){
							zongshu += he[i];
						}
						zongshu = zongshu / 40;
						Measuing = zongshu * 11000 / chengzADC ;
						zongshu = 0;
						memset(he,0,sizeof(he));
						if(Measuing < factdsp.P30 * custvs.CL / 100 + no_load - chavalue){
							static TIME rorationtime;
							roration_time = GetDiffTime(&rorationtime,&broration);
							if(factdsp.P19 == 0){
								if(roration_time - roration >= factdsp.T1 && drum_motor_roration){
									//±‰∑¥œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 0;
								}
								else if(roration_time - roration >= factdsp.T2 && !drum_motor_roration){
									//±‰’˝œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 1;
								}
								if(Measuing <= 0.88 * factdsp.P30 * custvs.CL / 100 + no_load +  - chavalue){
									if(drum_motor_roration){
										Drum_Motor(1);
										HAL_Delay(drumtime);
									}
									else{
										Drum_Motor(0);
										HAL_Delay(drumtime);
									}
								}
								else{
									static TIME Inching;
									inchingtime = GetDiffTime(&Inching,&binching);
									if(drum_motor_roration)
										Drum_Motor(1);
									else
										Drum_Motor(0);
									HAL_Delay(delaytt);
									Drum_Motor(2);
									HAL_Delay(delaytt1);
									diandong = 1;
								}
							}
							else{
								if(roration_time - roration >= factdsp.T1 && drum_motor_roration){
									//±‰∑¥œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 0;
								}
								else if(roration_time - roration >= factdsp.T2 && !drum_motor_roration){
									//±‰’˝œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 1;
								}
								if(Measuing <= factdsp.P23 * factdsp.P30 * custvs.CL / 10000 + no_load - chavalue){
									if(drum_motor_roration){
										Drum_Motor(1);
										HAL_Delay(drumtime);
									}
									else{
										Drum_Motor(0);
										HAL_Delay(drumtime);
									}
								}
								else{
									static TIME Inching;
									inchingtime = GetDiffTime(&Inching,&binching);
									if(drum_motor_roration)
										Drum_Motor(On);
									else
										Drum_Motor(Off);
									HAL_Delay(delaytt);
									Drum_Motor(2);
									HAL_Delay(delaytt1);
									diandong = 1;
								}
							}
							if(inchingtime >= 10){
								Down_finish = 5;
								break;
							}
						}
						else{
							Down_finish = 5;
						}
						junzhi = 0;
//						if(Measuing < 4000){
//							Down_finish = 3;
//							break;
//						}
					}
					if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
						char Error[48] = {0};
						sprintf(Error,"04A Low Produc");
						if(LARGE_SET == GPIO_PIN_RESET){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						}
						else if(factdsp.P18){
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Error);
						}
					}
				}
				else if(downfinish_0 > 6 && diandong == 0){
					Drum_Motor(2);
					broration = TRUE;
					drum_motor_roration = 1;
					if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
						if(deletewarn >= 1){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							deletewarn = 0;
							TIM4_Disable();
							bdownfinish_0 = true;
							zerofinish = 0;
	//						disweight = 0;
							weight = 100;
							lowproduct = 0;
							Lift_Motor(On);
							while(1){
								Measuing = AdcBuf[0] * 10000 * 3.3 / chengzADC / 3;
								if(Measuing >= liftweight){
									HAL_Delay(delaysd);
									Lift_Motor(2);
									Measuing = 0;
									HAL_Delay(haltime);
									break;
								}
							}
						}
						else if(lowproduct == 0){
							Lift_Motor(On);//…œ…˝
							HAL_Delay(2250);
							Lift_Motor(2);
							lowproduct = 1;
							TIM4_Enable();
						}
						else if(factdsp.P18){
							Drum_Motor(2);
							char Error[48] = {0};
							char Errorexplain[48] = {0};
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							sprintf(Error,"Err-04A");
							sprintf(Errorexplain,"Low Product Add Food");
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)Error);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Errorexplain);
							sprintf(Error,"Press L to Continue");
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)Error);
							HAL_Delay(500);
						}
					}
					else{
						if(deletewarn >= 1){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							deletewarn = 0;
							TIM4_Disable();
							bdownfinish_0 = true;
							zerofinish = 0;
	//						disweight = 0;
							weight = 100;
							Down_finish = 4;
							frybridge = 0;
							break;
						}
						else if(frybridge == 0){
							Lift_Motor(On);//…œ…˝
							HAL_Delay(2250);
							Lift_Motor(2);
							frybridge = 1;
							TIM4_Enable();
						}
						else{
							Drum_Motor(2);
							char Error[20] = {0};
							char Errorexplain[40] = {0};
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							sprintf(Error,"Err-04B");
							sprintf(Errorexplain,"Fry Brigde");
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)Error);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Errorexplain);
							sprintf(Error,"Press L to Continue");
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)Error);
							HAL_Delay(500);
						}
					}
				}
				realweight = Measuing - no_load;
				if(errordelete >= 250){
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Down_finish = 6;
					bdownfinish_0 = true;
					break;
				}
			}
			Drum_Motor(2);
		}
		else if(copies == 2){
			int16_t he[80] = {0};
			uint16_t junzhi = 0;
			int zongshu = 0;
			int frybridge = 0;
			int lowproduct = 0;
			while(Measuing < factdsp.P29 * custvs.CL / 100 + no_load  - chavalue){
				static TIME downfinishtime;
				downfinish_0 = GetDiffTime(&downfinishtime,&bdownfinish_0);
				if(downfinish_0 <= 6 || diandong == 1){
					//if(downfinish_0 >= 5){
						if(Measuing <= smallwei * factdsp.P29 * custvs.CL / 100 + no_load - chavalue){
							if(drumover >= 5){
								if(AdcBuf[3] >= factdsp.P13){
									
									//±®æØ»°œ˚£¨ªª≥…’˝∑¥œÚ◊™
									/*custvs.DrTQ++;
									drum = 1;
									Lift_Motor(On);//…œ…˝
//									HAL_Delay(lifttime);
									HAL_Delay(1500);
									Lift_Motor(2);*/
									
									//’˝∑¥œÚ◊™
									if(factdsp.T1 == 999){
										Drum_Motor(Off);
										HAL_Delay(factdsp.T2 * 1000);
										drumover = 0;
									}
									else{
										if(drum_motor_roration){
											drum_motor_roration = 0;
											Drum_Motor(0);
											HAL_Delay(drumtime);
										}
										else{
											drum_motor_roration = 1;
											Drum_Motor(1);
											HAL_Delay(drumtime);
										}
										//HAL_Delay(10);
									}
								}
								drumover = 0;
							}
							else{
								if(AdcBuf[3] >= factdsp.P13){
									drumover++;
									Drum_Motor(2);
								}
								else
									drumover = 0;
							}
						}
					//}
					//TIM3_Disable();
					he[junzhi++] = AdcBuf[0];
					HAL_Delay(1);
					if(junzhi == 80){
						for	(uint16_t i=0;i<80-1;i++){
							for(uint16_t j=0;j<80-i-1;j++){
								if(he[j] > he[j+1]){
									int asd = he[j+1];
									he[j+1] = he[j];
									he[j] = asd;
								}
							}
						}
						for(uint16_t i=20;i<60;i++){
							zongshu += he[i];
						}
						zongshu = zongshu / 40;
						Measuing = zongshu * 11000 / chengzADC ;
						zongshu = 0;
						memset(he,0,sizeof(he));
						if(Measuing < factdsp.P29 * custvs.CL / 100 + no_load - chavalue){
							static TIME rorationtime;
							roration_time = GetDiffTime(&rorationtime,&broration);
							if(factdsp.P19 == 0){
								if(roration_time - roration >= factdsp.T1 && drum_motor_roration){
									//±‰∑¥œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 0;
								}
								else if(roration_time - roration >= factdsp.T2 && !drum_motor_roration){
									//±‰’˝œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 1;
								}
								if(Measuing <= 0.89 * factdsp.P29 * custvs.CL / 100 + no_load +  - chavalue){
									if(drum_motor_roration){
										Drum_Motor(On);
										HAL_Delay(drumtime);
									}
									else{
										Drum_Motor(Off);
										HAL_Delay(drumtime);
									}
								}
								else{
									static TIME Inching;
									inchingtime = GetDiffTime(&Inching,&binching);
									if(drum_motor_roration)
										Drum_Motor(On);
									else
										Drum_Motor(Off);
										HAL_Delay(drumtime);
									HAL_Delay(delaytt);
									Drum_Motor(2);
									HAL_Delay(delaytt1);
									diandong = 1;
								}
							}
							else{
								if(roration_time - roration >= factdsp.T1 && drum_motor_roration){
									//±‰∑¥œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 0;
								}
								else if(roration_time - roration >= factdsp.T2 && !drum_motor_roration){
									//±‰’˝œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 1;
								}
								if(Measuing <= factdsp.P22 * factdsp.P29 * custvs.CL / 10000 + no_load - chavalue){
									if(drum_motor_roration){
										Drum_Motor(1);
										HAL_Delay(drumtime);
									}
									else{
										Drum_Motor(0);
										HAL_Delay(drumtime);
									}
								}
								else{
									static TIME Inching;
									inchingtime = GetDiffTime(&Inching,&binching);
									if(drum_motor_roration)
										Drum_Motor(On);
									else
										Drum_Motor(Off);
									HAL_Delay(delaytt);
									Drum_Motor(2);
									HAL_Delay(delaytt1);
									diandong = 1;
								}
							}
							if(inchingtime >= 10){
								Down_finish = 5;
								break;
							}
						}
						else{
							Down_finish = 5;
						}
						junzhi = 0;
//						if(Measuing < 4000){
//							Down_finish = 3;
//							break;
//						}
					}
					if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
						char Error[48] = {0};
						sprintf(Error,"04A Low Produc");
						if(LARGE_SET == GPIO_PIN_RESET){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						}
						else if(factdsp.P18){
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Error);
						}
					}
				}
				else if(downfinish_0 > 6 && diandong == 0){
					Drum_Motor(2);
					broration = TRUE;
					drum_motor_roration = 1;
					if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
						if(deletewarn >= 1){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							deletewarn = 0;
							TIM4_Disable();
							bdownfinish_0 = true;
							zerofinish = 0;
	//						disweight = 0;
							weight = 200;
							lowproduct = 0;
							Lift_Motor(On);
							while(1){
								Measuing = AdcBuf[0] * 10000 * 3.3 / chengzADC / 3;
								if(Measuing >= liftweight){
									HAL_Delay(delaysd);
									Lift_Motor(2);
									Measuing = 0;
									HAL_Delay(haltime);
									break;
								}
							}
						}
						else if(lowproduct == 0){
							Lift_Motor(On);//…œ…˝
							HAL_Delay(2250);
							Lift_Motor(2);
							lowproduct = 1;
							TIM4_Enable();
						}
						else if(factdsp.P18){
							Drum_Motor(2);
							char Error[48] = {0};
							char Errorexplain[48] = {0};
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							sprintf(Error,"Err-04A");
							sprintf(Errorexplain,"Low Product Add Food");
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)Error);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Errorexplain);
							sprintf(Error,"Press L to Continue");
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)Error);
							HAL_Delay(500);
						}
					}
					else{
						if(deletewarn >= 1){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							deletewarn = 0;
							TIM4_Disable();
							bdownfinish_0 = true;
							zerofinish = 0;
	//						disweight = 0;
							weight = 200;
							Down_finish = 4;
							break;
						}
						else if(frybridge == 0){
							Lift_Motor(On);//…œ…˝
							HAL_Delay(250);
							Lift_Motor(2);
							frybridge = 1;
							TIM4_Enable();
						}
						else{
							Drum_Motor(2);
							char Error[20] = {0};
							char Errorexplain[40] = {0};
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							sprintf(Error,"Err-04B");
							sprintf(Errorexplain,"Fry Brigde");
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)Error);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Errorexplain);
							sprintf(Error,"Press L to Continue");
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)Error);
							HAL_Delay(500);
						}
					}
				}
				realweight = Measuing - no_load;
				if(errordelete >= 250){
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Down_finish = 6;
					bdownfinish_0 = true;
					break;
				}
			}
			Drum_Motor(2);
		}
		else if(copies == 3){
			int16_t he[80] = {0};
			uint16_t junzhi = 0;
			int zongshu = 0;
			int frybridge = 0;
			int lowproduct = 0;
			while(Measuing < custvs.CL + no_load  - chavalue){
				static TIME downfinishtime;
				downfinish_0 = GetDiffTime(&downfinishtime,&bdownfinish_0);
				if(downfinish_0 <= 6 || diandong == 1){
					//if(downfinish_0 >= 5){
						if(Measuing <= smallwei * custvs.CL + no_load - chavalue){
							if(drumover >= 5){
								if(AdcBuf[3] >= factdsp.P13){
									
									//±®æØ»°œ˚£¨ªª≥…’˝∑¥œÚ◊™
									/*custvs.DrTQ++;
									drum = 1;
									Lift_Motor(On);//…œ…˝
//									HAL_Delay(lifttime);
									HAL_Delay(1500);
									Lift_Motor(2);*/
									
									//’˝∑¥œÚ◊™
									if(factdsp.T1 == 999){
										Drum_Motor(Off);
										HAL_Delay(factdsp.T2 * 1000);
										drumover = 0;
									}
									else{
										if(drum_motor_roration){
											drum_motor_roration = 0;
											Drum_Motor(0);
											HAL_Delay(drumtime);
										}
										else{
											drum_motor_roration = 1;
											Drum_Motor(1);
											HAL_Delay(drumtime);
										}
										//HAL_Delay(10);
									}
								}
								drumover = 0;
							}
							else{
								if(AdcBuf[3] >= factdsp.P13){
									drumover++;
									Drum_Motor(2);
								}
								else
									drumover = 0;
							}
						}
					//}
					//TIM3_Disable();
					he[junzhi++] = AdcBuf[0];
					HAL_Delay(1);
					if(junzhi == 80){
						for	(uint16_t i=0;i<80-1;i++){
							for(uint16_t j=0;j<80-i-1;j++){
								if(he[j] > he[j+1]){
									int asd = he[j+1];
									he[j+1] = he[j];
									he[j] = asd;
								}
							}
						}
						for(uint16_t i=20;i<60;i++){
							zongshu += he[i];
						}
						zongshu = zongshu / 40;
						Measuing = zongshu * 11000 / chengzADC ;
						zongshu = 0;
						memset(he,0,sizeof(he));
						if(Measuing < custvs.CL + no_load - chavalue){
							static TIME rorationtime;
							roration_time = GetDiffTime(&rorationtime,&broration);
							if(factdsp.P19 == 0){
								if(roration_time - roration >= factdsp.T1 && drum_motor_roration){
									//±‰∑¥œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 0;
								}
								else if(roration_time - roration >= factdsp.T2 && !drum_motor_roration){
									//±‰’˝œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 1;
								}
								if(Measuing <= 0.9 * custvs.CL + no_load +  - chavalue){
									if(drum_motor_roration){
										Drum_Motor(On);
										HAL_Delay(drumtime);
									}
									else{
										Drum_Motor(Off);
										HAL_Delay(drumtime);
									}
								}
								else{
									static TIME Inching;
									inchingtime = GetDiffTime(&Inching,&binching);
									if(drum_motor_roration)
										Drum_Motor(On);
									else
										Drum_Motor(Off);
									HAL_Delay(delaytt);
									Drum_Motor(2);
									HAL_Delay(delaytt1);
									diandong = 1;
								}
							}
							else{
								if(roration_time - roration >= factdsp.T1 && drum_motor_roration){
									//±‰∑¥œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 0;
								}
								else if(roration_time - roration >= factdsp.T2 && !drum_motor_roration){
									//±‰’˝œÚ◊™∂Ø
									//Drum_Motor(2);
									broration = TRUE;
									roration_time = 0;
									drum_motor_roration = 1;
								}
								if(Measuing <= factdsp.P21 * custvs.CL / 100 + no_load - chavalue){
									if(drum_motor_roration){
										Drum_Motor(On);
										HAL_Delay(drumtime);
									}
									else{
										Drum_Motor(Off);
										HAL_Delay(drumtime);
									}
								}
								else{
									static TIME Inching;
									inchingtime = GetDiffTime(&Inching,&binching);
									if(drum_motor_roration)
										Drum_Motor(On);
									else
										Drum_Motor(Off);
									HAL_Delay(delaytt);
									Drum_Motor(2);
									HAL_Delay(delaytt1);
									diandong = 1;
								}
							}
							if(inchingtime >= 10){
								Down_finish = 5;
								break;
							}
						}
						else{
							Down_finish = 5;
						}
						junzhi = 0;
//						if(Measuing < 4000){
//							Down_finish = 3;
//							break;
//						}
					}
					if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
						char Error[48] = {0};
						sprintf(Error,"04A Low Produc");
						if(LARGE_SET == GPIO_PIN_RESET){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
						}
						else if(factdsp.P18){
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Error);
						}
					}
				}
				else if(downfinish_0 > 6 && diandong == 0){
					Drum_Motor(2);
					broration = TRUE;
					drum_motor_roration = 1;
					if(HAL_GPIO_ReadPin(lowproduct_GPIO_Port,lowproduct_Pin) == 1){
						if(deletewarn >= 1){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							deletewarn = 0;
							TIM4_Disable();
							bdownfinish_0 = true;
							zerofinish = 0;
	//						disweight = 0;
							weight = 300;
							lowproduct = 0;
							Lift_Motor(On);
							while(1){
								Measuing = AdcBuf[0] * 10000 * 3.3 / chengzADC / 3;
								if(Measuing >= liftweight){
									HAL_Delay(delaysd);
									Lift_Motor(2);
									Measuing = 0;
									HAL_Delay(haltime);
									break;
								}
							}
						}
						else if(lowproduct == 0){
							Lift_Motor(On);//…œ…˝
							HAL_Delay(2250);
							Lift_Motor(2);
							lowproduct = 1;
							TIM4_Enable();
						}
						else if(factdsp.P18){
							Drum_Motor(2);
							char Error[48] = {0};
							char Errorexplain[48] = {0};
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							sprintf(Error,"Err-04A");
							sprintf(Errorexplain,"Low Product Add Food");
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)Error);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Errorexplain);
							sprintf(Error,"Press L to Continue");
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)Error);
							HAL_Delay(500);
						}
					}
					else{
						if(deletewarn >= 1){
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							deletewarn = 0;
							TIM4_Disable();
							bdownfinish_0 = true;
							zerofinish = 0;
	//						disweight = 0;
							weight = 300;
							Down_finish = 4;
							break;
						}
						else if(frybridge == 0){
							Lift_Motor(On);//…œ…˝
							HAL_Delay(2250);
							Lift_Motor(2);
							frybridge = 1;
							TIM4_Enable();
						}
						else{
							Drum_Motor(2);
							char Error[20] = {0};
							char Errorexplain[40] = {0};
							Lcm_GotoXY(0,0,0);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							Lcm_GotoXY(0,0,1);
							Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
							HAL_Delay(100);
							sprintf(Error,"Err-04B");
							sprintf(Errorexplain,"Fry Brigde");
							Lcm_GotoXY(0,0,1);
							Lcm_Disp_String((unsigned char*)Error);
							Lcm_GotoXY(0,1,1);
							Lcm_Disp_String((unsigned char*)Errorexplain);
							sprintf(Error,"Press L to Continue");
							Lcm_GotoXY(0,0,0);
							Lcm_Disp_String((unsigned char*)Error);
							HAL_Delay(500);
						}
					}
				}
				realweight = Measuing - no_load;
				if(errordelete >= 250){
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Down_finish = 6;
					bdownfinish_0 = true;
					break;
				}
			}
			Drum_Motor(2);
		}
		binching = true;
		bDown_Time = true;
		diandong = 0;
		inchingtime = 0;
	}
	else if(Down_finish == 5){
		bdownfinish_0 = true;
		HAL_Delay(1000);
		Lift_Motor(On);//…œ…˝
		HAL_Delay(lifttime);
		Lift_Motor(2);
		if(weight == 100)
			custvs.SC++;//–°∑›∑÷≈‰◊‘º”
		else if(weight == 200)
			custvs.MC++;
		else
			custvs.LC++;
		custvs.DC++;
		Down_finish = 1;
		TIM3_Enable();
		broration = TRUE;
		roration_time = 0;
		drum_motor_roration = 1;
	}
	else if(Down_finish == 1){
		TIM4_Enable();
		if(HAL_GPIO_ReadPin(dooropen_GPIO_Port,dooropen_Pin) == 0){
		//ºÏ≤‚µ Ω’®¿∫
			if(doorlock == 0){
				if(HAL_GPIO_ReadPin(basket_on_GPIO_Port,basket_on_Pin) == 0){
					HAL_Delay(factdsp.P16 - 10);
					if(HAL_GPIO_ReadPin(basket_on_GPIO_Port,basket_on_Pin)){
						return;
					}
					DoorOpen_Motor(On);//ø™√≈µÁª˙¥Úø™---’˝◊™
					doorlock = 1;
					/*if(AdcBuf[2] >= factdsp.P14){
						uint8_t aadx = 0;
						while(aadx < 10){
							HAL_Delay(10);
							if(AdcBuf[2] >= factdsp.P14)
								aadx++;
							else
								break;
						}
						if(aadx >= 10){
	//						Lift_Motor(On);//…œ…˝
	////						HAL_Delay(lifttime);
	//						HAL_Delay(1500);
	//						Lift_Motor(2);//…œ…˝
							DoorOpen_Motor(Off);
							osDelay(800);
							DoorOpen_Motor(2);
							custvs.DTQ++;
							opendoor = 1;
						}
					}*/
					DiffTime++;
					whiledown++;
				}
			}
		}
		else{
			doorlock = 0;
			DoorOpen_Motor(2);
			Down_finish = 2;
			whiledown = 0;
			HAL_Delay(delaytime);
			TIM4_Disable();
			return;
		}
		if(doorlock){
			doorzzz++;
			if(doorzzz >= weisig || AdcBuf[2] >= factdsp.P14){
				DoorOpen_Motor(Off);
				osDelay(800);
				DoorOpen_Motor(2);
////				osDelay(1000);
////				DoorOpen_Motor(On);
				doorlock = 0;
				doorzzz = 0;
				opendoor = 1;
			}
			else
				HAL_Delay(100);
		}
	}
	else if(Down_finish == 2){
		DoorOpen_Motor(Off);
		DiffTime++;
		if(AdcBuf[2] >= factdsp.P14){
			uint8_t aadx = 0;
			while(aadx < 10){
				HAL_Delay(100);
				if(AdcBuf[2] >= factdsp.P14)
					aadx++;
			}
			if(aadx >= 10){
//				Lift_Motor(On);//…œ…˝
////				HAL_Delay(lifttime);
//				HAL_Delay(1500);
//				Lift_Motor(2);//…œ…˝
				custvs.DTQ++;
				closedoor = 1;
			}
		}
		while(1){
			HAL_Delay(50);
			DoorOpen_Motor(Off);
			HAL_Delay(50);
			DiffTime++;
			if(DiffTime > close_time){
				DoorOpen_Motor(2);
				break;
			}
		}
		if(HAL_GPIO_ReadPin(basket_on_GPIO_Port,basket_on_Pin)){
			HAL_Delay(factdsp.P17);
			if(HAL_GPIO_ReadPin(basket_on_GPIO_Port,basket_on_Pin) == 0)
				return;
			DiffTime = 0;
			Down_finish = 4;
			bDown_Time = true;
		}
		no_load = 0;
//		disweight = 0;
//		disweight1 = 0;
//		weightfenshu = 0;
//		weightfenshu1 = 0;
		berror_code = 0;
		highalarm = 0;
		lowalarm = 0;
		doorzzz = 0;
		ParamSave();
	}
	Switching_Value();
}

void Switching_Value(void)
{
	static uint8_t bdoor_sensor = true;
	static uint32_t door_sensor_time = 0;
	static uint8_t bno_door = true;
	static uint32_t no_doortime = 0;
	/*if(HAL_GPIO_ReadPin(Outside_DoorOpen_GPIO_Port,Outside_DoorOpen_Pin)){
		static TIME outside;
		door_outside_time = GetDiffTime(&outside,&bdoor_outside);
		if(door_outside_time >= 60){
			if(outdoor == 0){
				char warning1[20] = {0};
				char warning2[40] = {0};
				Usart3_Printf("√≈ø™πÿ ß–ßªÚŒ¥≤ÂµÁ    ¥ÌŒÛ¥˙¬Î£∫dA\r\n");
				sprintf(warning1,"ERR-dA");
				sprintf(warning2,"Door Switch Unplugged");
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				Lcm_Disp_String((unsigned char *)warning1);
				Lcm_GotoXY(0,1,0);
				Lcm_Disp_String((unsigned char *)warning2);
				outdoor = 1;
				Record_Door_Opening_alarm++;
				custvs.DTO++;
				errorcode = 1;
			}
		}
	}*/
	
	//√≈¥´∏–∆˜---œ¬¡œ”√µƒ
	if(HAL_GPIO_ReadPin(dooropen_GPIO_Port,dooropen_Pin)){
		static TIME door_sensor;
		door_sensor_time = GetDiffTime(&door_sensor,&bdoor_sensor);
		if(door_sensor_time >= 60){
			if(sensordoor == 0){
				char warning1[20] = {0};
				char warning2[40] = {0};
				Lcm_GotoXY(0,0,1);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				HAL_Delay(100);
				Usart3_Printf("√≈¥´∏–∆˜ ß–ßªÚŒ¥≤ÂµÁ    ¥ÌŒÛ¥˙¬Î£∫07-1\r\n");
				sprintf(warning1,"ERR-07-1");
				sprintf(warning2,"Door Sensor Unplugged");
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
				Lcm_Disp_String((unsigned char *)warning1);
				Lcm_GotoXY(0,1,0);
				Lcm_Disp_String((unsigned char *)warning2);
//				sensordoor = 1;
				errorcode_0 = 1;
				berror_code = 1;
				ssada = 1;
				HAL_Delay(500);
			}
		}
	}
	else if(HAL_GPIO_ReadPin(DoorOpen_motor_en_GPIO_Port,DoorOpen_motor_en_Pin)){
		if(AdcBuf[2] < 100){
			static TIME no_door;
			no_doortime = GetDiffTime(&no_door,&bno_door);
			if(no_doortime >= 20){
				if(nodoor == 0){
					char warning1[20] = {0};
					char warning2[40] = {0};
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					HAL_Delay(100);
	//				Usart3_Printf("√≈µÁª˙ ß–ßªÚŒ¥≤ÂµÁ    ¥ÌŒÛ¥˙¬Î£∫07-3\r\n");
					sprintf(warning1,"ERR-07-3");
					sprintf(warning2,"Door Motor Unplugged");
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_Disp_String((unsigned char *)warning1);
					Lcm_GotoXY(0,1,0);
					Lcm_Disp_String((unsigned char *)warning2);
	//				nodoor = 1;
					errorcode_0 = 1;
					berror_code = 1;
					ssada = 1;
					HAL_Delay(500);
				}
			}
		}
		else{
			bno_door = true;
			no_doortime = 0;
		}
		if(Down_finish != 1){
			HAL_GPIO_WritePin(DoorOpen_motor_en_GPIO_Port,DoorOpen_motor_en_Pin, GPIO_PIN_RESET);
		}
	}
	else if(AdcBuf[4] <= 223){
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
			char warning1[48] = {0};
			char warning2[48] = {0};
			Lcm_GotoXY(0,0,1);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			Lcm_GotoXY(0,0,0);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			HAL_Delay(100);
//			Usart3_Printf("ø‚Œ¬ÃΩÕ∑ ß–ßªÚŒ¥≤ÂµÁ    ¥ÌŒÛ¥˙¬Î£∫P1\r\n");
			sprintf(warning1,"ERR-P1");
			sprintf(warning2,"C Temp Probe Unplugged");
			if(c_sensor == 0){
//				c_sensor = 1;
				errorcode_0 = 1;
				berror_code = 1;
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char *)warning1);
				Lcm_GotoXY(0,1,0);
				Lcm_Disp_String((unsigned char *)warning2);
				ssada = 1;
				HAL_Delay(500);
			}
		}
	}
	else if(AdcBuf[5] <= 273){
		if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0 && factcp.P2 == 0){
			char warning1[48] = {0};
			char warning2[48] = {0};
			Lcm_GotoXY(0,0,1);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			Lcm_GotoXY(0,0,0);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			HAL_Delay(100);
//			Usart3_Printf("’Ù∑¢∆˜ÃΩÕ∑ ß–ßªÚŒ¥≤ÂµÁ    ¥ÌŒÛ¥˙¬Î£∫P2\r\n");
			sprintf(warning1,"ERR-P2");
			sprintf(warning2,"V Temp Probe Unplugged");
			if(v_sensor == 0){
				Lcm_GotoXY(0,0,0);
				Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
//				v_sensor = 1;
				errorcode_0 = 1;
				berror_code = 1;
				Lcm_GotoXY(0,0,0);
				Lcm_Disp_String((unsigned char *)warning1);
				Lcm_GotoXY(0,1,0);
				Lcm_Disp_String((unsigned char *)warning2);
				ssada = 1;
				HAL_Delay(500);
			}
		}
	}
	else if(alarmsign == 1 && highalarm == 0){
		char warning1[48] = {0};
		char warning2[48] = {0};
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		Lcm_GotoXY(0,0,0);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		HAL_Delay(100);
		sprintf(warning1,"ERR-HA ");
		sprintf(warning2,"Temp is too high");
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char*)warning1);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char*)warning2);
		Record_High_Temp++;
		Record_Refri_Probe_alarm++;
		berror_code = 1;
//		highalarm = 1;
		ssada = 1;
		HAL_Delay(500);
	}
	else if(alarmsign == 2 && lowalarm == 0){
		char warning1[48] = {0};
		char warning2[48] = {0};
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		Lcm_GotoXY(0,0,0);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		HAL_Delay(100);
		sprintf(warning1,"ERR-LA ");
		sprintf(warning2,"Temp is too low");
		Lcm_GotoXY(0,0,0);
		Lcm_Disp_String((unsigned char*)warning1);
		Lcm_GotoXY(0,1,0);
		Lcm_Disp_String((unsigned char*)warning2);
		Record_Low_Temp++;
		Record_Refri_Probe_alarm++;
		berror_code = 1;
//		lowalarm = 1;
		ssada = 1;
		HAL_Delay(500);
	}
	else{
		bdoor_sensor = true;
		bno_door = true;
		//if(outdoor || sensordoor || nodoor || c_sensor || v_sensor){
		if(ssada == 1){
			nodoor = 0;
			outdoor = 0;
			sensordoor = 0;
			c_sensor = 0;
			v_sensor = 0;
			errorcode_0 = 0;
			berror_code = 0;
			Lcm_GotoXY(0,0,0);
			Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
			ssada = 0;
		}
		//}
	}
}

void DeviceCheck(void)
{
	//…Ë±∏◊‘ºÏ---VS
	//∑÷≈‰π¶ƒ‹
	//»Ìø™πÿ∞¥º¸4√Î---S/M/L£∫–°/÷–/¥Û
	//≤Œ ˝…Ë÷√
	if(Menu == 1){
		//Ω¯»Î≤Àµ•
		
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		Lcm_GotoXY(0,0,0);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		TIM3_Disable();
		MenuSelectShow();
		int16_t he[100] = {0};
		uint16_t junzhi = 0;
		int zongshu = 0;
		int16_t he1[100] = {0};
		uint16_t junzhi1 = 0;
		int zongshu1 = 0;
		while(Menu){
			Measuing = AdcBuf[0] * 11000 / chengzADC ;
			if(custdsp.Line == 1 && stm32_config.CUSTSelected2 && jiaozhunkey > 0){
				if(Downjiaozhun == 4){
					Lift_Motor(On);
//					Usart3_Printf("%d\r\n",(int)Measuing);
					HAL_Delay(10);
					if(Measuing >= liftweight){
						//Usart3_Printf("µΩ¥Ô¡¶æÿ,“‚Àº «ø…“‘ø™ º≥∆÷ÿ\r\n");
						HAL_Delay(delaysd_2);
						Lift_Motor(2);//Õ£÷π
						Downjiaozhun = 3;
						Measuing = 0;
						HAL_Delay(3000);
						//load_cell = 0;
					}
//					else if(AdcBuf[1] <= liftadc){
//						//Usart3_Printf("µΩ¥Ô¡¶æÿ,“‚Àº «ø…“‘ø™ º≥∆÷ÿ\r\n");
//						HAL_Delay(delaysd1_2);
//						Lift_Motor(2);//Õ£÷π
//						Downjiaozhun = 3;
//						Measuing = 0;
//						HAL_Delay(3000);
//						//load_cell = 0;
//					}
				}
				else if(Downjiaozhun == 3){
					uint8_t ax = 1;
					while(ax){
						he[junzhi++] = AdcBuf[0];
						HAL_Delay(1);
						if(junzhi == 100){
							for	(uint16_t i=0;i<100-1;i++){
								for(uint16_t j=0;j<100-i-1;j++){
									if(he[j] > he[j+1]){
										int asd = he[j+1];
										he[j+1] = he[j];
										he[j] = asd;
									}
								}
							}
							for(uint16_t i=20;i<80;i++){
								zongshu += he[i];
							}
							zongshu = zongshu / 60;
							custdsp.P02_P = zongshu * 11000 / chengzADC ;
							MenuSelectShow();
//							Usart3_Printf("ƒ£ƒ‚¡ø: %d\r\n ",zongshu);
//							Usart3_Printf(" µ≤‚÷ÿ¡ø: %d\r\n ",zongshu * 11000 / chengzADC);
//							Usart3_Printf("–£◊ºø’‘ÿ÷µ£∫%d g \r\n\r\n",custdsp.P02_P);
							Downjiaozhun = 0;
//							HAL_Delay(3000);
							memset(he,0,sizeof(he));
							junzhi = 0;
							zongshu = 0;
							ax = 0;
						}
						MenuSelectShow();
					}
				}
				else if(Downjiaozhun == 0){
					if(custdsp.Line == 1 && stm32_config.CUSTSelected2 >= 1 && jiaozhunkey == 2){
						uint8_t bx = 1;
						while(bx){
							he1[junzhi1++] = AdcBuf[0];
							HAL_Delay(1);
							if(junzhi1 == 100){
								for	(uint16_t i=0;i<100-1;i++){
									for(uint16_t j=0;j<60-i-1;j++){
										if(he1[j] > he1[j+1]){
											int asd = he1[j+1];
											he1[j+1] = he1[j];
											he1[j] = asd;
										}
									}
								}
								for(uint16_t i=20;i<80;i++){
									zongshu1 += he1[i];
								}
								zongshu1 = zongshu1 / 60;
								custdsp.P02_C = zongshu1 * 11000 / chengzADC - custdsp.P02_P;
								MenuSelectShow();
//								Usart3_Printf("ƒ£ƒ‚¡ø: %d\r\n ",zongshu1);
//								Usart3_Printf("–£◊º¥Û∑›÷µ£∫%d\r\n",custdsp.P02_C - custdsp.P02_P);
								Downjiaozhun = 4;
								jiaozhun = 0;
								zongshu1 = 0 ;
								junzhi1 = 0;
								memset(he1,0,sizeof(he1));
								bx = 0;
								Lift_Motor(On);//…œ…˝
								HAL_Delay(1500);
								Lift_Motor(2);//…œ…˝
								custvs.CP = custdsp.P02_P;
								custvs.CL = custdsp.P02_C;
							}
						}
						ParamSave();
						jiaozhunkey = 0;
					}
				}
				/*if(custdsp.P02_P >= 5750 && custdsp.P02_P <= 6250){
					//ø’‘ÿ’˝≥£
					custvs.CP = custdsp.P02_P;
					Usart3_Printf("ø’‘ÿ÷µ%d\r\n",custvs.CP);
				}
				//∑≈»Î¥Û∑› ÌÃı
				if(Measuing - custvs.CP >= 100){
					custdsp.P02_C = Measuing - custvs.CP;
					if(custdsp.P02_C >= 400 && custdsp.P02_C <= 600){
						//‘⁄∑∂Œßƒ⁄£¨ƒ«√¥±£¥Ê≤Œ ˝
						custvs.CL = custdsp.P02_C;
						jiaozhun = 0;
						custvs.CC++;//–£◊º¥Œ ˝º”“ª
						Usart3_Printf("¥Û∑›≤‚¡ø÷µ’˝≥£:%d\r\n",custvs.CL);
					}
				}*/
//				Usart3_Printf(" µ≤‚÷µ£∫%d %dø’‘ÿ÷µ£∫%d ¥Û∑›÷µ£∫%d\r\n",(int)Measuing,Downjiaozhun,custdsp.P02_P,custdsp.P02_C - custdsp.P02_P);
			}
			Key_Scan();
			HAL_Delay(100);
		}
		Standby = 0;
	}
}

void Calibration(void)
{
	//«·∞¥“ª¥Œstandbyº¸/***********≥∆÷ÿ–£◊ºø™ º**************/
	if(Standby >= 100){
		//œ‘ æReady
		Lcm_GotoXY(0,0,1);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		Lcm_GotoXY(0,0,0);
		Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
		char basket[48] = {0};
		sprintf(basket,"Ready                   ");
		Lcm_GotoXY(0,0,1);
		Lcm_Disp_String((unsigned char*)basket);
		
		/*HAL_Delay(1000);
		Standby = 0;
		Menu = 1;
		stm32_config.Menu_Tier = 1;
		CUST_FACT = 0;
		jiaozhun = 1;
		DeviceCheck();
		return;*/
	}
}

uint8_t Check_Ch376sUart2Connect_(void)
{
    uint8_t x = 0, res;
  
    for(x = 0; x < 5; x++)		//»Ù ◊¥ŒÕ®—∂ ß∞‹£¨‘Ú∂‘CH376–æ∆¨‘ŸΩ¯––5¥ŒÕ®—∂≤‚ ‘
    {
        xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* ≤‚ ‘µ•∆¨ª˙”ÎCH376÷Æº‰µƒÕ®—∂Ω”ø⁄ */
        xWriteCH376Data( 0x65 );
        res = xReadCH376Data( );

        /* Õ®—∂Ω”ø⁄≤ª’˝≥£,ø…ƒ‹‘≠“Ú”–:Ω”ø⁄¡¨Ω”“Ï≥£,∆‰À¸…Ë±∏”∞œÏ(∆¨—°≤ªŒ®“ª),¥Æø⁄≤®Ãÿ¬ ,“ª÷±‘⁄∏¥Œª,æß’Ò≤ªπ§◊˜ */
        if(res == 0x9A)
        {
					printf("\r\nCH376”ÎSTM3–æ∆¨’˝≥££°Ω” ’ ˝æ›Œ™£∫%#X  char: %c\r\n", res,res);
           // printf("Udisk.uarttest == %d\r\n", Udisk.uarttest);

            return USB_INT_SUCCESS; //Õ®—∂’˝≥££¨Ã¯≥ˆÕ®—∂≤‚ ‘°£
        }
        else
        {

            printf("CH376”ÎSTM32Õ®—∂ ß∞‹£°∑µªÿ÷µŒ™£∫%X\r\n", res);
            printf("’˝‘⁄Ω¯––µ⁄ %d ¥ŒÕ®—∂÷ÿ ‘°£\r\n", x);
	
        }
    }
		return 0;
}
void usb_test(void)
{
	char usbdis[20];
	uint8_t temp;
	temp=Check_Ch376sUart2Connect_();
	if (temp== USB_INT_SUCCESS)
	{
//		sprintf(usbdis,"1 success");
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)usbdis);
//		HAL_Delay(1000);
//		printf( "Uart2Connect SUCCESS and get code: %#x\r\n",temp );
		temp = mInitCH376Host();
		if (temp !=USB_INT_SUCCESS) temp=mInitCH376Host();
	}
	else 
	{
//		sprintf(usbdis,"1 U failed");
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)usbdis);
//		HAL_Delay(1000);
//		printf("Uart2Connect error %#x\r\n",temp);
		
	}
	
	if (temp== USB_INT_SUCCESS)
	{
//		sprintf(usbdis,"2 success");
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)usbdis);
//		HAL_Delay(1000);
//		printf("CH376Host init [ OK ] get code:%#x\r\n\r\n",temp);
		temp=Check_UdiskConnect();
	}
	else
	{
//		sprintf(usbdis,"2 U failed");
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)usbdis);
//		HAL_Delay(1000);
//		printf("CH376Host init [NG]\r\n");
		
	}
	if (temp == USB_INT_SUCCESS)//USB_INT_SUCCESS=0x14
	{
		udiskread = 1;
//		sprintf(usbdis,"3 success");
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)usbdis);
//		HAL_Delay(1000);
//		printf("CH376DiskConnect ∫Ø ˝ ºÏ≤‚µΩ U≈Ã≤Â»Î°£\r\n");
	}
	else
	{
//		sprintf(usbdis,"3 U failed");
//		Lcm_GotoXY(0,0,0);
//		Lcm_Disp_String((unsigned char*)usbdis);
//		HAL_Delay(1000);
//		printf("CH376DiskConnect ∫Ø ˝ Œ¥ºÏ≤‚µΩ U≈Ã≤Â»Î°£\r\n");
	}
	
	
}

uint8_t writeUDisk()
{
//“ª∑÷÷”º«¬º“ª¥Œ
//    static TIME UDiskStartTime;
//    uint32_t UDiskDiffTime = GetDiffTime(&UDiskStartTime, &bUDiskStartTime);
	static uint8_t t=0;
	t++;
					
//		printf("TimeToWriteUDisk---->\r\n");
	memset(ShortName, 0, sizeof(ShortName));
	sprintf(ShortName, "/PARAMTER.TXT");
	uint8_t s = CH376FileOpen((unsigned char *)ShortName);
//		printf("File open----> %#X\r\n",s);

	if(s == ERR_DISK_DISCON || s == DEF_DISK_DISCONN)
	{
			UDiskRemove();
			Udisk.disk = 0;
			Udisk.mount = 0;
			return 0;
	}
	else if(s == ERR_MISS_FILE)
	{
		s = CH376FileCreatePath((PUINT8)ShortName);
		if(s == USB_INT_SUCCESS){
			char udis[40] = {0};
			sprintf(udis,"File Create Success");
			Lcm_GotoXY(0,0,1);
			Lcm_Disp_String((unsigned char*)udis);
			HAL_Delay(1000);
		}
		return 1;
	}
	else if ( s == USB_INT_SUCCESS )
	{
		//TIM3_Disable();
		char FileDataBuf[350] = {0};
		memset(FileDataBuf, 0, sizeof(FileDataBuf));
//				uint16_t len = sprintf(FileDataBuf, "[write:[ %d ]  times ]%s",t,"UDISC write function\r\n try xd xa \xd\xa" ); /* Ω´∂˛÷∆÷∆ ˝æ›∏Ò ΩŒ™“ª––◊÷∑˚¥Æ */
		/*uint16_t len = sprintf(FileDataBuf,"St:%d,Hy:%.0f,LS:%d,US:%d,ot:%.0f,oE:%.0f,od:%d,AC:%d,Cy:%d,Cn:%d,dAd:%d,\r\ndy:%d,\r\ntd:%d,dE:%d,id:%d,Md:%d,dd:%d,dF:%d,dt:%d,\r\nFd:%d,FS:%d,FAd:%d,Fn:%d,FF:%d,dAd2:%d,\r\nAU:%d,AL:%d,Ad:%d,dA:%d,\r\nP10:%d,P11:%d,P13:%d,P14:%d,P16:%d,P17:%d,P18:%d,P19:%d,P21:%d,P22:%d,P23:%d,P29:%d,P30:%d\r\n\r\n",
																				factcp.St,factcp.Hy,factcp.LS,factcp.US,factcp.ot,factcp.oE,factcp.od,factcp.AC,factcp.Cy,factcp.Cn,factcp.dAd,//11
																				factdis.dy,//1
																				factdef.td,factdef.dE,factdef.id,factdef.Md,factdef.dd,factdef.dF,factdef.dt,//7
																				factfan.Fd,factfan.FS,factfan.FAd,factfan.Fn,factfan.FF,factfan.dAd,//6
																				factal.AU,factal.AL,factal.Ad,factal.dA,//4
																				factdsp.P10,factdsp.P11,factdsp.P13,factdsp.P14,factdsp.P16,factdsp.P17,factdsp.P18,factdsp.P19,factdsp.P21,factdsp.P22,factdsp.P23,factdsp.P29,factdsp.P30);//13*/
		uint16_t len = sprintf(FileDataBuf,"=1,=%d,=%.1f,=%d,=%d,=%.1f,=%d,=%.1f,=%d,=%d,=%d,=%d,=%d,\r\n=%d,=%d,=%d,=%d,\r\n=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,\r\n=%d,=%d,=%d,=%d,=%d,=%d,\r\n=%d,=%d,=%d,=%d,\r\n=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d,=%d\r\n\r\n",
																						factcp.St,factcp.Hy,factcp.LS,factcp.US,factcp.ot,factcp.P2,factcp.oE,factcp.od,factcp.AC,factcp.Cy,factcp.Cn,factcp.dAd,//11
																						factdis.CF,factdis.rE,factdis.Ld,factdis.dy,//1
																						factdef.td,factdef.dE,factdef.id,factdef.Md,factdef.dd,factdef.dF,factdef.dt,factdef.dP,//7
																						factfan.Fd,factfan.FS,factfan.FAd,factfan.Fn,factfan.FF,factfan.dAd,//6
																						factal.AU,factal.AL,factal.Ad,factal.dA,//4
																						factdsp.P10,factdsp.P11,factdsp.P13,factdsp.P14,factdsp.P16,factdsp.P17,factdsp.P18,factdsp.P19,factdsp.P21,factdsp.P22,factdsp.P23,factdsp.P26,factdsp.P28,factdsp.P29,factdsp.P30);//13
		CH376ByteLocate(0xFFFFFFFF);//“∆∂ØŒƒº˛÷∏’ÎµΩŒƒº˛ƒ©Œ≤
		CH376ByteWrite((PUINT8)FileDataBuf, len, &len);
		//TIM3_Enable();

		CH376FileClose( TRUE );  /* πÿ±’Œƒº˛,…»«¯ƒ£ ΩÕ®≥£≤ª◊‘∂Ø∏¸–¬Œƒº˛≥§∂»,–Ë“™◊‘∂Ø∏¸–¬Œƒº˛≥§∂» */
//		GetUdiskFreeSpace();//≤È—ØU≈Ã £”‡ø’º‰
//			printf("-->>succeful:%d tiems ok  ****************************\r\n",t);
//		if(Menu != 1)
//			readUdisk();
		return 2;
	}
}
void readUdisk(void)
{ 
    uint8_t readBuf[20] = {0};
    memset(readBuf, 0, sizeof(readBuf));
    uint16_t len = sprintf((char *)readBuf,"/PARAMTER.TXT");

    uint8_t s = CH376FileOpen(readBuf);
    if(s == ERR_MISS_FILE){
//				printf("readUdisk file open [ ERR_MISS_FILE ]");
    }
    else if(s == ERR_DISK_DISCON || s == DEF_DISK_DISCONN){
//				printf("readUdisk file open [ ERR_DISK_DISCON ]");
        UDiskRemove();
        HAL_Delay(2000);
    }
    else if(s == USB_INT_SUCCESS){
        CH376ByteLocate(0);
        uint8_t ReadBuffer[300] = {0};
		char readBuff[300] = {0};
//		char buffer[300] = {0};
//		char* xx = 0;
		char* p = 0;
        len = 0;
        CH376ByteRead(ReadBuffer, 300, &len);
				sprintf(readBuff,"%s",ReadBuffer);
//				sprintf(buffer,"%s",ReadBuffer);
//				xx = strtok(buffer,",");
//				xx = strtok(xx,"=");
//				xx = strtok(NULL,"=");
//				factcp.St = atoi(xx);
				uint16_t aad = 0;
				p = strtok(readBuff,"=");
				while(p != NULL){
					if(aad == 0){
						p = strtok(NULL,"=");
						factcp.St = custcp.St = atoi(p);
					}
					else if(aad == 1){
						factcp.Hy = custcp.Hy = atof(p);
					}
					else if(aad == 2){
						factcp.LS = atoi(p);
					}
					else if(aad == 3){
						factcp.US = atoi(p);
					}
					else if(aad == 4){
						factcp.ot = custcp.ot = atof(p);
					}
					else if(aad == 5){
						factcp.P2 = custcp.p2 = atof(p);
					}
					else if(aad == 6){
						factcp.oE = atof(p);
					}
					else if(aad == 7){
						factcp.od = atoi(p);
					}
					else if(aad == 8){
						factcp.AC = custcp.AC = atoi(p);
					}
					else if(aad == 9){
						factcp.Cy = atoi(p);
					}
					else if(aad == 10){
						factcp.Cn = atoi(p);
					}
					else if(aad == 11){
						factcp.dAd = atoi(p);
					}
					else if(aad == 12){
						factdis.CF = custdis.CF = atof(p);
					}
					else if(aad == 13){
						factdis.rE = custdis.rE = atof(p);
					}
					else if(aad == 14){
						factdis.Ld = atof(p);
					}
					else if(aad == 15){
						factdis.dy = atoi(p);
					}
					else if(aad == 16){
						factdef.td = atoi(p);
					}
					else if(aad == 17){
						factdef.dE = custdef.dE = atoi(p);
					}
					else if(aad == 18){
						factdef.id = custdef.id = atoi(p);
					}
					else if(aad == 19){
						factdef.Md = custdef.Md = atoi(p);
					}
					else if(aad == 20){
						factdef.dd = atoi(p);
					}
					else if(aad == 21){
						factdef.dF = atoi(p);
					}
					else if(aad == 22){
						factdef.dt = atoi(p);
					}
					else if(aad == 23){
						factdef.dP = atof(p);
					}
					else if(aad == 24){
						factfan.Fd = custfan.Fd = atoi(p);
					}
					else if(aad == 25){
						factfan.FS = atoi(p);
					}
					else if(aad == 26){
						factfan.FAd = atoi(p);
					}
					else if(aad == 27){
						factfan.Fn = custfan.Fn = atoi(p);
					}
					else if(aad == 28){
						factfan.FF = custfan.FF = atoi(p);
					}
					else if(aad == 29){
						factfan.dAd = atoi(p);
					}
					else if(aad == 30){
						factal.AU = custal.AU = atoi(p);
					}
					else if(aad == 31){
						factal.AL = custal.AL = atoi(p);
					}
					else if(aad == 32){
						factal.Ad = atoi(p);
					}
					else if(aad == 33){
						factal.dA = atoi(p);
					}
					else if(aad == 34){
						factdsp.P10 = atoi(p);
					}
					else if(aad == 35){
						factdsp.P11 = atoi(p);
					}
					else if(aad == 36){
						factdsp.P13 = atoi(p);
					}
					else if(aad == 37){
						factdsp.P14 = atoi(p);
					}
					else if(aad == 38){
						factdsp.P16 = atoi(p);
					}
					else if(aad == 39){
						factdsp.P17 = atoi(p);
					}
					else if(aad == 40){
						factdsp.P18 = atoi(p);
					}
					else if(aad == 41){
						factdsp.P19 = atoi(p);
					}
					else if(aad == 42){
						factdsp.P21 = atoi(p);
					}
					else if(aad == 43){
						factdsp.P22 = atoi(p);
					}
					else if(aad == 44){
						factdsp.P23 = atoi(p);
					}
					else if(aad == 45){
						factdsp.P26 = atoi(p);
					}
					else if(aad == 46){
						factdsp.P28 = atoi(p);
					}
					else if(aad == 47){
						factdsp.P29 = atoi(p);
					}
					else if(aad == 48){
						factdsp.P30 = atoi(p);
						break;
					}
					
					aad++;
					p = strtok(NULL,"=");
				}
//				len=sprintf(readBuff,"%s\r\n",ReadBuffer);
//        printf("\r\n<<--CH376ByteRead: %s\r\n len: %d\r\n", readBuff, len); /* “‘◊÷Ω⁄Œ™µ•Œª¥”Œƒº˛∂¡≥ˆ ˝æ›,◊º±∏∂¡ 512 ∏ˆ◊÷Ω⁄ */
        CH376FileClose( TRUE );
		ParamSave();
    }
	return;
}



void UDiskRemove()
{
		uint8_t s = SafeRemoveDisk();//∞≤»´“∆≥˝U≈Ã
    if(s == USB_INT_SUCCESS || s == 0)
    {
        UDiskRemove();
        HAL_Delay(3000);
    }
    printf("U Disk Removed");
//    bIsUdiskInsert = false;
//    UdiskMounted = false;
//    InitUdiskInsert = false;
   // stm32_config.iUDiskStatus = false;
}


int16_t GetUdiskFreeSpace()
{
    UINT8   UdiskInfoBuf[64];
    memset(UdiskInfoBuf, 0, sizeof(UdiskInfoBuf));
    uint16_t volume;
    CH376DiskQuery( (PUINT32)UdiskInfoBuf );  /* ≤È—Ø¥≈≈Ã £”‡ø’º‰–≈œ¢,…»«¯ ˝ */

    /* ºÏ≤ÈU≈ÃªÚ’ﬂSDø®µƒ £”‡ø’º‰,µ•Œª MB £¨volume ◊Ó¥Û÷µŒ™ 65535MB, 64GB */
    volume = *(PUINT32)UdiskInfoBuf / ( 1000000 / DEF_SECTOR_SIZE );

    if (volume >= 50)
    {
        Udisk.freespace = 1;
        //printf("Udisk.freespace == %d\r\n", Udisk.freespace);
    }
    else
    {
        Udisk.freespace = 0;
        //printf("Udisk.freespace == %d\r\n", Udisk.freespace);
    }
    //printf( "DiskQuery: \r\n" );
    printf( "’˝‘⁄≤È—Ø¥≈≈Ã £”‡ø’º‰°£free cap = %d MB\r\n", volume );  /* …œ√Ê“ª––µƒº∆À„ø…ƒ‹ª·“Á≥ˆ,ªª∏ˆÀ≥–Úº∆À„ */
    return volume;
}
void TIM3_Enable(void)
{
    HAL_TIM_Base_Start_IT(&htim3);
}

void TIM3_Disable(void)
{
    HAL_TIM_Base_Stop_IT(&htim3);
}

void TIM4_Enable(void)
{
    HAL_TIM_Base_Start_IT(&htim4);
}

void TIM4_Disable(void)
{
    HAL_TIM_Base_Stop_IT(&htim4);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart5){
	}
}
void task_RX_TX(void *paramter)
{
	//uint8_t ser_sync_code1 = SER_SYNC_CODE1;
	//HAL_UART_Transmit(&huart3, (uint8_t *)&ser_sync_code1, 1, 0xff);
//	UDiskDetect();
	Uart_RX_TX();
}

void task_TempShow(void *paramter)
{
	// ±º‰∏¸–¬
	RTCTimeUpdate();
	if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
		ShowTemp();
		Temperature_Alarm();
	}
}

void task_Freeze(void *paramter)
{
	/*Case_mean_value[i] = AdcBuf[4];
	Vapor_mean_value[i] = AdcBuf[5];
	i++;
	if(i > 99){
		for(uint8_t j=0;j<100-1;j++){
			for(uint8_t k=0;k<100-1-j;k++){
				if(Case_mean_value[k] > Case_mean_value[k+1]){
					int asd = Case_mean_value[k+1];
					Case_mean_value[k+1] = Case_mean_value[k];
					Case_mean_value[k] = asd;
				}
				if(Vapor_mean_value[k] > Vapor_mean_value[k+1]){
					int asd = Vapor_mean_value[k+1];
					Vapor_mean_value[k+1] = Vapor_mean_value[k];
					Vapor_mean_value[k] = asd;
				}
			}
		}
		for(uint8_t j=20;j<80;j++){
			mean_value += Case_mean_value[j];
			mean_value_1 += Vapor_mean_value[j];
		}
		CaseV = (mean_value / 60) * 3.3 / 4096;
		VaporV = (mean_value_1 / 60)* 3.3 / 4096;
		i = 0;
		mean_value = 0;
		mean_value_1 = 0;
	}*/
	//Usart3_Printf("µ⁄%d¥Œ:ƒ£ƒ‚¡ø£∫%d\r\n",i,Case_mean_value[i-1]);
	/*mean_value += Case_mean_value[i-1];
	mean_value_1 += Vapor_mean_value[i-1];
	CaseV = (mean_value / i)* 3.3 / 4096 - 0.02;
	VaporV = (mean_value_1 / i)* 3.3 / 4096 - 0.02;
	if(i > 99){
		//Usart3_Printf("æ˘÷µ1:%f  æ˘÷µ2:%f\r\n",((mean_value / i)* 3.3 / 4096),((mean_value_1 / i)* 3.3 / 4096));
		mean_value = 0;
		mean_value_1 = 0;
		i = 0;
	}*/
	/*int16_t fixC = 0;
	fixC = AdcBuf[4];
	if(fixC >= 0 && fixC < 10){
		CaseV = fixC * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixC);
	}
	else if(fixC >= 10 && fixC < 100){
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ«∞£∫%d\r\n",fixC);
//		fixC = fixC / 10;
//		fixC = fixC * 10;
		CaseV = fixC * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixC);
	}
	else if(fixC >= 100 && fixC < 1000){
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ«∞£∫%d\r\n",fixC);
//		fixC = fixC / 10;
//		fixC = fixC * 10;
		CaseV = fixC * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixC);
	}
	else if(fixC >= 1000){
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ«∞£∫%d\r\n",fixC);
//		fixC = fixC / 10;
//		fixC = fixC * 10;
		CaseV = fixC * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixC);
	}*/

	if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
		Freeze();
	}
//	Switching_Value();
}

void task_Defrost(void *paramter)
{
	/*int16_t fixV = 0;
	fixV = AdcBuf[5];
	if(fixV >= 0 && fixV < 10){
		VaporV = fixV * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixV);
	}
	else if(fixV >= 10 && fixV < 100){
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ«∞£∫%d\r\n",fixV);
//		fixV = fixV / 10;
//		fixV = fixV * 10;
		VaporV = fixV * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixV);
	}
	else if(fixV >= 100 && fixV < 1000){
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ«∞£∫%d\r\n",fixV);
//		fixV = fixV / 10;
//		fixV = fixV * 10;
		VaporV = fixV * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixV);
	}
	else if(fixV >= 1000){
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ«∞£∫%d\r\n",fixV);
//		fixV = fixV / 10;
//		fixV = fixV * 10;
		VaporV = fixV * 3.3 / 4096;
//		Usart3_Printf("ƒ£ƒ‚¡ø±‰ªØ∫Û£∫%d\r\n",fixV);
	}*/
	if(HAL_GPIO_ReadPin(Master_Slave_GPIO_Port,Master_Slave_Pin) == 0){
		Defrost();
		Fan();
	}
}

void task_DeviceCheck(void * paramter)
{
	Scan();
//	Allocation(1);
	DeviceCheck();
}


/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	if(htim->Instance == TIM3){
		if(SMALL == GPIO_PIN_RESET){
			//∞¥œ¬Small
//			Small++;
			if(Down_finish == 1)
				weight = stm32_config.S;
//			Usart3_Printf("–°%d ∑›¡ø%d\r\n", Small,weight);
//			HAL_Delay(10);
		}
		else if(MID == GPIO_PIN_RESET){
			//∞¥œ¬Mid
//			Mid++;
			if(Down_finish == 1)
				weight = stm32_config.M;
//			Usart3_Printf("÷–%d ∑›¡ø%d\r\n", Mid,weight);
			HAL_Delay(10);
		}
		
		if(LARGE_SET == GPIO_PIN_RESET){
			//∞¥œ¬Large
			Large_Set++;
			//Scan();
			if(Large_Set >= 250){
					//Ω¯»Î≤Àµ•
					Large_Set = 0;
					Menu = 1;
					stm32_config.Menu_Tier = 4;
			}
			else if(ssada){
					bAlarm = true;
					Alarm_3 = 0;
					ssada = 0;
					nodoor = 0;
					outdoor = 0;
					sensordoor = 0;
					c_sensor = 0;
					v_sensor = 0;
					errorcode_0 = 0;
					berror_code = 0;
					alarmsign = 0;
				}
//			Usart3_Printf("¥Û£∫%d ∑›¡ø%d\r\n",Large_Set,weight);
			//HAL_Delay(10);
		}
		else{
			if(Large_Set > 1 && Large_Set <= 249){
				Large_Set = 0;
				weight = stm32_config.LSet;
//				Usart3_Printf("¥Û£∫%d ∑›¡ø%d\r\n",Large_Set,weight);
			}
		}
		
		if(STANDBY  == GPIO_PIN_RESET){
			Standby++;
			if(Standby >= 250){
				static uint8_t bdown = 0;
				if(Down_finish == 6){
					if(bdown == 0)
						Down_finish = 4;//ø™ º∑÷≈‰
					else
						Down_finish = bdown;//∑÷≈‰π˝¡À£¨µ»¥˝’®¿∂
					/*Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					char basket[48] = {0};
					sprintf(basket,"Ready                   ");
					Lcm_GotoXY(0,0,1);
					Lcm_Disp_String((unsigned char*)basket);
					HAL_Delay(500);*/
				}
				else if(Down_finish == 1){
					/*Lcm_GotoXY(0,0,0);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡
					Lcm_GotoXY(0,0,1);
					Lcm_Wr_Command(0x01); //œ‘ æ«Â∆¡*/
					bdown = Down_finish;
					//πÿ±’∑÷≈‰π§◊˜
					Down_finish = 6;
				}
				else
					Standby = 0;
				Standby = 0;
			}
//			Usart3_Printf("ø™ º%d ∑›¡ø%d\r\n", Standby,weight);
//			HAL_Delay(10);
		}
		else{
			if(Standby < 250)
				Standby = 0;
		}
		
		if(UP == GPIO_PIN_RESET){
			//∞¥œ¬Small
			Up++;
			if(Up >= 250){
				factdef.dP = 0;
				Defrost();
				Up = 0;
			}
//			Usart3_Printf("…œ%d ∑›¡ø%d\r\n", Up,weight);
//			HAL_Delay(10);
		}
		else
			Up = 0;
		
		if(DOWN == GPIO_PIN_RESET){
			//∞¥œ¬Small
//			Down++;
//			Usart3_Printf("œ¬%d ∑›¡ø%d\r\n", Down,weight);
			HAL_Delay(10);
		}
/*		if(Menu){
			if(SMALL == GPIO_PIN_RESET){
				CUST_FACT = 0;
			}
			if(MID == GPIO_PIN_RESET){
				CUST_FACT = 1;
			}
			if(LARGE_SET == GPIO_PIN_RESET){
				Menu = 0;
			}
		}
*/
	}

	else if(htim->Instance == TIM4){
		if(Down_finish != 1)
			TIM3_Disable();
		if(LARGE_SET == GPIO_PIN_RESET){
			deletewarn++;
			if(ssada){
				bAlarm = true;
				Alarm_3 = 0;
				ssada = 0;
				nodoor = 0;
				outdoor = 0;
				sensordoor = 0;
				c_sensor = 0;
				v_sensor = 0;
				errorcode_0 = 0;
				berror_code = 0;
				alarmsign = 0;
			}
		}
		if(STANDBY == GPIO_PIN_RESET){
			errordelete++;
			if(errordelete >= 250){
				Down_finish = 6;
				bdownfinish_0 = true;
				drum = 0;
				opendoor = 0;
				closedoor = 0;
			}
		}
		else{
			if(errordelete >= 250){
				TIM4_Disable();
				HAL_Delay(1000);
				TIM3_Enable();
				errordelete = 0;
			}
		}
		if(Down_finish == 1 && drum == 0 && opendoor == 0 && closedoor == 0){
			if(HAL_GPIO_ReadPin(dooropen_GPIO_Port,dooropen_Pin) == 0){
			//ºÏ≤‚µΩ’®¿∫
				if(HAL_GPIO_ReadPin(basket_on_GPIO_Port,basket_on_Pin) == 0){
					HAL_Delay(factdsp.P16 - 10);
					if(HAL_GPIO_ReadPin(basket_on_GPIO_Port,basket_on_Pin)){
						return;
					}
					DoorOpen_Motor(On);//ø™√≈µÁª˙¥Úø™---’˝◊™
					doorlock = 1;
				}
			}
		}
	}
	else if(ssada){
		if(LARGE_SET == GPIO_PIN_RESET){
			bAlarm = true;
			Alarm_3 = 0;
			ssada = 0;
			nodoor = 0;
			outdoor = 0;
			sensordoor = 0;
			c_sensor = 0;
			v_sensor = 0;
			errorcode_0 = 0;
			berror_code = 0;
			alarmsign = 0;
		}
	}
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	Usart3_Printf("Error Handler!\r\n");
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
