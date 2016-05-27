#ifndef __INFTACSONIC_H
#define __INFTACSONIC_H

#include "config.h"
#include "delay.h"


#define div 1/(double)12
#define consume   65535 / ((double)FOSC * div )       //溢出一次所用时间 

double distance();
void InitTimer1();

#endif