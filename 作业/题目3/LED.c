/***********************************************
 *	auther:YI
 *	time:2020-1-15-15:20
 *
 *	作业三
 *  LED接LED
 *  Buttom接独立按键
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int  u16;                                                                                        
typedef unsigned long u32;

void interrupt_config(void); //配置函数
void delayms(u8 ms);				 //延时函数
#define LED P0

u8 run_state=1;
u8 LIG=0;

/****************************
 *				主函数
*****************************/
void main()
{
	interrupt_config();//配置
	while(1)
	{
		LED = 0x00;
		delayms(LIG);
		LED = 0xff;
		delayms(100-LIG);
	}
}

/****************************
 *		  	延时函数
*****************************/
void delayms(u8 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<1;i++);
	}
}

/****************************
 *	 中断服务配置函数
*****************************/
void interrupt_config(void)
{		
//定时器配置
	TMOD = 0x01;	//启动方式+功能选择+模式选择
	TH0=0xd8;			//计数器高4位
	TL0=0xf0;			//计数器低4位
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
	static u8 flag=0;
	if(run_state)
	{
		if(flag==0)
		{
			if(++LIG==100)
			{
				flag=1;
			}
		}
		else
		{
			if(--LIG==0)
			{
				flag=0;
			}
		}
	}
	
	TH0=0xd8;	//复位
	TL0=0xf0;	//复位
}

void I0Con(void) interrupt 0//外部中断触发函数
{
	u8 i,j;
	if(run_state)
	{
		run_state=0;
	}
	else
	{
		run_state=1;
	}
	
	for(i=0;i<255;i++)	//消抖！
	{
		LED=0x00;
		for(j=0;j<=LIG;j++);
		LED=0xff;
		for(j=0;j<=100-LIG;j++);
	}
	IE0=0;				//中断标记置零！
}