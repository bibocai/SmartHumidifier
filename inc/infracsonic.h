#ifndef __INFTACSONIC_H
#define __INFTACSONIC_H

#include "config.h"
#include "delay.h"


#define div 1/(double)12
#define consume   65535 / ((double)FOSC * div )       //���һ������ʱ�� 

double distance();
void InitTimer1();

#endif