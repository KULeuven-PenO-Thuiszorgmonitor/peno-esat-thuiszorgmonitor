#ifndef INITIALISATIE_H_
#define INITIALISATIE_H_


char result[400]; // fix dit char bij ver10. char nodig voor bitsshift en grootte is 10
volatile unsigned int adcgeheugen;
volatile unsigned int send;
volatile unsigned int ADCcounter;
unsigned char hartslag[1];
unsigned char to_encrypt[15];
unsigned char matrix[4][8];
unsigned char to_send[32];
void list2matrix(char input[32],char output[4][8]);
void matrix2list(unsigned char input[4][8],unsigned char output[32]);
//void Cbit_2_8bit(unsigned char a[10],unsigned char b[15]);
void init_LED(void);

#endif /* INITIALISATIE_H_ */
