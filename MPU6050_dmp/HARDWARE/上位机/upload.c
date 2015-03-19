#include"upload.h"
#include"usart.h"

//数据通过串口1上传上位机驱动程序

/**************************实现函数********************************************
*函数原型:		void UART1_ReportIMU(s16 yaw,s16 pitch,s16 roll
				,s16 alt,s16 tempr,s16 press)
*功　　能:		向上位机发送经过解算后的姿态数据
输入参数：
		s16 yaw 经过解算后的航向角度。单位为0.1度 0 -> 3600  对应 0 -> 360.0度
		s16 pitch 解算得到的俯仰角度，单位 0.1度。-900 - 900 对应 -90.0 -> 90.0 度
		s16 roll  解算后得到的横滚角度，单位0.1度。 -1800 -> 1800 对应 -180.0  ->  180.0度
		s16 alt   气压高度。 单位0.1米。  范围一个整型变量
		s16 tempr 温度 。 单位0.1摄氏度   范围：直到你的电路板不能正常工作
		s16 press 气压压力。单位10Pa  一个大气压强在101300pa 这个已经超过一个整型的范围。需要除以10再发给上位机
		s16 IMUpersec  姿态解算速率。运算IMUpersec每秒。
输出参数：没有	
*******************************************************************************/
void UART1_ReportIMU(s16 yaw,s16 pitch,s16 roll
,s16 alt,s16 tempr,s16 press,s16 IMUpersec)
{
 	unsigned int temp=0xaF+2;
	char ctemp;
	UsartSend(0xa5);
	UsartSend(0x5a);
	UsartSend(14+2);
	UsartSend(0xA1);

	if(yaw<0)yaw=32768-yaw;
	ctemp=yaw>>8;
	UsartSend(ctemp);
	temp+=ctemp;
	ctemp=yaw;
	UsartSend(ctemp);
	temp+=ctemp;

	if(pitch<0)pitch=32768-pitch;
	ctemp=pitch>>8;
	UsartSend(ctemp);
	temp+=ctemp;
	ctemp=pitch;
	UsartSend(ctemp);
	temp+=ctemp;

	if(roll<0)roll=32768-roll;
	ctemp=roll>>8;
	UsartSend(ctemp);
	temp+=ctemp;
	ctemp=roll;
	UsartSend(ctemp);
	temp+=ctemp;

	if(alt<0)alt=32768-alt;
	ctemp=alt>>8;
	UsartSend(ctemp);
	temp+=ctemp;
	ctemp=alt;
	UsartSend(ctemp);
	temp+=ctemp;

	if(tempr<0)tempr=32768-tempr;
	ctemp=tempr>>8;
	UsartSend(ctemp);
	temp+=ctemp;
	ctemp=tempr;
	UsartSend(ctemp);
	temp+=ctemp;

	if(press<0)press=32768-press;
	ctemp=press>>8;
	UsartSend(ctemp);
	temp+=ctemp;
	ctemp=press;
	UsartSend(ctemp);
	temp+=ctemp;

	UsartSend(temp%256);
	UsartSend(0xaa);
}
