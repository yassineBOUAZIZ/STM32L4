#include "exti.h"
#include <stm32l4xx.h>


void pc13_exti_init( void)
{
	/*disable global interrupts*/
	__disable_irq();
	/*enable clock access for GPIOC*/
	RCC->AHB2ENR |= (1U<<2);
	/*configure PC13 as input*/
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);
	/*enable clock access to  SYSCFG*/
	RCC->APB2ENR |=(1U<<0);
	
	/*select PORTC for EXTI13*/
	
	SYSCFG->EXTICR[3] &= ~(1U<<4);
	SYSCFG->EXTICR[3] |= (1U<<5);
	SYSCFG->EXTICR[3] &= ~(1U<<6);
	SYSCFG->EXTICR[3] &= ~(1U<<7);
	
	/*unmask EXTI13*/
	EXTI->IMR1 |=(1U<<13); 
	/*select falling edge trigger*/
	EXTI->FTSR1 |=(1U<<13);
	/*enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	/*enable global interrupts */
	__enable_irq();

}

void uart2_rx_interupt_init(void)
{
	// Enable the internal HSI oscillator (16 MHz)
RCC->CR |= RCC_CR_HSION;

// Wait for HSI to stabilize
while (!(RCC->CR & RCC_CR_HSIRDY));

// Configure HSI as the system clock source (SYSCLK) by setting SW[1:0] = 01
RCC->CFGR |= (1 << 0);

// Enable clock for GPIOA (AHB2 bus)
RCC->AHB2ENR |= (1 << 0);

// Enable clock for USART2 (APB1 bus)
RCC->APB1ENR1 |= (1 << 17);
	
// Set PA3 to alternate function mode
GPIOA->MODER &= ~(3U << 6);  // Clear mode bits for PA3
GPIOA->MODER |= (2U << 6);   // Set PA3 to alternate function mode (10)

// Set alternate function AF7 (USART2) for PA2 and PA3
GPIOA->AFR[0] &= ~(0xF << 12); // Clear AFRL for PA3
GPIOA->AFR[0] |= (7 << 12);       // Set AF7 for  PA3

// Disable USART2 to configure its settings
USART2->CR1 &= ~(1 << 0); // Clear UE (USART Enable)

// Configure USART2 in 8-bit mode, no parity, 1 stop bit
USART2->CR1 &= ~((1 << 28) | (1 << 29)); // 8-bit mode
USART2->CR1 &= ~(1 << 15);               // No parity
USART2->CR2 &= ~(3 << 12);               // 1 stop bit (clear STOP[13:12])

// Configure baud rate to 9600
// Baudrate = f_CK / USARTDIV, with USARTDIV = 0x683 for HSI (16 MHz)
USART2->BRR = 0x683;

// Enable transmission and reception modes for USART2
USART2->CR1 |= (1 << 2); // Set RE (Receiver Enable)
USART2->CR1 |=(1U<<5);   //enable RXNIE interrupt
NVIC_EnableIRQ(USART2_IRQn);//enable USART2 interrupt in NVIC

// Enable USART2
USART2->CR1 |= (1 << 0); // Set UE (USART Enable)

}
