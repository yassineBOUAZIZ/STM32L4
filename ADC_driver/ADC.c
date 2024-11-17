
#include "adc_driver.h"
#include <stm32l4xx.h>


void ADC_Init()
{
	// Enable GPIOA clock (bit 0 of AHB2ENR for GPIOA)
    RCC->AHB2ENR |= (1 << 0);
    
    // Enable ADC clock (bit 13 of AHB2ENR for ADC1/ADC2)
    RCC->AHB2ENR |= (1 << 13);
    
    // Select the clock source for ADC (bits 28 and 29 of CCIPR to set SYSCLK as ADC clock source)
    RCC->CCIPR |= (1 << 28);
    RCC->CCIPR |= (1 << 29);
    
    // Configure PA0 as analog mode (bits 0 and 1 of MODER to 1)
    GPIOA->MODER |= (1 << 0);
    GPIOA->MODER |= (1 << 1);
    
    // Connect PA0 to ADC channel by enabling analog switch (bit 0 of ASCR)
    GPIOA->ASCR |= (1 << 0);
    
    // Ensure ADC is disabled before configuration (clear bit 29 of CR)
    ADC1->CR &= ~(1 << 29);
    
    // Enable ADC voltage regulator (set bit 28 of CR)
    ADC1->CR |= (1 << 28);
    
    // Wait for the ADC voltage regulator to stabilize (bit 0 of ISR set)
    ADC1->ISR |= (1 << 0);
    
    // Enable the ADC (set bit 0 of CR)
    ADC1->CR |= (1 << 0);
    
    // Configure ADC for single conversion mode (clear CONT bit in CFGR, bit 13)
    ADC1->CFGR |= (1 << 13);
		
		 // Wait until ADC is ready (bit 0 of ISR set)
    while (!(ADC1->ISR & (1 << 0))) {}
    
    // Configure the ADC sequence: set channel 5 in SQR1
    // Channel 5 corresponds to bits 6 to 8 in SQR1 (binary 101)
    ADC1->SQR1 |= (1 << 6);  // Set bit 6
    ADC1->SQR1 &= ~(1 << 7); // Clear bit 7
    ADC1->SQR1 |= (1 << 8);  // Set bit 8
		
	
}



void ADC_StartConversion(void)
{
	 // Start ADC conversion (set bit 2 of CR)
        ADC1->CR |= (1 << 2);
	
}

uint16_t ADC_GetValue(void)
{
	
	 // Wait for the conversion to complete (bit 2 of ISR set)
        while (!(ADC1->ISR & (1 << 2))) {}
        
        // Read the conversion result from DR
        return ADC1->DR;
			

}
