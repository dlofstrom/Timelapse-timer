/*
	
	adc.c
	Analog to digital converter
	
	Daniel Löfström, 2016-02-15
	
*/
#include "adc.h"

//--------------------------------------------
//
// Initialize ADC
// TODO: generalize for any pin
//
//--------------------------------------------
void adc_init() {
	//Left adjusted and ADC3 (PB3)
	ADMUX |= (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);
	
	//64 prescaler for good resolution (in the <200kHz range)
	ADCSRA |= (1 << ADPS1) | (1 << ADPS2);
}

//--------------------------------------------
//
// Enable ADC
//
//--------------------------------------------
void adc_enable() {
	//PRR &= ~(0 << PRADC); //Power Reduction enable ADC timer
	ADCSRA |= (1 << ADEN); //Enable ADC
}

//--------------------------------------------
//
// Disable ADC
//
//--------------------------------------------
void adc_disable() {
	ADCSRA &= ~(1 << ADEN); //Disable ADC
	//PRR |= (1 << PRADC); //Power Reduction disable ADC timer
}

//--------------------------------------------
//
// Read ADC value
// This is slow
// TODO: Change this to an interrupt version instead
//
//--------------------------------------------
uint8_t adc_read() {
	//Start ADC conversion
	ADCSRA |= (1<<ADSC);
	_delay_ms(10);
	
	//Wait for conversion
	while (!(ADCSRA & (1<<ADIF)));
	
	//Save value
	return ADCH;
}