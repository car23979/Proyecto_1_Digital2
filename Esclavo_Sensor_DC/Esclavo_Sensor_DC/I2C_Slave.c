/*
 * I2C.c
 *
 * Created: 05/02/2026 08:12:55 p. m.
 *  Author: Admin
 */ 

#include "I2C_Slave.h"

void I2C_Slave_Init(uint8_t address)
{
	TWAR = (address << 1);     // Dirección esclavo
	TWCR = (1 << TWEN) |       // Habilitar TWI
	(1 << TWEA) |       // Habilitar ACK
	(1 << TWINT);       // Limpiar bandera
}

uint8_t I2C_Slave_WaitForCommand(void)
{
	while (!(TWCR & (1 << TWINT)));

	uint8_t status = TWSR & 0xF8;

	// 0x60 = SLA+W recibido
	if (status == 0x60)
	{
		TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
		while (!(TWCR & (1 << TWINT)));
		return TWDR;
	}

	return 0xFF;
}

uint8_t I2C_Slave_ReadData(void)
{
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}
