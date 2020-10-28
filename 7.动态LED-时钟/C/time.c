/***********************************************
 *	auther:YI
 *	time:2010-1-12-21:37
 *
 *	P0接J12 P3接JP16
 *	P2接JP5
 *  (防抖？)
************************************************/

#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数

u8 tab_num[]  = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40};	//段选
u8 disp_led[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe}; 									//位选
sbit ADD = P2^0;//按钮

void main()
{
	u8 i,j,flag=0;
	u8 timeNum[8]={0,0,10,0,0,10,0,0};
	
	while(1)
	{
		if(++j>70)
		{
			j=0;
			timeNum[0]++;
			if(timeNum[0]==10)
			{
				timeNum[0]=0;
				timeNum[1]++;
				if(timeNum[1]==6)
				{
					timeNum[1]=0;
					timeNum[3]++;
					if(timeNum[3]==10)
					{
						timeNum[3]=0;
						timeNum[4]++;
						if(timeNum[4]==6)
						{
							timeNum[4]=0;
							timeNum[6]++;
							if(timeNum[7]==2 && timeNum[6]==4)
							{
								timeNum[7]=0;
								timeNum[6]=0;
							}
							if(timeNum[6]==10)
							{
								timeNum[6]=0;
								timeNum[7]++;
							}
						}
					}
				}
			}
		}
		
		if(flag == 0)//按一次增加一次
		{
			if(ADD == 0)
			{
				flag = 1;
				j = 200;
				continue;
			}
		}
		if(flag == 1)
		{
			if(ADD == 1)
			{
				flag = 0;
			}
		}
		
		for(i=0;i<8;i++)
		{
			P3 = disp_led[i];
			P0 = tab_num[ timeNum[7-i] ];
			delayms(2);
			P0 = 0x00;
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