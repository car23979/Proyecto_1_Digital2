/*
 * Proyecto1_Esclavo_SERVO_DC.c
 *
 * Created: 05/02/2026 07:22:32 p. m.
 * Author : Mario Bentacourt y David Carranza
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "servo_timer1.h"
#include "DC.h"

// I2C
#define SLAVE_SERVO_DC_ADDR  0x20

// Comandos I2C
#define CMD_SERVO_SET_ANGLE  0x10
#define CMD_SERVO_OPEN       0x11
#define CMD_SERVO_CLOSE      0x12

// Servo
#define SERVO_MIN_ANGLE      0
#define SERVO_MAX_ANGLE      180
#define SERVO_OPEN_ANGLE     120
#define SERVO_CLOSE_ANGLE    20


uint8_t command;
uint8_t angle;

int main(void)
{
	// Inicializaciones
	Servo_Init();
	TWI_Slave_Init(SLAVE_SERVO_DC_ADDR);

	while (1) {
		// Esperar evento I2C
		if ((TWSR & 0xF8) == 0x80) // Dato recibido
		{
			command = TWDR;

			switch (command)
			{
				case CMD_SERVO_SET_ANGLE:
				angle = TWI_Slave_Read();
				Servo_SetAngle(angle);
				break;

				case CMD_SERVO_OPEN:
				Servo_SetAngle(SERVO_OPEN_ANGLE);
				break;

				case CMD_SERVO_CLOSE:
				Servo_SetAngle(SERVO_CLOSE_ANGLE);
				break;

				default:
				// comando no válido
				break;
			}

			// Preparar siguiente recepción
			TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
		}
	}
}