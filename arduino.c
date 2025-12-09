#include<LPC21xx.h>
#include "type.h"
#include "arduino_defines.h"

void pinMode(u32 pinNo,u32 pinDir)
{
        if(pinNo<32)
        {
                if(pinDir==OUTPUT)
                {
                        IODIR0|=1<<pinNo;
                }
                else
                {
                        IODIR0&=~(1<<pinNo);
                }
        }
        else if(pinNo>=32 && pinNo<=47)
        {
                if(pinDir==OUTPUT)
                {
                         IODIR1|=1<<pinNo-16;
                }
                else
                {
                        IODIR1&=~(1<<pinNo-16);
                }
        }
}
void digitalWrite(u32 pinNo,u32 bit)
{
        if(pinNo<32)
        {
                bit?(IOSET0=1<<pinNo):(IOCLR0=1<<pinNo);
        }
        else if(pinNo>=32 && pinNo<=47)
        {
                bit?(IOSET1=1<<(pinNo-16)):(IOCLR1=(1<<pinNo-16));
        }
}
u32 digitalRead(u32 pinNo)
{
        u32 bit;
        if(pinNo<32)
        {
                bit=((IOPIN0>>pinNo)&1);
        }
        else if(pinNo>=32 && pinNo<=47)
        {
                bit=((IOPIN1>>pinNo-16)&1);
        }
        return bit;
}
void portMode(u32 pinStartPos,u32 npins,u32 pinDir)
{
        if(pinStartPos<32)
        {
                if(pinDir==OUTPUT)
                {
                        IODIR0|=((1<<npins)-1)<<pinStartPos;
                }
                else
                {
                        IODIR0&=~(((1<<npins)-1)<<pinStartPos);
                }
        }
        else if(pinStartPos>=32 && pinStartPos<=47)
        {
                if(pinDir==OUTPUT)
                {
                        IODIR1|=((1<<npins)-1)<<pinStartPos-16;
                }
                else
                {
                        IODIR1&=~(((1<<npins)-1)<<pinStartPos-16);
                }
        }
}
 void write2pins(u32 pinStartPos,u32 npins,u32 data)
{
        if(pinStartPos<32)
        {
                IOCLR0=((1<<npins)-1)<<pinStartPos;
                IOSET0=data<<pinStartPos;
        }
        else if(pinStartPos>=32 && pinStartPos<=47)
        {
                IOCLR1=((1<<npins)-1)<<(pinStartPos-16);
                IOSET1=data<<(pinStartPos-16);
        }
}
u32 readpins(u32 pinStartPos,u32 npins)
{
        u32 data;
        if(pinStartPos < 32)
        {
                data=((IOPIN0 >> pinStartPos) & ((1 << npins)-1));
        }
        else if(pinStartPos >= 32 && pinStartPos <= 47)
        {
                data=((IOPIN1 >> pinStartPos) & ((1 << npins)-1));
        }
        return data;
}
