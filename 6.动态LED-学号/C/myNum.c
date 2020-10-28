#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数

u8 tab_num[]  = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};	//段选
u8 disp_led[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe}; 						//位选

void main()
{
	u8 myNum[]={8,2,0,1,9,2,1,1,1,1,0,6,6,8};//14
	u8 i,j,m;
	u16 n;
	while(1)
	{
		for(j=0;j<=6;j++)
		{
			for(n=0;n<50000;n++)
			{
				for(i=j,m=0;i<i+8;i++,m++)
				{
					P1 = disp_led[m];
					P0 = tab_num[ myNum[i] ];
					delayms(5);
				}
			}
		}
		for(j=0;j<=6;j++)
		{
			for(n=0;n<50000;n++)
			{
				for(i=j,m=0;i<i+8;i++,m++)
				{
					P1 = disp_led[m];
					P0 = tab_num[ myNum[i] ];
					delayms(5);
				}
			}
		}
	}
}

void delayms(u32 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
	}
}