//#include "STC12C5A60S2.H"
//#include "..\STC15F2K60S2.h"
//#include <intrins.h>
#include "stm32f10x.h"
#include "TFT_Driver.h"
#include "TFT_Graphics.h"
#include "rtthread.h"



#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR
#define uint unsigned int
#define uchar unsigned char
///* TFT */
//sbit LCD_RS = P1^2;  	//����/�����л�
//sbit LCD_WR = P1^1;		//д����
////sbit LCD_RD =P2^3;    //�����ƣ����ö�TFTʱ���Բ�����
//sbit LCD_CS=P1^3;		//Ƭѡ	
//sbit LCD_REST = P1^4;	      //��λ  
//sbit LCD_EN = P3^7;	      //��λ 
//#define DataPort P0                //���ݿ�ʹ��P0��
///* touch panel interface define */
//sbit DCLK	   =    P2^5;   
//sbit CS        =    P2^4;
//sbit DIN       =    P2^3;
//sbit BUSY      =    P2^2;	
//sbit DOUT      =    P2^1;																
//sbit Penirq    =    P2^0;

struct pix_ Tp_pix;	 //��ǰ���������ȡ��ֵ 
/////////////////////////////////////////////////////////////



/*

void spistart()                                     //SPI��ʼ
{
	CS=1;
	DCLK=1;
	DIN=1;
	DCLK=1;
}

void WriteCharTo7843(unsigned char num)          //SPIд����
{
unsigned char count=0;
DCLK=0;
for(count=0;count<8;count++)
{
    num<<=1;
	DIN=CY;
	DCLK=0; _nop_();_nop_();_nop_();                //��������Ч
	DCLK=1; _nop_();_nop_();_nop_();
}
}

unsigned int ReadFromCharFrom7843()             //SPI ������
{
unsigned char count=0;
unsigned int Num=0;
for(count=0;count<12;count++)
{  Num<<=1;
   DCLK=1; _nop_();_nop_();_nop_();                //�½�����Ч
   DCLK=0; _nop_();_nop_();_nop_();
   if(DOUT) Num++;    }
return(Num);
}	

----------------------------------------------------------------
                           д����
----------------------------------------------------------------*/
void Write_Cmd(unsigned int CMD)
{	
	*(__IO uint8_t *) (Bank1_LCD_C) = (uint8_t)CMD>>8;
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_5);		
	*(__IO uint8_t *) (Bank1_LCD_C) = (uint8_t)CMD;
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_5);	
}
/*----------------------------------------------------------------
                           д���� ˫8λ
----------------------------------------------------------------*/
void Write_Data(unsigned int Data)
{	
		*(__IO uint8_t *) (Bank1_LCD_D)= (uint8_t)Data>>8;
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_5);	
		*(__IO uint8_t *) (Bank1_LCD_D)= (uint8_t)Data;
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_5);	
}
/*----------------------------------------------------------------
                         д���д����
���������x ��Ҫ��������� 16λ
          y ��Ҫ��������� 16λ
----------------------------------------------------------------*/
void  Write_Cmd_Data (unsigned int x,unsigned int y)
{
	Write_Cmd(x);	
	Write_Data(y);
}

/*----------------------------------------------------------------
                         д16λ����
----------------------------------------------------------------*/
void  Write_Data_U16(unsigned int y)
{
	*(__IO uint8_t *) (Bank1_LCD_D)= (uint8_t)y>>8;
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_5);	
	*(__IO uint8_t *) (Bank1_LCD_D)= (uint8_t)y;
		GPIO_ResetBits(GPIOD, GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_5);
}
/*----------------------------------------------------------------
                         ����TFT��ʾ�������귶Χ
----------------------------------------------------------------*/
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
  Write_Cmd_Data(WINDOW_XADDR_START,x0);
  Write_Cmd_Data(WINDOW_XADDR_END,x1);
  Write_Cmd_Data(WINDOW_YADDR_START,y0);
  Write_Cmd_Data(WINDOW_YADDR_END,y1);
  Write_Cmd_Data(GRAM_XADDR,x0);
  Write_Cmd_Data(GRAM_YADDR,y0);
  Write_Cmd (0x0022);//LCD_WriteCMD(GRAMWR);
}
void int2string(unsigned int dd,unsigned char *str)//int��������ת�����ַ���
{unsigned int m=dd;                                //��ʾ��������
	str[0]=m/10000+48;m=m%10000;//��λ
	str[1]=m/1000+48;m=m%1000;//ǧλ
	str[2]=m/100+48;m=m%100;  //��λ
	str[3]=m/10+48;m=m%10;    //ʮλ
	str[4]=m+48;              //��λ
} 
void long2string(unsigned long dd,unsigned char *str)//int��������ת�����ַ���
{unsigned long m=dd;                                //��ʾ��������
	str[0]=m/10000000+48;m=m%10000000;//��λ
	str[1]=m/1000000+48;m=m%1000000;//��λ
	str[2]=m/100000+48;m=m%100000;//��λ
	str[3]=m/10000+48;m=m%10000;//��λ
	str[4]=m/1000+48;m=m%1000;//ǧλ
	str[5]=m/100+48;m=m%100;  //��λ
	str[6]=m/10+48;m=m%10;    //ʮλ
	str[7]=m+48;              //��λ
}
void int2string_TFTaxis_X(int dd,unsigned char *str)
{int m=(4096-dd-320)/15+7;
	str[0]=m/100+48;m=m%100;//��λ
	str[1]=m/10+48;m=m%10;  //ʮλ
	str[2]=m+48;            //��λ	             
}  
void int2string_TFTaxis_Y(int dd,unsigned char *str)
{int m=(dd-220)/11;
	str[0]=m/100+48;m=m%100;//��λ
	str[1]=m/10+48;m=m%10;  //ʮλ
	str[2]=m+48;            //��λ	             
} 

/*
unsigned char Makpix(struct pix_ pix1,struct pix_ pix2)
{
unsigned char l=0;
int x=pix1.x>pix2.x?pix1.x-pix2.x:pix2.x-pix1.x;
int y=pix1.y>pix2.y?pix1.y-pix2.y:pix2.y-pix1.y;
if(x<14&&y<11)	 //����˲���2��ȡ����ֵ���̫�����Ϊ����
{
	l=1;
	Tp_pix.x=(pix1.x+pix2.x)/2;
	Tp_pix.y=(pix1.y+pix2.y)/2;
}

return l;
}
struct pix_ AD7843()            
{

	struct pix_ pix;
	CS=0;
	WriteCharTo7843(0x90);        //�Ϳ����� 10010000 ���ò�ַ�ʽ��X���� ��ϸ����й�����
	DCLK=1; _nop_();_nop_();_nop_();_nop_();
	DCLK=0; _nop_();_nop_();_nop_();_nop_();
	pix.y=ReadFromCharFrom7843();
	WriteCharTo7843(0xD0);       //�Ϳ����� 11010000 ���ò�ַ�ʽ��Y���� ��ϸ����й�����
	DCLK=1; _nop_();_nop_();_nop_();_nop_();
	DCLK=0; _nop_();_nop_();_nop_();_nop_();
	pix.x=ReadFromCharFrom7843();
	CS=1; 
	return pix;
}
*/
//unsigned char Getpix() //ȡ����ֵ���˴�ʹ������˲���2��ȡ����ֵ���̫�����Ϊ����
//{
//	struct pix_ pix1;
//	struct pix_ pix2; 
//	pix1=AD7843();
//	pix2=AD7843();
//   
// 	return	Makpix(pix1,pix2);	
//}
void Delay_ms(unsigned int num)		//@35MHz
{
	unsigned char i, j;
	for(;num>0;num--)
	{
		i = 69;
		j = 20;
		do
		{
			while (--j);
		} while (--i);
	}
}



void TFT_Init(void)
{	//delay_ms(100); 
	GPIO_SetBits(GPIOD, GPIO_Pin_7);
		GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    Delay_ms(5);				   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
		Delay_ms(5);

	Delay_ms(50);
//############# void Power_Set(void) ################//
    Write_Cmd_Data(0x0000,0x0000);
    Write_Cmd_Data(0x0000,0x0000);
    Write_Cmd_Data(0x0000,0x0000);
    Write_Cmd_Data(0x0000,0x0000);
    Write_Cmd_Data(0x0010,0x0600);   // SLP=0,
	  Delay_ms(30);
    Write_Cmd_Data(0x0007,0x0000);       
    Write_Cmd_Data(0x0012,0x011A);
    Write_Cmd_Data(0x00A4,0x0001);
    Write_Cmd_Data(0x0008,0x020E);  // FP,BP
    Write_Cmd_Data(0x000A,0x0008);
    Write_Cmd_Data(0x000D,0x0008);
    Write_Cmd_Data(0x0030,0x0707);
    Write_Cmd_Data(0x0031,0x0007);
    Write_Cmd_Data(0x0032,0x0603); 
    Write_Cmd_Data(0x0033,0x0700); 
    Write_Cmd_Data(0x0034,0x0202); 
    Write_Cmd_Data(0x0035,0x0002); 
    Write_Cmd_Data(0x0036,0x1E00); 
    Write_Cmd_Data(0x0037,0x0707); 
    Write_Cmd_Data(0x0038,0x0000); 
    Write_Cmd_Data(0x0039,0x0000); 
    Write_Cmd_Data(0x003A,0x0707); 
    Write_Cmd_Data(0x003B,0x0000); 
    Write_Cmd_Data(0x003C,0x0007); 
    Write_Cmd_Data(0x003D,0x0000); 
         Delay_ms(30);  
	  Write_Cmd_Data(0x0011,0x0007);  		 
	  Write_Cmd_Data(0x0060,0x2700);
	  Write_Cmd_Data(0x0090,0x0016);  // DIVI, RTNI
    Write_Cmd_Data(0x0017,0x0001); 
	  Write_Cmd_Data(0x0019,0x0000); // TBT[1:0]
         Delay_ms(30);   
    Write_Cmd_Data(0x0010,0x16B0);		          
    Write_Cmd_Data(0x0012,0x011A); 
      Delay_ms(30);   
    Write_Cmd_Data(0x0013,0x1800); // VDV[4:0]   
    Write_Cmd_Data(0x002A,0x000E); // VCMSEL, VCM2[4:0]
    Write_Cmd_Data(0x0029,0x000E); // VCM1[4:0]
	  Delay_ms(30);
    Write_Cmd_Data(0x0012,0x013A); // VCOMR[0], VREG1R, PSON, PON, VRH[3:0]
      Delay_ms(100);
    Write_Cmd_Data(0x0050,0x0000); 
    Write_Cmd_Data(0x0051,0x00EF); 
    Write_Cmd_Data(0x0052,0x0000); 
    Write_Cmd_Data(0x0053,0x013F); 
    Write_Cmd_Data(0x0020,0x0000); 
    Write_Cmd_Data(0x0021,0x0000);           
    Write_Cmd_Data(0x0061,0x0001); 
    Write_Cmd_Data(0x006A,0x0000); 
    Write_Cmd_Data(0x0080,0x0000); 
    Write_Cmd_Data(0x0081,0x0000); 
    Write_Cmd_Data(0x0082,0x0000); 
    Write_Cmd_Data(0x0083,0x0000); 
    Write_Cmd_Data(0x0084,0x0000); 
    Write_Cmd_Data(0x0085,0x0000);         
    Write_Cmd_Data(0x0092,0x0300); 
    Write_Cmd_Data(0x0093,0x0005); 
    Write_Cmd_Data(0x0095,0x0000); 
    Write_Cmd_Data(0x0097,0x0000); 
    Write_Cmd_Data(0x0098,0x0000); 
    Write_Cmd_Data(0x0001,0x0100); 
    Write_Cmd_Data(0x0002,0x0700); 
    Write_Cmd_Data(0x0003,0x1030); 
    Write_Cmd_Data(0x0004,0x0000); 
    Write_Cmd_Data(0x000C,0x0000); 
    Write_Cmd_Data(0x000F,0x0000); 
    Delay_ms(30);   
    Write_Cmd_Data(0x0007,0x0001);
    Write_Cmd_Data(0x0007,0x0021); 
    Delay_ms(30);
    Write_Cmd_Data(0x0010,0x16B0);  // Write final user�s setting values to BT bits
    Write_Cmd_Data(0x0011,0x0007);  // Write final user�s setting values to VC bits
    Delay_ms(30);
    Write_Cmd_Data(0x0007,0x0061); 
    Delay_ms(30);
    Write_Cmd_Data(0x0007,0x0173); 
    Delay_ms(30);
		Clear_Screen(Blue);
}
void TouchToLcd(struct pix_ *Touch_Data)
{
	Touch_Data->x=(4096-Touch_Data->x-320)/15+7;
	Touch_Data->y=(Touch_Data->y-220)/11;	
}
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
	unsigned int i,j;
	LCD_SetPos(x0,x1,y0,y1);
	for (i=y0;i<=y1;i++)
	{
	   for (j=x0;j<=x1;j++)
	       Write_Data_U16(Color);

	}
}
