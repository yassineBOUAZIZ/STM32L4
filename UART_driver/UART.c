
#include "C:\Users\BAZINFO\Desktop\real_st\uart_driver\MDK-ARM\uart.h"
#include <stm32l4xx.h>

/* 
 * Function to initialize UART2 in transmit mode
 */
void uart2_tx_init(void) 
{
    // Enable the internal HSI oscillator (16 MHz)
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait for HSI to stabilize
    
    // Configure HSI as the system clock source (SYSCLK)
    RCC->CFGR |= (1 << 0); 

    // Enable clock for GPIOA (AHB2 bus)
    RCC->AHB2ENR |= (1 << 0);

    // Enable clock for USART2 (APB1 bus)
    RCC->APB1ENR1 |= (1 << 17);

    // Configure PA2 (USART2_TX) pin in alternate function mode (AF7)
    GPIOA->MODER &= ~(1 << 4);  // Clear bit 4 (PA2 mode)
    GPIOA->MODER |= (1 << 5);   // Set bit 5 (alternate function mode)
    GPIOA->AFR[0] |= (1 << 8);  // AF7 (bit 8)
    GPIOA->AFR[0] |= (1 << 9);  // AF7 (bit 9)
    GPIOA->AFR[0] |= (1 << 10); // AF7 (bit 10)
    GPIOA->AFR[0] &= ~(1 << 11); // AF7 (clear bit 11)

    // Disable USART2 to configure its settings
    USART2->CR1 &= ~(1 << 0); // Clear UE (USART Enable)

    // Configure USART2 in 8-bit mode, no parity, 1 stop bit
    USART2->CR1 &= ~((1 << 28) | (1 << 29)); // 8-bit mode
    USART2->CR1 &= ~(1 << 15);               // No parity
    USART2->CR2 &= ~(1 << 12);               // 1 stop bit (clear STOP[13:12])
    USART2->CR2 &= ~(1 << 13);               // 1 stop bit (clear STOP[13:12])

    // Configure baud rate to 9600
    // Baudrate = f_CK / USARTDIV, with USARTDIV = 0x683 for HSI (16 MHz)
    USART2->BRR = 0x683;

    // Enable USART2
    USART2->CR1 |= (1 << 0); // Set UE (USART Enable)

    // Enable transmission mode for USART2
    USART2->CR1 |= (1 << 3); // Set TE (Transmitter Enable)
}


/* 
 * Function to send a character via UART2
 * ch: character to send
 */
void uart2_write(uint32_t ch) 
{
    // Wait until the data register is empty (TXE = 1)
    while ((USART2->ISR & (1 << 7)) == 0) {} 

    // Write the character to the TDR data register
    USART2->TDR = ch; 
}


/* 
 * Function to send a string via UART2
 * str: pointer to the string to send
 */
void uart2_write_string(const char *str)
{
    while (*str) // Iterate through each character in the string
    {
        uart2_write(*str); // Send the current character
        str++; // Move to the next character
    }
}

