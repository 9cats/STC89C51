/***********************************************
 *	auther:YI
 *	time:2020-1-14-10:30
 *
 *	定时器控制LED
 *  LED接最简单的LED
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int  u16;                                                                                        
typedef unsigned long u32;

void Time0_interrupt_config(void); //配置函数
	
#define LED P2

void main()
{
	LED=0;
	Time0_interrupt_config();
	while(1);
}

/**********************************************
 *  定时器终端的配置函数
************************************************/
void Time0_interrupt_config(void)
{
	TMOD = 0x01;	//启动方式+功能选择+模式选择
	TH0=0x3d;			//(65536-50000)/256;
	TL0=0xb0;			//(65536-50000)%256;
	EA=1;   			//总允许
	ET0=1;  			//启动
	TR0=1;  			//源允许
}
/**********************************************
 *  定时器中断函数
************************************************/
void TCon(void) interrupt 1
{
	static u8 num=0;
	TH0=0x3d;			//(65536-50000)/256;
	TL0=0xb0;			//(65536-50000)%256;
	if(++num==20)
	{
		LED = ~LED;
		num=0;
	}
}
