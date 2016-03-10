# 
# Makefile for attiny85
# Daniel Löfström, 2015-11-10
# 
# Compiles all .c files in src autlomatically
# 
# make clean - removes build files
# make - compiles source code
# make flash - programs the microcontroller
# make fuse - sets the fuses
# make install - all above
# 


DEVICE 		= attiny85
CLOCK      	= 8000000
#PROGRAMMER	= dragon_isp
PROGRAMMER	= avrisp
#PORT 		= /dev/tty.usbmodem411 -v -v -v -F -b 19200
#PORT 		= usb
PORT		= COM5 
BAUD		= 19200

FLASH		= -U flash:w:bin/main.hex:i
FUSES 		= -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m


CFLAGS	= -g -mmcu=$(DEVICE) -DF_CPU=$(CLOCK) -Os -Wall
COMPILE	= avr-gcc $(CFLAGS)

ADFLAGS	= -c $(PROGRAMMER) -p $(DEVICE) -P $(PORT) -b $(BAUD)
AVRDUDE = avrdude $(ADFLAGS)

SOURCES	= $(wildcard src/*.c)
OBJECTS	= $(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all:	bin/main.hex

#.c.o:
obj/%.o: src/%.c
	$(COMPILE) -c $< -o $@


install: all
	$(AVRDUDE) $(FLASH) $(FUSES)

flash:  all
	$(AVRDUDE) $(FLASH)

fuse:
	$(AVRDUDE) $(FUSES)

clean:
	rm -f bin/main.hex bin/main.elf $(OBJECTS) *~
	
bin/main.elf: $(OBJECTS)
	$(COMPILE) -o bin/main.elf $(OBJECTS)
 
bin/main.hex: bin/main.elf
	rm -f bin/main.hex
	avr-objcopy -j .text -j .data -O ihex bin/main.elf bin/main.hex	


	