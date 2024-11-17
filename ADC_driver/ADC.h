/*
	*adc.h
	*created on : augest 03 2024
	*auther : Yassine

*/


#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>

// Function prototypes
void ADC_Init(void);
void ADC_StartConversion(void);
uint16_t ADC_GetValue(void);

#endif // ADC_DRIVER_H
