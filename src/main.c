#include "config.h"
#include "delay.h"
#include "uart.h"
#include "dht11.h"
#include "nokia5110.h"
#include "infracsonic.h"
#include "stdio.h"


#define NORMAL 1
#define ADJUST_MIN 2
#define ADJUST_MAX 3


uchar status = 1;
uchar hum,tem;
uchar count;
uchar min_value = 44,max_value = 48;
double dist = 0;
uchar temp;
bit hum_on = False;
bit need_hum = False;


void main()
{
	T_H tem_hum;
	
	P1M0 |= 0x04;
	P1M1 &=~ 0x04;	//LED推挽输出
	
	P0M0 |= 0x80;
	P0M1 &=~ 0x80;	//雾化器控制口推挽输出
	
	IT0 = 1;	//下降沿
	EX0 = 1;	//外部中断
	
	InitUart1();
	Init5110();
	InitTimer1();

	lcdWriteChineseStr(Shandongdaxue,10,0,4);
	lcdWriteChineseStr(Hongjingbei,20,2,3);
		
	delay_ms(2000);	//上电延时
	
	lcdClear();
	
	printf("Init Complete!\r\n");
	
				
	while(1)
	{
		HUMIDIFIER = 1;
		if(hum_on != need_hum)
		{
			HUMIDIFIER = 0;
			delay_ms(100);
			HUMIDIFIER = 1;
			hum_on = ~hum_on;
			printf("Hum Switch!\r\n\r\n");
		}
		
		lcdPutStr("Status:",0,0);
		lcdShowDouble(0,7,(double)status,0);
		
		lcdPutStr("Min:",0,3);
		lcdShowDouble(3,4,(double)min_value,0);
		lcdPutStr("Max:",7,3);
		lcdShowDouble(3,11,(double)max_value,0);
		
		
		switch(status)
		{
			case NORMAL:{
				LED = 1;
				delay_ms(600);
				LED = 0;
				delay_ms(600);
				
				tem_hum = Rec_DHT();
				tem = tem_hum.Tem_Z;
				hum = tem_hum.Hum_Z;
				dist = distance();
				
				if(hum < min_value)
					need_hum = True;
				if(hum > max_value)
					need_hum = False;
								
				lcdClearAny(5,0,13);
				if(hum_on == True)
					lcdPutStr("Hum On",0,5);
				else if(hum_on == False)
					lcdPutStr("Hum Off",0,5);
				
				printf("need_hum:%u\r\nhum_on:%u\r\n\r\n",(uint)need_hum,(uint)hum_on);
				
				lcdShowDouble(1,0,(double)tem,0);
				lcdPutStr("'C",2,1);
				lcdShowDouble(1,7,(double)hum,0);
				lcdPutStr("%",9,1);
				lcdShowDouble(4,0,dist,3);
				printf("Status:%u\r\nTemperature:%u\r\nHumidity:%u\r\n%u<Hum<%u\r\n\r\n",(uint)status,(uint)tem_hum.Tem_Z,(uint)tem_hum.Hum_Z,(uint)min_value,(uint)max_value);
				
				
				break;
			}
			case ADJUST_MIN:{
				KEY_INC = 0;
				KEY_DEC = 0;
				if(KEY_INC == 1)
				{
					delay_ms(20);
					if(KEY_INC == 0)
					{
						printf("inc\r\n");
						if(++min_value >= max_value)
							min_value = max_value;
					}
				}
				if(KEY_DEC == 1)
				{
					delay_ms(20);
					if(KEY_DEC == 0)
					{
						printf("dec\r\n");
						if(--min_value <= 10)
							min_value = 10;
					}
				}
					
				break;
			}
			case ADJUST_MAX:{
				KEY_INC = 0;
				KEY_DEC = 0;
				if(KEY_INC == 1)
				{
					delay_ms(20);
					if(KEY_INC == 0)
					{
						printf("inc\r\n");
						if(++max_value >= 80)
							max_value = 80;
					}
				}
				if(KEY_DEC == 1)
				{
					delay_ms(20);
					if(KEY_DEC == 0)
					{
						printf("dec\r\n");
						if(--max_value <= min_value)
							max_value = min_value;
					}
				}
				
				break;
			}
			
		}
	}
}

//使用printf要打开串口中断清除TI位
void Uart1() interrupt 4 using 1
{
	uchar a;
    if (RI)
    {
        RI = 0;                 //清除RI位
        a = SBUF;              //P0显示串口数据
		SBUF=a;
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy1 = 0;               //清忙标志
    }
}

void exint0() interrupt 0
{
	delay_ms(20);
	if(!KEY_ADJUST)
	{
		status++;
		if(status == 4)
			status = 1;
	}
}