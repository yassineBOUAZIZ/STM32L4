/*
 * GP_timer.c
 *
 *  Created on: august 05, 2024
 *      Author: Yassine
 */

#include <stm32l4xx.h>



/*Initializes Timer 2 to generate a 1 Hz periodic signal*/
void tim2_1hz_init(void){
	 // Enable the internal HSI oscillator (16 MHz)
	    RCC->CR |= RCC_CR_HSION;
	    while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait for HSI to stabilize

	/*enable clock acces to timer 2*/
	RCC->APB1ENR1 |=(1<<0);
	/*set prescaler value*/
	TIM2->PSC =1599;
	/*set auto reload value*/
	TIM2->ARR = 999;
	/*clear counter*/
	TIM2->CNT = 0x00;
	/*enable timer*/
	TIM2->CR1 |= (1<<0);

}

/*Configures Timer 2 to toggle PA5 at a frequency defined by the timer settings*/
void Configure_TIM2_PA5_Toggle(void)
{
	// Enable clock access to GPIOA (bit 0 in AHB2ENR for GPIOA)
	RCC->AHB2ENR |= (1 << 0);

	// Configure GPIOA pin 5 as alternate function mode (clear bit 10, set bit 11 in MODER)
	GPIOA->MODER &= ~(1 << 10); // Clear bit 10
	GPIOA->MODER |= (1 << 11);  // Set bit 11

	// Select alternate function AF1 (TIM2_CH1) for GPIOA pin 5
	GPIOA->AFR[0] |= (1 << 20);                           // Set bit 20
	GPIOA->AFR[0] &= ~((1 << 21) | (1 << 22) | (1 << 23)); // Clear bits 21, 22, and 23

	// Enable clock access to Timer 2 (bit 0 in APB1ENR1 for TIM2)
	RCC->APB1ENR1 |= (1 << 0);

	// Set prescaler value for Timer 2 (PSC = 1599, for dividing clock frequency)
	TIM2->PSC = 1599;

	// Set auto-reload value for Timer 2 (ARR = 999, defining the period of the toggle signal)
	TIM2->ARR = 999;

	// Configure output compare mode to toggle mode (bits 4 and 5 set in CCMR1)
	TIM2->CCMR1 |= ((1 << 4) | (1 << 5));

	// Enable Timer 2 Channel 1 in compare mode (bit 0 in CCER)
	TIM2->CCER |= (1 << 0);

	// Clear Timer 2 counter
	TIM2->CNT = 0x00;

	// Enable Timer 2 (bit 0 in CR1)
	TIM2->CR1 |= (1 << 0);


}

/*Configures Timer 2 to generate a PWM signal on PA5 with a specified duty cycle*/
void tim2_PA5_PWM1(void)
{


	// Enable clock access to GPIOA (bit 0 in AHB2ENR for GPIOA)
	RCC->AHB2ENR |= (1 << 0);

	// Configure GPIOA pin 5 as alternate function mode (clear bit 10, set bit 11 in MODER)
	GPIOA->MODER &= ~(1 << 10); // Clear bit 10
	GPIOA->MODER |= (1 << 11);  // Set bit 11

	// Select alternate function AF1 (TIM2_CH1) for GPIOA pin 5
	GPIOA->AFR[0] |= (1 << 20);                           // Set bit 20
	GPIOA->AFR[0] &= ~((1 << 21) | (1 << 22) | (1 << 23)); // Clear bits 21, 22, and 23

	// Enable clock access to Timer 2 (bit 0 in APB1ENR1 for TIM2)
	RCC->APB1ENR1 |= (1 << 0);

	// Set prescaler value for Timer 2 to divide clock frequency (PSC = 15)
	TIM2->PSC = 15;

	// Set auto-reload value for Timer 2 (ARR = 999, for a 1 kHz frequency)
	TIM2->ARR = 999;

	// Set Capture/Compare Register 1 (CCR1) for a 50% duty cycle (CCR1 = 500)
	TIM2->CCR1 = 500;

	// Configure output compare mode to PWM mode 1 (bits 5 and 6 set, bit 4 cleared in CCMR1)
	TIM2->CCMR1 &= ~(1 << 4);       // Clear bit 4
	TIM2->CCMR1 |= ((1 << 5) | (1 << 6)); // Set bits 5 and 6

	// Enable Timer 2 Channel 1 in compare mode (bit 0 in CCER)
	TIM2->CCER |= (1 << 0);

	// Enable auto-reload preload (bit 7 in CR1)
	TIM2->CR1 |= (1 << 7);

	// Clear Timer 2 counter
	TIM2->CNT = 0x00;

	// Enable Timer 2 (bit 0 in CR1)
	TIM2->CR1 |= (1 << 0);

}

