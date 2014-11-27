#include <msp430.h>
#include "initialisatie.h"
#include "sensoren/ADC1.h"

#include "UART.h"
#include "WDT.h"
#include "RF.h"


int main(void){
	volatile unsigned int i; 				// volatile voor de compiler
	WDT_select();
	init_ADC(); 							// initialiseer de ADC
	init_UART(); 							// initialiseer de UART
	init_LED(); 							// initialiseer de LED's
	init_RF();								// initialiseer de radio
	send = 0;
	ADCcounter=0;

	while(1){
		ADC12CTL0 |= ADC12SC; 					// Start sampling/conversion
		while (ADCcounter<400){
			__bis_SR_register(GIE); 			// LPM0, ADC12_ISR will force exit
			__no_operation(); 					// For debugger
		}
		ADC12CTL0 ^= ADC12SC; 					// Stop sampling/conversion


	}
}




void init_LED(void){
	P1DIR |= BIT0+BIT1+BIT2; 			// P1.0 output (LED)
	P2DIR |= BIT3+BIT6+BIT7; 			// de 3 leds als output aanduiden
	P1OUT |= BIT0+BIT1; 						// LED on
}
