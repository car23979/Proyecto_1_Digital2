/*
 * I2C.c
 *
 * Created: 12/02/2026 07:39:30 p. m.
 *  Author: Admin
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "I2C.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

void I2C_MasterInit(unsigned long SCL_Clock, uint8_t Prescaler)
{
	DDRC &= ~((1 << DDC4) | (1 << DDC5));

	TWSR &= ~((1 << TWPS0) | (1 << TWPS1));

	switch(Prescaler)
	{
		case 1: break;
		case 4:  TWSR |= (1 << TWPS0); break;
		case 16: TWSR |= (1 << TWPS1); break;
		case 64: TWSR |= (1 << TWPS1) | (1 << TWPS0); break;
	}

	TWBR = ((F_CPU / SCL_Clock) - 16) / (2 * Prescaler);
}

uint8_t I2C_MasterStart()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	uint8_t status = (TWSR & 0xF8);
	return (status == 0x08);
}

uint8_t I2C_MasterRepeatedStart(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	uint8_t status = (TWSR & 0xF8);
	return (status == 0x10);
}

void I2C_MasterStop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t I2C_Master_Write(uint8_t dato)
{
	TWDR = dato;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));

	return (TWSR & 0xF8);
}

uint8_t I2C_MasterRead(uint8_t *buffer, uint8_t ack)
{
	if(ack)
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	else
	TWCR = (1 << TWEN) | (1 << TWINT);

	while(!(TWCR & (1 << TWINT)));

	uint8_t status = TWSR & 0xF8;

	if ((ack && status == 0x50) || (!ack && status == 0x58))
	{
		*buffer = TWDR;
		return 1;
	}

	return 0;
}
