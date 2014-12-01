#ifndef INITIALISATIE_H_
#define INITIALISATIE_H_


volatile char result[400];
volatile unsigned int adcgeheugen;
volatile unsigned int send;
volatile unsigned int ADCcounter;
unsigned char hartslag[1];
unsigned char matrix[4][8];
void list2matrix(char* input[32],char* output[4][8]);
void matrix2list(char* input[4][8],char* output[32]);
char to_send[32];

void init_LED(void);

#endif /* INITIALISATIE_H_ */
