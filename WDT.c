#define versie 1
#include <msp430.h>

void WDT_select(void){
#if versie == 1
	WDTCTL = (WDTPW+WDTTMSEL+WDTCNTCL+ 0x0003);// WDT 32ms, SMCLK, interval timer
	SFRIE1 |= WDTIE;                          // Enable WDT interrupt
	__bis_SR_register(GIE);					  // Enable algemene interrupts
#else
	WDTCTL = WDTPW + WDTHOLD; 				// Stop WDT
#endif
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	__no_operation();
}

