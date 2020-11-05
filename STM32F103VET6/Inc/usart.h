/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define RX_LEN 1024
#define TX_LEN 1024
	 
#define USART1_RX_LEN 1024
#define USART1_TX_LEN 1024
#define USART2_RX_LEN 1024
#define USART2_TX_LEN 1024
#define USART3_RX_LEN 1024
#define USART3_TX_LEN 1024
#define UART4_RX_LEN 1024
#define UART4_TX_LEN 1024
#define UART5_RX_LEN 1024
#define UART5_TX_LEN 1024
	 
typedef	struct
{
	uint8_t RX_flag;
	uint16_t	RX_Size;
	uint8_t	RX_pData[RX_LEN];
	uint8_t	RX_preflag;
} USART_RECEIVETYPE1;

typedef	struct
{
	uint8_t RX_flag;
	uint16_t	RX_Size;
	char	*RX_pData[RX_LEN];
	uint8_t	RX_preflag;
} USART_RECEIVETYPE2;

typedef	struct
{
	uint8_t RX_flag;
	uint16_t	RX_Size;
	uint8_t	RX_pData[RX_LEN];
	uint8_t	RX_preflag;
} USART_RECEIVETYPE3;

typedef	struct
{
	char RX_flag;
	uint16_t	RX_Size;
	uint8_t	RX_pData[RX_LEN];
	uint8_t	RX_preflag;
} USART_RECEIVETYPE4;

typedef	struct
{
	uint8_t RX_flag;
	uint16_t	RX_Size;
	uint8_t	RX_pData[RX_LEN];
	uint8_t	RX_preflag;
} USART_RECEIVETYPE5;

extern USART_RECEIVETYPE1 UsartReceiveType1;
extern USART_RECEIVETYPE2 UsartReceiveType2;
extern USART_RECEIVETYPE3 UsartReceiveType3;
extern USART_RECEIVETYPE4 UsartReceiveType4;
extern USART_RECEIVETYPE5 UsartReceiveType5;
/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

void Usart2_Printf(char *fmt, ...);
void Usart3_Printf(char *fmt, ...);
void Uart4_Printf(char *fmt, ...);
void Uart5_Printf(char *fmt, ...);

extern unsigned char USART1_Rx_Buf[1024]; //USART1�洢��������
extern unsigned char USART1_Rx_flg;              //USART1������ɱ�־
extern unsigned int  USART1_Rx_cnt;              //USART1�������ݼ�����
extern unsigned char USART1_temp[1];       		 //USART1�������ݻ���

extern unsigned char USART2_Rx_Buf[1024]; 		 //USART2�洢��������
extern unsigned char USART2_Rx_flg;              //USART2������ɱ�־
extern unsigned int  USART2_Rx_cnt;              //USART2�������ݼ�����
extern unsigned char USART2_temp[1];      		 //USART2�������ݻ���

extern unsigned char USART3_Rx_Buf[1024];			 //USART3�洢��������
extern unsigned char USART3_Rx_flg;							 //USART3������ɱ�־
extern unsigned int  USART3_Rx_cnt;							 //USART3�������ݼ�����
extern unsigned char USART3_temp[1];       	 	 //USART3�������ݻ���

extern unsigned char UART4_Rx_Buf[1024];			 //USART4�洢��������
extern unsigned char UART4_Rx_flg;							 //USART4������ɱ�־
extern unsigned int  UART4_Rx_cnt;							 //USART4�������ݼ�����
extern unsigned char UART4_temp[1];       	 	 //USART4�������ݻ���

extern unsigned char UART5_Rx_Buf[1024];			 //USART5�洢��������
extern unsigned char UART5_Rx_flg;							 //USART5������ɱ�־
extern unsigned int  UART5_Rx_cnt;							 //USART5�������ݼ�����
extern unsigned char UART5_temp[1];       	 	 //USART5�������ݻ���
extern void UsartReceive_IDLE1(UART_HandleTypeDef *huart);
extern void UsartReceive_IDLE2(UART_HandleTypeDef *huart);
extern void UsartReceive_IDLE3(UART_HandleTypeDef *huart);
extern void UsartReceive_IDLE4(UART_HandleTypeDef *huart);
extern void UsartReceive_IDLE5(UART_HandleTypeDef *huart);
#define		ERR_USB_UNKNOWN		0xFA	/* δ֪����,��Ӧ�÷��������,����Ӳ�����߳������ */
#define		UART_INIT_BAUDRATE	115200	/* Ĭ��ͨѶ������9600bps,����ͨ��Ӳ�������趨ֱ��ѡ����ߵ�CH376��Ĭ��ͨѶ������ */

//#define delay_ms1 HAL_Delay
//#define delay_us1 HAL_Delay
#define	SER_SYNC_1		0x57			/* ���������ĵ�1������ͬ���� */
#define	SER_SYNC_2		0xAB			/* ���������ĵ�2������ͬ���� */


void	CH376_PORT_INIT( void );  		/* CH376ͨѶ�ӿڳ�ʼ�� */

//void	xEndCH376Cmd( void );			/* ����CH376����,������SPI�ӿڷ�ʽ */

void	xWriteCH376Cmd( uint8_t mCmd );	/* ��CH376д���� */

void	xWriteCH376Data( uint8_t mData );	/* ��CH376д���� */

uint8_t	xReadCH376Data( void );			/* ��CH376������ */

uint8_t	Query376Interrupt( void );		/* ��ѯCH376�ж�(INT#����Ϊ�͵�ƽ) */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
