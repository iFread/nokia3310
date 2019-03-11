// определение методов nokia3310.h
#include <avr/interrupt.h>
#include "nokia3310.h"
//static uchar temp;

// определены в nokia3310.h
 bool flag=false;
 uchar dl=0;


	
void delay_ms(uchar msek)
{
 dl=0;
 flag=true;	
 TCNT0=0;
 TIFR|=1<<TOV0;
 TIMSK|=(1<<0);
 TCCR0|=(1<<0);
 
sei();

for(;msek>0;msek--)
 {while(flag)
 {};
flag=true;
dl=0; 
 }
cli();
	}
void delay_mks(uchar mks)
{     // 1мкс - 8 тактов датчика
 // для таких команд, нет смысла вызывать прерывания
bool mark=false;
uchar temp=3;
if(SREG & 0b10000000)
{
 cli();
 mark=true;
 }
for(;mks>0;mks--)
{
	while(temp--)
	{
	 asm("nop");
		};
	 temp=3;	
	//flag=true;
	//dl=30;
	}
if(mark)	
sei();		
 }



void set_byte( unsigned char dd,bool b)    // беззнаковый char содержит команду
{
	if(b)     //если отправляются данные
	port|=(1<<d_c) ;// выставляем  1 на нужный пин
	else 
	 port&=~(1<<d_c);
//отправка байта на дисплей
// delay_mc(1);
{ uchar temp1;
	  temp1=dd;  // присвоим передаваемый dd
 for(uchar i=0;i<8;i++)
  {
   
  if(temp1&0b10000000)
	port|=1<<PDIN;
 else 
	 port&=~(1<<PDIN);

	 port|=(1<<spi_sck); // дергаем тактовый сигнал
	 delay_mks(1);
	 temp1=temp1<<1;// сдвигаем 
	 port&=~(1<<spi_sck);
	   
	   }					// теперь полученный результат нужно установить на pdin
     } // блок для временной переменной
   }
void lcd_init()
{  // в темение 30мс после подачи питания должна быть инициализация
	
	port&=~(1<<res);
 delay_mks();
 port|=(1<<res);
 set_byte(0b00100001,false); // 0x21 functionSet -расширенный набор
set_byte(0b00010011,false); // 0x13 BiasSystem - смещение напряжения
 set_byte(0b00000110,false);//	 temperatureControl 
 
 set_byte(0b10110110,false);// 0xB8  SetVop повышеное напряжение
 // включаем обычный набор
 set_byte(0b00100000,false); //functionSet
 set_byte(0b00001100,false);// настраиваем отображение
 //настраиваем курсор
// set_byte(0b01000001,false);
// set_byte(0b10000011,false); // в положение x=0 y=0
 		}
