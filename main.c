/**
 *  
 * Pulse Solenoid Demo Code
 *
 */

#include <avr/io.h>
// F_CPU frequency to be defined at command line
#include <util/delay.h>
#include "i2c_primary.h"

// LED is on pin 2, PB3
#define LED       PB3

#define BLINK_MS  250
#define DIGIT_PAUSE_MS  1000

void led_setup(int pin)
{
	// setup led pin as output
	DDRB |= (1 << pin);
}

void blink(int pin)
{
	PORTB |= (1 << pin);
	_delay_ms(BLINK_MS);
	PORTB &= ~(1 << pin);
	_delay_ms(BLINK_MS);
}

void long_blink(int pin)
{
	PORTB |= (1 << pin);
	_delay_ms(3*BLINK_MS);
	PORTB &= ~(1 << pin);
	_delay_ms(BLINK_MS);
}

void blink_uint(int pin, uint16_t i)
{
	for(int d=sizeof(i) - 1; d >=0; d--) {
		uint8_t byte = i >> (d*8);
		uint8_t h = byte >> 4;
		uint8_t l = byte & 0xf;

		if(h == 0)
			long_blink(pin);
		else {
			for(int b=0; b < h; b++)
				blink(pin);

			_delay_ms(DIGIT_PAUSE_MS);
		}

		if(l == 0)
			long_blink(pin);
		else {
			for(int b=0; b < l; b++)
				blink(pin);

			_delay_ms(DIGIT_PAUSE_MS);
		}
	}
}

void blink_bool(int pin, uint8_t b)
{
	if(b)
		blink(pin);
	else
		long_blink(pin);
}

int main () {
	led_setup(LED);
	i2c_init();

	uint16_t moist = 0;
	uint8_t nack = 0;

	while (1) {
		//blink(LED);
		// Address, LSB 0 to write register
		i2c_start();
		nack = i2c_write_byte(0x36 << 1);
		//blink_bool(LED, nack & 1);
		// Register Base (Capacitive Sensor)
		nack = i2c_write_byte(0x0f);
		//blink_bool(LED, nack & 1);
		// Channel
		nack = i2c_write_byte(0x10);
		//blink_bool(LED, nack & 1);
		i2c_stop();
		//blink(LED);
		//

		_delay_ms(30);

		// device address (Read)
		i2c_start();
		nack = i2c_write_byte((0x36 << 1) | 1);
		//blink_bool(LED, nack & 1);
		// Read Register Data
		moist = i2c_read_byte(1) << 8;
		moist |= i2c_read_byte(0);
		i2c_stop();
		blink_uint(LED, moist);
		_delay_ms(2000);
	}
	return 0;
}
