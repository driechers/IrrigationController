#
# Makefile template for ATtiny45
# Derived from AVR Crosspack template
#

DEVICE     = attiny85           # See avr-help for all possible devices
CLOCK      = 1000000            # 1Mhz
PROGRAMMER = -c usbtiny -P usb  # For using Adafruit USBtiny
OBJECTS    = main.o i2c_primary.o
#FUSES      = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m  # settings as taken from http://www.engbedded.com/fusecalc/

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all: main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash: all
	$(AVRDUDE) -U flash:w:main.hex:i

#fuse:
#$(AVRDUDE) $(FUSES)

install: flash

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

# Targets for code debugging and analysis:
disasm: main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
