#include "WDT.h"
#include "defines.h"

void WDT_select(void){
#if WDT_VERSIE == 1
	WDTCTL = (WDTPW+WDTTMSEL+WDTCNTCL+ 0x0003);// WDT ..ms, SMCLK, interval timer
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
	P1OUT ^= BIT1+BIT2;
	P2OUT ^= BIT3;
}

