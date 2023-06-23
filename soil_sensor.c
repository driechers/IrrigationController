#include "soil_sensor.h"

void soil_init()
{
	i2c_init();
}

//TODO error handling
uint16_t moisture()
{
	uint16_t moist = 0;
	uint8_t nack = 0;

	// Address, LSB 0 to write register
	i2c_start();
	nack = i2c_write_byte(0x36 << 1);
	// Register Base (Capacitive Sensor)
	nack = i2c_write_byte(0x0f);
	// Channel
	nack = i2c_write_byte(0x10);
	i2c_stop();
	//

	_delay_ms(30);

	// device address (Read)
	i2c_start();
	nack = i2c_write_byte((0x36 << 1) | 1);
	// Read Register Data
	moist = i2c_read_byte(1) << 8;
	moist |= i2c_read_byte(0);
	i2c_stop();

	return moist;
}
