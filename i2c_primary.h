#ifndef I2C_PRIMARY_H
#define I2C_PRIMARY_H

#include <avr/io.h>
#include <util/delay.h>

#define PIN_SDA 				PB0
#define PIN_SCL 				PB2

#define WAIT_LONG				5 // 4,7us
#define WAIT_SHORT 				4 // 4,0us

// USISR mask
#define USISR_CLOCK_8_BITS		0b11110000
#define USISR_CLOCK_1_BIT  		0b11111110

void i2c_init();
void i2c_start();
void i2c_stop();

// controller sends a byte to the bus
// returns 0 if there's a valid nack, otherwise 1
unsigned char i2c_write_byte(unsigned char data);

// controller reads 1 byte from the bus
// and sends a nack if wanna read another one
// (1 = will read another one, 0 = stop sending)
// returns the read byte
unsigned char i2c_read_byte(unsigned char nack);
#endif
