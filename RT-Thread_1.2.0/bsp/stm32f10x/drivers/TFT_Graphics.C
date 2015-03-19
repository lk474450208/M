/*************************************************************************
文件名：TFT_Griphics.C
描  述：图形函数库（画点、线、简单图形、字符、字符串输出等）
作  者：
日  期：2012.4.20
*************************************************************************/
#include "TFT_Driver.H"
#include "TFT_Graphics.H"
#include "8X16.H"
//#include "bmp.h"
//#include "CHINESE.H"
#include "GB1616.H"
#include <math.h>

COLOR FrontColor;	        //前景色
LINE_WIDTH Thickness;       //线宽
Win_Size windowsize;
COLOR BkColor;
COLOR Text_btom_color;

void Clear_Screen(COLOR bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<=320;i++)
	{
	   for (j=0;j<=240;j++)
	       Write_Data_U16(bColor);
	}
}
void Set_Color(COLOR color)
{
    FrontColor = color;
}
void Set_BkColor(COLOR color)
{
     BkColor = color;
	 Text_btom_color = color;
}
void Draw_Point(unsigned int x, unsigned int y)
{
    LCD_SetPos(x,x,y,y);
	Write_Data_U16(FrontColor);
}
void Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    float Line_slop;
	int x_dis, y_dis, temp_y;    //x_dis、y_dis不能设为unsigned int，否则不会 <0
	unsigned int i = 1, j = 0;
	x_dis = x2-x1;
	y_dis = y2-y1;
	Line_slop = (float)y_dis/x_dis;
	//Line_slop = y_dis/x_dis;  //需要强制转换
	if(0 == x_dis)
	{
	    if(y_dis > 0)
		{
		   while(j<=Thickness)
		   {
		       LCD_SetPos(x1+j,x1+j,y1,y1+y_dis);
		       do
		       {
		   	       Write_Data_U16(FrontColor);
			       y_dis--; 
		       }while(y_dis);
			   j++;
		    } 
		}
		else
		{
		    y_dis=abs(y_dis);                //取绝对值，否则下面的y2+y_dis出错
            while(j<=Thickness)
			{
		   	    LCD_SetPos(x1+j,x1+j,y2,y2+y_dis);
			    do
			    {
			   	    Write_Data_U16(FrontColor);
				    y_dis--; 
			    }while(y_dis); 
				j++;   
			}
			
		}
	}
	else
	{
		if(0 == y_dis)
		{
		    if(x_dis > 0)
			{
			   while(j<=Thickness)
			   {
			       i=0;
				   LCD_SetPos(x1,x1+x_dis,y1+j,y1+j);
				   do
				   {
				   	   Write_Data_U16(FrontColor);
					   x_dis--; 
				   }while(x_dis);
				   j++;
			   }
			    
			}
			else
			{
			    x_dis=abs(x_dis);			//取绝对值，否则下面的x2+x_dis出错
	            while(j<=Thickness)
				{
				    i=0;
					LCD_SetPos(x2,x2+x_dis,y2+j,y2+j);
				    do
				    {
				   	    Write_Data_U16(FrontColor);
					    x_dis--; 
				    }while(x_dis);
					j++;
				}
				
			}
		}
		else
		{
		    while(j<=Thickness)
			{
			    i=0;
				do
				{
				    temp_y = (unsigned int)(Line_slop*i + y1);
					Draw_Point(x1+i+j, temp_y);
					i++;
				}while(i<=x_dis);
				j++;
			}
		}
	}     		
}
void Set_Linestyle(LINE_WIDTH width )
{
     Thickness = width;
}


void LCD_PrintNum(unsigned char x, unsigned int y,int num)
{
    unsigned char str[6];
    char i=0, j=0;
	if(num>=0)
	{
		str[i] = '+';
	}
	else
	{
		str[i] = '-';
		num = -num;
	}

		str[1]=num/10000+48;num=num%10000;//??
		str[2]=num/1000+48;num=num%1000;//??
		str[3]=num/100+48;num=num%100;  //??
		str[4]=num/10+48;num=num%10;    //??
		str[5]=num+48;
	for(i=0;i<6;i++)
	{
	    LCD_PutChar(x+8*j,y,str[i],FrontColor,Text_btom_color);
		j++;    
	}
}


void Rectangle(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
	Line(left,top,right,top);
	Line(right,top,right,bottom);
	Line(right,bottom,left,bottom);
	Line(left,bottom,left,top);
}

void bar(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
    unsigned int temp;
	unsigned int x_dis, y_dis;   
	LCD_SetPos(left,top,right,bottom); 
    x_dis=right-left+1;
	y_dis=bottom-top+1;

	while(x_dis--)
	{
	 	temp=y_dis;
		while(temp--)
	 	{	
			Write_Data_U16(FrontColor);
		}
	}

}
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);
 for(i=0; i<16;i++) {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			}
		}
}


void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor) {

		LCD_PutChar8x16( x, y, c, fColor, bColor );
	}




void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
{
	unsigned int i,j,k;
	LCD_SetPos(x,x+16-1,y, y+16-1);

	for (k=0;k<64;k++) 
	{ //64标示自建汉字库中的个数，循环查询内码
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1]))
	  { 
    	 for(i=0;i<32;i++) 
		 {
		  unsigned short m=codeGB_16[k].Msk[i];
		   for(j=0;j<8;j++) 
		   {
			if((m&0x80)==0x80)
		        {Write_Data_U16(fColor);}
			else {Write_Data_U16(bColor);}
			m<<=1;
			} 
		  }
	   }  
	}	
}

void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s,unsigned char num, unsigned int fColor, unsigned int bColor) {
unsigned char l=0;
for(;num>0;num--)
{
	if( *s < 0x80) 
		    {
			LCD_PutChar(x+l*8,y,*s,fColor,bColor);
			s++;l++;
			}
		else
		    {
			PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
			s+=2;l+=2;
			}
		}
}
void drawpoint(unsigned char x,unsigned int y,unsigned int color)
{//unsigned int i,j;
LCD_SetPos(x,x,y,y);
Write_Data_U16(color);
} 
/////////////////////////////////////////////////////////
void Paint(unsigned int X,unsigned int Y,unsigned int color)//画图，触摸坐标系的原点为右上角，TFT屏的坐标原点为左上角，故需坐标转换
{
 
int m=(4096-X-320)/15+7;
int n=(Y-220)/11;
drawpoint(m,n,color);     
}
/*
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high ,const uchar *pic)
void GUI_DisPicture(unsigned char x, unsigned int y, unsigned char length,unsigned int high)
{
    unsigned int temp=0,tmp=0,num=0;
	LCD_SetPos(x,y,x+length-1,y+high-1);
	num=length*high*2;
	do
	{  
	   //temp=pic[tmp]|( pic[tmp+1]<<8);
	   temp=pic[tmp+1];
	   temp=temp<<8;
	   temp=temp|pic[tmp];
	   Write_Data_U16(temp);//逐点显示
	   tmp+=2;
	}while(tmp<num);
}
*/

