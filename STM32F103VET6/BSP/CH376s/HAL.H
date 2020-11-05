/* CH376оƬ Ӳ������� V2.0 */
/* @think3r https://git.oschina.net/think3r */
/* �ṩI/O�ӿ��ӳ��� */


#ifndef	_HAL_H__
#define _HAL_H__

#include "main.h"
#include "CH376INC.H"		/* ʹ�� CH376INC.H �е����Ͷ��� */

/*=======================================�Զ�����������-========================================================*/

#include "usart.h"				    /* ʹ�ô��� 3 ��ΪͨѶ�ӿ� */

#define	UART_INIT_BAUDRATE	115200	/* Ĭ��ͨѶ������9600bps,����ͨ��Ӳ�������趨ֱ��ѡ����ߵ�CH376��Ĭ��ͨѶ������ */

#if 1
#define __CH376_DEBUG_ 	/* 	ʹ���Զ���� DEBUG */
#endif

#if 1
#define __mFlushBufferToDisk_DEBUG_  /*  �������ر�mFlushBufferToDisk() �����е� printf ���� debug ����  */
#endif

/* ʹ�� ddelay_ms1) ��ʱ���� */
/*  ��Ҫʹ�� RTC ʵʱʱ�� ��Ϊ �����ļ�����  */
/*  ��Ҫ��д������ʱ���ر� ��ʱɨ��U�̲������� ��ʱ��5��
	��ֲ����ʱ����д������ʱ�������رտ��Թرյ��жϣ�	 */

#if 1
#define delay_ms1 HAL_Delay
#define delay_us1 HAL_Delay
#endif


/*=======================================�Զ�����������-========================================================*/


/* ���ӵ�USB����״̬���� */
#define		ERR_USB_UNKNOWN		0xFA	/* δ֪����,��Ӧ�÷��������,����Ӳ�����߳������ */


void	CH376_PORT_INIT( void );  		/* CH376ͨѶ�ӿڳ�ʼ�� */

void	xEndCH376Cmd( void );			/* ����CH376����,������SPI�ӿڷ�ʽ */

void	xWriteCH376Cmd( UINT8 mCmd );	/* ��CH376д���� */

void	xWriteCH376Data( UINT8 mData );	/* ��CH376д���� */

UINT8	xReadCH376Data( void );			/* ��CH376������ */

UINT8	Query376Interrupt( void );		/* ��ѯCH376�ж�(INT#����Ϊ�͵�ƽ) */


#endif