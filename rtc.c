#include<LPC21XX.h>
#include "type.h"
#include "rtc_defines.h"
#include "lcd.h"
#include "lcd_defines.h"

s8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

void Init_RTC(void)
{
	PREINT=PREINT_VAL;
	PREFRAC=PREFRAC_VAL;
	CCR=RTC_RESET;
	CCR=RTC_ENABLE | RTC_CLKSRC;
}
void GETRTCTimeInfo(s32 *hour,s32 *min,s32 *sec)
{
	*hour=HOUR;
	*min=MIN;
	*sec=SEC;
}
void DisplayRTCTime(u32 hour,u32 min,u32 sec)
{
	cmdLCD(GOTO_LINE1_POS0);
	charLCD((hour/10)+48);
	charLCD((hour%10)+48);
	charLCD(':');
	charLCD((min/10)+48);
	charLCD((min%10)+48);
	charLCD(':');
	charLCD((sec/10)+48);
	charLCD((sec%10)+48);
}
void GETRTCDateInfo(s32 *date,s32 *month,s32 *year)
{
	*date=DOM;
	*month=MONTH;
	*year=YEAR;
}
void DisplayRTCDate(u32 date,u32 month,u32 year)
{
	cmdLCD(GOTO_LINE2_POS0);
	charLCD((date/10)+48);
	charLCD((date%10)+48);
	charLCD('/');
	charLCD((month/10)+48);
	charLCD((month%10)+48);
	charLCD('/');
	u32LCD(year);
}
void SetRTCTimeinfo(u32 hour,u32 min,u32 sec)
{
	HOUR=hour;
	MIN=min;
	SEC=sec;
}
void SetRTCDateinfo(u32 date,u32 month,u32 year)
{
	DOM=date;
	MONTH=month;
	YEAR=year;
}
void GetRTCDay(s32 *day)
{
	*day=DOW;
}
void SetRTCDay(u32 day)
{
	DOW=day;
}
void DisplayRTCDay(u32 dow)
{
	cmdLCD(GOTO_LINE1_POS0+10);
	strLCD(week[dow]);
}
void GETRTCHrInfo(s32 *hour)
{
	*hour=HOUR;
}
void GETRTCMinInfo(s32 *min)
{
	*min=MIN;
}
void SetRTCHrinfo(u32 hour)
{
	HOUR=hour;
}
void SetRTCMininfo(u32 min)
{
	MIN=min;
}
void SetRTCDaTinfo(u32 date)
{
	DOM=date;
}void SetRTCMonthinfo(u32 month)
{
	
	MONTH=month;
}
void SetRTCYearinfo(u32 year)
{
	YEAR=year;
}
