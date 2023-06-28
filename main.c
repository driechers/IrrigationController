/**
 *  
 * Irrigation Controller
 *
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "power_controller.h"
#include "soil_sensor.h"
#include "solenoid.h"
#include "config.h"
#include "eeprom.h"

// On Watchdog Reset ensure the water is turned
// off then put the board in low power mode
ISR (WDT_vect)
{
	//WDTCR |= 1 << WDCE | 1 << WDE;
	//WDTCR = 0;

	// Close it three times to be more certain
	solenoid_close();
	_delay_ms(1000);
	solenoid_close();
	_delay_ms(1000);
	solenoid_close();

	low_power_mode();
}

void watchdog_init()
{
	cli();
	WDTCR |= 1 << WDCE | 1 << WDE;
	WDTCR = 1 << WDIE | 1 << WDP3 | 1 << WDP0;
	sei();
}

void count_offset(uint8_t offset)
{
	uint16_t count = EEPROM_read_word(offset);

	if(count == 0xffff)
		count = 0;

	EEPROM_write_word(offset, count+1);
}

void count_boot()
{
	count_offset(0);
}

void count_shutdown()
{
	count_offset(2);
}

void count_water()
{
	count_offset(4);
}

void count_sensor_fault()
{
	count_offset(6);
}

int main ()
{
	uint16_t moist = 0;

	solenoid_init();
	soil_init();
	power_controller_init();
	watchdog_init();

	count_boot();

	moist = moisture();

	if(moist == 0)
		count_sensor_fault();
	else if(moist < WATER_THRESH)
	{
		solenoid_open();
		for(int t=0; t < WATER_TIME_S; t++)
		{
			_delay_ms(1000);
			wdt_reset();
		}

		// Close it three times to be more certain
		solenoid_close();
		_delay_ms(1000);
		solenoid_close();
		_delay_ms(1000);
		solenoid_close();
		count_water();
	}

	count_shutdown();
	_delay_ms(30);

	low_power_mode();

	return 0;
}
