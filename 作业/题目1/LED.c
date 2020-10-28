/***********************************************
 *	auther:YI
 *	time:2020-1-15-14:45
 *
 *	作业一
 *  LED接LED
 *  Buttom接独立按键
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int  u16;                                                                                        
typedef unsigned long u32;

void interrupt_config(void); //配置函数
void delayms(u32 ms);				 //延时函数

#define LED P2
#define Buttom P3^2;

u8 frequency=1;	//LED闪烁的频率

/****************************
 *				主函数
*****************************/
void main()
{
	LED=0;
	interrupt_config();
	while(1);
}

/****************************
 *		  	延时函数
*****************************/
void delayms(u32 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
	}
}

/****************************
 *	 中断服务配置函数
*****************************/
void interrupt_config(void)
{		
//定时器配置
	TMOD = 0x01;	//启动方式+功能选择+模式选择
	TH0=0x3d;			//计数器高4位
	TL0=0xb0;			//计数器低4位
	TR0=1;  			//源允许	
	ET0=1;  			//启动
	
//外部中断Buttom配置
	IT0=1;				//触发方式
	EX0=1;				//源允许
	
//开！
	EA=1;   			//总允许
}

/****************************
 *		 中断服务函数
*****************************/
void T0Con(void) interrupt 1//定时器触发函数
{
	static num=0;
	TH0=0x3c;	//复位
	TL0=0xb0;	//复位
	if(++num>frequency)
	{
		LED = ~LED;
		num=0;
	}
}

void B0Con(void) interrupt 0//外部中断触发函数
{
	frequency++;
	if(frequency>10)
	{
		frequency=1;
	}
	
	delayms(100);	//消抖！！
	IE0=0;				//中断标记置零！
}
