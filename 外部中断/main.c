#include <reg51.h>

sbit LS138A = P2^2;
sbit LS138B = P2^3;
sbit LS138C = P2^4; 

unsigned int int0Num, int1Num, ledOut[8];

unsigned char code DIG_NUM[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};


void systemInit(){
	IT0 = 1; //采用下降沿中断
	EX0 = 1; //允许外部中断0

	IT1 = 1; //采用下降沿中断
	EX1 = 1; //允许外部中断1
	EA = 1; //允许CPU中断
}

void delayMs(unsigned char i)
{
	unsigned char j;
	for (; i > 0; --i)
		for (j = 200; j > 0; --j);
}

void main(){
	unsigned char i;
	systemInit();
	while (1){
		ledOut[0] = DIG_NUM[int0Num%10000/1000];
		ledOut[1] = DIG_NUM[int0Num%1000/100];
		ledOut[2] = DIG_NUM[int0Num%100/10];
		ledOut[3] = DIG_NUM[int0Num%10];

		ledOut[4] = DIG_NUM[int1Num%10000/1000];
		ledOut[5] = DIG_NUM[int1Num%1000/100];
		ledOut[6] = DIG_NUM[int1Num%100/10];
		ledOut[7] = DIG_NUM[int1Num%10];

		for (i = 0; i < 8; ++i){
			P0 = ledOut[i];
			switch(i)
			{
				case 0: LS138A = 0; LS138B = 0; LS138C = 0; break;
				case 1: LS138A = 1; LS138B = 0; LS138C = 0; break;
				case 2: LS138A = 0; LS138B = 1; LS138C = 0; break;
				case 3: LS138A = 1; LS138B = 1; LS138C = 0; break;
				case 4: LS138A = 0; LS138B = 0; LS138C = 1; break;
				case 5: LS138A = 1; LS138B = 0; LS138C = 1; break;
				case 6: LS138A = 0; LS138B = 1; LS138C = 1; break;
				case 7: LS138A = 1; LS138B = 1; LS138C = 1; break;
			}
			delayMs(5);
		}

	}
}

void Int0_zd(void)	interrupt 0 using 1
{
	EX0 = 0;
	++int0Num;
	EX0 = 1;
}

void Int1_zd(void)	interrupt 2 using 2
{
	EX1 = 0;
	++int1Num;
	EX1 = 1;
}