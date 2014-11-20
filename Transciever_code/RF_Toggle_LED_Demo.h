#include <cc430x513x.h>
#include "HAL/RF1A.h"
#include "HAL/hal_pmm.h"

/*******************
 * Function Definition
 */
void Transmit(unsigned char *buffer, unsigned char length);
void ReceiveOn(void);
void ReceiveOff(void);

void InitButtonLeds(void);
void InitRadio(void);
