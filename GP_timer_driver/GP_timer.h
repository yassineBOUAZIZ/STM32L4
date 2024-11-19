/*
 * GP_timer.h
 *
 *  Created on: august 5, 2024
 *      Author: YASSINE
 */
#include <stdint.h>
#include <stm32l4xx.h>

#ifndef GP_TIMER_H_
#define GP_TIMER_H_

void tim2_1hz_init(void);
void Configure_TIM2_PA5_Toggle(void);
void tim2_PA5_PWM1(void);

#endif /* GP_TIMER_H_ */
