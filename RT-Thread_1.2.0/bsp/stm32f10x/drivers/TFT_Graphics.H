/*************************************************************************
文件名：TFT_Graphics.H
描  述：图形函数库库函数外部声明
作  者：
日  期：2012.4.20
*************************************************************************/

#ifndef __TFT_Graphics_H__
#define __TFT_Graphics_H__


#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


//#define unsigned int uint

typedef unsigned int COLOR;
typedef unsigned char BYTE;
typedef unsigned char LINE_WIDTH;
typedef struct
{
    unsigned int xstart;
	unsigned int xend;
	unsigned int ystart;
	unsigned int yend;
	unsigned int xdis;
	unsigned int ydis;
}Win_Size;




#define RGB(R, G, B) ((COLOR)(R&0XF8)<<8|(COLOR)(G&0XFC)<<3|(COLOR)(B&0XF8)>>3)



//static void Set_Window(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void Set_Window(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1);
void Clear_Screen(COLOR bColor);
void Draw_Point(unsigned int x, unsigned int y);
void Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void Set_Linestyle(LINE_WIDTH width );
void LCD_PrintNum(unsigned char x, unsigned int y,int num);

void Rectangle(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);
void bar(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);
void drawpoint(unsigned char x,unsigned int y,unsigned int color);
void Paint(unsigned int X,unsigned int Y,unsigned int color);//画图，触摸坐标系的原点为右上角，TFT屏的坐标原点为左上角，故需坐标转换

void Set_Color(COLOR color);
void Set_BkColor(COLOR color);

void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s,unsigned char num, unsigned int fColor, unsigned int bColor);

void GUI_DisPicture(unsigned char x, unsigned int y, unsigned char length,unsigned int high);

#endif

