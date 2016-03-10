/*
	
	lut.h
	Look-up table in flash memory
	
	Daniel Löfström, 2016-02-15
	
*/
#ifndef LUT_H
#define LUT_H

#include <avr/io.h>
#include <avr/pgmspace.h>

#define DELAY_LUT_SIZE 256
#define DISABLED -1
	
// Get LUT value
int get_lut_value(uint8_t ind);
	
#endif