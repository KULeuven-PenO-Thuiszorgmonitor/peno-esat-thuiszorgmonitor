#ifndef DECR_H_
#define DECR_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"







void keyexpansion(unsigned char [4][4], unsigned char [4][44]);

void subbytes(unsigned char [4][4]);
void shiftrows(unsigned char [4][4]);
unsigned char multiply(unsigned char, int);
void mixcolumns(unsigned char [4][4]);
void addroundkey(unsigned char [4][4], unsigned char [4][44], int);

void invaddroundkey(unsigned char [4][4], unsigned char [4][44], int);
void invshiftrows(unsigned char [4][4]);
void invsubbytes(unsigned char [4][4]);

void aes(unsigned char [4][4], unsigned char [4][4]);
void invaes(unsigned char [4][4], unsigned char [4][4]);

void rijndael4(unsigned char [4][4]);
void addblock(unsigned char [4][4], unsigned char [4][4]);
void pelican(unsigned char [4][4],unsigned char [], unsigned char [4][4]);

void resetkey(void);
volatile char t;
unsigned char key[4][44];

void opdrachtreceive(unsigned char result[4][8], unsigned char tekst[8]);



void opdrachtsend(unsigned char reslijst[LENGTERES+1], unsigned char result[4][8]);

#endif /* DECR_H_ */
