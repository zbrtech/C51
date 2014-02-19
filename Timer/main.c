#include <reg51.h>
#include <intrins.h>

#define LED_PORT P0	 //数码显示

sbit LSP138A = P2^2;	//位选
sbit LSP138B = P2^3;
sbit LSP138C = P2^4;

unsigned int ledNumVal,  ledOut[8];
unsigned char code	dispTab[] = {
~0xC0,~0xF9,~0xA4,~0xB0,~0x99,~0x92,~0x82,~0xF8,~0x80,~0x90,
~0x88,~0x83,~0xC6,~0xA1,~0x86,~0xbf,~0xc7,~0x8c,~0xc1, ~0xff, ~0xf7};
void systemInit()
{
	TMOD = 0x00; //工作模式0， 13位计数器,最大8192， C/T = 0，由内部系统提供工作脉冲 -- 12M，12分频， 周期1us.
	TH0 = (8192 - 1000)/32;
	TL0 = (8192 - 1000)%32; 
	IE = 0x8a; //允许计时器中断
	TR0 = 1; //启动定时器工作
}

void delay(unsigned int i)
{
	  char j;
	  for (; i > 0; --i)
	  	for (j = 200; j > 0; --j);
}
int main()
{	 
	systemInit();
	 while (1){
	 	unsigned char i;
		
		ledOut[0] = dispTab[ledNumVal%10000/1000];
		ledOut[1] = dispTab[ledNumVal%1000/100];
		ledOut[2] = dispTab[ledNumVal%100/10];
		ledOut[3] = dispTab[ledNumVal%10];	
		
		for (i = 0; i < 8; ++i)
		{
			LED_PORT = ledOut[i];
			switch(i){
				case 0:LSP138A = 0; LSP138B = 0; LSP138C = 0;break;
				case 1:LSP138A = 1; LSP138B = 0; LSP138C = 0;break;
				case 2:LSP138A = 0; LSP138B = 1; LSP138C = 0;break;
				case 3:LSP138A = 1; LSP138B = 1; LSP138C = 0;break;
				case 4:LSP138A = 0; LSP138B = 0; LSP138C = 1;break;
				case 5:LSP138A = 1; LSP138B = 0; LSP138C = 1;break;
				case 6:LSP138A = 0; LSP138B = 1; LSP138C = 1;break;
				case 7:LSP138A = 1; LSP138B = 1; LSP138C = 1;break;
			}
			delay(150);
		}	
	 }
	 return 0;
}

/*
 *  T0 1ms 中断
 */
void   T0zd(void) interrupt 1	   /* （中断号）0: 外部中断1， 1: Timer0中断 2: 外部中断2 3: Timer1中断 4: 串口中断*/
{
	 TH0 = (8192 - 1000)/32;
	 TL0 = (8192 - 1000)%32;
	 ++ledNumVal;
}