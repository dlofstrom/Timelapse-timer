/*
	
	main.c
	
	Low power test project
	attiny85 project
	
	dlofstrom , 2016-02-05
	
*/

#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "sleep.h"
#include "watchdog.h"
#include "lut.h"


void blink_delay(unsigned int ms) {
	unsigned int d;
	for (d=ms; d>0; d--) {
		_delay_ms(100);
	}
}

//Delay variable
uint8_t delay_index = 0;
int delay_value = 0;
int current_delay = 0;

//Initially disabled
uint8_t timelapse_enabled = 0;


int main (void) {
	
	//Setup watchdog and interrupt
	watchdog_init();
	sleep_init();
	
	//ADC
	adc_init();
	
	//LED
	DDRB |= (1 << PB2);
	PORTB &= ~(1 << PB2);
	
	while (1) {
		//Ugly set delay implementation 
		//TODO: Clean up, use sleep instead of delay
		//TODO: ADC resolution sleep
		if (button_interrupt_get()) {
			watchdog_disable();
			timelapse_enabled = 0;
			adc_enable();
			_delay_ms(100);
			
			while (PINB & (1 << PB4)) {
				//Wait for ADC (Slow)
				delay_index = adc_read();
				
				//Lookup delay value
				delay_value = get_lut_value(delay_index);
				
				///Blink the read delay
				//Disabled
				if (delay_value == DISABLED) {
					PORTB |= (1 << PB2);
					_delay_ms(500);
				}
				//0-10s blink once
				else if (delay_value < 100) {
					PORTB |= (1 << PB2);
					_delay_ms(100);
					PORTB &= ~(1 << PB2);
					blink_delay(delay_value-1);
				}
				//10-100s blink twice
				else if (delay_value < 1000) {
					PORTB |= (1 << PB2);
					_delay_ms(100);
					PORTB &= ~(1 << PB2);
					_delay_ms(100);
					PORTB |= (1 << PB2);
					_delay_ms(100);
					PORTB &= ~(1 << PB2);
					blink_delay(delay_value/10-3);
				}
				//100-1000s blink tree times
				else {
					PORTB |= (1 << PB2);
					_delay_ms(100);
					PORTB &= ~(1 << PB2);
					_delay_ms(100);
					PORTB |= (1 << PB2);
					_delay_ms(100);
					PORTB &= ~(1 << PB2);
					_delay_ms(100);
					PORTB |= (1 << PB2);
					_delay_ms(100);
					PORTB &= ~(1 << PB2);
					blink_delay(delay_value/100-5);
				}
				
			}
			
			current_delay = delay_value/10;
			
			//Disable ADC
			adc_disable();
			
			if (delay_value != DISABLED) {
				//Enable timer i not disabled
				watchdog_enable();
				//Enabled after first button press
				timelapse_enabled = 1;
			} else {
				PORTB &= ~(1 << PB2);
			}
			
			//Interrupt handled
			button_interrupt_reset();
		}
		
		
		
		//Initially disabled
		if (timelapse_enabled) {
			//Count down to 0
			if (current_delay > 0) {
				current_delay -= watchdog_set_delay(current_delay);
			} else {
				current_delay = delay_value/10;
				
				//Flash LED at proper delay
				//Pin change for low power
				PORTB |= (1 << PB2);
				PORTB &= ~(1 << PB1); //Port always set to 0
				DDRB |= (1 << PB1); //Sink - output low
				_delay_ms(200);
				PORTB &= ~(1 << PB2);
				DDRB &= ~(1 << PB1); //Tri-state - pulled up by camera

				
			}
			
			
			
		}
		
		//Go to sleep
		sleep();
		
	}
	
	return 1;
}
























