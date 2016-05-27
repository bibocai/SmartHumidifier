#ifndef __CONFIG_H
#define __CONFIG_H

#include "STC15F2K61S2.h"

#define FOSC 11059200L
#define False 0
#define True !False

typedef unsigned char uchar;
typedef unsigned int	uint;

/*****    Nokia 5110       ******/
sbit RST = P0^0;
sbit CE  = P0^1;
sbit DC  = P0^2;
sbit DIN = P0^3;
sbit CLK = P0^4;

/*****    infracsonic      ******/
sbit TRIG = P0^5;
sbit ECHO = P0^6;


sbit LED = P1^2;
sbit DHTIO = P1^3;
sbit HUMIDIFIER = P0^7;

/*****   Key    **********/
sbit KEY_ADJUST = P3^2;
sbit KEY_DEC = P1^4;
sbit KEY_INC = P1^5;


#endif