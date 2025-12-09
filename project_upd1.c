#include<LPC21xx.h>
#include<string.h>
#include "kpm.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "type.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "arduino.h"
#include "arduino_defines.h"
#include "pin_function_defines.h"
#include "pin_connect_block.h"
#include "editsec.h"
#include "displaysec.h"
#include "authenti.h"

#define LED_PIN 23//p0.23
#define EINT1_VIC_CHNO	15
#define EINT1_PIN_0_3 PIN_FUNCTION4

void init_interrupt(void);
void eint1_isr(void)__irq;

s8 storedpass[]="12312";
s32 starthr=7;
s32 endhr=11;

s32 hour,min,sec,date,month,year,day;
s32 eint1_flag=0;

s8 rtcmenu[][5]={"hr","min","sec","date","mon","year","day"};

s32 main()
{
	s8 key,n=10;
	s8 press;
	Init_LCD();
	Init_RTC();
	Init_kpm();
	init_interrupt();
	pinMode(LED_PIN,OUTPUT);
	SetRTCTimeinfo(9,41,0);
	SetRTCDateinfo(25,11,2025);
	SetRTCDay(2);
	do 
	{
		displaytime();
		key=keyscan();
		if(key=='A')
		{
			if(enterpass(storedpass))
			{
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("CORRECT!");
				delay_s(1);
				clearLCD();
				if(checktimeslot(&hour,&starthr,&endhr))
				{
					clearLCD();
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("ACCESS GIVEN!");
					delay_s(1);
					clearLCD();
					while(n)
					{
						digitalWrite(LED_PIN,1);
						delay_ms(800);
						digitalWrite(LED_PIN,0);
						delay_ms(800);
						n--;
					}n=10;
				}
				else
				{
					clearLCD();
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("ACCESS DENIED!");
					delay_s(2);
					clearLCD();
				}
			}
			else
			{
					clearLCD();
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("INCORRECT!");
					delay_s(2);
				clearLCD();
			}
		}
		if(eint1_flag==1)
		{
		while(1)
		{
			displaymenu();
			press=getkey();
			if(press=='4')
			{
				clearLCD();
				delay_ms(50);
				break;
			}
			else if(press=='1')
			{
				editrtc();
			}
			else if(press=='2')
			{
				editwrkhr(&starthr,&endhr);
			}
			else if(press=='3')
			{
				editpass(storedpass,6);
			}
			else
			{
				clearLCD();
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("ENTER VALID KEY");
				delay_s(1);
			}
		}
			eint1_flag=0;
		}
		
	}while(1);
}
void init_interrupt(void)
{
	cfgportpinfunc(0,3,EINT1_PIN_0_3);
	VICIntEnable=1<<EINT1_VIC_CHNO;
	VICVectCntl0=(1<<5) | EINT1_VIC_CHNO;
	VICVectAddr0=(u32)eint1_isr;
	EXTMODE=1<<0;
}
void eint1_isr(void)__irq
{
	eint1_flag=1;
	EXTINT=1<<1;
	
	VICVectAddr=0;
}

