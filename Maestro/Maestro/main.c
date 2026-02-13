/*
 * Maestro.c
 *
 * Created: 12/02/2026 07:37:51 p. m.
 * Author : Admin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"

#define SLAVE_ACTUATORS_ADDR  0x30
#define SLAVE_ENV_ADDR        0x31

#define CMD_PUMP_DOSE  0x20
#define CMD_SERVO_OPEN 0x10
#define CMD_SERVO_CLOSE 0x11

#define CMD_READ_SOIL  0x40

#define SOIL_THRESHOLD 100

int main(void)
{
	uint8_t soil_value = 0;

	I2C_MasterInit(100000UL, 1);

	while(1)
	{
		// Leer humedad suelo
		if(I2C_MasterStart())
		{
			I2C_Master_Write((SLAVE_ENV_ADDR<<1)|I2C_WRITE);
			I2C_Master_Write(CMD_READ_SOIL);

			I2C_MasterRepeatedStart();
			I2C_Master_Write((SLAVE_ENV_ADDR<<1)|I2C_READ);
			I2C_MasterRead(&soil_value, I2C_NACK);

			I2C_MasterStop();
		}

		// Decisión riego
		if(soil_value < SOIL_THRESHOLD)
		{
			I2C_MasterStart();
			I2C_Master_Write((SLAVE_ACTUATORS_ADDR<<1)|I2C_WRITE);
			I2C_Master_Write(CMD_PUMP_DOSE);
			I2C_Master_Write(10);
			I2C_MasterStop();
		}

		_delay_ms(3000);
	}
}
