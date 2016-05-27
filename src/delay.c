#include "delay.h"

void delay_us(uint t)		//@11.0592MHz
{
	while(t--)
	{
		_nop_();
		_nop_();
		_nop_();
	}
}

void delay_ms(uint t)		//@11.0592MHz
{
	unsigned char i, j;
	while(t--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}

void delay_10ms(uint t)		//@11.0592MHz
{
	unsigned char i, j;
	while(t--)
	{
		i = 108;
		j = 145;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

