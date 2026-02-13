/*
 * stepper_uln2003.c
 *
 * Created: 12/02/2026 07:21:00 p. m.
 *  Author: Admin
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "stepper_uln2003.h"

#define IN1 PD4
#define IN2 PD5
#define IN3 PD6
#define IN4 PD7

static const uint8_t sequence[8] =
{
	0b00010000,
	0b00110000,
	0b00100000,
	0b01100000,
	0b01000000,
	0b11000000,
	0b10000000,
	0b10010000
};

void Stepper_Init(void)
{
	DDRD |= (1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4);
}

void Pump_Dose(uint16_t steps)
{
	static uint8_t index = 0;

	for (uint16_t i = 0; i < steps; i++)
	{
		index = (index + 1) % 8;
		PORTD = (PORTD & 0x0F) | sequence[index];
		_delay_ms(2);
	}

	Stepper_Stop();
}

void Stepper_Stop(void)
{
	PORTD &= 0x0F;
}
