/*
 * Maestro.c
 *
 * Created: 12/02/2026 07:37:51 p. m.
 * Author : Admin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "UART.h"


#define SLAVE_ACTUATORS_ADDR  0x30

#define CMD_PUMP_START  0x20
#define CMD_PUMP_STOP   0x21
#define CMD_SERVO_OPEN 0x10
#define CMD_SERVO_CLOSE 0x11

#define RX_BUFFER_SIZE 32

volatile char rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_index = 0;
volatile uint8_t command_ready = 0;

/************************************************************************/
/* FUNCIONES I2C                                                        */
/************************************************************************/

void Pump_Start_Command(void)
{
	I2C_MasterStart();
	I2C_Master_Write((SLAVE_ACTUATORS_ADDR<<1)|I2C_WRITE);
	I2C_Master_Write(CMD_PUMP_START);
	I2C_MasterStop();
}

void Pump_Stop_Command(void)
{
	I2C_MasterStart();
	I2C_Master_Write((SLAVE_ACTUATORS_ADDR<<1)|I2C_WRITE);
	I2C_Master_Write(CMD_PUMP_STOP);
	I2C_MasterStop();
}

void Servo_Open(void)
{
	I2C_MasterStart();
	I2C_Master_Write((SLAVE_ACTUATORS_ADDR<<1)|I2C_WRITE);
	I2C_Master_Write(CMD_SERVO_OPEN);
	I2C_MasterStop();
}

void Servo_Close(void)
{
	I2C_MasterStart();
	I2C_Master_Write((SLAVE_ACTUATORS_ADDR<<1)|I2C_WRITE);
	I2C_Master_Write(CMD_SERVO_CLOSE);
	I2C_MasterStop();
}

/************************************************************************/
/* PROCESAMIENTO UART                                                   */
/************************************************************************/

void Process_Command(void)
{
	// Ejemplos:
	// P1 -> Start bomba
	// P0 -> Stop bomba
	// S1 -> Servo abrir
	// S0 -> Servo cerrar

	if(rx_buffer[0] == 'P')
	{
		if(rx_buffer[1] == '1')
		{
			Pump_Start_Command();
			UART_SendString("Pump START\r\n");
		}
		else if(rx_buffer[1] == '0')
		{
			Pump_Stop_Command();
			UART_SendString("Pump STOP\r\n");
		}
	}
	else if(rx_buffer[0] == 'S')
	{
		if(rx_buffer[1] == '1')
		{
			Servo_Open();
			UART_SendString("Servo OPEN\r\n");
		}
		else if(rx_buffer[1] == '0')
		{
			Servo_Close();
			UART_SendString("Servo CLOSE\r\n");
		}
	}
}


/************************************************************************/
/* ISR                                                                  */
/************************************************************************/

ISR(USART_RX_vect)
{
	char c = UDR0;

	if(c == '\n' || c == '\r')
	{
		rx_buffer[rx_index] = '\0';
		command_ready = 1;
		rx_index = 0;
	}
	else
	{
		if(rx_index < RX_BUFFER_SIZE - 1)
		rx_buffer[rx_index++] = c;
	}
}

/************************************************************************/
/* MAIN                                                                 */
/************************************************************************/

int main(void)
{
	I2C_MasterInit(100000UL, 1);
	UART_Init(UART_BAUD_9600_16MHZ, UART_INTERRUPTS_ENABLED);

	sei();   // Habilitar interrupciones globales

	UART_SendString("Sistema listo\r\n");

	while(1)
	{
		if(command_ready)
		{
			Process_Command();
			command_ready = 0;
		}
	}
}
