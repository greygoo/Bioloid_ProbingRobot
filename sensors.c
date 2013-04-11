#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "global.h"
#include "serial.h"


int read_dms() 
{
        DDRA  = 0xFC;
	PORTA = 0xFC;

	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);     // ADC Enable, Clock 1/64div.
	ADMUX = ADC_PORT_1;

	PORTA &= ~0x80;                 // ADC Port 1 IR ON

	_delay_us(12);                  // Short Delay for rising sensor signal
	ADCSRA |= (1 << ADIF);          // AD-Conversion Interrupt Flag Clear
	ADCSRA |= (1 << ADSC);          // AD-Conversion Start

	while( !(ADCSRA & (1 << ADIF)) );       // Wait until AD-Conversion complete

	PORTA = 0xFC;                           // IR-LED Off

	printf( "DMS: %d\r\n", ADC); // Print Value on USART

	return ADC;
}


int read_ir()
{
        DDRA  = 0xFC;
	PORTA = 0xFC;

	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);     // ADC Enable, Clock 1/64div.
	ADMUX = ADC_PORT_2;

	PORTA &= ~0x40;                 // ADC Port 1 IR ON

	_delay_us(12);                  // Short Delay for rising sensor signal
	ADCSRA |= (1 << ADIF);          // AD-Conversion Interrupt Flag Clear
	ADCSRA |= (1 << ADSC);          // AD-Conversion Start

	while( !(ADCSRA & (1 << ADIF)) );       // Wait until AD-Conversion complete

	PORTA = 0xFC;                           // IR-LED Off

	printf( "IR: %d\r\n", ADC); // Print Value on USART

	return ADC;
}
