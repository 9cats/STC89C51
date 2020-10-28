/***********************************************
 *	auther:YI
 *	time:2020-1-14-10:30
 *
 *	时钟++中断服务
 *	WX位选接J12
 *	DX段选接J16		
 *  CON（控制）接独立按键
************************************************/
#include <reg52.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;                                                                                        
typedef unsigned long u32;

void delayms(u32 ms);		 		//延时函数
void interrupt_config(void); //配置函数
	
#define WX P2
#define DX P0
sbit CON=P3^3;

u8 tab_num[]  = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40};	//段选
u8 disp_led[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe}; 									//位选
u32 timestamp=0;        //时间戳
u8 dispvlu[8]={0,0,10,0,0,10,0,0};
u8 i;

void main()
{
	EA=1;
	EX1=1;	
	IT1=1;
	while(1)
	{
		dispvlu[7]=timestamp%60%10;
		dispvlu[6]=timestamp%60/10;
		
		dispvlu[4]=timestamp/60%60%10;
		dispvlu[3]=timestamp/60%60/10;
		
		dispvlu[1]=timestamp/60/60%10;
		dispvlu[0]=timestamp/60/60/10;
		
		for(i=0;i<8;i++)
		{
			WX = disp_led[i];
			DX = tab_num[ dispvlu[i] ];
			delayms(1);
			DX = 0x00;
		}
	}
}

void interrupt_config(void)
{
	EA=1;   //总允许
	EX1=1;  //源允许
	IT1=1;  //触发方式
}


void delayms(u32 ms)//延时函数
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
	}
}

void timeSet(void) interrupt 2
{
	u8 i=10,j;
	while(i--)
		for(j=0;j<85;j++);
	timestamp++;
	IE1=0;
}