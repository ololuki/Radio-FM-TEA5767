/*
 * i2cHardware.h
 *
 * Created: 2015-12-09 11:21:14
 * Author: Ololuki
 * ololuki.pl
 *
 */


#ifndef I2CHARDWARE_H_
#define I2CHARDWARE_H_

#include <avr/io.h>

// Prêdkoœæ transmisji w b/s
#define I2CHARDWARE_SPEED 100000

#define I2C_ACK 1
#define I2C_NACK 0

void twi_init(void);
void twi_onTimer(void);	// wywo³ywaæ z czêstotliwoœci¹ ok. 100 Hz, za³¹czyæ timer przed u¿yciem twi!!!

void twi_start(void);  //rozpoczyna transmisjê I2C
void twi_stop(void);  //koñczy transmisjê I2C
uint8_t twi_send(uint8_t data);  //wysy³a bajt danych, zwraca ack
uint8_t twi_get(uint8_t ack);  //odbiera i zwraca bajt danych, wysy³a ack
uint8_t twi_sendBufferOnce(uint8_t address, const uint8_t *buffer, uint8_t bufferSize); //wysy³a pod adres bajty z bufora o podanym rozmiarze
uint8_t twi_receiveBufferOnce(uint8_t address, uint8_t *buffer, uint8_t bufferSize); // odbiera spod adresu bajty z bufora o podanym rozmiarze
uint8_t twi_sendBufferRepeat(uint8_t address, uint8_t *buffer, uint8_t bufferSize, uint8_t numberOfTries); //wysy³a pod adres bajty z bufora o podanym rozmiarze przez podan¹ liczbê prób, jak siê nie uda to error
uint8_t twi_receiveBufferRepeat(uint8_t address, uint8_t *buffer, uint8_t bufferSize, uint8_t numberOfTries); // odbiera spod adresu bajty z bufora o podanym rozmiarze przez podan¹ liczbê prób, jak siê nie uda to error


uint8_t twi_isErrorOccured(void);	// zwraca bool czy wyst¹pi³ error
void twi_reset(void);	// resetuje twi - wysy³a stop i zeruje isError

#endif /* I2CHARDWARE_H_ */