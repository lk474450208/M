#include "chinese.h"
#include "chfont.h"
#include "lcd.h"
#include "delay.h"	
	   
			    
//在LCD上的（x，y）处画点
//color：点的颜色
void LCD_Draw_Point(u16 x,u16 y,u16 color)
{
	u16 temp;
	temp=POINT_COLOR;
	POINT_COLOR=color;
    LCD_DrawPoint(x,y);
	POINT_COLOR=temp;
}
//在指定位置 显示1个16*16的汉字
//(x,y):汉字显示的位置
//index:tfont数组里面的第几个汉字
//color:这个汉字的颜色
void Show_CH_Font16(u16 x,u16 y,u8 index,u16 color,u8 mode)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<32;t++)//每个16*16的汉字点阵 有32个字节
    { 
		if(t<16)temp=tfont16[index*2][t];      //前16个字节
		else temp=tfont16[index*2+1][t-16];    //后16个字节	                          
     for(t1=0;t1<8;t1++)
		{ 
			if(mode) 
			{
			if(temp&0x80)LCD_Draw_Point(x,y,color);//画实心点
			}
			else
			{	
				if(temp&0x80)LCD_Draw_Point(x,y,color);
				else LCD_Draw_Point(x,y,BACK_COLOR);   //画空白点（使用背景色）
			}
			temp<<=1;
			y++;
		if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
			}	
		}
					
    }          
}

 


	
//在指定位置 显示1个24*24的汉字
//(x,y):汉字显示的位置
//index:tfont数组里面的第几个汉字
//color:这个汉字的颜色
void Show_CH_Font24(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<72;t++)//每个24*24的汉字点阵 有72个字节
    {   
		if(t<24)temp=tfont24[index*3][t];           //前24个字节
		else if(t<48)temp=tfont24[index*3+1][t-24]; //中24个字节	                          
        else temp=tfont24[index*3+2][t-48];         //后24个字节
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point(x,y,color);//画实心点
			else LCD_Draw_Point(x,y,BACK_COLOR);   //画空白点（使用背景色）
			temp<<=1;
			y++;
			if((y-y0)==24)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//在xy处开始显示第sta到第end个汉字
void Hanzi(u16 x,u16 y,u16 color,u16 sta,u16 end,u16 mode)
{
	u8 t;
	for(t=sta;t<end+1;t++)//6个汉字
	{
		Show_CH_Font16(x ,y,t,color,mode);
		    x+=16;
//		    delay_ms(10);
			if(240-x<16)
		{
				y=y+16;
				x=0;    		
		}
	}
}







