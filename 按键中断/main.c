#include <reg51.h>


#define LED_PORT P0

typedef unsigned char uint8;
typedef unsigned char uint16;

uint8 code dig_number[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
uint8 num = 5;

void interrupt_init()
{
	EX0 = 1;
	EA = 1;
	IT0 = 0; //
}

void delay(uint16 n)
{
	   while(n--);
}

int main()
{
	LED_PORT = ~0x6d;
	interrupt_init();
	while(1);
	return 0;
}

void interrupt_0() interrupt 0
{
	delay(10000);
	if (INT0 == 0)
	{
		++num;
		if (num >= 10) num = 0;
		LED_PORT = ~dig_number[num];
		while(!INT0);
	}
}