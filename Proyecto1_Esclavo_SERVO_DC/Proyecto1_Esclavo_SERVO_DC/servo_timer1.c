/*
 * servo_timer1.c
 
 *
 * Created: 11/04/2025 01:35:52 p. m.
 *  Author: Admin
 */ 

// pwm.c
#include <avr/io.h>
#include "servo_timer1.h"

void Timer1_Servo1_Init(void) {
	DDRB |= (1 << PINB1); // PB1 como salida
	// No se configura el timer completo aquí
	// Solo se asume que Timer1 ya está configurado en otra libreria
}

void SERVO1_set(uint16_t pulso) {
	OCR1A = pulso;
}
