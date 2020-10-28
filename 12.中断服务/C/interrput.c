/***********************************************
 *	auther:YI
 *	time:2020-1-14-10:30
 *
 *	点亮一排LED（最简单）
 *	Col接矩阵列(JP12)
 *	
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;                                                                                        
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数

#define LED P0

void main()
{
	EA  = 1;
	EX0 = 1;
	IT0 = 1;
	LED=0x00;
	while(1)
	{
		delayms(50);
	}
}


void function1() interrupt 0
{
	LED = 0xff;
}


void delayms(u32 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
	}
}
	