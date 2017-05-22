/*
 * tea5767.cpp
 *
 * Created: 2015-11-08 16:04:40
 * Author: Ololuki
 * ololuki.pl
 *
 */ 

#include "tea5767.h"


uint16_t Tea5767::pllConfigNumber;


uint8_t Tea5767::configData[5] = {
	0x00,	// mute, searchMode, PLL13..PLL8
	0x00,	// PLL7..PLL0
	0x90 + 0x08,	// searchUpDown, searchStopLvl, , hiLoSideInj, monoStereo, muteLeft, muteRight, swPort1
	0x10,	// swPort2, standBy, bandLimits, xtal, softMute, hcc, snc, searchIndicator
	0x80	// PLLref, deemph, not used
};


void Tea5767::init()
{
	twi_init();
}


void Tea5767::write(const uint8_t * data)
{
	uint8_t isError;
	do{
		isError = twi_sendBufferOnce(0xC0, data, 5);
	}while(isError);
}


// odczytuje 5 bajtów z uk³adu TEA5767 po interfejsie i2c
uint8_t * Tea5767::read(uint8_t* data)
{	
	uint8_t isError;
	do{
		isError = twi_receiveBufferOnce(0xC0, data, 5);
	}while(isError);
	return data;
}


//8800 - 10800
void Tea5767::setFreq(uint32_t freq)
{
	uint16_t newPllConfigNumber = 4000*((uint32_t)freq+225)/32768;
	if (newPllConfigNumber != pllConfigNumber)
	{
		pllConfigNumber = newPllConfigNumber;
		configData[0] = (configData[0] & 0b11000000) | ((pllConfigNumber >> 8) & 0b00111111);
		configData[1] = pllConfigNumber;
		write(configData);
	}
}


uint16_t Tea5767::getPllConfigNumber(){
	return pllConfigNumber;
}


