#include <reg51.h>

#define LED_PORT P0	  //段选
#define SEL_PORT P1	  //位选

unsigned char code DIG_CODE[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
								 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //显示0,1,2,3,4,5,6,7
unsigned char DIS_CODE[8];
unsigned char code DIG_SPACE[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};	 //位选

void Display();
void delay(unsigned char c);
int main()
{
	unsigned char i;
	for (i = 0; i < 8; ++i)
		DIS_CODE[i] = DIG_CODE[i];
	while(1)
	{
		Display();
	}
	return 0;
}

void Display()
{
	unsigned char i;
	unsigned char j;
	for (i = 0; i < 8; ++i)
	{
		SEL_PORT = DIG_SPACE[i];   //共阴极位选
		LED_PORT = DIS_CODE[2];	   //发送数据
		//j = 10;
		//while(--j);
		delay(10);

		LED_PORT = 0x00; //消隐
	}
}

void delay(unsigned char c)
{
	unsigned char a, b;
	for (; c > 0; --c)
		for (a = 38; a > 0; ++a)
			for (b = 130; b > 0; ++b);
		 	
}
