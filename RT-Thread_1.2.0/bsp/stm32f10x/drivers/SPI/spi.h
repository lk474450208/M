#ifndef _SPI_H_
#define _SPI_H_

#include <rtthread.h>
#include "stm32f10x.h"
#define USING_DMA

extern void SPI1_Init(void);
extern void SPI2_Init(void);
extern rt_uint8_t SPI2_ReadWriteByte(rt_uint8_t TxData);
extern rt_uint8_t SPI_WriteByte(SPI_TypeDef* SPIx,rt_uint8_t Byte);
	
#endif
