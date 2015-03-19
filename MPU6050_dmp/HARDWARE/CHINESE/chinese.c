#include "chinese.h"
#include "chfont.h"
#include "lcd.h"
#include "delay.h"	
	   
			    
//��LCD�ϵģ�x��y��������
//color�������ɫ
void LCD_Draw_Point(u16 x,u16 y,u16 color)
{
	u16 temp;
	temp=POINT_COLOR;
	POINT_COLOR=color;
    LCD_DrawPoint(x,y);
	POINT_COLOR=temp;
}
//��ָ��λ�� ��ʾ1��16*16�ĺ���
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void Show_CH_Font16(u16 x,u16 y,u8 index,u16 color,u8 mode)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<32;t++)//ÿ��16*16�ĺ��ֵ��� ��32���ֽ�
    { 
		if(t<16)temp=tfont16[index*2][t];      //ǰ16���ֽ�
		else temp=tfont16[index*2+1][t-16];    //��16���ֽ�	                          
     for(t1=0;t1<8;t1++)
		{ 
			if(mode) 
			{
			if(temp&0x80)LCD_Draw_Point(x,y,color);//��ʵ�ĵ�
			}
			else
			{	
				if(temp&0x80)LCD_Draw_Point(x,y,color);
				else LCD_Draw_Point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
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

 


	
//��ָ��λ�� ��ʾ1��24*24�ĺ���
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void Show_CH_Font24(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<72;t++)//ÿ��24*24�ĺ��ֵ��� ��72���ֽ�
    {   
		if(t<24)temp=tfont24[index*3][t];           //ǰ24���ֽ�
		else if(t<48)temp=tfont24[index*3+1][t-24]; //��24���ֽ�	                          
        else temp=tfont24[index*3+2][t-48];         //��24���ֽ�
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
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

//��xy����ʼ��ʾ��sta����end������
void Hanzi(u16 x,u16 y,u16 color,u16 sta,u16 end,u16 mode)
{
	u8 t;
	for(t=sta;t<end+1;t++)//6������
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







