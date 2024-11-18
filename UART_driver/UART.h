/*
	*uart.h
	*created on : augest 03 2024
	*auther : Yassine

*/


#ifndef UART_H
#define UART_H

#include <stdint.h>

// Function prototypes
void uart2_write(uint32_t ch);
void uart2_write_string(const char *str);
void uart2_tx_init(void);

#endif // UART_DRIVER_H

