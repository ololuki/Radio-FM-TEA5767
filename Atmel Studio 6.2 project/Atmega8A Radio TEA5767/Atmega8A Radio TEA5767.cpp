/*
 * Atmega8A_Radio_TEA5767.cpp
 *
 * Created: 2015-11-01 22:18:31
 * Author: Ololuki
 * ololuki.pl
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tea5767.h"


inline void setPullupOnButtonPins()
{
	PORTC |= (1 << PC3);	// btn1
	PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4);				// btn 2 3 4
}


inline bool isButton1Pressed()
{
	return !(PINC & (1 << PC3));
}


inline bool isButton2Pressed()
{
	return !(PIND & (1 << PC2));
}


inline bool isButton3Pressed()
{
	return !(PIND & (1 << PC3));
}


inline bool isButton4Pressed()
{
	return !(PIND & (1 << PC4));
}


inline void setTimer0Prescaler256()
{
	TCCR0 |= (1 << CS02);
}


inline void setTimer0EnableOverflowInterrupt()
{
	TIMSK |= (1 << TOIE0);
}


int main(void)
{
	uint32_t memoryStationInKHz[4] = {97900, 102200, 99700, 105600};
	Tea5767 tea5767;
	
	setPullupOnButtonPins();
	setTimer0Prescaler256();
	setTimer0EnableOverflowInterrupt();
	sei();	// za³¹czyæ timer i przerwania przed u¿yciem i2c
	tea5767.init();	
	tea5767.setFreq(memoryStationInKHz[0]);
	
	while(1)
	{
		if (isButton1Pressed())
		{
			tea5767.setFreq(memoryStationInKHz[0]);
		}
		if (isButton2Pressed())
		{
			tea5767.setFreq(memoryStationInKHz[1]);
		}
		if (isButton3Pressed())
		{
			tea5767.setFreq(memoryStationInKHz[2]);
		}
		if (isButton4Pressed())
		{
			tea5767.setFreq(memoryStationInKHz[3]);
		}
		_delay_ms(1000);
	}
}


// ok. 122Hz
ISR(TIMER0_OVF_vect)
{
	twi_onTimer();
}