#include <reg51.h>

#define LED_PORT P1

unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//ÏÔÊ¾0~9µÄÖµ

void delayMs(int n)
{
	unsigned int a, b;
	for (n = 1; n > 0; --n)
		for (a = 110; a > 0; --a)
			for (b = 110; b > 0; --b);
}
int main()
{
	unsigned int i;
	while(1)
	{
		for	(i = 0; i <10; ++i)
			{
				LED_PORT = ~DIG_CODE[i];
				delayMs(10000);
			}
	}
	return 0;
}