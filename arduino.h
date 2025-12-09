#ifndef __ARDUINO_H__
#define __ARDUINO_H__
#include "type.h"
void pinMode(u32 pinNo,u32 pinDir);
void digitalWrite(u32 pinNo,u32 bit);
u32 digitalRead(u32 pinNo);
void portMode(u32 pinStartPos,u32 npins,u32 pinDir);
void write2pins(u32 pinStartPos,u32 npins,u32 data);
u32 readpins(u32 pinStartPos,u32 npins);
#endif
