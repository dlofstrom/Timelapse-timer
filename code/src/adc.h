/*
	
	adc.h
	Analog to digital converter
	
	Daniel Löfström, 2016-02-15
	
*/
#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <util/delay.h>

// Initialize ADC
void adc_init();

// Enable ADC
void adc_enable();

// Disable ADC
void adc_disable();

// Read ADC value
uint8_t adc_read();

#endif