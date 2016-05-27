#ifndef __DHT11_H
#define __DHT11_H

#include "config.h"
#include "delay.h"
#include "stdio.h"

typedef struct{
	uchar Tem_Z;
	uchar Tem_X;
	uchar Hum_Z;
	uchar Hum_X;
}T_H;

//uchar Check;
T_H Rec_DHT();                //DHT11½ÓÊÕº¯Êý

#endif