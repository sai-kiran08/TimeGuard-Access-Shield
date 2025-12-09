#ifndef __EDITSEC_H__
#define __EDITSEC_H__
#include "type.h"

void timedit(void);
void datedit(void);
void editday(void);
s8 getkey(void);
void editrtc(void);
void editwrkhr(s32 *starthr,s32 *endhr);
void incsthr(s32 *sthr);
void incendhr(s32 *enhr);
void editpass(s8 *pass,s32 size);
void houredit(void);
void minedit(void);
void editdate(void);
void monthedit(void);
void yearedit(void);

#endif
