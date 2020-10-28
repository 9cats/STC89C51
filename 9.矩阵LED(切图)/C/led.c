/***********************************************
 *	auther:YI
 *	time:2020-1-13-14:08
 *
 *	Ran接矩阵行(JP19(绿)/20(红))
 *	Col接矩阵列(JP12)
 *	只需要修改页内容  和  速度
************************************************/

#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;                                                                                        
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数

#define Row P0
#define Col P2

u8 code Col_vlu[8]={0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe};
u8 code Row_vlu[][8]={
{0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00},
{0x00,0x00,0x7E,0x12,0x12,0x0C,0x00,0x00},
{0x00,0x7E,0x20,0x10,0x08,0x04,0x7E,0x00},
{0x00,0x00,0x7F,0x49,0x49,0x36,0x00,0x00},/*"修改此处",0*/
};

void main()
{
	u8 i,j,m;
	while(1)
	{
		for(j=0;j<sizeof(Row_vlu)/8;j++)
		{
			for(m=0;m<50;m++)//速率  [可修改]
			{
				for(i=0;i<8;i++)
				{
					Col = Col_vlu[i];
					Row = Row_vlu[j][i];
					delayms(1);
					Row = 0x00;
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