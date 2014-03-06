/*========================================================================
#   FileName: LCD1602.h
#     Author: luchu1993
#      Email: luchu1993@163.com
#   HomePage: http://www.luchu1993.com
# LastChange: 2014-03-05 13:49:36
========================================================================*/

#ifndef _LCD_1602_H
#define _LCD_1602_H
#include <reg51.h>
#include <intrins.h>

typedef unsigned int uint16;
typedef unsigned char uint8;

sbit LCD_RS = P2^6; //单片机管脚p2.6
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;

/* 延迟4个时钟周期 */
void nop_4();

/* 检测lcd忙碌 */
bit lcd_busy();

/* LCD清屏函数 */
void lcd_clr();

/* 写指令函数 */
void lcd_wcmd(uint8 cmd);

/* 写数据函数 */
void lcd_wdat(uint8 dat);

/* LCD初始化 */
void lcd_init();

/* 延时nms毫秒函数 */
void delayMs(uint16 nms);

#endif
