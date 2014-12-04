#include <msp430.h>
#include "initialisatie.h"


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


void send_UART0(unsigned char* to_UART){
	volatile unsigned int i; 									// volatile voor de compiler
	volatile unsigned char index;								// index en i zijn iteratievariabelen

	for(index = 0; index < sizeof(to_UART)/sizeof(char); index++){
		//i=20000;while (i>0){i--;} 								// even wachten
		while (!(UCA0IFG&UCTXIFG)); 							// USCI_A0 TX buffer ready?
		UCA0TXBUF = to_UART[index]; 								// stuur data
		P1OUT ^= BIT0; 											// switch led
	}
}

void send_UART(char getal){
	while (!(UCA0IFG&UCTXIFG)); 							// USCI_A0 TX buffer ready?
	UCA0TXBUF = getal; 								// stuur data
	P1OUT ^= BIT0; 											// switch led
}


// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG - interrupts from receiving something
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    send^=1;
    break;
  case 4:break;                             // Vector 4 - TXIFG - interrupts from sending something
  default: break;
  }
}
