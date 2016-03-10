/*
	
	sleep.h
	Sleep functionality
	attiny85
	
	Daniel Löfström, 2016-02-15
	
*/
#ifndef SLEEP_H
#define SLEEP_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Check if button interrupt is set
uint8_t button_interrupt_get();

// Button interrupt handled
void button_interrupt_reset();


// Initialize sleep functionality
void sleep_init();

// Sleep
void sleep();

#endif