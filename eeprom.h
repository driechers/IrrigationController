#ifndef EEPROM_H
#define EEPROM_H

unsigned char EEPROM_read(unsigned char ucAddress);
void EEPROM_write(unsigned char ucAddress, unsigned char ucData);

#endif
