///**
//  ******************************************************************************
//  * File Name          : lcd.c
//  * Description        : This file provides code for the configuration
//  *                      of all used smg pins.
//  ******************************************************************************

//  */

///* Includes ------------------------------------------------------------------*/
//#include "lcd.h"
//#include "main.h"
////#include "gpio.h"
//#include "stdio.h"
//#include "tim.h"


////#define STB(PinState) HAL_GPIO_WritePin(LCD_STB_GPIO_Port,LCD_STB_Pin,PinState)
////#define CLK(PinState) HAL_GPIO_WritePin(LCD_CLK_GPIO_Port,LCD_CLK_Pin,PinState)
////#define SIO(PinState) HAL_GPIO_WritePin(LCD_SIO_GPIO_Port,LCD_SIO_Pin,PinState)//#define ZERO1 		0x3F
////#define ZERO2 		0x00		/***********0***********/
////#define ONE1  		0x6
////#define ONE2  		0x00		/***********1***********/
////#define TWO1  		0xDB
////#define TWO2  		0x00		/***********2***********/
////#define THREE1 		0xCF
////#define THREE2	 	0x00		/***********3***********/
////#define FOUR1  		0xE6
////#define FOUR2  		0x00		/***********4***********/
////#define FIVE1  		0xED
////#define FIVE2  		0x00		/***********5***********/
////#define SIX1			0xFD
////#define SIX2			0x00		/***********6***********/
////#define SEVEN1		0x7
////#define SEVEN2 		0x00		/***********7***********/
////#define EIGHT1 		0xFF
////#define EIGHT2 		0x00		/***********8***********/
////#define NINE1  		0xef
////#define NINE2  		0x00		/***********9***********/


////#define A1    		0x86
////#define A2	  		0x24		/***********A***********/
////#define B1	  		0xFC
////#define B2	  		0x00		/***********B***********/
////#define C1	  		0x39
////#define C2	  		0x00		/***********C***********/
////#define D1	  		0xDE
////#define D2	  		0x00		/***********D***********/
////#define E1	  		0xF9
////#define E2	  		0x00		/***********E***********/
////#define FF1	  		0xF1
////#define FF2	  		0x00		/***********F***********/
////#define G1	  		0xBD
////#define G2	  		0x00		/***********G***********/
////#define H1	  		0xF6
////#define H2	  		0x00		/***********H***********/
////#define I1	  		0x9
////#define I2	  		0x12		/***********I***********/
////#define J1	  		0x1E
////#define J2	  		0x00		/***********J***********/
////#define K1	  		0x70
////#define K2	  		0xC			/***********K***********/
////#define L1	  		0x38
////#define L2	  		0x00		/***********L***********/
////#define M1	  		0x37
////#define M2	  		0x12		/***********M***********/
////#define N1	  		0x36
////#define N2	  		0x9			/***********N***********/
////#define O1	  		0xDC
////#define O2	  		0x00		/***********O***********/
////#define PP1	  		0xF3
////#define PP2	  		0x00		/***********P***********/
////#define Q1	  		0xE7
////#define Q2	  		0x00		/***********Q***********/
////#define R1	  		0x71
////#define R2	  		0xC			/***********R***********/
////#define S1	  		0x8
////#define S2	  		0xC			/***********S***********/
////#define T1	  		0x1
////#define T2	  		0x12		/***********T***********/
////#define U1	  		0x3E
////#define U2	  		0x00		/***********U***********/
////#define V1	  		0x6
////#define V2	  		0x9			/***********V***********/
////#define W1	  		0x36
////#define W2	  		0x28		/***********W***********/
////#define X1	  		0x00
////#define X2	  		0x2D		/***********X***********/
////#define Y1	  		0x00
////#define Y2	  		0x15		/***********Y***********/
////#define Z1	  		0x9
////#define Z2	  		0x24		/***********Z***********/
////#define nus 20

// //共阴数码管0~5字型码，以实际电路接法为准
///***************延时函数**************/
//void delay_us(unsigned int n)
//{
//	delayXus(n);
//}


///***************发送8bit数据，从低位开始**************/
//void send_8bit(unsigned char dat)	
//{
//  unsigned char i;
//  for(i=0;i<8;i++)
//  {	 
//    CLK1(0);
//    if(dat&0x01) 
//	    SIO1(1);
//	 else 
//	    SIO1(0);
//	 delay_us(3);
//	 CLK1(1);
//	 dat>>=1;
//	 delay_us(3);
//  }
//	//enter idle
//  CLK1(0);
//  SIO1(0);
//}


///******************发送控制命令***********************/
//void send_command(unsigned char word)
//{
// STB(1);
// delay_us(10);
// STB(0);
// send_8bit(word);
//}

///************显示函数，数码管1~16位显示0~F************/
//void display_smg(unsigned char * code)		
//{
// unsigned char i;
// send_command(0x40);	//设置数据命令:普通模式、地址自增1，写数据到显存
// send_command(0xc0);	//设置显示地址命令：从00H开始
// for(i=0;i<16;i++)		//发送16字节的显存数据
// {
//  send_8bit(code[i]);
// }
// send_command(0x8F);	//设置显示控制命令：打开显示，并设置为16/16.
// STB(1);
//}

//void STB(unsigned char State){
////	if(State == 0){
////		HAL_GPIO_WritePin(LCD_STB_GPIO_Port,LCD_STB_Pin,GPIO_PIN_RESET);
////	}
////	else
////		HAL_GPIO_WritePin(LCD_STB_GPIO_Port,LCD_STB_Pin,GPIO_PIN_SET);
//}

//void CLK1(unsigned char State){
////	if(State == 0){
////		HAL_GPIO_WritePin(LCD_CLK_GPIO_Port,LCD_CLK_Pin,GPIO_PIN_RESET);
////	}
////	else
////		HAL_GPIO_WritePin(LCD_CLK_GPIO_Port,LCD_CLK_Pin,GPIO_PIN_SET);
//}

//void SIO1(unsigned char State){
////	if(State == 0){
////		HAL_GPIO_WritePin(LCD_SIO_GPIO_Port,LCD_SIO_Pin,GPIO_PIN_RESET);
////	}
////	else
////		HAL_GPIO_WritePin(LCD_SIO_GPIO_Port,LCD_SIO_Pin,GPIO_PIN_SET);
//}
////单独文件时的调试例程，放入工程时不使用,仅用于Demo。
//void main_smg(void)
//{
////display_smg(CODE);	 //因只有6个数码管，所以电显示0~5
////HAL_Delay(500);
////display_smg(CODE_OFF);
////HAL_Delay(500);
////display_smg(CODE_NUM);
////HAL_Delay(500);	
//	
//}

// 
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
