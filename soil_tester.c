#include <avr/io.h>
#include <util/delay.h>

#include "power_controller.h"
#include "soil_sensor.h"
#include "eeprom.h"

/*
 * READ first byte of eeprom to use as index.
 * WRITE two bytes read from sensor at index.
 */
int main () {
	soil_init();

	uint16_t moist = moisture();
	
	uint8_t index = EEPROM_read(0);

	if(index == 0x00 || index == 0xff)
		index = 1;

	EEPROM_write(index+1, moist & 0xff);
	moist >>= 8;
	EEPROM_write(index, moist & 0xff);
	EEPROM_write(0, index+2);

	_delay_ms(30);

	low_power_mode();

	return 0;
}
