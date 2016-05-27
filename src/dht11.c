#include "dht11.h"


void DHT11_Start()           //����������ʼ�ź�
{
//         DHTIO=1;
//         delay_us(10);
         DHTIO=0;
         Delay20ms();   //���ֵ�ƽʱ�����18ms
         DHTIO=1;
         Delay10us();
				 Delay10us();
				 Delay10us();	//�ӳٵȴ�20-40us
}
/********DHT11����һ���ֽ�*******/
uchar receive_data()
{
	uchar i;
	uchar temp = 0;
	for(i = 0; i < 8;i++)
	{
		temp = temp<<1;
		while(!DHTIO);
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		if(DHTIO)
		{
			temp |= 0x01;
			Delay10us();
			Delay10us();
			Delay10us();
			Delay10us();
		}
		else
		{
			temp &= 0xFE;
		}
	}
	return temp;
}
//uchar receive_data()
//{
//	uchar data_byte;
//	uchar i,temp,count;
// data_byte=0;
// for(i=0;i<8;i++)
// {
//		count=2;
//		while(!DHTIO);//�ȴ�50us�͵�ƽ����
//	 printf("data comes\r\n");
//	 temp=0;
//		delay_us(40);
//		if(DHTIO)  
//		{			
//			printf("temp = 1\r\n");
//			temp=1;
//			count=2;
//			//while((DHTIO)&&count++);   
//			while(DHTIO);
//		}
//		printf("data finish,temp = %u\r\n",(uint)temp);
//		data_byte<<=1;  
//		data_byte|=temp;
// }
//  return data_byte;
//}
/********DHT11��������*******/
T_H Rec_DHT()
{
	uchar Check,Tem_Z,Tem_X,Hum_Z,Hum_X;
	uint sum;
	T_H t_h = {0,0,0,0};
  uchar flag;
  DHT11_Start();//��ʼ
  DHTIO=1;      //�ȴ���Ӧ
	while(DHTIO);
	if(!DHTIO)    //�ӻ���Ӧ
	{
		while(!DHTIO); 
		//�жϴӻ��Ƿ񷢳�80us�͵�ƽ
		while(DHTIO);
		//�жϴӻ��Ƿ񷢳�80us�ߵ�ƽ
		Hum_Z = receive_data();   //ʪ������
		Hum_X = receive_data();   //ʪ��С��
		Tem_Z = receive_data();   //�¶�����
		Tem_X = receive_data();   //�¶�С��
		Check = receive_data();   //У��λ
		DHTIO = 1;
		
		sum = Tem_Z + Tem_X + Hum_Z + Hum_X;
		
		//if(Check == sum&0xFF)
		if(1)
		{
			t_h.Tem_Z = Tem_Z;
			t_h.Tem_X = Tem_X;
			t_h.Hum_Z = Hum_Z;
			t_h.Hum_X = Hum_X;
    }
	}
	return t_h;
}
	