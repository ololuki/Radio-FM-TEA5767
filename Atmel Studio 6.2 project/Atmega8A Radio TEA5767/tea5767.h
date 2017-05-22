/*
 * tea5767.h
 *
 * Created: 2015-11-08 16:05:02
 * Author: Ololuki
 * ololuki.pl
 *
 */


#ifndef TEA5767_H_
#define TEA5767_H_

#include <avr/io.h>
#include "i2cHardware.h"


//wszystko static, ¿eby nie przekazywaæ wskaŸnika na klasê za ka¿dym razem, bo to zajmuje miejsce

class Tea5767 {
	public:
		static void init();
		
		static uint8_t* read(uint8_t* data);
		static void setFreq(uint32_t freq); //8800 - 10800
		
		static uint16_t getPllConfigNumber();
	private:
		static void write(const uint8_t* data);
		
		static uint16_t pllConfigNumber;
		static uint8_t configData[5];
};


#endif /* TEA5767_H_ */