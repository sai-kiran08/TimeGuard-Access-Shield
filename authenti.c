#include "kpm.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "type.h"
#include<string.h>

u32 enterpass(s8 *storedpass)
{
	u32 i;
	s8 key;
	s8 password[6];
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENTER PASSWORD");
	i=0;
	while(i<5)
	{
		key=keyscan();
		if(key=='C')
		{
			i=0;
			clearLCD();
			memset(password,0,sizeof(password));
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("ENTER PASSWORD");
			cmdLCD(GOTO_LINE2_POS0);
			continue;
		}
		else if(key=='B' && i>0)
		{
			i--;
			password[i]='\0';
			cmdLCD(GOTO_LINE2_POS0+i);
			charLCD(' ');
			cmdLCD(GOTO_LINE2_POS0+i);
			while(keyscan()=='B');
			continue;
		}
		else if(key>='0' && key<='9')
		{
			password[i]=key;
			cmdLCD(GOTO_LINE2_POS0+i);
			charLCD('*');
			i++;
			while(keyscan()==key);
		}
		delay_ms(200);
	}password[5]='\0';
	if(strcmp(storedpass,password)==0)
	{
		return 1;
	}
	else
	{
		memset(password,0,sizeof(password));
		return 0;
	}
}
u32 checktimeslot(s32 *hour,s32 *starthr,s32 *endhr)
{
	if((*hour)>=(*starthr) && (*hour)<=(*endhr))
	{
			return 1;
	}
	else
		return 0;
}
