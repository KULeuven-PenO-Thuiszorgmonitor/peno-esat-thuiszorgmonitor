#ifndef ADC1_H_
#define ADC1_H_

void init_ADC(void);
__interrupt void ADC12_ISR(void);
int adcgeheugen;

#endif /* ADC1_H_ */
