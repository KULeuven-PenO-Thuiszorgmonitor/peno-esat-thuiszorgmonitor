#ifndef RF_H_
#define RF_H_


#include <cc430x513x.h>
#include "Transciever_code/HAL/RF1A.h"
#include "Transciever_code/HAL/HAL_PMM.h"


/*******************
 * Function Definition
 */

void Transmit(unsigned char *buffer, unsigned char length);
void ReceiveOn(void);
void ReceiveOff(void);

void InitButtonLeds(void);
void InitRadio(void);

unsigned char Receive_data(unsigned char ADDRESS);

// Variablen
#define  PACKET_LEN         (0x05)			// PACKET_LEN <= 61
#define  RSSI_IDX           (PACKET_LEN)    // Index of appended RSSI
#define  CRC_LQI_IDX        (PACKET_LEN+1)  // Index of appended LQI, checksum
#define  CRC_OK             (BIT7)          // CRC_OK bit
#define  PATABLE_VAL        (0x51)          // 0 dBm output

//extern RF_SETTINGS rfSettings;

unsigned char packetReceived;
unsigned char packetTransmit;

unsigned char RxBuffer[PACKET_LEN+2];
unsigned char RxBufferLength = 0;
const unsigned char TxBuffer[PACKET_LEN]= {0x01, 0x02, 0x03, 0x04, 0x05};
unsigned int buttonPressed = 0;
unsigned int i = 0;

unsigned char transmitting = 0;
unsigned char receiving = 0;

unsigned char temp[PACKET_LEN+2];

#endif /* RF_H_ */
