#include "infracsonic.h"

void InitTimer1()
{
	AUXR &= 0xBF;	 //设置为12分频
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TF1 = 0;		//清除TF1标志
	TR1 = 0;
}

//double distance()
//{	
//	double distmp = 0;	
//	uint tmp = 0,overflow = 0;//计算溢出次数
//	TL1 = 0x00;		//设置定时初值
//	TH1 = 0x00;		//设置定时初值
//	TRIG=1;	
//	Delay10us();
//	Delay10us();
//	TRIG=0;
//	while(ECHO==0);
//	TR1=1;		
//	while(ECHO==1)
//	{
//		tmp = TH1;
//		while(TH1 == tmp );
//			if(tmp > TH1)
//		{
//			overflow++;
//		}
//	}	
//	TR1=0;
//	distmp= (overflow+(TH1*256+TL1)/(double)65535) * consume* 340.0 /2 * 100; 
//	//distmp = overflow+(TH1*256+TL1);
//	return distmp;
//}

double distance()	
{

 double distemp=0;
 

   TRIG = 1;
   Delay10us();
	Delay10us();
   TRIG = 0;
   while(ECHO==0);
   TR1 = 1; //开定时器
   
  while(ECHO==1);
    TR1=0;
	

	distemp= ((TH1*256+TL1)*1.08) *  340.0 /2 /10000; 
//	printf("TL0 IS %bd",TL1);
//	printf("TH0 IS %bd",TH1);
	TH1 = 0;
	TL1 = 0;
	return distemp;
}