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

/************************************************************************/
/* DIRECCIONES I2C                                                      */
/************************************************************************/
#define SLAVE_ACTUATORS_ADDR  0x30   // Nano 1
#define SLAVE_ENV_ADDR        0x31   // Nano 2

/************************************************************************/
/* COMANDOS NANO 1 (Servo + Bomba)                                     */
/************************************************************************/
#define CMD_PUMP_DOSE         0x20
#define CMD_SERVO_OPEN        0x10
#define CMD_SERVO_CLOSE       0x11

/************************************************************************/
/* COMANDOS NANO 2 (Sensor + DC)                                        */
/************************************************************************/
#define CMD_READ_SOIL         0x40
#define CMD_FAN_ON            0x41
#define CMD_FAN_OFF           0x42

/************************************************************************/
/* PARÁMETROS DE CONTROL                                                */
/************************************************************************/
#define SOIL_THRESHOLD        100
#define PUMP_DOSE_AMOUNT      10

/************************************************************************/
/* FUNCIONES AUXILIARES                                                 */
/************************************************************************/

uint8_t Read_Soil(void)
{
	uint8_t soil_value = 0;

	if(I2C_MasterStart())
	{
		I2C_Master_Write((SLAVE_ENV_ADDR << 1) | I2C_WRITE);
		I2C_Master_Write(CMD_READ_SOIL);

		I2C_MasterRepeatedStart();
		I2C_Master_Write((SLAVE_ENV_ADDR << 1) | I2C_READ);
		I2C_MasterRead(&soil_value, I2C_NACK);

		I2C_MasterStop();
	}

	return soil_value;
}

void Activate_Pump(uint8_t dose)
{
	if(I2C_MasterStart())
	{
		I2C_Master_Write((SLAVE_ACTUATORS_ADDR << 1) | I2C_WRITE);
		I2C_Master_Write(CMD_PUMP_DOSE);
		I2C_Master_Write(dose);
		I2C_MasterStop();
	}
}

void Servo_Open(void)
{
	if(I2C_MasterStart())
	{
		I2C_Master_Write((SLAVE_ACTUATORS_ADDR << 1) | I2C_WRITE);
		I2C_Master_Write(CMD_SERVO_OPEN);
		I2C_MasterStop();
	}
}

void Servo_Close(void)
{
	if(I2C_MasterStart())
	{
		I2C_Master_Write((SLAVE_ACTUATORS_ADDR << 1) | I2C_WRITE);
		I2C_Master_Write(CMD_SERVO_CLOSE);
		I2C_MasterStop();
	}
}

/************************************************************************/
/* MAIN                                                                  */
/************************************************************************/

int main(void)
{
	uint8_t soil_value = 0;

	I2C_MasterInit(100000UL, 1);

	while(1)
	{
		soil_value = Read_Soil();

		if(soil_value < SOIL_THRESHOLD)
		{
			Activate_Pump(PUMP_DOSE_AMOUNT);
		}

		_delay_ms(3000);
	}
}
