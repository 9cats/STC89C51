/**********************************************************************
 *	auther:YI
 *	time:2020-1-13-9:23
 *
 *	LED接JP3(静态LED) buttom接JP4(矩阵按钮)
 *	注:矩阵按钮为3*4    要改成4*4只要把扫描函数后面的   -4  去掉
***********************************************************************/

#include <reg51.h>
#include <intrins.h>
#define Buttom P2
#define LED P0
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数
u8 scanButtom(void);		//扫描矩阵按键

u8 disp_vlu[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0x8e};//静态LED显示的值

void main()
{
	LED = disp_vlu[ scanButtom() ];
	delayms(50);
}

void delayms(u32 ms)
{
	u8 i;
	while(ms--)
	{
		for(i=0;i<85;i++);
	}
}

/********************************************
 *	函数作用:扫描按键
 *	形参:无
 *  返回:按键编号(无则为0)
*********************************************/
u8 scanButtom(void)
{
	u8 key=0;
	
	Buttom = 0xf0;
	if(!(Buttom==0xf0))
	{
		switch(Buttom)
		{
			case 0x70:key=0;break;
			case 0xb0:key=4;break;
			case 0xd0:key=8;break;
			case 0xe0:key=12;break;
		}
		Buttom = 0x0f;
		if(!(Buttom==0x0f))
		{
			switch(Buttom)
			{
				case 0x07:return key+1-4;
				case 0x0b:return key+2-4;
				case 0x0d:return key+3-4;
				case 0x0e:return key+4-4;
			}
		}
	}
	return 0;
}
