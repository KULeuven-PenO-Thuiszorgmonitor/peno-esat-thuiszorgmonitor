#include <msp430.h>
#include "initialisatie.h"
#include "interrupts.h"

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

void init_ADC(void){
	P2SEL |= BIT0; 						// P2.0 ADC option select
	ADC12CTL0 = ADC12SHT02 + ADC12ON; 	// Sampling time, ADC12 on
	ADC12CTL1 = ADC12SHP; 				// Use sampling timer
	ADC12IE = 0x01; 					// Enable interrupt
	ADC12CTL0 |= ADC12ENC;
}
void init_UART(void){
	PMAPPWD = 0x02D52;					// Get write-access to port mapping regs
	P3MAP1 = PM_UCA0RXD; 				// Map UCA0RXD output to P3.1
	P3MAP0 = PM_UCA0TXD; 				// Map UCA0TXD output to P3.0
	PMAPPWD = 0; 						// Lock port mapping registers

	P3DIR |= BIT0; 						// Set P3.0 as TX output
	P3SEL |= BIT0 + BIT1; 				// Select P3.0 & P3.1 to UART function

	UCA0CTL1 |= UCSWRST; 				// **Put state machine in reset**
	UCA0CTL1 |= UCSSEL_2; 				// SMCLK
	UCA0BR0 = 9; 						// 1MHz 115200 (see User's Guide)
	UCA0BR1 = 0; 						// 1MHz 115200
	UCA0MCTL |= UCBRS_1 + UCBRF_0; 		// Modulation UCBRSx=1, UCBRFx=0
	UCA0CTL1 &= ~UCSWRST; 				// **Initialize USCI state machine**
	UCA0IE |= UCRXIE; 					// Enable USCI_A0 RX interrupt

}
void init_LED(void){
	P1DIR |= BIT0; 						// P1.0 output (LED)
	P2DIR |= BIT3+BIT6+BIT7; 			// de 3 leds als output aanduiden
	P1OUT |= BIT0; 						// LED on
}


