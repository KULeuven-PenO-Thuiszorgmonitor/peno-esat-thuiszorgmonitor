#define VERSIE 10
//1:hartslagmonitor analyse
//10:hartslagmonitor ruw

#include <msp430.h>
#include "initialisatie.h"

#if VERSIE == 0
#elif VERSIE ==1

#include "sensoren/ADC1.h"
#include "UART.h"
#include "WDT.h"
#include "RF.h"
#include "analyse.h"
#include "CRYPT.h"

int main(void){
	volatile unsigned int i; 				// volatile voor de compiler
	WDT_select();
	init_ADC(); 							// initialiseer de ADC
	init_UART(); 							// initialiseer de UART
	init_LED(); 							// initialiseer de LED's
	send = 0;
	ADCcounter=0;
	while(1){
		ADC12CTL0 |= ADC12SC; 					// Start sampling/conversion
		while (ADCcounter<400){
			__bis_SR_register(GIE); 			// LPM0, ADC12_ISR will force exit
			__no_operation(); 					// For debugger
		}
		ADC12CTL0 ^= ADC12SC; 					// Stop sampling/conversion
		ADCcounter = 0;
		hartslag[0] = analyse1(result);
		opdrachtsend(hartslag, matrix);
		matrix2list(matrix,to_send);
		//verzending
	}
}


#elif VERSIE == 10
#include "sensoren/ADC1.h"
#include "UART.h"
#include "WDT.h"
#include "RF.h"
#include "analyse.h"
#include "CRYPT.h"

int main(void){
	volatile unsigned int i; 				// volatile voor de compiler
	WDT_select();
	init_ADC(); 							// initialiseer de ADC
	init_UART(); 							// initialiseer de UART
	init_LED(); 							// initialiseer de LED's
	init_RF();								// initialiseer de radio
	send = 0;
	ADCcounter=0;
	ADC12CTL0 |= ADC12SC; 					// Start sampling/conversion
		while (ADCcounter<10){
			__bis_SR_register(GIE); 			// LPM0, ADC12_ISR will force exit
			__no_operation(); 					// For debugger
		}
	ADCcounter=0;
//	Cbit_2_8bit(result,to_encrypt);
	opdrachtsend(to_encrypt,matrix);
	matrix2list(matrix,to_send);
	//verzending
}
#else
#endif


void matrix2list(unsigned char input[4][8],unsigned char output[32]){
	volatile unsigned int j;
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			output[8*i+j] = input[i][j];
		}
	}
}
void list2matrix(char input[32],char output[4][8]){
    for(i=0;i<32;i++){
    	output[i/4][i%4]= input[i];
    }
}

//void Cbit_2_8bit(char a[10],unsigned char b[15]){
//	volatile char i;
//	volatile char j=0;
//	for (i=0;i<10;i++){
//		if(!i%2){
//			b[j]  =a[i]>>4;
//			b[j+1]=a[i]<<4;
//			j++;
//		}else{
//			b[j] +=a[i]>>8;
//			b[j+1]=a[i];
//			j+=2;
//		}
//	}
//}

void init_LED(void){
	P1DIR |= BIT0+BIT1+BIT2; 			// P1.0 output (LED)
	P2DIR |= BIT3+BIT6+BIT7; 			// de 3 leds als output aanduiden
	P1OUT |= BIT0+BIT1; 						// LED on
}
