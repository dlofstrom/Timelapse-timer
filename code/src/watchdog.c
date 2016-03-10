/*
	
	watchdog.c
	Watchdog timer functionality
	attiny85
	
	Daniel Löfström, 2016-02-15
	
*/
#include "watchdog.h"


//--------------------------------------------
//
// Watchdog interrupt routine
//
//--------------------------------------------
ISR(WDT_vect) {
	//Reset interrupt
	//WDIE is cleared after each interrupt
	//this has to be set every time to avoid reset (sec 8.5.2)
	WDTCR |= (1 << WDIE); //Watchdog interrupt enabled
}


//--------------------------------------------
//
// Set watchdog delay
// TODO: Fix this so that the microcontroller sleeps as long as possible
//
//--------------------------------------------
uint8_t watchdog_set_delay(int wd_del) {
	//Watchdog timer control
	WDTCR |= (1 << WDCE); //Watchdog change enabled
	
	//WDTCR |= (1 << WDIE); //Watchdog interrupt enabled
	
	/* 	
	WDP3	WDP2	WDP1	WDP0	WDT Cyc			Typ Time-out (5.0V)
	0		0		0		0		2k (2048)		16 ms
	0		0		0		1		4K (4096)		32 ms
	0		0		1		0		8K (8192)		64 ms
	0		0		1		1		16K (16384)		0.125 s
	0		1		0		0	 	32K (32764)		0.25 s
	0		1		0		1		64K (65536)		0.5 s
	0		1		1		0		128K (131072)	1.0 s
	0		1		1		1		256K (262144)	2.0 s
	1		0		0		0		512K (524288)	4.0 s
	1		0		0		1		1024K (1048576)	8.0 s
	1		0		1		0		Reserved
	1		0		1		1		Reserved
	1		1		0		0		Reserved
	1		1		0		1		Reserved
	1		1		1		0		Reserved
	1		1		1		1		Reserved
	*/	
	//WDTCR |= (1 << WDP3) | (0 << WDP2) | (0 << WDP1) | (1 << WDP0); //8 s
	WDTCR &= ~((1 << WDP3) | (1 << WDP0)); //1 s
	WDTCR |= (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0); //1 s
	WDTCR &= ~(1 << WDCE); //Watchdog change disabled
	
	return 1;
}


//--------------------------------------------
//
// Initialize watchdog
//
//--------------------------------------------
void watchdog_init() {
	//Power Reduction Register
	PRR |= (1 << PRTIM1) | (1 << PRTIM0) | (1 << PRUSI);//All but | (1 << PRADC);
	//PRR |= (1 << PRADC); //Power Reduction ADC
	//PRR &= ~(0 << PRADC); //Power Reduction enable ADC
	
	//Base delay
	watchdog_set_delay(8);
}

//--------------------------------------------
//
// Enable watchdog
//
//--------------------------------------------
void watchdog_enable() {
	//Watchdog change enabled
	WDTCR |= (1 << WDCE);
	
	//Watchdog enabled, Watchdog interrupt enabled
	WDTCR |= (1 << WDE) | (1 << WDIE);
	
	//Watchdog change disabled
	WDTCR &= ~(1 << WDCE);
}

//--------------------------------------------
//
// Disable watchdog
//
//--------------------------------------------
void watchdog_disable() {
	//Flags cleared
	MCUSR = 0x00;
	
	//Watchdog change enabled and Watchdog enabled at the same time to disable
	WDTCR |= (1 << WDCE)  | (1 << WDE);
	
	//Watchdog disabled
	WDTCR &= ~((1 << WDCE) | (1 << WDE) | (1 << WDIE));
}