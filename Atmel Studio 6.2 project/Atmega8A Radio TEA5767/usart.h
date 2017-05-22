/*
 * usart.h
 *
 * Created: 2015-07-07 15:46:06
 * Author: Ololuki
 * ololuki.pl
 *
 */


#ifndef USART_H_
#define USART_H_

#include "avr/io.h"
#include <stdlib.h>

class Usart {
	public:
		static void init();
		static void send(uint8_t dataToSend);
		static void sendString(uint8_t * stringToSend);
		static void sendNumber(int32_t numberToSend);
		static void sendNumber(uint32_t numberToSend);
		static void sendNumberHex(uint8_t numberToSend);
		static void sendNumberBin(uint8_t numberToSend);
};


#endif /* USART_H_ */