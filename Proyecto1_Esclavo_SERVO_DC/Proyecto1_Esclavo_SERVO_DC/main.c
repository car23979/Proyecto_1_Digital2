/*
 * Proyecto1_Esclavo_SERVO_DC.c
 *
 * Created: 05/02/2026 07:22:32 p. m.
 * Author : Mario Bentacourt y David Carranza
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "timer1_servo1.h"
#include "PWM3.h"
#include "timer1_config.h"
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


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

