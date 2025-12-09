#include "type.h"
#include "rtc.h"
#include "kpm.h"
#include "lcd.h"
#include "rtc_defines.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "delay.h"
#include "editsec.h"
#include<string.h>

void editrtc(void)
{
	s8 a;
	clearLCD();
	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("1:TIME 2:DATE");
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("3:DAY  C:BACK");
		a=getkey();
		if(a=='C')
		{
			clearLCD();
			delay_ms(50);
			break;
		}
		else if(a>='0' && a<='9')
		{
			switch(a)
			{
				case '1':timedit();break;
				case '2':datedit();break;
				case '3':editday();break;
			}
		}
	}
}
void editwrkhr(s32 *starthr,s32 *endhr)
{
	s8 k;
	s32 sthr=*starthr;
	s32 enhr=*endhr;
	clearLCD();
	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("1:STAHR 2:ENDHR");
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("C:BACK");
		k=getkey();
		if(k=='C')
		{
			clearLCD();
			break;
		}
		else
		{
			switch(k)
			{
				case '1':incsthr(&sthr);break;
				case '2':incendhr(&enhr);break;
			}
		}
		*starthr=sthr;
		*endhr=enhr;
		
	}
	
}
void incsthr(s32 *sthr)
{
	s8 k;
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("2:INC 8:DEC C:OK");
	while(1)
	{
		k=getkey();
		if(k=='C')
		{
			clearLCD();
			break;
		}
		else if(k=='2')
		{
			if((*sthr)<24)
					(*sthr)++;
		}
		else if(k=='8')
		{
			if((*sthr)>1)
					(*sthr)--;
		}
		cmdLCD(GOTO_LINE2_POS0);
		charLCD(((*sthr)/10)+48);
		charLCD(((*sthr)%10)+48);
	}
}
void incendhr(s32 *enhr)
{
	s8 k;
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("2:INC 8:DEC C:OK");
	while(1)
	{
		k=getkey();
		if(k=='C')
		{
			clearLCD();
			break;
		}
		else if(k=='2')
		{
			if((*enhr)<24)
					(*enhr)++;
		}
		else if(k=='8')
		{
			if((*enhr)>1)
					(*enhr)--;
		}
		cmdLCD(GOTO_LINE2_POS0);
		charLCD(((*enhr)/10)+48);
		charLCD(((*enhr)%10)+48);
	}
}
void timedit(void)
{
	s8 a;
	clearLCD();
	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("1:HR 2:MIN C:BAC");
		a=getkey();
		if(a=='C')
		{
			clearLCD();
			delay_ms(50);
			break;
		}
		switch(a)
		{
			case '1':houredit();break;
			case '2':minedit();break;
		}
	}
}
void houredit(void)
{
	s8 a;
	u32 i;
	u32 hour;
	s8 hr[2];
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENT HR 0-23 C:OK");
	while(1)
	{
		for(i=0;i<2;i++)
		{
			a=getkey();
			if(a>='0' && a<='9')
			{
					cmdLCD(GOTO_LINE2_POS0+i);
					hr[i]=a;
					charLCD(hr[i]);
			}
		}
		if(i==2)
		{
			hour=(hr[0]-'0')*10+(hr[1]-'0');
			if(hour<=23)
			{
				SetRTCHrinfo(hour);
				while(1)
				{
					a=getkey();
					if(a=='C')
						break;
				}
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("HOURS SET");
				delay_ms(500);
				return;
			}
			else
			{
				i=0;
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("INVALID ENTER");
				delay_ms(500);
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("ENT HR 0-23 C:OK");
			}
		}
	}
}
void minedit(void)
{
	s8 a;
	u32 i;
	u32 minutes;
	s8 min[2];
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENT MIN0-59 C:OK");
	while(1)
	{
		for(i=0;i<2;i++)
		{
			a=getkey();
			if(a>='0' && a<='9')
			{
					cmdLCD(GOTO_LINE2_POS0+i);
					min[i]=a;
					charLCD(min[i]);
			}
		}
		if(i==2)
		{
			minutes=(min[0]-'0')*10+(min[1]-'0');
			if(minutes<=59)
			{
				SetRTCMininfo(minutes);
				while(1)
				{
					a=getkey();
					if(a=='C')
						break;
				}
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("MINUTES SET");
				delay_ms(500);
				return;
			}
			else
			{
				i=0;
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("INVALID ENTER");
				delay_ms(500);
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("ENT MIN0-59 C:OK");
			}
		}
	}
}
void datedit(void)
{
	s8 a;
	clearLCD();
	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("1:DAT 2:MON");
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("3:YEAR C:BACK");
		a=getkey();
		if(a=='C')
		{
			clearLCD();
			delay_ms(50);
			break;
		}
		switch(a)
		{
			case '1':editdate();break;
			case '2':monthedit();break;
			case '3':yearedit();break;
		}
	}
}
void editdate(void)
{
	s8 a;
	u32 i;
	u32 date;
	s8 dt[2];
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENT DAT 0-31 C:OK");
	while(1)
	{
		for(i=0;i<2;i++)
		{
			a=getkey();
			if(a>='0' && a<='9')
			{
					cmdLCD(GOTO_LINE2_POS0+i);
					dt[i]=a;
					charLCD(dt[i]);
			}
		}
		if(i==2)
		{
			date=(dt[0]-'0')*10+(dt[1]-'0');
			if(date<=31)
			{
				SetRTCDaTinfo(date);
				while(1)
				{
					a=getkey();
					if(a=='C')
						break;
				}
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("DATE SET");
				delay_ms(500);
				clearLCD();
				return;
			}
			else
			{
				i=0;
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("INVALID ENTER");
				delay_ms(500);
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("ENT DAT 0-31 C:OK");
			}
		}
	}
}
void monthedit(void)
{
	s8 a;
	u32 i;
	u32 month;
	s8 mn[2];
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENT MON0-12 C:OK");
	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENT MON0-12 C:OK");
		for(i=0;i<2;i++)
		{
			a=getkey();
			if(a>='0' && a<='9')
			{
					cmdLCD(GOTO_LINE2_POS0+i);
					mn[i]=a;
					charLCD(mn[i]);
			}
			
		}
		if(i==2)
		{
			month=(mn[0]-'0')*10+(mn[1]-'0');
			if(month<=12)
			{
				SetRTCMonthinfo(month);
				while(1)
				{
					a=getkey();
					if(a=='C')
						break;
				}
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("MONTH SET");
				delay_ms(500);
				return;
			}
			else
			{
				i=0;
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("INVALID ENTER");
				delay_ms(500);
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("ENT MON0-12 C:OK");
			}
		}
	}
}
void yearedit(void)
{
	s8 a;
	u32 i;
	u32 year;
	s8 yr[4];
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("ENTER YEAR C:OK");
	while(1)
	{
		for(i=0;i<4;i++)
		{
			a=getkey();
			if(a>='0' && a<='9')
			{
					cmdLCD(GOTO_LINE2_POS0+i);
					yr[i]=a;
					charLCD(yr[i]);
			}
		}
		if(i==4)
		{
			year=(yr[0]-'0')*1000+(yr[1]-'0')*100+(yr[2]-'0')*10+(yr[3]-'0');
			if(year<=2030)
			{
				SetRTCYearinfo(year);
				while(1)
				{
					a=getkey();
					if(a=='C')
						break;
				}
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("YEARS SET");
				delay_ms(500);
				return;
			}
			else
			{
				i=0;
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("INVALID ENTER");
				delay_ms(500);
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("ENTER YEAR");
			}
		}
	}
}
void editday(void)
{
	s8 k;
	u32 day;
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("0:SU 1:M 2:TU3:W");
	cmdLCD(GOTO_LINE2_POS0);
	strLCD("4:TH 5:F 6:SA");
	while(1)
	{
		k=getkey();
		if(k>='0' && k<='9')
		{
			cmdLCD(GOTO_LINE2_POS0+15);
			charLCD(k);
			day=(k-'0');
			SetRTCDay(day);
		}
		else if(getkey()=='C')
		{
			clearLCD();
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("DAY SET");
			delay_ms(50);
			break;
		}
	}
}
void editpass(s8 *pass,s32 size)
{
	 s8 a;
    u32 i;
    clearLCD();
    cmdLCD(GOTO_LINE1_POS0);
    strLCD("ENT NEW PASS C:OK");
    while(1)
    {
        for(i=0; i<5; )
        {
            a = getkey();
            if(a >= '0' && a <= '9')
            {
                pass[i] = a;
                cmdLCD(GOTO_LINE2_POS0 + i);
                charLCD(a);
                i++;
            }
            else if(a == 'C')
            {
                clearLCD();
                cmdLCD(GOTO_LINE1_POS0);
                strLCD("ENTER 5 DIGITS");
								delay_ms(100);
								clearLCD();
								cmdLCD(GOTO_LINE1_POS0);
								strLCD("ENT NEW PASS C:OK");
								memset(pass,0,size);
								i=0;
                continue; 
            }
        }
        pass[5] = '\0';  
        while(1)
        {
            a = getkey();
            if(a == 'C')   
            {
                clearLCD();
                cmdLCD(GOTO_LINE1_POS0);
                strLCD("PASSWORD SET");
                delay_ms(600);
                return;
            }
        }
    }
}
s8 getkey()
{
    s8 k,pressedKey;
    do {
        k = keyscan();
    } while(k == 'n');
     pressedKey = k;
    while(keyscan() != 'n');
    return pressedKey;
}

