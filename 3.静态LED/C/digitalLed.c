#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

void delay(u32 ms)
{
	u8 i;
	while(ms--)
	for(i=0;i<170;i++);
}

int main()
{
	u8 tab[20]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90,0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,0x89 ,0x9 ,0x89 ,0x9};
	u8 i;
	while(1)
	{
		for(i=0;i<19;i++)
		{
			P0=tab[i];
			delay(500);
		}
	}
}