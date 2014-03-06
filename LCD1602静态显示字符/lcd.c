#include"lcd.h"
void lcd1602_delayMs(uint16 c)   //误差 0us
{
    uint8 a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

/*******************************************************************************
* 函 数 名         : lcd1602_wcmd
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //当没有定义这个LCD1602_4PINS时
void lcd1602_wcmd(uint8 com)	  //写入命令
{
	LCD1602_EN = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	lcd1602_port = com;     //放入命令
	lcd1602_delayMs(1);		//等待数据稳定

	lcd1602_EN = 1;	          //写入时序
	Lcd1602_delayMs(5);	  //保持时间
	lcd1602_EN = 0;
}
#else 
void lcd1602_wcmd(uint8 com)	  //写入命令
{
	LCD1602_EN = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	lcd1602_port = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	lcd1602_delayMs(1);

	LCD1602_EN = 1;	 //写入时序
	lcd1602_delayMs(5);
	LCD1602_EN = 0;

//	Lcd1602_Delay1ms(1);
	lcd1602_port = com << 4; //发送低四位
	lcd1602_delayMs(1);

	LCD1602_EN = 1;	 //写入时序
	lcd1602_delayMs(5);
	LCD1602_EN = 0;
}
#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void lcd1602_wdata(uint8 dat)			//写入数据
{
	LCD1602_EN = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	lcd1602_port = dat; //写入数据
	lcd1602_delayMs(1);

	LCD1602_EN = 1;   //写入时序
	lcd1602_delayMs(5);   //保持时间
	LCD1602_EN = 0;
}
#else
void lcd1602_wdata(uint8 dat)			//写入数据
{
	LCD1602_EN = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	lcd1602_port = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	lcd1602_delayMs(1);

	LCD1602_EN = 1;	  //写入时序
	lcd1602_delayMs(5);
	LCD1602_EN = 0;

	lcd1602_port = dat << 4; //写入低四位
	lcd1602_delayMs(1);

	LCD1602_EN = 1;	  //写入时序
	lcd1602_delayMs(5);
	LCD1602_EN = 0;
}
#endif
/*******************************************************************************
* 函 数 名       : lcd1602_init()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void lcd1602_init()						  //LCD初始化子程序
{
 	lcd1602_wcmd(0x38);  //开显示
	lcd1602_wcmd(0x0c);  //开显示不显示光标
	lcd1602_wcmd(0x06);  //写一个指针加1
	lcd1602_wcmd(0x01);  //清屏
	lcd1602_wcmd(0x80);  //设置数据指针起点
}
#else
void lcd1602_init()						  //LCD初始化子程序
{
	lcd1602_wcmd(0x32);	 //将8位总线转为4位总线
	lcd1602_wcmd(0x28);	 //在四位线下的初始化
	lcd1602_wcmd(0x0c);  //开显示不显示光标
	lcd1602_wcmd(0x06);  //写一个指针加1
	lcd1602_wcmd(0x01);  //清屏
	lcd1602_wcmd(0x80);  //设置数据指针起点
}
#endif
