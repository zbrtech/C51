/*========================================================================
#   FileName: main.c
#     Author: luchu1993
#      Email: luchu1993@163.com
#   HomePage: http://www.luchu1993.com
# LastChange: 2014-02-24 19:35:02
========================================================================*/
#include <reg51.h>


typedef unsigned char uint8;
typedef unsigned int uint16;

#define KEY P2
#define LED_PORT P0
uint8 code table[17] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71, 0x40};
uint16 code tab[] = {64026, 64106, 64256, 64396, 64526, 64586, 64686, 64776, 
					 64816, 64896, 64966, 65026, 65066, 65116, 65156, 65176};

sbit BEEP = P3^7;
uint8 disp_buf;
uint8 key;

uint8 STH0;
uint8 STL0;
void delayMs(uint16 xms)
{		 
	uint16 i, j;
	for (i = xms; i > 0; i--)
		for (j = 110; j > 0; j--);
}

void MatrixKey()
{
	KEY = 0xff;
	KEY = 0x0f;

	if (KEY != 0x0f)
	{
		delayMs(10);  //按键消抖
		if (KEY != 0x0f)
		{
			KEY = 0x0f;
			switch(KEY)
			{
				case 0x07:	key =  0; break;
				case 0x0b:	key =  1; break;
				case 0x0d:	key =  2; break;
				case 0x0e:	key =  3; break;
			}
			KEY = 0xf0;
			switch(KEY)
			{
				case 0x70:	key +=  0; break;
				case 0xb0:	key +=  4; break;
				case 0xd0:	key +=  8; break;
				case 0xe0:	key += 12; break;
			}

			disp_buf = table[key];
			STH0 = tab[key]/256;
			STL0 = tab[key]%256;
			TR0 = 1; //开启定时器
			while(KEY != 0xf0); //等待按键松开
			TR0 = 0;  //关闭定时器
			BEEP = 1;
		}
	}
}

int main()
{
	KEY = 0xff;
	LED_PORT = 0xff;
	TMOD = 0x01;
	EA =1; ET0 =1;
	disp_buf = 0x40;

	while(1)
	{
		MatrixKey();
		LED_PORT = ~disp_buf;
		delayMs(2);
	}
	return 0;
}

void timer0 (void) interrupt 1
{
	TH0 = STH0;
	TL0 = STL0;
	BEEP = ~BEEP;
}
