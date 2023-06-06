/**
 *  
 * Pulse Solenoid Demo Code
 *
 */

#include <avr/io.h>
// F_CPU frequency to be defined at command line
#include <util/delay.h>

// LED is on pin 2, PB3
#define OPEN      PB3
#define CLOSE     PB4
#define PULSE_MS 30
#define DELAY_MS 1000

int main () {
	uint8_t open = 0;
	uint16_t ms = 0;

	// setup h-bridge pins for output in port B's direction register
	DDRB |= (1 << OPEN);
	DDRB |= (1 << CLOSE);

	// set h-bridge pin HIGH
	PORTB |= (1 << OPEN);
	PORTB |= (1 << CLOSE);

	while (1) {	
		open = !open;

		if (open) {
			// Send Open Pulse
			PORTB &= ~(1 << OPEN);
			_delay_ms(PULSE_MS);
			PORTB |= (1 << OPEN);
		} else {
			// Send Close Pulse
			PORTB &= ~(1 << CLOSE);
			_delay_ms(PULSE_MS);
			PORTB |= (1 << CLOSE);
		}

		// delay for between open and close
		for (ms = DELAY_MS; ms > 0; ms -= 10) {
			_delay_ms(10);
		}
	}

	return 0;
}
