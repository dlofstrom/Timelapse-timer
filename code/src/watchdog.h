/*
	
	watchdog.h
	Watchdog timer functionality
	attiny85
	
	Daniel Löfström, 2016-02-15
	
*/
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Set watchdog delay
uint8_t watchdog_set_delay(int wd_del);

// Initialize watchdog
void watchdog_init();

// Enable watchdog
void watchdog_enable();

// Disable watchdog
void watchdog_disable();

#endif