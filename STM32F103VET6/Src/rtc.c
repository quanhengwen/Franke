/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RTC_TimeTypeDef currentTime;
RTC_DateTypeDef currentDate;
time_t timestamp;
struct tm currTime;
char timestamp_buf[16];


uint8_t ConvertBCD(uint8_t b)//byte转换为BCD码
{
    //高四位
    uint8_t b1 = (uint8_t)(b / 10);
    //低四位
    uint8_t b2 = (uint8_t)(b % 10);
    return (uint8_t)((b1 << 4) | b2);
}

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0x16;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
  DateToUpdate.Month = RTC_MONTH_DECEMBER;
  DateToUpdate.Date = 0x24;
  DateToUpdate.Year = 0x19;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
char *time_to_timestamp(void)
{
    memset(timestamp_buf, 0, sizeof(timestamp_buf));
    /* Code to get timestamp
    *
    *  You must call HAL_RTC_GetDate() after HAL_RTC_GetTime() to unlock the values
    *  in the higher-order calendar shadow registers to ensure consistency between the time and date values.
    *  Reading RTC current time locks the values in calendar shadow registers until Current date is read
    *  to ensure consistency between the time and date values.
    */

    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

    currTime.tm_year = currentDate.Year + 100;  // In fact: 2000 + 18 - 1900
    currTime.tm_mday = currentDate.Date;
    currTime.tm_mon  = currentDate.Month -1;

    currTime.tm_hour = currentTime.Hours -8;
    currTime.tm_min  = currentTime.Minutes;
    currTime.tm_sec  = currentTime.Seconds;

    timestamp = mktime(&currTime);

    sprintf(timestamp_buf, "%u", timestamp);
    return timestamp_buf;
}

HAL_StatusTypeDef SyncTimeFromServer(uint8_t year,uint8_t month,uint8_t date,uint8_t hour,uint8_t min,uint8_t sec)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef DateToUpdate = {0};

    /** Initialize RTC and set the Time and Date
    */
    sTime.Hours = ConvertBCD(hour);
    sTime.Minutes = ConvertBCD(min);
    sTime.Seconds = ConvertBCD(sec);

    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
    DateToUpdate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
    DateToUpdate.Month = ConvertBCD(month);
    DateToUpdate.Date = ConvertBCD(date);
    DateToUpdate.Year = ConvertBCD(year);

    if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }

    return HAL_OK;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
