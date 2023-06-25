#include "soil_sensor.h"

void soil_init()
{
	i2c_init();
}

// Returns 0 on error otherwise the sensor value
uint16_t moisture()
{
	uint16_t moist = 0;

	// Address, LSB 0 to write register
	i2c_start();
	if(i2c_write_byte(0x36 << 1) & 0x1)
		return 0;
	// Register Base (Capacitive Sensor)
	if(i2c_write_byte(0x0f) & 0x1)
		return 0;
	// Channel
	if(i2c_write_byte(0x10) & 0x1)
		return 0;
	i2c_stop();
	//

	_delay_ms(30);

	// device address (Read)
	i2c_start();
	if(i2c_write_byte((0x36 << 1) | 1) & 0x1)
		return 0;
	// Read Register Data
	moist = i2c_read_byte(1) << 8;
	moist |= i2c_read_byte(0);
	i2c_stop();

	return moist;
}
