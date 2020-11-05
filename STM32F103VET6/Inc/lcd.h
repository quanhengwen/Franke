/**
  ******************************************************************************
  * File Name          : lcd.h
  * Description        : This file contains all the functions prototypes for 
  *                      the smg  
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
#ifndef __smg_H
#define __smg_H
//#include "main.h"

void send_command(unsigned char word);
void display_smg(unsigned char * code);
void send_8bit(unsigned char dat);
void main_smg(void);
void STB(unsigned char State);
void CLK1(unsigned char State);
void SIO1(unsigned char State);

#endif

