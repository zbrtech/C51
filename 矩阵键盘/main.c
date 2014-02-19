#include <reg51.h>

#define KEY_PORT P1
#define LED_PORT P0

unsigned char code DIG_CODE[]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

unsigned char keyValue;
void delay10Ms();
void keyDown();

int main()
{
	while (1)
	{
		keyDown();
		LED_PORT = ~DIG_CODE[keyValue];
	}
	return 0;
}

void keyDown()
{
	unsigned char a;
	KEY_PORT = 0x0f;
	if (KEY_PORT != 0x0f)
	{
		delay10Ms();  	//°´¼üÏû¶¶
		if (KEY_PORT != 0x0f)
	    {
			switch (KEY_PORT)
			{
				case 0x07:	  keyValue = 0; break;
				case 0x0b:	  keyValue = 1; break;
				case 0x0d:	  keyValue = 2; break;
				case 0x0e:	  keyValue = 3; break;
			}
			KEY_PORT = 0xf0;    //ÁÐ¼ì²â
			switch (KEY_PORT)
			{
				case 0x70:	 break;
				case 0xb0:	 keyValue += 4; break;
				case 0xd0:	 keyValue += 8; break;
				case 0xe0:	 keyValue += 12; break;
			}

			while (a < 50 && KEY_PORT != 0xf0)
			{
				delay10Ms();
				++a;
			}
		}
	}
}

void delay10Ms()
{
	unsigned char a, b;
	for (a = 38; a > 0; --a)
		for (b = 130; b >0; --b);
}