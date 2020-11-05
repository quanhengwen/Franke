/* CH376芯片 硬件抽象层 V2.0 */
/* @think3r https://git.oschina.net/think3r */
/* 提供I/O接口子程序 */


#ifndef	_HAL_H__
#define _HAL_H__

#include "main.h"
#include "CH376INC.H"		/* 使用 CH376INC.H 中的类型定义 */

/*=======================================自定义设置区域-========================================================*/

#include "usart.h"				    /* 使用串口 3 作为通讯接口 */

#define	UART_INIT_BAUDRATE	115200	/* 默认通讯波特率9600bps,建议通过硬件引脚设定直接选择更高的CH376的默认通讯波特率 */

#if 1
#define __CH376_DEBUG_ 	/* 	使用自定义的 DEBUG */
#endif

#if 1
#define __mFlushBufferToDisk_DEBUG_  /*  开启、关闭mFlushBufferToDisk() 函数中的 printf 函数 debug 功能  */
#endif

/* 使用 ddelay_ms1) 延时函数 */
/*  需要使用 RTC 实时时钟 作为 长短文件名。  */
/*  需要在写入数据时，关闭 定时扫描U盘插入与否的 定时器5。
	移植程序时，在写入数据时，尽量关闭可以关闭的中断；	 */

#if 1
#define delay_ms1 HAL_Delay
#define delay_us1 HAL_Delay
#endif


/*=======================================自定义设置区域-========================================================*/


/* 附加的USB操作状态定义 */
#define		ERR_USB_UNKNOWN		0xFA	/* 未知错误,不应该发生的情况,需检查硬件或者程序错误 */


void	CH376_PORT_INIT( void );  		/* CH376通讯接口初始化 */

void	xEndCH376Cmd( void );			/* 结束CH376命令,仅用于SPI接口方式 */

void	xWriteCH376Cmd( UINT8 mCmd );	/* 向CH376写命令 */

void	xWriteCH376Data( UINT8 mData );	/* 向CH376写数据 */

UINT8	xReadCH376Data( void );			/* 从CH376读数据 */

UINT8	Query376Interrupt( void );		/* 查询CH376中断(INT#引脚为低电平) */


#endif
