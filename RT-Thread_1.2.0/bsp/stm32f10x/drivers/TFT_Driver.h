#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif
//unsigned char pic[];
/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0
#define Gray		   0xc615
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write


struct pix_
{
	unsigned int x;
	unsigned int y;
};
void delayms1(unsigned int count);
//void spistart();                                    
void WriteCharTo7843(unsigned char num);          
//unsigned int ReadFromCharFrom7843();            	
void delayms(int count);  // /* X1ms */
void Write_Cmd(unsigned int CMD);
void Write_Data(unsigned int Data);
void  Write_Cmd_Data (unsigned int x,unsigned int y);
void  Write_Data_U16(unsigned int y);
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void int2string(unsigned int dd,unsigned char *str);//int类型数据转换成字符串
void long2string(unsigned long dd,unsigned char *str);//int类型数据转换成字符串  
void int2string_TFTaxis_X(int dd,unsigned char *str);  
void int2string_TFTaxis_Y(int dd,unsigned char *str);
//unsigned char Makpix(struct pix_ pix1,struct pix_ pix2);
//struct pix_ AD7843();            
//unsigned char Getpix(); //取采样值，此处使用软件滤波，2次取样的值相差太大的视为噪声
void delay(unsigned int i);
void TFT_Init(void);
void TouchToLcd(struct pix_ *Touch_Data);
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);








				
#endif

