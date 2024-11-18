/*
 * GP_timer.c
 *
 *  Created on: August 05, 2024
 *      Author: BAZINFO
 */

#include <stm32l4xx.h>

// Function to initialize Timer 2 to generate a 1 Hz signal
void tim2_1hz_init(void)
{
    // Enable the internal High-Speed Internal (HSI) oscillator (16 MHz)
    RCC->CR |= RCC_CR_HSION;                 // Set the HSI enable bit
    while (!(RCC->CR & RCC_CR_HSIRDY));      // Wait until the HSI is ready (stable)

    // Enable clock access to Timer 2
    RCC->APB1ENR1 |= (1 << 0);               // Set the TIM2EN bit in APB1ENR1 to enable TIM2

    // Set the prescaler value
    TIM2->PSC = 1599;                        // Divide the timer clock by 1600 (PSC + 1)
                                             // If TIM2 clock = 16 MHz, new clock = 16 MHz / 1600 = 10 kHz

    // Set the auto-reload value
    TIM2->ARR = 999;                         // Timer counts up to 999 before resetting
                                             // At 10 kHz, this gives a time period of (ARR + 1) / clock = 1000 / 10 kHz = 0.1 s

    // Clear the timer counter
    TIM2->CNT = 0x00;                        // Reset the counter value to 0

    // Enable the timer
    TIM2->CR1 |= (1 << 0);                   // Set the CEN (Counter Enable) bit in CR1 to start the timer
}
