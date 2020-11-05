/* CH376芯片 硬件标准异步串口连接的硬件抽象层 V2.0 */
/* @think3r https://git.oschina.net/think3r */
/* 提供I/O接口子程序 */
/* 本例中的硬件连接方式如下 */
/* 单片机的引脚    CH376芯片的引脚
      TXD                  RXD
      RXD                  TXD       */

#include "HAL.H"                     /* WART_HW.C 对应头文件  */
#include "CH376INC.H"				/* 使用 CH376INC.H 中的命令码宏定义及其它类型定义 */
#include "tim.h"

void	CH376_PORT_INIT( void )  /* 由于使用异步串口读写时序,所以进行初始化 */
{
    //	usart2_init(UART_INIT_BAUDRATE);

    //	#ifdef __CH376_DEBUG_
    //	printf("UART2 串口成功初始化波特率 9600 \r\n");
    //    #endif
}

#define	xEndCH376Cmd()  /* 结束CH376命令,仅用于SPI接口方式，串口方式不需要*/

void	xWriteCH376Cmd( UINT8 mCmd )  /* 向CH376写命令 */
{
    /* 启动操作的第1个串口同步码 0x57 */
	uint8_t ser_sync_code1 = SER_SYNC_CODE1;
	uint8_t ser_sync_code2 = SER_SYNC_CODE2;
    HAL_UART_Transmit(&huart3, (uint8_t *)&ser_sync_code1, 1, 0xff);
    //	/* 启动操作的第2个串口同步码 0xAB */
    HAL_UART_Transmit(&huart3, (uint8_t *)&ser_sync_code2, 1, 0xff);
    HAL_UART_Transmit(&huart3, (uint8_t *)&mCmd, 1, 0xff);
}

void	xWriteCH376Data( UINT8 mData )  /* 向CH376写数据 */
{
    HAL_UART_Transmit(&huart3, (uint8_t *)&mData, 1, 0xff);
}

UINT8	xReadCH376Data( void )  /* 从CH376读数据 */
{
    uint8_t data = 0;
    HAL_UART_Receive(&huart3, &data, 1, 0x0fff);
    return data;
}

/* 查询CH376中断(INT#低电平) */
UINT8	Query376Interrupt( void )
{
    /* 如果未连接CH376的中断引脚则查询串口中断状态码 */
    if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == SET)
    {
        __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_RXNE); //丢弃串口接收到的终端状态
        return( 1 );
    }
    else
    {
        return( 0 );
    }
}







