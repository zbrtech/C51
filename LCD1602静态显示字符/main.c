#include <reg51.h>
#include "lcd.h"

main()
{
	uint8 code line1[] = {"    CSLG    "};
	uint8 code line2[] = {"Hello Wrold!"};
	uint8 i;

	lcd1602_init();
	for(;;)
	{
		i = 0;
		lcd1602_wcmd(0x10 | 0x80);
		while (line1[i] != '\0')
		{
			lcd1602_wdata(line1[i]);
			i++;
		}
		lcd1602_wcmd(0x50 | 0x80);
		i = 0;
		while (line2[i] != '\0')
		{
			lcd1602_wdata(line2[i]);
			i++;
		}
	
		for (i = 0; i < 16; ++i)
		{
			lcd1602_wcmd(0x18);
			lcd1602_delayMs(500);
		}
	}	
}