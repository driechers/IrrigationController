
#include <avr/io.h>

uint8_t EEPROM_read(uint8_t ucAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));

	/* Set up address register */
	EEAR = ucAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_write(uint8_t ucAddress, uint8_t ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));

	/* Set Programming mode */
	EECR = (0<<EEPM1)|(0<<EEPM0);
	/* Set up address and data registers */
	EEAR = ucAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}

uint16_t EEPROM_read_word(uint8_t ucAddress)
{
	return EEPROM_read(ucAddress) << 8 |
		EEPROM_read(ucAddress + 1);
}

void EEPROM_write_word(uint8_t ucAddress, uint16_t ucData)
{
	EEPROM_write(ucAddress, ucData >> 8);
	EEPROM_write(ucAddress + 1, ucData & 0xff);
}
