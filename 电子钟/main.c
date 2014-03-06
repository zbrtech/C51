#include <reg51.h>
#define LED_PORT P0

typedef unsigned int uint16;
typedef unsigned char uint8;

uint8 hour = 23; uint8 min = 59; uint8 sec = 45;
uint8 count_10ms = 0;

sbit K1 = P2^0;
sbit K2 = P2^1;
sbit K3 = P2^2;
sbit K4 = P2^3;

sbit LSPA = P2^5;
sbit LSPB = P2^6;
sbit LSPC = P2^7;

sbit BEEP = P3^7;
bit K1_FLAG = 0;

uint8 code seg_data[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
						 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71, 0x40};
uint16  disp_buf[8] = {0};
void delayMs(unsigned int nms)
{
	unsigned int i , j;
	for (i = nms; i > 0; i--)
		for (j = 110; j > 0; j--);
}

void beep()
{
	BEEP = 0;
	delayMs(1);
	BEEP = 1;
	delayMs(1);
}


void conv(uint8 in1, uint8 in2, uint8 in3)
{
	 disp_buf[0] = in1 / 10;
	 disp_buf[1] = in1 % 10;

	 disp_buf[3] = in2 / 10;
	 disp_buf[4] = in2 % 10;

	 disp_buf[6] = in3 /10;
	 disp_buf[7] = in3 % 10;

	 disp_buf[2] = 16;
	 disp_buf[5] = 16;
}

void display()
{
	uint8 i;
	for (i = 0; i < 8; ++i)
	{
		switch(i)
		{
			case 0: LSPA = 0; LSPB = 0; LSPC = 0; break;
			case 1: LSPA = 1; LSPB = 0; LSPC = 0; break;
			case 2: LSPA = 0; LSPB = 1; LSPC = 0; break;
			case 3: LSPA = 1; LSPB = 1; LSPC = 0; break;
			case 4: LSPA = 0; LSPB = 0; LSPC = 1; break;
			case 5: LSPA = 1; LSPB = 0; LSPC = 1; break;
			case 6: LSPA = 0; LSPB = 1; LSPC = 1; break;
			case 7: LSPA = 1; LSPB = 1; LSPC = 1; break;
		}
		LED_PORT = seg_data[disp_buf[i]];
		delayMs(1);
		LED_PORT = 0x00;
	}
}

void key_process()
{
	TR1 = 0; //¹Ø±Õ¶¨Ê±Æ÷;
	if (K2 == 0)
	{
		delayMs(10);
		if (K2 == 0)
		{
			while(!K2) { beep();}
			hour++;
			if (hour == 24)  hour = 0;
		}
	}

	if (K3 == 0)
	{
		delayMs(10);
		if (K3 == 0)
		{
			 while(!K3) { beep();}
			 min++;
			 if (min == 60) min = 0;
		}
	}

	if (K4 == 0)
	{			  
		delayMs(10);
		if (K4 == 0)
		{
			while(!K4) {beep();}
			TR1 = 1;
			K1_FLAG = 0;
		}
		
	}
}

void timer1_init()
{
	TMOD = 0x10;
    TH1 = 0x0D8;
    TL1 = 0x0F0;
    EA = 1;
    ET1 = 1;
    TR1 = 1;
}
int main()
{
	P0 = 0x00;
	P2 = 0xff;
	timer1_init();
	while(1)
	{
		display();
		if (K1 == 0)
		{
			 delayMs(10);
			 if (K1 == 0)
			 {
				while(!K1){beep(); }
				K1_FLAG = 1;
			 }
		}
		if (K1_FLAG == 1) key_process();
		conv(hour,min, sec);
	}
	return 0;
}

void timer1() interrupt 3
{
	TH1 = 0x0D8; TL1 = 0x0F0;
	count_10ms++;
	if (count_10ms >= 100)
	{
		count_10ms = 0;	sec++;
		if (sec == 60)
		{
			min++; sec= 0;
			if (min == 60)
			{
				hour++; min = 0;
				if (hour == 24)
				{
					hour = 0; min = 0; sec = 0;
				}
			}
		}
	}
}