#ifndef __LCD_H
#define __LCD_H		
#include <rtthread.h>
#include "stdlib.h"

//SPI��ʾ���ӿ�
//LCD_RST
#define SPILCD_RST_SET  GPIO_SetBits(GPIOB, GPIO_Pin_0)//PB0 
#define SPILCD_RST_RESET GPIO_ResetBits(GPIOB, GPIO_Pin_0)//PB0  
//LCD_RS//dc  
#define SPILCD_RS_SET  GPIO_SetBits(GPIOC, GPIO_Pin_4)//PC4 
#define SPILCD_RS_RESET  GPIO_ResetBits(GPIOC, GPIO_Pin_4)//PC4  
//LCD_CS  
#define SPILCD_CS_SET GPIO_SetBits(GPIOA, GPIO_Pin_4)//PA4 
#define SPILCD_CS_RESET  GPIO_ResetBits(GPIOA, GPIO_Pin_4)//PA4 

  
//LCD��Ҫ������
typedef struct  
{ 					    
	rt_uint16_t width;			//LCD ���
	rt_uint16_t height;			//LCD �߶�
	rt_uint16_t id;				//LCD ID
	rt_uint8_t	wramcmd;		//��ʼдgramָ��
	rt_uint8_t  setxcmd;		//����x����ָ��
	rt_uint8_t  setycmd;		//����y����ָ��	 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern rt_uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern rt_uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	LCD_REST PBout(1) //LCD REST    		 PB1 	    
//LCD��ַ�ṹ��
typedef struct
{
	rt_uint16_t LCD_REG;
	rt_uint16_t LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111110=0X3E			    
#define LCD_BASE        ((rt_uint32_t)(0x60000000 | 0x0007FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(rt_uint16_t Color);	 												//����
void LCD_SetCursor(rt_uint16_t Xpos, rt_uint16_t Ypos);										//���ù��
void LCD_DrawPoint(rt_uint16_t x,rt_uint16_t y);											//����
void LCD_Fast_DrawPoint(rt_uint16_t x,rt_uint16_t y,rt_uint16_t color);								//���ٻ���
void Draw_Circle(rt_uint16_t x0,rt_uint16_t y0,rt_uint8_t r);										//��Բ
void LCD_DrawLine(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);							//����
void LCD_DrawRectangle(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);		   				//������
void LCD_Fill(rt_uint16_t sx,rt_uint16_t sy,rt_uint16_t ex,rt_uint16_t ey,rt_uint16_t color);		   				//��䵥ɫ
void LCD_Color_Fill(rt_uint16_t sx,rt_uint16_t sy,rt_uint16_t ex,rt_uint16_t ey,rt_uint16_t *color);				//���ָ����ɫ
void LCD_ShowChar(rt_uint16_t x,rt_uint16_t y,rt_uint8_t num,rt_uint8_t size,rt_uint8_t mode);						//��ʾһ���ַ�
void LCD_ShowNum(rt_uint16_t x,rt_uint16_t y,rt_uint32_t num,rt_uint8_t len,rt_uint8_t size);  						//��ʾһ������
void LCD_ShowxNum(rt_uint16_t x,rt_uint16_t y,rt_uint32_t num,rt_uint8_t len,rt_uint8_t size,rt_uint8_t mode);				//��ʾ ����
void LCD_ShowString(rt_uint16_t x,rt_uint16_t y,rt_uint16_t width,rt_uint16_t height,rt_uint8_t size,rt_uint8_t *p);		//��ʾһ���ַ���,12/16����
	  
void showimage(rt_uint16_t x,rt_uint16_t y); //��ʾ40*40ͼƬ
void LCD_WriteReg(rt_uint8_t LCD_Reg, rt_uint16_t LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void LCD_WR_DATA8(rt_uint8_t da);   //д8λ����  
 
void showhanzi16(unsigned int x,unsigned int y,unsigned char index);//16*16����
void showhanzi32(unsigned int x,unsigned int y,unsigned char index);//32*32����						  		 
#endif  
