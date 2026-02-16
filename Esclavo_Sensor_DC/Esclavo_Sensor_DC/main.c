/*
 * Esclavo_Sensor_DC.c
 *
 * Created: 15/02/2026 09:55:55 p. m.
 * Author : David Carranza
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "ADC.h"
#include "I2C_Slave.h"

/************************************************************************/
/*                          CONFIGURACIÓN                               */
/************************************************************************/

#define SLAVE_ADDR		0x31
#define CMD_READ_SOIL	0x40

#define SOIL_POWER_PIN	PB0	 // D8


/************************************************************************/
/*                                                                      */
/************************************************************************/