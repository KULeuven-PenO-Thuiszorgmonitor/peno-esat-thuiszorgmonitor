#include "initialisatie.h"

#if SENSOR_VERSIE == 9
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
		int uitkomst_analyse =  analyse1(result);
		if (send){
			send_UART(uitkomst_analyse);
		}

		//verzending
	}
}

#elif SENSOR_VERSIE ==1

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
//	init_UART(); 							// initialiseer de UART
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
		int uitkomst_analyse =  analyse1(result);
		hartslag[0] = (char) uitkomst_analyse;
		opdrachtsend(hartslag, matrix);
		matrix2list(matrix,to_send);
		//verzending
	}
}


#elif SENSOR_VERSIE == 10
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
//	init_UART(); 							// initialiseer de UART
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


#elif SENSOR_VERSIE == 90
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
	while(1){
		while (ADCcounter<10){
		__bis_SR_register(GIE); 			// LPM0, ADC12_ISR will force exit
		__no_operation(); 					// For debugger
		}
	ADCcounter=0;
	send_UART0(to_encrypt);
	}


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

void Cbit_2_8bit(unsigned int a[10],unsigned char b[15]){
	volatile char i;
	volatile char j=0;
	for (i=0;i<10;i++){
		if(!i%2){
			b[j]  =a[i]>>4;
			b[j+1]=a[i]<<4;
			j++;
		}else{
			b[j] +=a[i]>>8;
			b[j+1]=a[i];
			j+=2;
		}
	}
}

void bit8_2_bitC(unsigned char a[15],unsigned int b[10]){
	volatile char i;
	volatile char j=0;
		for (i=0;i<10;i++){
			if(!i%2){
				b[i]=(int)a[j]  <<4;
				b[i]+=a[j+1]>>4;
				j++;
			}else{
				b[i]=(int)a[j]<<8;
				b[i]+=a[j+1];
				j+=2;
			}
		}
}

void init_LED(void){
	P1DIR |= BIT0+BIT1+BIT2; 			// P1.0 output (LED)
	P2DIR |= BIT3+BIT6+BIT7; 			// de 3 leds als output aanduiden
	P1OUT |= BIT0+BIT1; 						// LED on
}
