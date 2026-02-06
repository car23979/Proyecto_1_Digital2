/*
 * servo_timer1.c
 
 *
 * Created: 11/04/2025 01:35:52 p. m.
 *  Author: Admin
 */ 

// pwm.c
#include <avr/io.h>
#include "servo_timer1.h"

#define SERVO_MIN_PULSE 2000   // 1 ms
#define SERVO_MAX_PULSE 4000   // 2 ms
// Servo
#define SERVO_MIN_ANGLE      0
#define SERVO_MAX_ANGLE      180
#define SERVO_OPEN_ANGLE     120
#define SERVO_CLOSE_ANGLE    20

void Servo_Init(void) {
	// PB1 = OC1A (D9)
	DDRB |= (1 << PB1);

	// Fast PWM, TOP = ICR1
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // prescaler 8

	// 50 Hz (20 ms)
	ICR1 = 39999;

	// Posición inicial
	OCR1A = SERVO_MIN_PULSE;
}

void Servo_SetAngle(uint8_t angle) {
	if (angle > SERVO_MAX_ANGLE)
	angle = SERVO_MAX_ANGLE;

	OCR1A = SERVO_MIN_PULSE +
	((uint32_t)angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE)) / 180;
}