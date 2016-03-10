/*
	
	sleep.c
	Sleep functionality
	attiny85
	
	Daniel Löfström, 2016-02-15
	
*/
#include "sleep.h"

//--------------------------------------------
//
// Pin change interrupt
//
//--------------------------------------------
uint8_t button_interrupt = 0;
ISR(PCINT0_vect) {
	//Set the flag if the button is pressed (not released)
	if (PINB & (1 << PB4)) button_interrupt = 1;
}


//--------------------------------------------
//
// Check if button interrupt is set
//
//--------------------------------------------
uint8_t button_interrupt_get() {
	return button_interrupt;
}

//--------------------------------------------
//
// Button interrupt handled
//
//--------------------------------------------
void button_interrupt_reset() {
	button_interrupt = 0;
}


//--------------------------------------------
//
// Initialize sleep functionality
//
//--------------------------------------------
void sleep_init() {
	////Sleep instructions
	//MCUCR |= (1 << SE); //Sleep enable
	//MCUCR &= ~(1 << SE); //Sleep disable
	//MCUCR |= (1 << SM1) | (0 << SM0); //Power down
	//MCUCR |= (0 << SM1) | (1 << SM0); //ADC Noise Reduction
	
	////Interrupts
	GIMSK |= (1 << PCIE); //External interrupt enable
	PCMSK |= (1 << PCINT4); //Pin change interrupt on PB4
	//sei();
}


//--------------------------------------------
//
// Sleep
// Executes sleep instructions and handles wake up
//
//--------------------------------------------
void sleep() {
	//Enable interrupt
	sei();

	//Enable and execute sleep
	MCUCR |= (1 << SE); //Sleep enable
	MCUCR |= (1 << SM1) | (0 << SM0); //Power down
	//watchdog_enable();
	sleep_cpu();//------ Sleeping here ------
	
	//Disable interrupt
	//cli();
	
	//Disable sleep after wake up
	MCUCR &= ~(1 << SE); //Sleep disable
}