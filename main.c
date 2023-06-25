/**
 *  
 * Irrigation Controller
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include "power_controller.h"
#include "soil_sensor.h"
#include "solenoid.h"
#include "config.h"
#include "eeprom.h"

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

void count_water()
{
	count_offset(2);
}

void count_sensor_fault()
{
	count_offset(4);
}

int main ()
{
	uint16_t moist = 0;

	solenoid_init();
	soil_init();
	power_controller_init();

	count_boot();

	moist = moisture();

	if(moist == 0)
		count_sensor_fault();
	else if(moist < WATER_THRESH)
	{
		solenoid_open();
		_delay_ms(5000);
		solenoid_close();
		count_water();
	}

	_delay_ms(30);

	while(1)
		low_power_mode();

	return 0;
}
