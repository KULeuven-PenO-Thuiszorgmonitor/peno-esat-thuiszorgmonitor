#ifndef UART_H_
#define UART_H_

void send_UART(void);
void init_UART(void);
__interrupt void USCI_A0_ISR(void);

#endif /* UART_H_ */
