#include "mTemp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t adc_get(adc_channel_t channel) {
    uint24_t convertedValue = 0;
    uint16_t num[12], tmp;

    for (int i = 0; i < 12; i++) {
        num[i] = ADC_GetConversion(channel);
    }

    //    for (int i = 0; i < 5; i++) {
    //        convertedValue = convertedValue + ADC_GetConversion(channel);
    //    }
    //    convertedValue = convertedValue / 5;

    for (int i = 0; i < 12; i = i + 1) {
        for (int j = i + 1; j < 12; j = j + 1) {
            if (num[i] > num[j]) {
                //????
                tmp = num[i];
                num[i] = num[j];
                num[j] = tmp;
            }
        }
    }

    //    convertedValue = 0;
    //    for (int i = 0; i < 10; i++) {
    //        convertedValue = convertedValue + num[i + 1];
    //    }
    //    convertedValue = convertedValue / 10;

    return num[6];
}

uint8_t Thermistor(uint16_t convertedValue) {

    double media = (double) convertedValue;

    // Convert the thermal stress value to resistance
    media = 1023 / media - 1;
    media = SERIESRESISTOR / media;

    //Calculate temperature using the Beta Factor equation
    double temperatura;
    temperatura = media / TERMISTORNOMINAL; // (R/Ro)
    temperatura = log(temperatura); // ln(R/Ro)
    temperatura /= BCOEFFICIENT; // 1/B * ln(R/Ro)
    temperatura += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
    temperatura = 1.0 / temperatura; // Invert the value
    temperatura -= 273.15; // Convert it to Celsius

    return (uint8_t) temperatura;
}
