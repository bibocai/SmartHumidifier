#include "infracsonic.h"

void InitTimer1()
{
	AUXR &= 0xBF;	 //����Ϊ12��Ƶ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TF1 = 0;		//���TF1��־
	TR1 = 0;
}

//double distance()
//{	
//	double distmp = 0;	
//	uint tmp = 0,overflow = 0;//�����������
//	TL1 = 0x00;		//���ö�ʱ��ֵ
//	TH1 = 0x00;		//���ö�ʱ��ֵ
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
   TR1 = 1; //����ʱ��
   
  while(ECHO==1);
    TR1=0;
	

	distemp= ((TH1*256+TL1)*1.08) *  340.0 /2 /10000; 
//	printf("TL0 IS %bd",TL1);
//	printf("TH0 IS %bd",TH1);
	TH1 = 0;
	TL1 = 0;
	return distemp;
}