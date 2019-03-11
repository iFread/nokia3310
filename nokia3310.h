#ifndef _NOKIA3310_H_
#define _NOKIA3310_H_

#include <avr/io.h>
#include <avr/iom8.h> 
#define  PDIN  2
#define d_c  4
#define spi_sck  3
#define res 1
#define port  PORTB
//#define true 1
//#define false 0
typedef unsigned char uchar;

extern bool flag;
extern uchar dl;

  
//static uchar dl=0;
//typedef 4 lcd_res;
void set_byte(uchar dd=0b00000000,bool s=true);
void lcd_init();
//void delay_mc(uchar b);// вводим количество мс задержки
// для задержек времени
void delay_ms(uchar msek=1);
void delay_mks(uchar mks=1);




#endif
