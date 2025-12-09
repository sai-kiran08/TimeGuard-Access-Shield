#include "lcd_defines.h"
#include "lcd.h"
#include "rtc.h"
#include "rtc_defines.h"
extern s32 hour,min,sec,date,month,year,day;
s8 Menu[][20]={"1:RTC    2:WRHR","3:PASS    4:EXIT"};
void displaytime(void)
{
		GETRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GETRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
}
void displaymenu(void)
{
	clearLCD();
	cmdLCD(GOTO_LINE1_POS0);
	strLCD(Menu[0]);
	cmdLCD(GOTO_LINE2_POS0);
	strLCD(Menu[1]);
}
