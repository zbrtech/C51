#include <reg51.h>

typedef unsigned char uint8;
typedef unsigned int uint16;

#define LED_PORT P0

uint8 code dig_number[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40};

void delay(uint16 n)
{
	while(n--);
}

int main()
{
	uint8 i = 0;
	while (1)
	{
		for (i = 0; i < 6; ++i)
		{
			LED_PORT = ~dig_number[i];
			delay(20000);
		}
							 
	}
	return 0;
}