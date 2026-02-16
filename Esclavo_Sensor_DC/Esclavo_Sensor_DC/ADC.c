/*
 * ADC.c
 *
 * Created: 15/02/2026 09:57:35 p. m.
 *  Author: David Carranza
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include "ADC.h"

void ADC_Init(void)
{
	ADMUX = (1 << REFS0);	//Referencia AVcc
	ADCSRA = (1 << ADEN) |	// Habilitar ADC
			 (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
}

uint16_t ADC_Read(uint8_t channel)
{
	
}