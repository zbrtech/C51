#include <reg51.h>

typedef unsigned char uint8;
typedef unsigned int uint16;

#define LED_PORT P0

sbit LSPA = P2^0;
sbit LSPB = P2^1;
sbit LSPC = P2^2;
uint8 code dig_number[] = {0x39, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0f};

void delay(uint8 n)
{
	while(n--);
}

void main()
{
	uint8 i;
		 while(1)
		 {
		 	  for (i = 0; i < 8; ++i)
			  {
			  		switch(i)
					{
						case 0:	 LSPA = 0;LSPB = 0; LSPC = 0; break;
						case 1:	 LSPA = 1;LSPB = 0; LSPC = 0; break;
						case 2:	 LSPA = 0;LSPB = 1; LSPC = 0; break;
						case 3:	 LSPA = 1;LSPB = 1; LSPC = 0; break;
						case 4:	 LSPA = 0;LSPB = 0; LSPC = 1; break;
						case 5:	 LSPA = 1;LSPB = 0; LSPC = 1; break;
						case 6:	 LSPA = 0;LSPB = 1; LSPC = 1; break;
						case 7:	 LSPA = 1;LSPB = 1; LSPC = 1; break;
					} 
					P0 = dig_number[i];
					delay(1000);
			  }
		 }
}


