#include <reg52.h>

#define LED_PORT P2

/*
*  delay some time.
*/
void Delay10Ms(unsigned int i)
{
		 unsigned int a, b;
		 for (; i > 0; --i)
		 	for(a = 38; a > 0; --a)
				for (b = 130; b > 0; --b);
}

int main()
{
	unsigned char  led;

	led = 0xfe;

	while(1)
	{
		LED_PORT = led;
		Delay10Ms(50);
		led <<= 1;
		if (LED_PORT == 0x00)
			led = 0xfe;
	}
	return 0;
}