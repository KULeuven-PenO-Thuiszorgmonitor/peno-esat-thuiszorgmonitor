#include <msp430.h>
#include "../initialisatie.h"
#include "../UART.h"

void init_ADC(void){
	P2SEL |= BIT0; 						// P2.0 ADC option select
	ADC12CTL0|= ADC12SHT0_13; 			// Sampling time (1024) , ADC12 on
	ADC12CTL1|=ADC12CSTARTADD_0;
	ADC12CTL1 = ADC12SHP; 				// Use sampling timer
	ADC12IE = 0x01; 					// Enable interrupt
	ADC12CTL2|=ADC12PDIV;				// deelt de klokfreq van 5MHz door 4. hierna nog eens delen!!
	ADC12CTL1|=ADC12DIV_7;				// deelt de klokfreq nog eens door 8
	ADC12CTL1|=ADC12CONSEQ_2; 			// zet de adc in Repeat-single-channel modus > hierna pas ADC12ON
	ADC12CTL0|=ADC12ON;
	ADC12CTL0|=ADC12MSC;
	ADC12CTL0 |= ADC12ENC;				// dit moet als laatste!!


}


#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    adcgeheugen=ADC12MEM0;
	result[0]=adcgeheugen;
	result[1]=adcgeheugen>>8;
	if (send){
		send_UART();					// verzend de data
	}
  //  __bic_SR_register_on_exit(LPM0_bits);   // Exit active CPU

  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}
