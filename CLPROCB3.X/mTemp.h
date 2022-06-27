/* 
 * File:   mTemp.h
 * Author: KaoChihChien
 *
 * Created on December 24, 2020, 12:55 AM
 */

#ifndef MTEMP_H
#define	MTEMP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/adc.h"
    
// Nominal temperature value for the thermistor
#define TERMISTORNOMINAL 100000
// Nominl temperature depicted on the datasheet
#define TEMPERATURENOMINAL 25
// Number of samples 
#define NUMAMOSTRAS 5
// Beta value for our thermistor
#define BCOEFFICIENT 3977
// Value of the series resistor
#define SERIESRESISTOR 100000
    
    uint16_t adc_get(adc_channel_t channel);
    uint8_t Thermistor (uint16_t convertedValue);

#ifdef	__cplusplus
}
#endif

#endif	/* MTEMP_H */

