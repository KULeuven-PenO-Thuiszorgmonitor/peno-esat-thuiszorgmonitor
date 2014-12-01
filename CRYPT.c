#include "CRYPT.h"
const unsigned char submatrix[16][16]={
      {0x63u, 0x7cu, 0x77u, 0x7bu, 0xf2u, 0x6bu, 0x6fu, 0xc5u, 0x30u, 0x01u, 0x67u, 0x2bu, 0xfeu, 0xd7u, 0xabu, 0x76u},
      {0xcau, 0x82u, 0xc9u, 0x7du, 0xfau, 0x59u, 0x47u, 0xf0u, 0xadu, 0xd4u, 0xa2u, 0xafu, 0x9cu, 0xa4u, 0x72u, 0xc0u},
      {0xb7u, 0xfdu, 0x93u, 0x26u, 0x36u, 0x3fu, 0xf7u, 0xccu, 0x34u, 0xa5u, 0xe5u, 0xf1u, 0x71u, 0xd8u, 0x31u, 0x15u},
      {0x04u, 0xc7u, 0x23u, 0xc3u, 0x18u, 0x96u, 0x05u, 0x9au, 0x07u, 0x12u, 0x80u, 0xe2u, 0xebu, 0x27u, 0xb2u, 0x75u},
      {0x09u, 0x83u, 0x2cu, 0x1au, 0x1bu, 0x6eu, 0x5au, 0xa0u, 0x52u, 0x3bu, 0xd6u, 0xb3u, 0x29u, 0xe3u, 0x2fu, 0x84u},
      {0x53u, 0xd1u, 0x00u, 0xedu, 0x20u, 0xfcu, 0xb1u, 0x5bu, 0x6au, 0xcbu, 0xbeu, 0x39u, 0x4au, 0x4cu, 0x58u, 0xcfu},
      {0xd0u, 0xefu, 0xaau, 0xfbu, 0x43u, 0x4du, 0x33u, 0x85u, 0x45u, 0xf9u, 0x02u, 0x7fu, 0x50u, 0x3cu, 0x9fu, 0xa8u},
      {0x51u, 0xa3u, 0x40u, 0x8fu, 0x92u, 0x9du, 0x38u, 0xf5u, 0xbcu, 0xb6u, 0xdau, 0x21u, 0x10u, 0xffu, 0xf3u, 0xd2u},
      {0xcdu, 0x0cu, 0x13u, 0xecu, 0x5fu, 0x97u, 0x44u, 0x17u, 0xc4u, 0xa7u, 0x7eu, 0x3du, 0x64u, 0x5du, 0x19u, 0x73u},
      {0x60u, 0x81u, 0x4fu, 0xdcu, 0x22u, 0x2au, 0x90u, 0x88u, 0x46u, 0xeeu, 0xb8u, 0x14u, 0xdeu, 0x5eu, 0x0bu, 0xdbu},
      {0xe0u, 0x32u, 0x3au, 0x0au, 0x49u, 0x06u, 0x24u, 0x5cu, 0xc2u, 0xd3u, 0xacu, 0x62u, 0x91u, 0x95u, 0xe4u, 0x79u},
      {0xe7u, 0xc8u, 0x37u, 0x6du, 0x8du, 0xd5u, 0x4eu, 0xa9u, 0x6cu, 0x56u, 0xf4u, 0xeau, 0x65u, 0x7au, 0xaeu, 0x08u},
      {0xbau, 0x78u, 0x25u, 0x2eu, 0x1cu, 0xa6u, 0xb4u, 0xc6u, 0xe8u, 0xddu, 0x74u, 0x1fu, 0x4bu, 0xbdu, 0x8bu, 0x8au},
      {0x70u, 0x3eu, 0xb5u, 0x66u, 0x48u, 0x03u, 0xf6u, 0x0eu, 0x61u, 0x35u, 0x57u, 0xb9u, 0x86u, 0xc1u, 0x1du, 0x9eu},
      {0xe1u, 0xf8u, 0x98u, 0x11u, 0x69u, 0xd9u, 0x8eu, 0x94u, 0x9bu, 0x1eu, 0x87u, 0xe9u, 0xceu, 0x55u, 0x28u, 0xdfu},
      {0x8cu, 0xa1u, 0x89u, 0x0du, 0xbfu, 0xe6u, 0x42u, 0x68u, 0x41u, 0x99u, 0x2du, 0x0fu, 0xb0u, 0x54u, 0xbbu, 0x16u}};

const unsigned char invsbox[16][16]={
      {0x52u, 0x09u, 0x6au, 0xd5u, 0x30u, 0x36u, 0xa5u, 0x38u, 0xbfu, 0x40u, 0xa3u, 0x9eu, 0x81u, 0xf3u, 0xd7u, 0xfbu},
   	  {0x7cu, 0xe3u, 0x39u, 0x82u, 0x9bu, 0x2fu, 0xffu, 0x87u, 0x34u, 0x8eu, 0x43u, 0x44u, 0xc4u, 0xdeu, 0xe9u, 0xcbu},
      {0x54u, 0x7bu, 0x94u, 0x32u, 0xa6u, 0xc2u, 0x23u, 0x3du, 0xeeu, 0x4cu, 0x95u, 0x0bu, 0x42u, 0xfau, 0xc3u, 0x4eu},
      {0x08u, 0x2eu, 0xa1u, 0x66u, 0x28u, 0xd9u, 0x24u, 0xb2u, 0x76u, 0x5bu, 0xa2u, 0x49u, 0x6du, 0x8bu, 0xd1u, 0x25u},
      {0x72u, 0xf8u, 0xf6u, 0x64u, 0x86u, 0x68u, 0x98u, 0x16u, 0xd4u, 0xa4u, 0x5cu, 0xccu, 0x5du, 0x65u, 0xb6u, 0x92u},
      {0x6cu, 0x70u, 0x48u, 0x50u, 0xfdu, 0xedu, 0xb9u, 0xdau, 0x5eu, 0x15u, 0x46u, 0x57u, 0xa7u, 0x8du, 0x9du, 0x84u},
      {0x90u, 0xd8u, 0xabu, 0x00u, 0x8cu, 0xbcu, 0xd3u, 0x0au, 0xf7u, 0xe4u, 0x58u, 0x05u, 0xb8u, 0xb3u, 0x45u, 0x06u},
      {0xd0u, 0x2cu, 0x1eu, 0x8fu, 0xcau, 0x3fu, 0x0fu, 0x02u, 0xc1u, 0xafu, 0xbdu, 0x03u, 0x01u, 0x13u, 0x8au, 0x6bu},
      {0x3au, 0x91u, 0x11u, 0x41u, 0x4fu, 0x67u, 0xdcu, 0xeau, 0x97u, 0xf2u, 0xcfu, 0xceu, 0xf0u, 0xb4u, 0xe6u, 0x73u},
      {0x96u, 0xacu, 0x74u, 0x22u, 0xe7u, 0xadu, 0x35u, 0x85u, 0xe2u, 0xf9u, 0x37u, 0xe8u, 0x1cu, 0x75u, 0xdfu, 0x6eu},
      {0x47u, 0xf1u, 0x1au, 0x71u, 0x1du, 0x29u, 0xc5u, 0x89u, 0x6fu, 0xb7u, 0x62u, 0x0eu, 0xaau, 0x18u, 0xbeu, 0x1bu},
      {0xfcu, 0x56u, 0x3eu, 0x4bu, 0xc6u, 0xd2u, 0x79u, 0x20u, 0x9au, 0xdbu, 0xc0u, 0xfeu, 0x78u, 0xcdu, 0x5au, 0xf4u},
      {0x1fu, 0xddu, 0xa8u, 0x33u, 0x88u, 0x07u, 0xc7u, 0x31u, 0xb1u, 0x12u, 0x10u, 0x59u, 0x27u, 0x80u, 0xecu, 0x5fu},
      {0x60u, 0x51u, 0x7fu, 0xa9u, 0x19u, 0xb5u, 0x4au, 0x0du, 0x2du, 0xe5u, 0x7au, 0x9fu, 0x93u, 0xc9u, 0x9cu, 0xefu},
      {0xa0u, 0xe0u, 0x3bu, 0x4du, 0xaeu, 0x2au, 0xf5u, 0xb0u, 0xc8u, 0xebu, 0xbbu, 0x3cu, 0x83u, 0x53u, 0x99u, 0x61u},
      {0x17u, 0x2bu, 0x04u, 0x7eu, 0xbau, 0x77u, 0xd6u, 0x26u, 0xe1u, 0x69u, 0x14u, 0x63u, 0x55u, 0x21u, 0x0cu, 0x7du}};
int nokey = 1;
const unsigned char rc[10] = {0x01u, 0x02u, 0x04u, 0x08u, 0x10u, 0x20u,0x40u, 0x80u, 0x1bu, 0x36u};
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
void opdrachtsend(unsigned char reslijst[LENGTERES+1], unsigned char result[4][8])
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
    

    for(t=0;t<LENGTERES;t++){
    data[t/4][t%4]= reslijst[t];
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

    reslijst[LENGTERES] = 0;

    unsigned char code_mac[4][4] = {
    {0xf5u, 0x47u, 0xd5u, 0x85u},
    {0xd2u, 0x2bu, 0x92u, 0xdcu},
    {0x27u, 0x3eu, 0xa0u, 0xe7u},
    {0x31u, 0xa4u, 0xb7u, 0x71u}};

    resetkey();
    pelican(code_mac, reslijst, datamac);

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
