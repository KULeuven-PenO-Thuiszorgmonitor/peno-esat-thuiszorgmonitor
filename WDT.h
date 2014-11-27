#ifndef WDT1_H_
#define WDT1_H_

#include <msp430.h>
__interrupt void WDT_ISR(void);
void WDT_select(void);


#endif /* WDT1_H_ */
