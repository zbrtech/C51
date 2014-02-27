#include <reg51.h>
#include <intrins.h>
typedef unsigned int uint16;
typedef unsigned char uint8;

uint8 code dig[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint8 time_count = 0, count = 0;

sbit BEEP = P3^7;

void delayMs(unsigned int nms)
{
	unsigned int i , j;
	for (i = nms; i > 0; i--)
		for (j = 110; j > 0; j--);
}

void display()
{
	P0 = dig[count / 10];
	P2 = 0x7f;
	delayMs(5);

	P0 = dig[count % 10];
	P2 = 0xbf;
	delayMs(5);

	P2 = 0xff;
}

void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0x0B0;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void beep()
{
	  BEEP = 0 ;
	  delayMs(5);
	  BEEP = 1;
	  delayMs(5);
}
int main()
{
	P0 = 0xff;
	P2 = 0xff;
	
	InitTimer0();

	while(1)
	{
		display();
	}
	return 0;
}

void timer0() interrupt 1 
{
	TH0 = 0x3C;
    TL0 = 0x0B0;
	time_count++;
	if (time_count == 20)
	{
		time_count = 0;
		beep();
		count++;
	}
	
	if (count == 60) 	count = 0;	
}