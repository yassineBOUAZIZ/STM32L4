#include "USART_tx_DMA.h"
#include <stm32l4xx.h>


/**
 * @brief Initializes DMA1 Channel 7 for memory-to-peripheral data transfer.
 * 
 * This function sets up DMA1 Channel 7 for transferring data from a memory 
 * source to a peripheral destination (USART2_TX in this example). It configures 
 * the DMA controller, sets the source and destination addresses, and enables the 
 * DMA channel with appropriate settings.
 * 
 * @param src  Address of the memory source (data buffer).
 * @param dest Address of the peripheral destination register (USART2->TDR).
 * @param len  Number of data units to transfer.
 */
void dma1_channel7_init(uint32_t src, uint32_t dest, uint32_t len) {
    // Enable the clock for DMA1
    RCC->AHB1ENR |= (1U << 0); // DMA1EN is bit 0 in AHB1ENR

    // Configure the DMA request mapping for USART2_TX (code 2 in CSELR)
    DMA1_CSELR->CSELR = (2U << 24); // USART2_TX corresponds to bits 27:24

    // Ensure the DMA channel is disabled before configuration
    DMA1_Channel7->CCR &= ~(1U << 0); // EN bit (bit 0) to 0
    while (DMA1_Channel7->CCR & (1U << 0)) {} // Wait until EN bit is cleared

    // Set the DMA registers for source, destination, and transfer size
    DMA1_Channel7->CPAR = dest;  // Peripheral address (USART2->TDR)
    DMA1_Channel7->CMAR = src;   // Memory address (data buffer)
    DMA1_Channel7->CNDTR = len;  // Number of data items to transfer

    // Configure DMA channel control settings
    DMA1_Channel7->CCR = 0; // Reset configuration
    DMA1_Channel7->CCR |= (1U << 7)  // MINC: Memory increment mode (bit 7)
                        | (1U << 4)  // DIR: Memory-to-peripheral direction (bit 4)
                        | (1U << 13) // PL[1]: Medium priority (bit 13)
                        | (1U << 1); // TCIE: Transfer complete interrupt (bit 1)

    // Enable the DMA interrupt in the NVIC
    NVIC_EnableIRQ(DMA1_Channel7_IRQn);

    // Enable the DMA channel to start the transfer
    DMA1_Channel7->CCR |= (1U << 0); // EN: Enable the channel (bit 0)
}

/**
 * @brief DMA1 Channel 7 interrupt handler.
 * 
 * This interrupt service routine (ISR) handles DMA1 Channel 7 transfer completion. 
 * It clears the transfer complete flag and allows the user to add custom code 
 * to handle the transfer completion event.
 */
void DMA1_Channel7_IRQHandler(void) {
    // Check if the transfer complete interrupt flag is set
    if (DMA1->ISR & (1U << 25)) { 
        // Clear the transfer complete interrupt flag
        DMA1->IFCR |= (1U << 25);

        // Custom code to handle the end of the transfer can be added here
    }
}
