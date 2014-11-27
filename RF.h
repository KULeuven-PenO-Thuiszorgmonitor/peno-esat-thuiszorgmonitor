#ifndef RF_H_
#define RF_H_


#include <cc430x513x.h>
#include "Transciever_code/HAL/RF1A.h"
#include "Transciever_code/HAL/HAL_PMM.h"
#include <stdio.h>
#include <string.h>

/*******************
 * Function Definition
 */

void Transmit(unsigned char *buffer, unsigned char length);
void ReceiveOn(void);
void ReceiveOff(void);
void append(unsigned char* array_in, unsigned char address, unsigned char* array_out);
void Send_Data(unsigned char ADDRESS, unsigned char* Data);
void init_RF(void);
void InitRadio(void);

unsigned char* Receive_data(unsigned char* RxBuffer, unsigned char ADDRESS, unsigned char* Received_data);

// Variablen
#define  PACKET_LEN         (0x21)			// PACKET_LEN <= 61
#define  RSSI_IDX           (PACKET_LEN)    // Index of appended RSSI
#define  CRC_LQI_IDX        (PACKET_LEN+1)  // Index of appended LQI, checksum
#define  CRC_OK             (BIT7)          // CRC_OK bit
#define  PATABLE_VAL        (0x51)          // 0 dBm output

extern RF_SETTINGS rfSettings;

unsigned char packetReceived;
unsigned char packetTransmit;

unsigned char RxBuffer[PACKET_LEN+2];
unsigned char RxBufferLength;
unsigned char TxBuffer[PACKET_LEN];
unsigned int i;

unsigned char transmitting;
unsigned char receiving;

unsigned char ADDRESS;
unsigned char Data[PACKET_LEN];
unsigned char Received_data[PACKET_LEN];

#endif /* RF_H_ */
