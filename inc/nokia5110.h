#ifndef LCD5510_H_
#define LCD5510_H_
#include "delay.h"
#include "config.h"
#include "Font6_8.h" 
#include "Font16_16.h"

 
void lcdDC(uchar dt,uchar command);
void lcdClear(void);
void Init5110(void);
void lcdSetXY(uchar X,uchar Y);
void lcdWriteChar6_8(uchar row,uchar page,uchar character);	 //row : 0~13  page :0~5 
void lcdWriteChar16_16(uchar row,uchar page,uchar character);	 //row : 0~13  page :0~5 
void lcdClearAny(uchar page,uchar Row_S,uchar Row_E);
void lcdShowDouble(uchar page,uchar row,double y,uchar n); //n为显示小数的位数
void lcdWriteChar(uchar value);
void lcdPutChar(uchar value,uchar x,uchar y);
void lcdWriteStr(uchar * str);
void lcdPutStr(uchar * str,uchar x,uchar y);
void lcdWriteChineseStr(uchar Hanzi[],uchar x,uchar y,uchar num);
void lcdWriteChinese(uchar Hanzi[],uchar x,uchar y);

#endif