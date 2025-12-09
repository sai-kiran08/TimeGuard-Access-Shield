#ifndef __RTC_H__
#define __RTC_H__
#include "type.h"

void Init_RTC(void);
void GETRTCTimeInfo(s32 *hour,s32 *min,s32 *sec);
void DisplayRTCTime(u32 hour,u32 min,u32 sec);
void GETRTCDateInfo(s32 *date,s32 *month,s32 *year);
void DisplayRTCDate(u32 date,u32 month,u32 year);
void SetRTCTimeinfo(u32 hour,u32 min,u32 sec);
void SetRTCDateinfo(u32 date,u32 month,u32 year);
void GetRTCDay(s32 *day);
void SetRTCDay(u32 day);
void DisplayRTCDay(u32 dow);
void GETRTCHrInfo(s32 *hour);
void GETRTCMinInfo(s32 *min);
void SetRTCHrinfo(u32 hour);
void SetRTCMininfo(u32 min);
void SetRTCDaTinfo(u32 date);
void SetRTCMonthinfo(u32 month);
void SetRTCYearinfo(u32 year);

#endif
