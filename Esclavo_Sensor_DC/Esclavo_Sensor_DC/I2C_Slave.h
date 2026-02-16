/*
 * I2C.h
 *
 * Created: 05/02/2026 08:13:09 p. m.
 *  Author: Admin
 */ 


#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include <avr/io.h>
#include <stdint.h>

void I2C_Slave_Init(uint8_t address);
uint8_t I2C_Slave_WaitForCommand(void);
uint8_t I2C_Slave_ReadData(void);



#endif /* I2C_SLAVE_H_ */