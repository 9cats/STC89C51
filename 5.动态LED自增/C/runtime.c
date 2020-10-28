#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
void delayms(u32 ms);		//延时函数

u8 tab_num[]  = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};	//段选
u8 disp_led[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd ,0xfe}; 						//位选
//            0111 1111               1111 0111

void main()
{
	u8 disp_vlue[8],i=0;
	u32 vlue=10;
	while(1)
	{
		if(++i>=5)
		{
			i=0;
			vlue++;
		}
		
		disp_vlue[0]=vlue%10000/1000;
		disp_vlue[1]=vlue%1000/100;
		disp_vlue[2]=vlue%100/10;
		disp_vlue[3]=vlue%10;
		
		disp_vlue[4]=vlue%10000/1000;
		disp_vlue[5]=vlue%1000/100;
		disp_vlue[6]=vlue%100/10;
		disp_vlue[7]=vlue%10;
		
		for(i=0;i<8;i++)
		{
			P3 = disp_led[i];
			P0 = tab_num[ disp_vlue[i] ];
			delayms(3);
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