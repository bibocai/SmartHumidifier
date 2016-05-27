#include "dht11.h"


void DHT11_Start()           //主机发出开始信号
{
//         DHTIO=1;
//         delay_us(10);
         DHTIO=0;
         Delay20ms();   //保持电平时间大于18ms
         DHTIO=1;
         Delay10us();
				 Delay10us();
				 Delay10us();	//延迟等待20-40us
}
/********DHT11接收一个字节*******/
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
//		while(!DHTIO);//等待50us低电平结束
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
/********DHT11接收数据*******/
T_H Rec_DHT()
{
	uchar Check,Tem_Z,Tem_X,Hum_Z,Hum_X;
	uint sum;
	T_H t_h = {0,0,0,0};
  uchar flag;
  DHT11_Start();//开始
  DHTIO=1;      //等待响应
	while(DHTIO);
	if(!DHTIO)    //从机响应
	{
		while(!DHTIO); 
		//判断从机是否发出80us低电平
		while(DHTIO);
		//判断从机是否发出80us高电平
		Hum_Z = receive_data();   //湿度整数
		Hum_X = receive_data();   //湿度小数
		Tem_Z = receive_data();   //温度整数
		Tem_X = receive_data();   //温度小数
		Check = receive_data();   //校验位
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
	