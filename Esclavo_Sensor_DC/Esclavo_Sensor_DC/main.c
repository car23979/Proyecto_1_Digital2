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
/*                               MAIN                                    */
/************************************************************************/

int	main(void)
{
	uint8_t command;
	uint16_t soil_value;
	
	// Inicializadores
	I2C_Slave_Init(SLAVE_ADDR);
	ADC_Init();
	
	// Configuración de pin de alimentación del sensor
	DDRB |= (1 << SOIL_POWER_PIN);
	PORTB &= ~(1 << SOIL_POWER_PIN);	// Apagado inicialmente
	
	while(1)
	{
		command = I2C_Slave_WaitForCommand();
		 if (command == CMD_READ_SOIL)
		 {
			 // Encender sensor
			 PORTB |= (1 << SOIL_POWER_PIN)
			 _delay_ms(50);		// Estabilizar lectura
			 
			 soil_value = ADC_Read(0);	// A0
			 
			 // Apagar sensor
			 PORTB &= ~(1 << SOIL_POWER_PIN);
			 
			 // Convertir a 8 bits para I2C
			 uint8_t soil_value = soil_value >> 2;
			 
			 // Preparar respuesta
			 TWDR = soil_8bit;
			 
		 }
		 
		 // Re-armar TWI
		 TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
		 
	}
}