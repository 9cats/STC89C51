#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
void delay(u32 ms);
void LED1();
void LED2();

int main()
{
	while(1)
	{
		LED1();
		LED2();
	}
}

void delay(u32 ms)
{
	u8 i;
	while(ms--)
	for(i=0;i<170;i++);
}

void LED1()
{
	static u8 i=0;
	u8 tab[20]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90,0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,0x89 ,0x9 ,0x89 ,0x9};
	i = i%20;
	P0=tab[i++];
	delay(200);
}

void LED2()
{
	static u32 i=0;
	i = i%8;
	if(i%8==0)
	{
		P2=0xfe;
	}
	P2=_crol_(P2,1);
	i++;
	delay(200);
}
/*
void LED2(u8 mode)
{
	u8 i;
	switch(mode)
	{
		case 1:
			for(i=1,P2=0xfe;i<=8;i++)
			{
				timing(1000);
				P2=_crol_(P2,1);
			}
			break;
		case 2:
			for(i=1,P2=0x7f;i<=8;i++)
			{
				timing(1000);
				P2=_cror_(P2,1);
			}
			break;
		case 3:
			for(i=1,P2=0xff;i<=8;i++)
			{
				P2-=1<<(i-1);
				timing(1000);
			}
			break;
		case 4:
			for(i=8,P2=0xff;i>0;i--)
			{
				P2-=1<<(i-1);
				timing(1000);
			}			
			break;
		case 5:
			for(i=0;i<5;i++)
			{
				P2=0xaa;
				timing(1000);
				P2=0x55;
				timing(1000);
			}
			break;
	}
}
*/