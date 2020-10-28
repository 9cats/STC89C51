/***********************************************
 *	auther:YI
 *	time:2020-1-14-10:30
 *
 *	渐变呼吸灯
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;                                                                                        
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数
void delay(u32 ms);

#define LED P0
u8 dis_led[8]={0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe};

void main()
{
	u8 i,j,m;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			for(m=0;m<5;m++)
			{
				for(j=0;j<8;j++)
				{
					LED = 0x00;
					delayms(10-i);
					LED = 0xff;
					delayms(i);
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
		for(i=0;i<1;i++);
	}
}
