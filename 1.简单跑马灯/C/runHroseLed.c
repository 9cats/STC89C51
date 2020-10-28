#include "reg51.h"
typedef unsigned char u8;
typedef unsigned int u32;


void delay(u32 ms)
{
	u32 i;
	for(;ms!=0;ms--)
	for(i=0;i<30;i++);
}

void run_hrose(u8 mode)
{
	u8 i;
	switch(mode)
	{
		case 1:
			for(i=1;i!=0;i=i<<1)
			{
				P2 = ~i;
				delay(1000);
			}
			break;
		case 2:
			for(i=0x80;i!=0;i=i>>1)
			{
				P2 = ~i;
				delay(1000);
			}
			break;
		case 3:
			P2 = 0xff;
			for(i=0;i<=7;i++)
			{
				P2 = ~((~P2)+(1<<i));
				delay(1000);
			}
			break;
		case 4:
			P2 = 0xff;
			for(i=0;i<=7;i++)
			{
				P2 = ~((~P2)+(1<<(7-i)));
				delay(1000);
			}
			break;
		case 5:
			for(i=1;i<=5;i++)
			{
				P2 = 0x0;
				delay(1000);
				P2 = 0xff;
				delay(1000);
			}
			break;
	}
}

void main()
{
	int i;
	while(1)
	{
		for(i=1;i<=5;i++)
		run_hrose(i);
	}
}
