/*
 * i2cHardware.c
 *
 * Created: 2015-12-09 11:20:58
 * Author: Ololuki
 * ololuki.pl
 *
 */


#include "i2cHardware.h"
#include "usart.h"

#define TWI_IS_SET_TWINT (TWCR & (1 << TWINT))


Usart usart;
volatile uint8_t twi_timer;

uint8_t twi_isError = 0;
uint8_t twi_isErrorOccured(void)
{
	return twi_isError;
}


void twi_reset(void)
{
	twi_stop();
	twi_isError = 0;
}


void twi_init(void)
{
	TWBR = 32;	// FCPU = 8MHz fclk = 100kHz
}


void twi_start(void)
{
	usart.sendString((uint8_t*)"\r\nSTART  ");
	TWCR |= 0b10100100;
	
	twi_timer = 200;
	while(twi_timer)
	{
		if (TWI_IS_SET_TWINT)
		{
			usart.sendNumberHex((uint32_t)TWSR & 0xFC);
			return;
		}
	}
	twi_isError = 1;
}


void twi_stop(void)
{
	usart.sendString((uint8_t*)"\r\nSTOP  ");
	TWCR |= 0b10010100;
	usart.sendNumberHex((uint32_t)TWSR & 0xFC);
}


// Wys³anie znaku - zwraca ack
uint8_t twi_send(uint8_t data)
{
	usart.sendString((uint8_t*)"\r\nSend  ");
	TWDR = data;
	TWCR = 0b10000100;
	twi_timer = 200;
	while(twi_timer)
	{
		if (TWI_IS_SET_TWINT)
		{
			usart.sendNumberHex((uint32_t)TWSR & 0xFC);
			return 0; // TODO: odczyt ACK i NACK
		}
	}
	twi_isError = 1;
	usart.sendString((uint8_t*)"\r\nSendError  ");
	usart.sendNumberHex((uint32_t)TWSR & 0xFC);
	uint8_t n = 0;	// TODO: odczyt ACK i NACK
	
	return n;
}


//odebranie znaku
uint8_t twi_get(uint8_t ack)
{
	TWCR = (0b10000100 | (ack << TWEA)); // dopisanie bitu ack
	
	usart.sendString((uint8_t*)"\r\nGet  ");
	twi_timer = 200;
	while(twi_timer)
	{
		if (TWI_IS_SET_TWINT)
		{
			usart.sendNumberHex((uint32_t)TWSR & 0xFC);
			return TWDR;
		}
	}
	twi_isError = 1;
	usart.sendString((uint8_t*)"\r\nGetError  ");
	usart.sendNumberHex((uint32_t)TWSR & 0xFC);
	return 0;
}


//wysy³a pod adres bajty z bufora o podanym rozmiarze
uint8_t twi_sendBufferOnce(uint8_t address, const uint8_t *buffer, uint8_t bufferSize)
{
	if(twi_isErrorOccured())
	{
		twi_reset();
	}
	twi_start();
	twi_send(address | 0);	// write to TEA5767
	for(uint8_t i=0; i < bufferSize; i++)
	{
		twi_send(buffer[i]);
	}
	twi_stop();
	if(twi_isErrorOccured()) return 1;
	return 0;
} 


// odbiera spod adresu bajty z bufora o podanym rozmiarze
uint8_t twi_receiveBufferOnce(uint8_t address, uint8_t *buffer, uint8_t bufferSize)
{
	if(twi_isErrorOccured())
	{
		twi_reset();
	}
	twi_start();
	twi_send(address | 1);	// read from TEA5767
	for(uint8_t i=0; i < bufferSize-1; i++)	// dla ostatniego elementu nie nadawaæ potwierdzenia ACK
	{
		buffer[i] = twi_get(I2C_ACK);
	}
	buffer[bufferSize-1] = twi_get(I2C_NACK);	// potwierdzenie NACK dla ostatneigo elementu
	twi_stop();
	if(twi_isErrorOccured()) return 1;
	return 0;
}


void twi_onTimer(void)
{
	twi_timer--;
}