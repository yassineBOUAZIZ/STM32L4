/*
 * exti.h
 *
 *  Created on: august 8, 2024
 *      Author: YASSINE
 */
 
#include <stdint.h>
#include <stm32l4xx.h>

#ifndef EXTI_H_
#define GP_TIMER_H_

void pc13_exti_init(void);
#define LINE13		(1U<<13)
void uart2_rx_interupt_init(void);

#endif /* EXTI_H_ */

