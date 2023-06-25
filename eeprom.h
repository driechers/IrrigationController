#ifndef EEPROM_H
#define EEPROM_H

uint8_t EEPROM_read(uint8_t ucAddress);
void EEPROM_write(uint8_t ucAddress, uint8_t ucData);

uint16_t EEPROM_read_word(uint8_t ucAddress);
void EEPROM_write_word(uint8_t ucAddress, uint16_t ucData);

#endif
