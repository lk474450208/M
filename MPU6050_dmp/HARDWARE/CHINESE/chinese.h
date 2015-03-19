#ifndef __CHINESE_H
#define __CHINESE_H	 
#include "sys.h"   


void TEST_FONT(void);
void Test_Show_CH_Font16(u16 x,u16 y,u8 index,u16 color);
void Test_Show_CH_Font24(u16 x,u16 y,u8 index,u16 color);
void Hanzi(u16 x,u16 y,u16 color,u16 sta,u16 end,u16 mode) ;
#endif
