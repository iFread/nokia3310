#ifndef _NOKIA3310_H_
#define _NOKIA3310_H_

#include <avr/io.h>
#include <avr/iom8.h> 
  //  pins
#define  res 1
#define  PDIN  2
#define  spi_sck  3
#define  d_c   4

#define port  PORTB
typedef unsigned char uchar;

extern bool flag;
extern uchar dl;
//metods
void set_byte(uchar dd=0b00000000,bool s=true);
void lcd_init();
void delay_ms(uchar msek=1);
void delay_mks(uchar mks=1);

#endif
