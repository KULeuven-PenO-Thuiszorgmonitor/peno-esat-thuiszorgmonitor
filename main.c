#define versie 1 //0:test 1:pulsoximeter 2:

#include <msp430.h>
#include "initialisatie.h"

#if versie == 0
#include "sensoren/ADC0.h"
#elif versie == 1
#include "sensoren/ADC1.h"
#endif

#include "UART.h"
#include "WDT.h"


int main(void){
	volatile unsigned int i; 				// volatile voor de compiler
	WDT_select();
	init_ADC(); 							// initialiseer de ADC
	init_UART(); 							// initialiseer de UART
	init_LED(); 							// initialiseer de LED's
	send = 0;
	while (1){
		ADC12CTL0 |= ADC12SC; 				// Start sampling/conversion
		__bis_SR_register(GIE); 			// LPM0, ADC12_ISR will force exit
		__no_operation(); 					// For debugger
		i=20000;while(i>0){i--;} 			// even wachten
		if (send){
			send_UART();					// verzend de data
		}
	}
}




void init_LED(void){
	P1DIR |= BIT0; 						// P1.0 output (LED)
	P2DIR |= BIT3+BIT6+BIT7; 			// de 3 leds als output aanduiden
	P1OUT |= BIT0; 						// LED on
}
