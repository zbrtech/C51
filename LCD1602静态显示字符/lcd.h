#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
#define LCD1602_4PINS

/**********************************
包含头文件
**********************************/
#include<reg51.h>

//---重定义关键词---//
#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16 
#define uint16 unsigned int
#endif

/**********************************
PIN口定义
**********************************/
#define lcd1602_port P0
sbit LCD1602_EN=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/**********************************
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void lcd1602_delayMs(uint16 c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void lcd1602_wcmd(uint8 com);
/*LCD1602写入8位数据子函数*/	
void lcd1602_wdata(uint8 dat);
/*LCD1602初始化子程序*/		
void lcd1602_init();						  

#endif
