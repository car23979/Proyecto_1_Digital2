/*
 * I2C.c
 *
 * Created: 05/02/2026 08:12:55 p. m.
 *  Author: Admin
 */ 

#include "I2C.h"

void TWI_Slave_Init(uint8_t address)
{
	TWAR = (address << 1);
	TWCR = (1 << TWEN) | (1 << TWEA);
}

uint8_t TWI_Slave_Read(void)
{
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void TWI_Slave_Write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
}
