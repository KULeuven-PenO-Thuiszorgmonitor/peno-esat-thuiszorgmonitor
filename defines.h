#ifndef DEFINES_H_
#define DEFINES_H_
/*
 * Dit is de define file, hierin kun je makkelijk tussen versies wisselen!
 * Versie 1:  hartslagmonitor, inclusief analyse van data + WDT
 * Versie 10: hartslagmonitor, exclusief analyse van data
 */

/*
 * ADC_VERSIE's:
 * 1 is result integer, niet splitsen van meetdata
 * 2 is result char   , opsplitsen van meetdata
 */

#define SENSOR_VERSIE 9

#if SENSOR_VERSIE == 1
#define WDT_VERSIE 1
#define LENGTERES 1
#define ADC_VERSIE 1

#elif SENSOR_VERSIE == 10
#define LENGTERES 15
#define WDT_VERSIE 1
#define ADC_VERSIE 2

#elif SENSOR_VERSIE == 2

#elif SENSOR_VERSIE == 9
#define WDT_VERSIE 1
#define LENGTERES 1
#define ADC_VERSIE 1
#endif

#if ADC_VERSIE == 1
#define RESULT_TYPE int
#elif ADC_VERSIE == 2
#define RESULT_TYPE char


#else
#define RESULT_TYPE int
#endif

#define RF_VERSIE 2

// RF_VERSIE 1 == SLAVE PULSOXY, 	ADDRESS = 0x01
// RF_VERSIE 2 == MASTER, 			ADDRESS = 0x04, ADDRESS_MASTER = 0x04
// RF_VERSIE 3 == SLAVE ECG, 		ADDRESS = 0x02
// RF_VERSIE 4 == SLAVE ZOOL, 		ADDRESS = 0x03

#endif /* DEFINES_H_ */
