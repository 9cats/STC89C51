/***********************************************
 *	auther:YI
 *	time:2020-1-16-9:55
 *
 *  题目一
 *  WX接位选
 *  DX接段选
 *  Buttom接独立按键
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int  u16;                                                                                        
typedef unsigned long u32;

void interrupt_config(void); //配置函数
void delayms(u32 ms); 				 //延时函数
void delayms1(u32 ms);				 //延时函数
void delayms2(u32 ms);				 //延时函数

#define WX P0
#define DX P2

u8 tab_num[]  = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40};	//段选
u8 led_num[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe}; 									  //位选
u32 timestamp=0;        //时间戳
u8 led_vlu[8]={0,0,10,0,0,10,0,0};
u8 run_state=1;	//标记运行的状态  1表示运行 2表示停止
u8 add_state=0; //标记时间戳增加状态

/****************************
 *				主函数
*****************************/
void main()
{
	u8 i;//循环变量
	interrupt_config();//配置
	while(1)
	{
		if(add_state)
		{
			timestamp++;
			add_state=0;
		}
		led_vlu[7]=timestamp%10;
		led_vlu[6]=timestamp%60/10;
		
		led_vlu[4]=timestamp/60%10;
		led_vlu[3]=timestamp/60%60/10;
		
		led_vlu[1]=timestamp/60/60%10;
		led_vlu[0]=timestamp/60/60/10;
		
		if(led_vlu[0] == 2)
		{
			if(led_vlu[0] == 4)
			{
				led_vlu[0]=0;
				led_vlu[1]=0;
			}
		}
		
		for(i=0;i<8;i++)
		{
			WX = led_num[i];
			DX = tab_num[ led_vlu[i] ];
			delayms(1);
			DX = 0x00;
		}
	}
}

/****************************
 *		  	延时函数
*****************************/
void delayms1(u32 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
	}
}

void delayms2(u32 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
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
/****************************
 *	 中断服务配置函数
*****************************/
void interrupt_config(void)
{		
//定时器配置
	TMOD = 0x01;	//启动方式+功能选择+模式选择
	TH0=0x3c;			//定时器高8位
	TL0=0xb0;			//定时器第八位
	TR0=1;  			//源允许	
	ET0=1;  			//启动
	
//外部中断Regin配置
	IT0=1;				//触发方式
	EX0=1;				//源允许
	
//外部中断Pluse配置
	IT1=1;				//触发方式
	EX1=1;				//源允许
	
//开！
	EA=1;   			//总允许
}

/****************************
 *		 中断服务函数
*****************************/
void T0Con(void) interrupt 1//定时器触发函数
{
	static num=0;
	TH0=0x3c;	//复位 (65536-50000)/256
	TL0=0xb0;	//复位 (65536-50000)%256
	if(run_state)
	{
		if(++num >= 20)
		{
			num=0;
			add_state=1;
		}
	}
}

void Regian(void) interrupt 0//外部中断触发函数---归零
{
	DX=0x00;
	timestamp = 0;

	delayms1(500);	//消抖！！
	IE0=0;				//中断标记置零！
}

void Pluse(void) interrupt 2//外部中断触发函数---暂停
{
	DX=0x00;
	if(run_state==1)
	{
		run_state=0;
	}
	else
	{
		run_state=1;
	}
	
	delayms2(500);	//消抖！！
	IE1=0;					//中断标记置零！
}
