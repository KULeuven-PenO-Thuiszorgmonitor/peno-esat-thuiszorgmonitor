//yolo
#include <msp430.h>
#include "initialisatie.h"
#include "ADC.h"
#include "UART.h"

int main(void){
	volatile unsigned int i; 				// volatile voor de compiler
	WDTCTL = WDTPW + WDTHOLD; 				// Stop WDT
	init_ADC(); 							// initialiseer de ADC
	init_UART(); 							// initialiseer de UART
	init_LED(); 							// initialiseer de LED's
	send = 0;
	while (1){
		ADC12CTL0 |= ADC12SC; 				// Start sampling/conversion
		__bis_SR_register(GIE); 			// LPM0, ADC12_ISR will force exit
		__no_operation(); 					// For debugger
		i=0;while (i<20000){i++;} 			// even wachten
		if (send){
			while (!(UCA0IFG&UCTXIFG)); 	// USCI_A0 TX buffer ready?
			UCA0TXBUF = result[0]; 			// stuur eerste deel data
			P1OUT ^= BIT0; 					// switch led
			i=0;while (i<20000){i++;} 		// even wachten
			while (!(UCA0IFG&UCTXIFG)); 	// USCI_A0 TX buffer ready?
			UCA0TXBUF = result[1]; 			// stuur tweede deel data
		}
	}
}



void init_LED(void){
	P1DIR |= BIT0; 						// P1.0 output (LED)
	P2DIR |= BIT3+BIT6+BIT7; 			// de 3 leds als output aanduiden
	P1OUT |= BIT0; 						// LED on
}
