#include "AT24Cxx.h"
#include "main.h"
#include "bsp_EEPROM.h"
//#include "lcd.h"
#include <string.h>

uint8_t gWriteBuffer[BufferSize];
uint8_t gReadBuffer[BufferSize];

#if 0
uint8_t flag = EEPROM_CheckOk();
uint8_t I2c_Buf_Write[256] = {0};
uint8_t I2c_Buf_Read[256] = {0};

if(flag == 1)
{
    uint16_t i;
    Usart3_Printf("检测到板载EEPROM（AT24C02）芯片\n");
    Usart3_Printf("待写入的数据:\n");
    for ( i = 0; i < 256; i++ ) //填充缓冲
    {
        I2c_Buf_Read[i] = 0;    // 清空接收缓冲区
        I2c_Buf_Write[i] = i;   // 为发送缓冲区填充数据
        Usart3_Printf("0x%02X ", I2c_Buf_Write[i]);
        if(i % 16 == 15)
            Usart3_Printf("\n");
    }
    //将I2c_Buf_Write中顺序递增的数据写入EERPOM中
    EEPROM_WriteBytes(I2c_Buf_Write, 0, 256);
    HAL_Delay(100);

    Usart3_Printf("读出的数据:\n");
    //将EEPROM读出数据顺序保持到I2c_Buf_Read中
    EEPROM_ReadBytes(I2c_Buf_Read, 0, 256);
    for (i = 0; i < 256; i++)
    {
        if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
        {
            Usart3_Printf("0x%02X ", I2c_Buf_Read[i]);
            Usart3_Printf("错误:I2C EEPROM写入与读出的数据不一致\n\r");
            break;
        }
        Usart3_Printf("0x%02X ", I2c_Buf_Read[i]);
        if(i % 16 == 15)
            Usart3_Printf("\n");
    }
    if(i == 256)
    {
        Usart3_Printf("EEPROM(AT24C02)读写测试成功\n\r");
    }
}
else
{
    Usart3_Printf("无法与板载EEPROM通信（AT24C02），读写测试失败\n");
}
#endif

int AT24Cxx_Write(uint8_t *pData)
{
    memset(&gWriteBuffer, 0, sizeof(gWriteBuffer));
    memcpy(gWriteBuffer, pData, BufferSize);
//		if(gWriteBuffer[0] == 0)
//		{
//			display(0,"为0","");
//			HAL_Delay(1000);
//		}
//		if(gWriteBuffer[0] == 1)
//		{
//			display(0,"为1","");
//			HAL_Delay(1000);
//		}
//    uint8_t err = 0;
    /* wrinte date to EEPROM */
    //    for(uint8_t i = 0; i < 3; i++)
    //    {
    //        err = 0;
    //        for (uint8_t j = 0; j < 32; j++)
    //        {
    //            if(HAL_I2C_Mem_Write(&hi2c1, ADDR_24LCxx_Write, 8 * j, I2C_MEMADD_SIZE_8BIT, gWriteBuffer + 8 * j, 8, 1000) == HAL_OK)
    //            {
    //                HAL_Delay(10);
    //            }
    //            else
    //            {
    //                err++;
    //                HAL_Delay(10);
    //            }
    //        }
    //        if(err == 0)
    //        {
    //            break;
    //        }
    //    }
    //    if(err != 0)
    //    {
    //        return 1;
    //    }
    EEPROM_WriteBytes(gWriteBuffer, 0, BufferSize);
    HAL_Delay(100);
    return 0;
    /* wrinte date to EEPROM */
}

int  AT24Cxx_Read(uint8_t *pData)
{
    memset(&gReadBuffer, 0, sizeof(gReadBuffer));
    memset(pData, 0, BufferSize);
    //uint8_t err = 0;
    /* read date from EEPROM */
    //    for(uint8_t i = 0; i < 3; i++)
    //    {
    //        if(HAL_I2C_Mem_Read(&hi2c1, ADDR_24LCxx_Read, 0, I2C_MEMADD_SIZE_8BIT, gReadBuffer, BufferSize, 1000) == HAL_OK)
    //        {
    //            memcpy(pData, gReadBuffer, BufferSize);
    //            break;
    //        }
    //        else
    //        {
    //            err++;
    //            HAL_Delay(10);
    //        }
    //    }
    //    if(err != 0)
    //    {
    //        return 1;
    //    }
    EEPROM_ReadBytes(gReadBuffer, 0, BufferSize);
    memcpy(pData, gReadBuffer, BufferSize);
    return 0;
}
