#include <avr/io.h>
#include <util/delay.h>

#include "power_controller.h"
#include "config.h"

void power_controller_init()
{
	// Set uC done pin to output
	DDRB |= (1 << DONE);

	// Ensure it is low
	PORTB &= ~(1 << DONE);
}

void low_power_mode()
{
	PORTB |= (1 << DONE);
	_delay_ms(30);
	PORTB &= ~(1 << DONE);
	_delay_ms(30);
}
