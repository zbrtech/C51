#include "i2c.h"

void I2C_Delay10us()
{
	 uchar a, b;
	 
	 for (b = 1; b > 0; --b)
	 	for (a = 2; a > 0; --a);
}

void I2C_Strat()
{
	I2C_SDA = 1;
	I2C_Delay10us();
	I2C_SCL = 1;
	I2C_Delay10us();
	I2C_SDA = 0;
	I2C_Delay10us();
	I2C_SCL = 0;
	I2C_Delay10us();
}

I2C_Stop()
{
	I2C_SDA = 0;
	I2C_Delay10us();
	I2C_SCL = 1;
	I2C_Delay10us();
	I2C_SDA = 1;
	I2C_Delay10us();
}

uchar I2C_SendByte(uchar dat, uchar ack)
{
	uchar a = 0,b = 0;
	for (a = 0; a < 8; ++a)
	{
		I2C_SDA = dat >>7;
		dat <<= 1;
		I2C_Delay10us();
		I2C_SCL = 1;
		I2C_Delay10us();
		I2C_SCL = 0;
		I2C_Delay10us();
	}

	I2C_SDA = 1;
	I2C_Delay10us();
	I2C_SCL = 1;

	while (I2C_SDA && (ack == 1))
	{
		b++;
		if (b > 200)
		{
			I2C_SCL = 0;
			I2C_Delay10us();
			return 0;
		}
	}

	I2C_SCL  = 0;
	I2C_Delay10us();

	return 1;
}

uchar I2C_ReadByte()
{
	uchar a = 0, dat = 0;
	I2C_SDA = 1;
	I2C_Delay10us();
	for (a = 0; a < 8; ++a)
	{
		I2C_SCL = 1;
		I2C_Delay10us();
		dat <<= 1;
		dat |= I2C_SDA;
		I2C_Delay10us();
		I2C_SCL = 0;
		I2C_Delay10us();
	}

	return dat;
}










