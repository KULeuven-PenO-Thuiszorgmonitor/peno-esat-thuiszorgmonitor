#ifndef INITIALISATIE_H_
#define INITIALISATIE_H_


volatile char result[2];
volatile unsigned int adcgeheugen;
volatile unsigned int send;
void init_ADC(void);
void init_UART(void);
void init_LED(void);

#endif /* INITIALISATIE_H_ */
