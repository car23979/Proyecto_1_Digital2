/*
 * I2C.h
 *
 * Created: 05/02/2026 08:13:09 p. m.
 *  Author: Admin
 */ 


#ifndef TWI_SLAVE_H_
#define TWI_SLAVE_H_


#include <avr/io.h>

void TWI_Slave_Init(uint8_t address);
uint8_t TWI_Slave_Read(void);
void TWI_Slave_Write(uint8_t data);


#endif /* TWI_SLAVE_H_ */