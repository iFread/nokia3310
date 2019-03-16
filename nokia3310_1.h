//библиотека для работы с дисплеем
//nokia3310

/*
	Включает
	* инициализацию -init_lcd()
	* очистку дисплея 
	* очистить поле 
	* очистить линию
	* вывод символа
	* вывод строки 
	* 
	pins display:
	1. -VDD(питание)
	2. - SCLK - тактовый сигнал spi
	3. SDIN - линия данных spi
	 4. DС - данные(1)/команда(0)
	 5.SCE(выбор кристала при 0 принимает данные, при 1, игнорирует)
     6.gnd 
	 7- vout(при подключении от 5 v развязка с1..10мкФ)
	 8- reset
	 // при подаче питания подаем на reset кратковременный 0, после подачи 1 готов к приему команды.
	 * по линии sdin вводятся данные; защелкивание бита идет по переднему фронту
	 * здвиг по заднему фронту на SCLK, если во время передачи восьмого бита на 
	 * D/C -1 прием данных, если 0 - команда.
	 *   команды диспле в формате 
	 * 	functionSet
	 * 		D/C  |    управляющий байт          |             описание значений битов
	 * 		 0   |  0  0  1  0 0 PD  V   H  		| PD- 1 -в режиме низкого эл.потребления, 0-кристал включен
	* 											  V адресация v=1 вертикальная, v=0 горизонтальная
	* 											  H - набор инструкций, 1- расширенный, 0- обычный
	* 	write data
			 1   |      dddd   dddd        | передача байта данных в память экрана
	инструкции обычного набора (functionSet H=0)
	1. DisplayControl:
			0	 |   0000  1D0E            | D=0,E=0 дисплей пустой
			* 							   |D=1 ,E=0 обычный режим (0- светлая точка,1 - темная)
			* 							    | D=0,E=1  все элементы включены
			* 								|D=1,E=1  итверсия (1 светлая точка, 0- темная точка)
		SetY 0 01000 YYY установить адрес по строкам Y
		SetX 0 1XXX XXXX установить по столбцам X
		Расширенный набор инструкций (H=1):
		* TemperatureControl 
		* 		0 	0001 01TT              |TT ставить 10
		*  BiasSystem 
		* 		0   0001 0BBB               | BBB=011 
		* SetVop 
		* 		0   1VVV VVVV               | ставить 100 1000  
		
		
			

*/
#ifndef _NOKIA3310_H_
#define _NOKIA3310_H_

#include <avr/io.h>
#include <avr/iom8.h> 
#define  PDIN  2
#define ce 0
#define d_c  4
#define spi_sck  3
#define res 1
#define port  PORTD
//#define true 1
//#define false 0
typedef unsigned char uchar;

extern volatile bool  flag;
extern volatile uchar  dl;


void send_byte(uchar dd,uchar s=1);
void lcd_init();
void lcd_clear();
void clearStr(uchar x, uchar y);  // очистка строки 
void send_Ch(const uchar (*ptr)[5],char ch ); //отправляем код символа в ascii
void setAddr(uchar x=0x80,uchar y=0x40); // Установка курсора на x =0..83, y=0..5
void send_str(char*str);
//void delay_mc(uchar b);// вводим количество мс задержки
// для задержек времени
void delay_ms(uchar msek=1);
void delay_mks(uchar mks=1);

static const uchar abc[][5]= {{0xFE,0x11,0x11,0x11,0xFE},         //A
				{ 0x7F, 0x49, 0x49, 0x49, 0x36},   // B 0x42  66
              { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C 0x43  67
                { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D 0x44  68
                { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E 0x45  69
                { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F 0x46  70
                { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G 0x47  71
                { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H 0x48  72
                { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I 0x49  73
                { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J 0x4A  74
                { 0x7F, 0x08, 0x14, 0x22, 0x41 },    // K 0x4B  75
               { 0x7F, 0x40, 0x40, 0x40, 0x40 },    // L 0x4C  76
                { 0x7F, 0x02, 0x0C, 0x02, 0x7F },     // M 0x4D  77
                { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N 0x4E  78
                { 0x3E, 0x41, 0x41, 0x41, 0x3E },    // O 0x4F  79
                { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P 0x50  80
                 { 0x3E, 0x41, 0x51, 0x21, 0x5E },  // Q 0x51  81
                 { 0x7F, 0x09, 0x19, 0x29, 0x46 },  // R 0x52  82
                 {0x46, 0x49, 0x49, 0x49, 0x31 },   // S 0x53  83
                 { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T 0x54  84
                 { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U 0x55  85
                 { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V 0x56  86
                  { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W 0x57  87
                  { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X 0x58  88
                  { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y 0x59  89
                  { 0x61, 0x51, 0x49, 0x45, 0x43 }};   // Z 0x5A  90};



#endif
