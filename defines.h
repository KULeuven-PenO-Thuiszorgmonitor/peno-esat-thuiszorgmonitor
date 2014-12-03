#ifndef DEFINES_H_
#define DEFINES_H_
/*
 * Dit is de define file, hierin kun je makkelijk tussen versies wisselen!
 * Versie 1:  hartslagmonitor, inclusief analyse van data + WDT
 * Versie 10: hartslagmonitor, exclusief analyse van data
 */

#define SENSOR_VERSIE 10

#if SENSOR_VERSIE == 1
#define WDT_VERSIE 1
#define LENGTERES 1

#elif SENSOR_VERSIE == 10
#define LENGTERES 15
#define WDT_VERSIE 1

#elif SENSOR_VERSIE == 2

#endif



#define RF_VERSIE 2

// RF_VERSIE 1 == SLAVE PULSOXY, 	ADDRESS = 0x01
// RF_VERSIE 2 == MASTER, 			ADDRESS = 0x04, ADDRESS_MASTER = 0x04
// RF_VERSIE 3 == SLAVE ECG, 		ADDRESS = 0x02
// RF_VERSIE 4 == SLAVE ZOOL, 		ADDRESS = 0x03

#endif /* DEFINES_H_ */
