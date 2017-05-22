/*
 * usart.cpp
 *
 * Created: 2015-07-07 15:45:44
 * Author: Ololuki
 * ololuki.pl
 *
 */


#include "usart.h"

#define USART_BAUD_RATE 9600		// TODO: zmieniæ na private: const BAUD_RATE


void Usart::init() {
	UCSRB |= (1 << TXEN);	//enable transmit
	UBRRL = F_CPU/16/USART_BAUD_RATE - 1;		//51;		// baudrate 9600 for 8MHz Asynch normal mode  (U2X = 0)
	DDRD |= (1 << PD1);		//TXD as output
}


void Usart::send(uint8_t dataToSend) {
	UDR = dataToSend;
	while(!(UCSRA & (1 << UDRE)));	//wait for data shift out
}


void Usart::sendString(uint8_t * stringToSend) {
	while(* stringToSend) {
		send(* stringToSend++);
	}
}


void Usart::sendNumber(int32_t numberToSend) {
	char buffer[12];
	ltoa(numberToSend, buffer, 10);
	sendString((uint8_t*)buffer);
}


void Usart::sendNumber(uint32_t numberToSend) {
	char buffer[12];
	ultoa(numberToSend, buffer, 10);
	sendString((uint8_t*)buffer);
}


void Usart::sendNumberHex(uint8_t numberToSend) {
	char buffer[12];
	ultoa(numberToSend, buffer, 16);
	sendString((uint8_t*)buffer);
}


void Usart::sendNumberBin(uint8_t numberToSend) {
	char buffer[12];
	ultoa(numberToSend, buffer, 2);
	sendString((uint8_t*)buffer);
}