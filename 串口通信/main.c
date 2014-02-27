#include <reg51.h>

void usartConfig(void)
{
	  	SCON = 0x50; //REN=1允许接收数据； 工作方式1， 8位Uart方式
		PCON = 0x80; //波特率不加倍
		TMOD = 0x20; //T1工作在方式2（自动重装）
		TH1 = 0xf3;
		TL1 = 0xf3;
		ES = 1; //打开接受中断
		TR1 = 1;  //打开计数器
		EA = 1; //CPU中断使能
}

void main()
{
	while(1)
	{	
	}
}

void T1_zd(void) interrupt 4   //串口中断
{
	unsigned char receiveData;

	receiveData = SBUF;
	RI = 0;
	SBUF = receiveData;
	while (!TI);
	TI = 0;

}