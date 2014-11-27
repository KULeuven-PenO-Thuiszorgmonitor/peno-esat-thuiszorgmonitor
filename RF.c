#include "RF.h"


void WriteToTxBuffer(ADDRESS, Data)
{
	TxBuffer[0] = ADDRESS;
	append(TxBuffer, Data);
}

void  append(unsigned char s[], unsigned char c) {
     unsigned int len = sizeof(s);
     s[len] = c;
     s[len+1] = '\0';
}

void Send_Data(ADDRESS, Data)
{
	const unsigned char TxBuffer[PACKET_LEN]={0x00,0x00,0x00,0x00,0x00};

	WriteToTxBuffer(ADDRESS, Data);

	ReceiveOff();
	receiving = 0;

	Transmit( (unsigned char*)TxBuffer, sizeof TxBuffer);
	transmitting = 1;
}





void init_RF(void){
	// Increase PMMCOREV level to 2 for proper radio operation
	SetVCore(2);
	ResetRadioCore();
	InitRadio();

	ReceiveOn();
	receiving = 1;
}

unsigned char *Receive_data(unsigned char ADDRESS){
	// Contact Cedric for errors

	// Check for ADDRESS:
	// If ADDRESS = Correct:
	//		Return contents of RxBuffer
	// If ADDRESS = False:
	//		Break
	const int count = 33;
	char *ret = malloc(count);
	volatile unsigned i;
// Read the length byte from the FIFO
        RxBufferLength = ReadSingleReg( RXBYTES );
        ReadBurstReg(RF_RXFIFORD, RxBuffer, RxBufferLength);

// Stop here to see contents of RxBuffer
        __no_operation();

// Check the CRC results
        if(RxBuffer[CRC_LQI_IDX] && CRC_OK){
        	// Check to see if the ADDRESS is correct)
        	if(RxBuffer[BIT0] && ADDRESS){
        		for(i = count; i > 0; i--){
        			ret[i] = RxBuffer[i];
        		}
        		return ret;
        	}
        }
        return 0;
}


void InitRadio(void)
{
  // Set the High-Power Mode Request Enable bit so LPM3 can be entered
  // with active radio enabled
  PMMCTL0_H = 0xA5;
  PMMCTL0_L |= PMMHPMRE_L;
  PMMCTL0_H = 0x00;

  WriteRfSettings(&rfSettings);

  WriteSinglePATable(PATABLE_VAL);
}

void Transmit(unsigned char *buffer, unsigned char length)
{
  RF1AIES |= BIT9;
  RF1AIFG &= ~BIT9;                         // Clear pending interrupts
  RF1AIE |= BIT9;                           // Enable TX end-of-packet interrupt

  WriteBurstReg(RF_TXFIFOWR, buffer, length);

  Strobe( RF_STX );                         // Strobe STX
}

void ReceiveOn(void)
{
  RF1AIES |= BIT9;                          // Falling edge of RFIFG9
  RF1AIFG &= ~BIT9;                         // Clear a pending interrupt
  RF1AIE  |= BIT9;                          // Enable the interrupt

  // Radio is in IDLE following a TX, so strobe SRX to enter Receive Mode
  Strobe( RF_SRX );
}

void ReceiveOff(void)
{
  RF1AIE &= ~BIT9;                          // Disable RX interrupts
  RF1AIFG &= ~BIT9;                         // Clear pending IFG

  // It is possible that ReceiveOff is called while radio is receiving a packet.
  // Therefore, it is necessary to flush the RX FIFO after issuing IDLE strobe
  // such that the RXFIFO is empty prior to receiving a packet.
  Strobe( RF_SIDLE );
  Strobe( RF_SFRX  );
}

#pragma vector=CC1101_VECTOR
__interrupt void CC1101_ISR(void)
{
  switch(__even_in_range(RF1AIV,32))        // Prioritizing Radio Core Interrupt
  {
    case  0: break;                         // No RF core interrupt pending
    case  2: break;                         // RFIFG0
    case  4: break;                         // RFIFG1
    case  6: break;                         // RFIFG2
    case  8: break;                         // RFIFG3
    case 10: break;                         // RFIFG4
    case 12: break;                         // RFIFG5
    case 14: break;                         // RFIFG6
    case 16: break;                         // RFIFG7
    case 18: break;                         // RFIFG8
    case 20:                                // RFIFG9
      if(receiving)			    // RX end of packet
      {
        // Read the length byte from the FIFO
        RxBufferLength = ReadSingleReg( RXBYTES );
        ReadBurstReg(RF_RXFIFORD, RxBuffer, RxBufferLength);

        // Stop here to see contents of RxBuffer
        __no_operation();

        // Check the CRC results
        if(RxBuffer[CRC_LQI_IDX] & CRC_OK)
        	P1OUT ^= BIT0;
      }
      else if(transmitting)		    // TX end of packet
      {
        RF1AIE &= ~BIT9;                    // Disable TX end-of-packet interrupt
        P2OUT &= ~BIT6;                     // Turn off LED after Transmit
        transmitting = 0;
      }
      else while(1); 			    // trap
      break;
    case 22: break;                         // RFIFG10
    case 24: break;                         // RFIFG11
    case 26: break;                         // RFIFG12
    case 28: break;                         // RFIFG13
    case 30: break;                         // RFIFG14
    case 32: break;                         // RFIFG15
  }
  __bic_SR_register_on_exit(LPM3_bits);
}
