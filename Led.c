/*
 * Led.c
 *
 *  Created on: 2020-10-9
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "includes.h"
#include "PinConfig.h"
#include "Work.h"
#include "Led.h"
#include "SoftSpi.h"

extern unsigned char LED_Stop_PWM_Flag;
extern unsigned int Stop_High_Addr,Stop_Low_Addr;
extern unsigned int RT_High_Addr,RT_Low_Addr;

void LED_Stop_AllOpen(void)
{
	Stop_High_Addr=0xFFFF;
	Stop_Low_Addr=0;
}
void LED_Stop_PWMOpen(void)
{
	Stop_High_Addr=0xFFFF;
	Stop_Low_Addr=0xFFFF;
}
void LED_Stop_AllClose(void)
{
	Stop_High_Addr=0;
	Stop_Low_Addr=0xFFFF;
}
void Led_RT_AllOpen(void)
{
	RT_High_Addr = 0x7;
	RT_Low_Addr = 0x7;
}
void Led_RT_WaterOpen(void)
{
	delay_ms(220);
	RT_Low_Addr = 0x7;
	RT_High_Addr = 0x1;
	delay_ms(RT_Interval);
	RT_High_Addr = 0x3;
	delay_ms(RT_Interval);
	RT_High_Addr = 0x7;
	delay_ms(RT_Interval);
}
void Led_RT_AllClose(void)
{
	RT_High_Addr = 0;
	RT_Low_Addr = 0x7;
}
void Led_Tail_AllOpen(void)
{
	uchar i;
	for(i=OUT1;i<=OUT8;i++)
	{
		SPI_Write_2Byte(1,i,0xFF);
	}
	SPI_Write_2Byte(1,0x37,0x00);//update
	for(i=OUT1;i<=OUT15;i++)
	{
		SPI_Write_2Byte(2,i,0xFF);
	}
	SPI_Write_2Byte(2,OUT16,0x57);
	SPI_Write_2Byte(2,0x37,0x00);//update
}
void Led_Tail_AllClose(void)
{
	uchar i;
	for(i=OUT1;i<=OUT8;i++)
	{
		SPI_Write_2Byte(1,i,0x00);
	}
	SPI_Write_2Byte(1,0x37,0x00);//update
	for(i=OUT1;i<=OUT16;i++)
	{
		SPI_Write_2Byte(2,i,0x00);
	}
	SPI_Write_2Byte(2,0x37,0x00);//update
}
void Tail12_Breath_Open(void)
{
	uint8 i;
	for(i=0;i<52;i++)
	{
		SPI_Write_2Byte(1,0x1F,i*5);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(20);
	}
}
void Tail12_Breath_Close(void)
{
	uint8 i;
	for(i=0;i<52;i++)
	{
		SPI_Write_2Byte(1,0x1F,0xFF-i*5);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(20);
	}
}
void Tail12_Breath_CloseTo10(void)
{
	uint8 i;
	for(i=0;i<49;i++)
	{
		SPI_Write_2Byte(1,0x1F,0xFF-i*5);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
	}
}
void Tail_LowWater_Open(void)
{
	uint8 i;
	for(i=OUT1;i<=OUT8;i++)
	{
		SPI_Write_2Byte(U1,i,0x55);//update
		SPI_Write_2Byte(U1,0x37,0x00);//update
		delay_ms(50);
	}
}
void Tail_HighWater_Open(void)
{
	uint8_t i = 0;
	SPI_Write_2Byte(1,OUT1,0xFF);//update
	SPI_Write_2Byte(1,0x37,0x00);//update
	SPI_Write_2Byte(2,OUT16,0x55);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
	Stop_Low_Addr = 0xFFF;
	Stop_High_Addr = 0;
	Stop_High_Addr += 1<<0;
	delay_ms(50);
	Stop_High_Addr += 1<<1;
	delay_ms(50);
	Stop_High_Addr += 1<<2;
	delay_ms(50);
	Stop_High_Addr += 1<<3;
	delay_ms(50);
	Stop_High_Addr += 1<<4;
	for(i = 0;i<8;i++)
	{
		SPI_Write_2Byte(1,OUT1+i,0x55);//update
		SPI_Write_2Byte(1,OUT2+i,0xFF);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(50);
	}
	SPI_Write_2Byte(2,OUT1,0x55);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
	for(i = 0;i<14;i++)
	{
		SPI_Write_2Byte(2,OUT1+i,0);//update
		SPI_Write_2Byte(2,OUT2+i,0x55);//update
		SPI_Write_2Byte(2,0x37,0x00);//update
		delay_ms(50);
	}
	SPI_Write_2Byte(2,OUT15,0);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
}
void Tail_LowWater_Blinky(void)
{
	uint8 i;
	for(i=0x20;i<=0x25;i++)
	{
		SPI_Write_2Byte(1,i-1,0xFF);//update
		SPI_Write_2Byte(1,i,0x10);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
	for(i=0x26;i<=0x30;i++)
	{
		Stop_Low_Addr += 1<<(i-0x26);
		SPI_Write_2Byte(1,i-1,0xFF);//update
		SPI_Write_2Byte(1,i,0x10);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
	Stop_Low_Addr = 0xFFF;
	delay_ms(40);
}
void Stop_HighBackWater_Open(void)
{
	Stop_High_Addr = 0xFFF;
	Stop_Low_Addr = 0xFFF;
	Stop_Low_Addr = 0x7;
	delay_ms(50);
	Stop_Low_Addr = 0xB;
	delay_ms(50);
	Stop_Low_Addr = 0xD;
	delay_ms(50);
	Stop_Low_Addr = 0xE;
	delay_ms(50);
	Stop_Low_Addr = 0xF;
	SPI_Write_2Byte(2,OUT16,0xFF);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
	SPI_Write_2Byte(2,OUT16,0x55);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
}
void Tail1_FullBackWater_Open(void)
{
	uint8_t i = 0;
	SPI_Write_2Byte(1,OUT1,0xFF);//update
	SPI_Write_2Byte(1,0x37,0x00);//update
	SPI_Write_2Byte(2,OUT16,0xFF);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
	Stop_High_Addr = 0xFFF;
	Stop_Low_Addr = 0xFFF;
	Stop_Low_Addr -= 1<<0;
	delay_ms(50);
	Stop_Low_Addr -= 1<<1;
	delay_ms(50);
	Stop_Low_Addr -= 1<<2;
	delay_ms(50);
	Stop_Low_Addr -= 1<<3;
	delay_ms(50);
	Stop_Low_Addr -= 1<<4;
	for(i = 0;i<8;i++)
	{
		SPI_Write_2Byte(1,OUT1+i,0xFF);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(50);
	}
	for(i = 0;i<15;i++)
	{
		SPI_Write_2Byte(2,OUT1+i,0xFF);//update
		SPI_Write_2Byte(2,0x37,0x00);//update
		delay_ms(50);
	}
}
void Tail2_Stop_FullWater_Open(void)
{
	SPI_Write_2Byte(2,OUT16,0x55);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
	SPI_Write_2Byte(2,OUT16,0);//update
	SPI_Write_2Byte(2,0x37,0x00);//update
	delay_ms(50);
}
void Tail1_2_Stop_BackWater_Close(void)
{
	uint8 i;
	Stop_High_Addr = 0;
	Stop_Low_Addr = 0xFFF;
	for(i=0x30;i>=0x26;i--)
	{
		Stop_High_Addr += 1<<(i-0x26);
		SPI_Write_2Byte(1,i,0x10);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
	Stop_High_Addr += 1<<(11);
	delay_ms(40);
	for(i=0x25;i>=0x20;i--)
	{
		SPI_Write_2Byte(1,i,0x10);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
}
void Tail1_2_Stop_FullWater_Close(void)
{
	uint8 i,j;
	Stop_High_Addr = 0xFFF;
	Stop_Low_Addr = 0xFFF;
	for(i=0x30;i>=0x26;i--)
	{
		Stop_Low_Addr -= (1<<(i-0x1F));
		SPI_Write_2Byte(1,i,0x10);//update
		SPI_Write_2Byte(1,i-1,0xFF);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
	Stop_Low_Addr = 0;
	delay_ms(40);
	Stop_High_Addr = 0;
	Stop_Low_Addr = 0;
	for(i=0x2B;i>=0x20;i--)
	{
		if(i<=0x25)
		{
			Stop_Low_Addr = 1<<(13-(i-0x1F));
			Stop_High_Addr = ~(Stop_Low_Addr);
			SPI_Write_2Byte(1,i,0x10);//update
			SPI_Write_2Byte(1,i-1,0xFF);//update
			SPI_Write_2Byte(1,0x37,0x00);//update
			delay_ms(40);
		}
		else
		{
			Stop_Low_Addr = 1<<(13-(i-0x1F));
			Stop_High_Addr = ~(Stop_Low_Addr);
		}
	}
	Tail12_Breath_CloseTo10();//熄灭
	for(j=1;j<6;j++)//除1全亮
	{
		for(i=0x25;i>=0x20;i--)//除1全亮
		{
			SPI_Write_2Byte(1,i,j*51);//update
			SPI_Write_2Byte(1,0x37,0x00);//update
		}
		delay_ms(40);
	}
	for(i=0;i<3;i++)//T2点亮 一半
	{
		SPI_Write_2Byte(1,0x26+i,0xFF );//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
	for(i=0;i<2;i++)//整根左移,T1到底
	{
		SPI_Write_2Byte(1,0x23-i,0x10);//update
		SPI_Write_2Byte(1,0x22-i,0xFF);//update
		SPI_Write_2Byte(1,0x23+i,0x10);//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		SPI_Write_2Byte(1,0x24+i,0xFF );//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
	}
	for(i=0;i<3;i++)//左移到底后缩进到T2的一半
	{
		SPI_Write_2Byte(2,0x1F+i,0x10 );//update
		SPI_Write_2Byte(2,0x37,0x00);//update
		delay_ms(40);
	}
	for(i=0;i<6;i++)//继续缩进，右边一半开始往回缩进
	{
		SPI_Write_2Byte(2,0x24+i,0 );//update
		SPI_Write_2Byte(2,0x24-i,0 );//update
		SPI_Write_2Byte(2,0x37,0x00);//update
		delay_ms(40);
	}
	delay_ms(160);
	Stop_High_Addr = 0;
	Stop_Low_Addr = 0;
	for(i=0;i<7;i++)//T2开始收拢，T1熄灭,制动流水
	{
		SPI_Write_2Byte(1,0x28-i,0xFF );//update
		SPI_Write_2Byte(1,0x27-i,0xFF );//update
		SPI_Write_2Byte(1,0x26-i,0x10 );//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
		SPI_Write_2Byte(1,0x28-i,0 );//update
		SPI_Write_2Byte(1,0x27-i,0 );//update
		SPI_Write_2Byte(1,0x26-i,0 );//update

		SPI_Write_2Byte(1,0x29-i,0 );//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		Stop_Low_Addr = 1<<(12-i);
		Stop_High_Addr = ~Stop_Low_Addr;
	}
	for(i=0;i<7;i++)//T1开始收拢,制动流水
	{
		SPI_Write_2Byte(1,0x29-i,0xFF );//update
		SPI_Write_2Byte(1,0x28-i,0x10 );//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		delay_ms(40);
		SPI_Write_2Byte(1,0x29-i,0 );//update
		SPI_Write_2Byte(1,0x28-i,0 );//update
		SPI_Write_2Byte(1,0x37,0x00);//update
		if(i<3)
		{
			Stop_Low_Addr = 1<<(2-i);
			Stop_High_Addr = ~Stop_Low_Addr;
		}
		else
		{
			Stop_Low_Addr = 0;
			Stop_High_Addr = ~Stop_Low_Addr;
		}
	}

}
