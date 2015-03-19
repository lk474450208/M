//#include "..\STC15F2K60S2.h"
//#include "..\User Code\\include.h"
sbit key1 = P3^7;
sbit key2 = P3^6;
sbit key3 = P3^3;
sbit key4 = P3^2;
bit runmode = 1;
extern SPWM_Data Sd;
unsigned int keyy;
void mode0_Draw_Init() 
{
	Clear_Screen(Black);
	LCD_PutString(10,20,"data1:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,60,"data2:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,100,"data3:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,140,"data4:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,180,"data5:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,220,"data6:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,260,"data7:<           >",sizeof("data1:<           >"),Yellow,Black);
	LCD_PutString(10,300,"Start",sizeof("Start"),Yellow,Black);
	keyy = 20;
}

void mode1_Draw_Init()
{
	Clear_Screen(Black);
}
char mode0_key_match()
{
unsigned char buf[5];
		 if(!key1)
		 {
		 	LCD_PutString(200,keyy," ",1,Black,Black);
			
			if(keyy==300)
			{
				keyy = 20;		
			}
			else
			{
				keyy+=40;					
			}
		 	while(!key1);
		 }
		 if(!key2)
		 {
			LCD_PutString(200,keyy," ",1,Black,Black);

			if(keyy <= 20)
			{
				keyy = 300;	
			}
			else
			{
				keyy-=40;				
			}
		 	while(!key2);
		 }
		 if(!key3)
		 {
			switch(keyy)
			{
				case 20:
				{
//					Sd.freq+=10;
//					int2string(Sd.freq,buf);
//					LCD_PutString(74,keyy,buf,5,Yellow,Black);
				}
				break;
				case 60:
				{
//					Sd.amp+=10;
//					int2string(Sd.amp,buf);
//					LCD_PutString(74,keyy,buf,5,Yellow,Black);				
				}
				break;
				case 100:
				{
	//				Sd.setoff+=10;
	//				int2string(Sd.setoff,buf);
//					LCD_PutString(74,keyy,buf,5,Yellow,Black);					
				}
				break;
				case 140:
				{
			
				}
				break;
				case 180:
				{
				
				}
				break;
				case 220:
				{
				
				}
				break;
				case 260:
				{
				
				}
				break;
				case 300:
				{
					runmode = 1;
					mode1_Draw_Init();
				}
				break;
				default:
				{
				
				}
			}
		 	while(!key3);
		 }
		 if(!key4)
		 {
			switch(keyy)
			{
				case 20:
				{
	//				Sd.freq-=10;
	//				int2string(Sd.freq,buf);
	//				LCD_PutString(74,keyy,buf,5,Yellow,Black);
				}
				break;
				case 60:
				{
		//			Sd.amp-=10;
		//			int2string(Sd.amp,buf);
		//			LCD_PutString(74,keyy,buf,5,Yellow,Black);
				}
				break;
				case 100:
				{
		//			Sd.setoff-=10;
		//			int2string(Sd.setoff,buf);
		//			LCD_PutString(74,keyy,buf,5,Yellow,Black);					
				}
				break;
				case 140:
				{
				
				}
				break;
				case 180:
				{
				
				}
				break;
				case 220:
				{
				
				}
				break;
				case 260:
				{
				
				}
				break;
				case 300:
				{
				   runmode = 1;
				   mode1_Draw_Init();
				}
				break;
				default:
				{
				
				}
			}
		 	while(!key4);
			
		 }
		 if(runmode == 0)
		 {
		 LCD_PutString(200,keyy,"<",1,Red,Black);
		 }					   
		 return 0;	
}

char mode1_key_match()
{
//unsigned char buf[5];

	if(!key1)
	{
		runmode = 0;
		mode0_Draw_Init();
		while(!key1);
	}
	if(!key2)
	{
	    while(!key2);
	}
	if(!key3)
	{

	    while(!key3);
	}
	if(!key4)
	{
//						Send_UART(Sd.freq);
//				Send_UART(Sd.freq<<8);				
	//			Send_UART(Sd.amp);
//				Send_UART(Sd.amp<<8);					
//				Send_UART(Sd.setoff);
	//			Send_UART(Sd.setoff<<8);
	    while(!key4);
	}

	return 0;
}