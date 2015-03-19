#include"upload.h"
#include"usart.h"

//����ͨ������1�ϴ���λ����������

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void UART1_ReportIMU(s16 yaw,s16 pitch,s16 roll
				,s16 alt,s16 tempr,s16 press)
*��������:		����λ�����;�����������̬����
���������
		s16 yaw ���������ĺ���Ƕȡ���λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
		s16 pitch ����õ��ĸ����Ƕȣ���λ 0.1�ȡ�-900 - 900 ��Ӧ -90.0 -> 90.0 ��
		s16 roll  �����õ��ĺ���Ƕȣ���λ0.1�ȡ� -1800 -> 1800 ��Ӧ -180.0  ->  180.0��
		s16 alt   ��ѹ�߶ȡ� ��λ0.1�ס�  ��Χһ�����ͱ���
		s16 tempr �¶� �� ��λ0.1���϶�   ��Χ��ֱ����ĵ�·�岻����������
		s16 press ��ѹѹ������λ10Pa  һ������ѹǿ��101300pa ����Ѿ�����һ�����͵ķ�Χ����Ҫ����10�ٷ�����λ��
		s16 IMUpersec  ��̬�������ʡ�����IMUpersecÿ�롣
���������û��	
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
