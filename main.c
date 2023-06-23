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

int main ()
{
	uint16_t moist = 0;

	solenoid_init();
	soil_init();
	power_controller_init();

	moist = moisture();

	if(moist < WATER_THRESH)
	{
		solenoid_open();
		_delay_ms(5000);
		solenoid_close();
	}

	while(1)
		low_power_mode();

	return 0;
}
