#ifndef __AT24Cxx_H
#define __AT24Cxx_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define ADDR_24LCxx_Write 0xA0
#define ADDR_24LCxx_Read 0xA1
#define BufferSize 0x100


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

int AT24Cxx_Write(uint8_t *pData);
int AT24Cxx_Read(uint8_t *pData);
#endif
