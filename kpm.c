#include "type.h"
#include "kpm_defines.h"
#include "kpm.h"
#include <LPC21xx.h>
s8 kpmLUT[4][4]={{'1','2','3','A'},
									{'4','5','6','B'},
									{'7','8','9','C'},
									{'*','0','#','D'}};
void Init_kpm(void)
{
	IODIR1 |= (15 << ROW0);
	IODIR1 &= ~(0x0F << COL0);
	
}
u32 colscan(void)
{
	u32 status;
	status= (((IOPIN1 >> COL0) & 15) < 15)?0:1;
	return status;
	//return (((IOPIN1 >> COL0) & 0x0F) == 0x0F);
}
u32 rowcheck(void)
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		IOPIN1 = (IOPIN1 &~(15<<ROW0)) | (~(1<<r)<<ROW0);
		//IOSET1 =(0X0F<<ROW0);
		//IOCLR1 =(1<<(ROW0+r));
			if(colscan()==0)
			{
				break;
			}
	}
	IOCLR1 = 15<<ROW0;
	return r;
}
u32 colcheck(void)
{
	u32 c;
	for(c=0;c<=3;c++)
	{
		if(((IOPIN1>>(COL0+c))&1)==0)
		{
			break;
		}
	}
	return c;
}
u32 keyscan(void)
{
	u32 r,c;
	u32 key;
//	Init_kpm();
	
//while(colscan());
	if(colscan())
		return 'n';
	
	r=rowcheck();
	
	c=colcheck();
	
	key=kpmLUT[r][c];
	
	return key;
	
}
