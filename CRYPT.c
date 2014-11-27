#include "CRYPT.h"
#define LENGTERES 2
/*
int maine (void)
{       unsigned char result[4][8];
        unsigned char ch1,ch2;
        char tekst[8];
// De gegevens die we binnenkrijgen.
        ch1 = 'x';
        ch2 = 'y';

        opdrachtsend(ch1, ch2, result);
// Het is deze result die moet verdergestuurd worden.
    return 0;
}

int maines (void)
{	// De gegevens die we binnenkrijgen na draadloze verzending.
	unsigned char result[4][8] = {
	{0xc2u, 0x0bu, 0x99u, 0x58u, 0x46u, 0xf8u, 0x05u, 0xc8u},
	{0xa1u, 0xbdu, 0x1au, 0x15u, 0x28u, 0xc0u, 0xc5u, 0x28u},
	{0x77u, 0x60u, 0xfdu, 0xb0u, 0xcbu, 0xbfu, 0x70u, 0x45u},
	{0x60u, 0x0au, 0x1cu, 0x2cu, 0xd7u, 0x79u, 0x7eu, 0x00u}};

   	unsigned char ch1,ch2;
   	char tekst[8];

   	opdrachtreceive(result, tekst);
   	printf("%s \n", tekst);
// Het resultaat na decryptie: ofwel de boodschap, ofwel 'error!'
// indien iets fout gelopen is.
    return 0;
}
*/
void resetkey(void)
{	nokey = 1;
}

unsigned char multiply(unsigned char code, int mult)
{
  unsigned char temp;
  switch (mult)
  { case 1: return code;
    case 2: { temp = code & 0x80u;
              code = code << 1;
              if (temp)
                 {return (code ^ 0x1bu);
                 }
                 else
                 return code;
            }
    case 3: return (code ^ multiply(code, 2));
    case 9: return (code ^ multiply(multiply(multiply(code, 2), 2), 2));
    case 11: return (multiply((multiply((multiply(code, 2)), 2) ^ code), 2) ^ code);
    case 13: return (multiply((multiply((multiply(code,2) ^ code),2)), 2) ^ code);
    case 14: return (multiply((multiply((multiply(code,2) ^ code), 2) ^ code), 2));
    default: return code;
  }
}

void subbytes(unsigned char data[4][4])
{ int row, column, rowp, columnp;
  unsigned char temp;
  for (row = 0; row<4; row++)
      {    for (column = 0; column <4; column++)
               { temp = data[row][column];
                 rowp = (int)((temp & 0xf0u)>>4);
                 columnp = (int)(temp & 0x0fu);
                 data[row][column] = submatrix[rowp][columnp];
               }
      }
}

void invsubbytes (unsigned char data[4][4])
{ int row, column, rowp, columnp;
  unsigned char temp;
  for (row = 0; row<4; row++)
      {    for (column = 0; column <4; column++)
               { temp = data[row][column];
              	 rowp = (int)((temp & 0xf0u)>>4);
                 columnp = (int)(temp & 0x0fu);
                 data[row][column] = invsbox[rowp][columnp];
               }
      }
}

void shiftrows(unsigned char data[4][4])
{ unsigned char temp;
  temp=data[1][0];
  data[1][0]=data[1][1];
  data[1][1]=data[1][2];
  data[1][2]=data[1][3];
  data[1][3]=temp;
  temp=data[2][0];
  data[2][0]=data[2][2];
  data[2][2]=temp;
  temp=data[2][1];
  data[2][1]=data[2][3];
  data[2][3]=temp;
  temp=data[3][3];
  data[3][3]=data[3][2];
  data[3][2]=data[3][1];
  data[3][1]=data[3][0];
  data[3][0]=temp;
}

void invshiftrows(unsigned char data[4][4])
{ unsigned char temp;
  temp=data[1][3];
  data[1][3]=data[1][2];
  data[1][2]=data[1][1];
  data[1][1]=data[1][0];
  data[1][0]=temp;
  temp=data[2][0];
  data[2][0]=data[2][2];
  data[2][2]=temp;
  temp=data[2][1];
  data[2][1]=data[2][3];
  data[2][3]=temp;
  temp=data[3][0];
  data[3][0]=data[3][1];
  data[3][1]=data[3][2];
  data[3][2]=data[3][3];
  data[3][3]=temp;
}


void mixcolumns(unsigned char data[4][4])
{ int column;
  unsigned char temp[4];
  for (column = 0; column<4; column++)
      { temp[0] =  multiply(data[0][column],2) ^
                   multiply(data[1][column],3) ^
                   data[2][column] ^ data[3][column];
        temp[1] =  data[0][column] ^ data[3][column] ^
                   multiply(data[1][column],2) ^
                   multiply(data[2][column],3);
        temp[2] =  data[0][column] ^ data[1][column] ^
                   multiply(data[2][column],2) ^
                   multiply(data[3][column],3);
        temp[3] =  data[1][column] ^ data[2][column] ^
                   multiply(data[0][column],3) ^
                   multiply(data[3][column],2);
        data[0][column] = temp[0];
        data[1][column] = temp[1];
        data[2][column] = temp[2];
        data[3][column] = temp[3];
      }
}

void invmixcolumns(unsigned char data[4][4])
{ int column;
  unsigned char temp[4];
  for (column = 0; column<4; column++)
      { temp[0] =  multiply(data[0][column],14) ^
                   multiply(data[1][column],11) ^
                   multiply(data[2][column],13) ^
                   multiply(data[3][column],9);
        temp[1] =  multiply(data[0][column],9) ^
                   multiply(data[1][column],14) ^
                   multiply(data[2][column],11) ^
                   multiply(data[3][column],13);
        temp[2] =  multiply(data[0][column],13) ^
                   multiply(data[1][column],9) ^
                   multiply(data[2][column],14) ^
                   multiply(data[3][column],11);
        temp[3] =  multiply(data[0][column],11) ^
                   multiply(data[1][column],13) ^
                   multiply(data[2][column],9) ^
                   multiply(data[3][column],14);
        data[0][column] = temp[0];
        data[1][column] = temp[1];
        data[2][column] = temp[2];
        data[3][column] = temp[3];
      }
}

void keyexpansion(unsigned char word[4][4], unsigned char key[4][44])
{ unsigned char temp[4], temp2;
  int row, column, rowp, columnp;
  for (row = 0; row<4; row++)
      {    for (column = 0; column <4; column++)
               key[row][column] = word[row][column];
      }
  for (column = 4; column < 44; column++)
      {
	  	   temp[0] = key[0][column-1];
           temp[1] = key[1][column-1];
           temp[2] = key[2][column-1];
           temp[3] = key[3][column-1];
           if (!(column & 0x3))
              {
                 temp2   = temp[0];
                 temp[0] = temp[1];
                 temp[1] = temp[2];
                 temp[2] = temp[3];
                 temp[3] = temp2;

                 rowp = (int)((temp[0] & 0xf0u)>>4);
                 columnp = (int)(temp[0] & 0x0fu);
                 temp[0] = submatrix[rowp][columnp];
                 rowp = (int)((temp[1] & 0xf0u)>>4);
                 columnp = (int)(temp[1] & 0x0fu);
                 temp[1] = submatrix[rowp][columnp];
                 rowp = (int)((temp[2] & 0xf0u)>>4);
                 columnp = (int)(temp[2] & 0x0fu);
                 temp[2] = submatrix[rowp][columnp];
                 rowp = (int)((temp[3] & 0xf0u)>>4);
                 columnp = (int)(temp[3] & 0x0fu);
                 temp[3] = submatrix[rowp][columnp];

                 columnp = (column / 4) - 1;
                 temp[0] = temp[0] ^ rc[columnp];
              }
            key[0][column] = key[0][column-4] ^ temp[0];
            key[1][column] = key[1][column-4] ^ temp[1];
            key[2][column] = key[2][column-4] ^ temp[2];
            key[3][column] = key[3][column-4] ^ temp[3];
      }
}

void addroundkey(unsigned char data[4][4], unsigned char key[4][44], int round)
{    int row, column, column4;
     for (column = 0; column <4; column++)
      {
      		column4 = round<<2 + column;
           for (row = 0; row<4; row++)
               data[row][column] = data[row][column] ^ key[row][column4];
      }
}

void aes(unsigned char data[4][4], unsigned char code[4][4])
{
 	int round;
 	if (nokey)
	 {	keyexpansion(code, key);
	 	nokey = 0;
	 }

	addroundkey(data, key, 0);

	for (round=1; round<10; round++)
	{	subbytes(data);
		shiftrows(data);
		mixcolumns(data);
		addroundkey(data, key, round);
	}

	subbytes(data);
	shiftrows(data);
	addroundkey(data, key, 10);
}

void invaes(unsigned char data[4][4], unsigned char code[4][4])
{	int round;

 	if (nokey)
	 {	keyexpansion(code, key);
	 	nokey = 0;
	 }

	addroundkey(data, key, 10);
	invshiftrows(data);
	invsubbytes(data);

	for (round=9; round>0; round--)
	{	addroundkey(data, key, round);
		invmixcolumns(data);
		invshiftrows(data);
		invsubbytes(data);
	}

	addroundkey(data, key, 0);
}



void rijndael4(unsigned char data[4][4])
{	int round;
	for (round=0; round<4; round++)
	{	subbytes(data);
		shiftrows(data);
		mixcolumns(data);
		addroundkey(data, key, 0);
	}
}

void addblock(unsigned char data[4][4], unsigned char data2[4][4])
{	int row, column;
     for (column = 0; column <4; column++)
     	for (row = 0; row<4; row++)
               data[row][column] = data[row][column] ^ data2[row][column];
}


void pelican(unsigned char code[4][4], unsigned char tekst[], unsigned char data[4][4])
{	int row, column;
	int length, ch, nofinish;
	unsigned char data2[4][4];

	for (row=0; row<4; row++)
		for (column=0; column<4;column++)
			data[row][column]=0;

	aes(data, code);
	ch = 0;
	nofinish = 1;
	while (nofinish)
	{for (column=0; column<4; column++)
		for (row=0; row<4; row++)
			{	if (tekst[ch] && nofinish)
					{	data2[row][column] = tekst[ch];
						ch++;
					}
				else
					{	if (!tekst[ch] && nofinish)
							{	data2[row][column] = 0x80u;
								nofinish = 0;
							}
						else data2[row][column] = 0x00u;
					}
			}
	 addblock(data, data2);
	 if (nofinish) rijndael4(data);
	}

	aes(data, code);

}
void opdrachtsend(unsigned char reslijst[LENGTERES], unsigned char result[4][8])
{	int row, column, temp;
	time_t t;
	unsigned char code_encryption[4][4] = {
    {0x00u, 0x04u, 0x08u, 0x0cu},
    {0x01u, 0x05u, 0x09u, 0x0du},
    {0x02u, 0x06u, 0x0au, 0x0eu},
    {0x03u, 0x07u, 0x0bu, 0x0fu}};

    unsigned char data[4][4]= {
    {0x00u, 0x00u, 0x00u, 0x00u},
    {0x00u, 0x00u, 0x00u, 0x00u},
    {0x00u, 0x00u, 0x00u, 0x00u},
    {0x00u, 0x00u, 0x00u, 0x00u}};

    unsigned char datamac[4][4];
    char tekst[]="xxxx";
    srand((unsigned) time(&t));
    
    
    for(char i = 0;i<LENGTERES;i++){
    data[i/4][i%4]= reslijst[i];
}
    temp = rand()&0xff;
    data[2][0]= (unsigned char)temp;
    temp = rand()&0xff;
    data[3][0]= (unsigned char)temp;
    for (column=1; column<4;  column++)
		for (row=0;row<4;  row++)
			{temp = rand()&0xff;
    		 data[row][column]= (unsigned char)temp;
			}

    resetkey();

    aes(data, code_encryption);

    tekst[0]=ch1;
    tekst[1]=ch2;
    tekst[2]=0;

    unsigned char code_mac[4][4] = {
    {0xf5u, 0x47u, 0xd5u, 0x85u},
    {0xd2u, 0x2bu, 0x92u, 0xdcu},
    {0x27u, 0x3eu, 0xa0u, 0xe7u},
    {0x31u, 0xa4u, 0xb7u, 0x71u}};

    resetkey();
    pelican(code_mac, tekst, datamac);

	for (column=0; column<4;  column++)
		for (row=0;row<4;  row++)
			result[row][column]=data[row][column];

	for (column=4; column<8;  column++)
		for (row=0;row<4;  row++)
			result[row][column]=datamac[row][column-4];

}

void opdrachtreceive(unsigned char result[4][8], unsigned char tekst[8])
{
	int row, column;
	int gelijk = 1;
	char fout[8]= "error! ";
	unsigned char code_encryption[4][4] = {
    {0x00u, 0x04u, 0x08u, 0x0cu},
    {0x01u, 0x05u, 0x09u, 0x0du},
    {0x02u, 0x06u, 0x0au, 0x0eu},
    {0x03u, 0x07u, 0x0bu, 0x0fu}};

    unsigned char data[4][4];
    unsigned char datamac[4][4];
	unsigned char datamac2[4][4];

	for (column=0; column<4;  column++)
		for (row=0; row<4;  row++)
			data[row][column]=result[row][column];

	for (column=4; column<8;  column++)
		for (row=0; row<4;  row++)
			datamac[row][column-4]=result[row][column];
	resetkey();
	invaes(data, code_encryption);

	tekst[0]=data[0][0];
	tekst[1]=data[1][0];
	tekst[2]=0;

    unsigned char code_mac[4][4] = {
    {0xf5u, 0x47u, 0xd5u, 0x85u},
    {0xd2u, 0x2bu, 0x92u, 0xdcu},
    {0x27u, 0x3eu, 0xa0u, 0xe7u},
    {0x31u, 0xa4u, 0xb7u, 0x71u}};

	resetkey();
	pelican(code_mac, tekst, datamac2);

	for (column=0; column<4;  column++)
		for (row=0; row<4;  row++)
			if (datamac[row][column] !=datamac2[row][column]) gelijk = 0;

	if (!gelijk)
		{	for (row=0; row<8;  row++) tekst[row]=fout[row];
		}
}
