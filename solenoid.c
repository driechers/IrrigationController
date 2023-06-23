/**
 *  
 * Pulse Solenoid h-bridge driver
 *
 */

#include <avr/io.h>
#include <util/delay.h>

#include "solenoid.h"
#include "config.h"

void solenoid_init()
{
	// setup h-bridge pins for output
	DDRB |= (1 << OPEN);
	DDRB |= (1 << CLOSE);

	// set h-bridge pins HIGH for less current consumption
	PORTB |= (1 << OPEN);
	PORTB |= (1 << CLOSE);
}

void solenoid_open()
{
	// Send Open Pulse
	PORTB &= ~(1 << OPEN);
	_delay_ms(PULSE_MS);
	PORTB |= (1 << OPEN);
}

void solenoid_close()
{
	// Send Close Pulse
	PORTB &= ~(1 << CLOSE);
	_delay_ms(PULSE_MS);
	PORTB |= (1 << CLOSE);
}
