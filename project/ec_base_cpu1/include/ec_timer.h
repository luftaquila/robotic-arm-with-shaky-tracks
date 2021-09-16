/*
 * ec_timer.h
 *
 *  Created on: 2021. 8. 5.
 *      Author: hosung
 */

#ifndef INCLUDE_EC_TIMER_H_
#define INCLUDE_EC_TIMER_H_

//check delay, its using timer0 and use 41clock
#define ECCLKS  ec_start_get_timer(CPUTIMER0_BASE, ec.test.timer_buffer)
#define ECCLKF  ec.test.delay = ec_finish_get_timer(CPUTIMER0_BASE, ec.test.timer_buffer) - 41U; \
                ec.test.delay_us = ec.test.delay / 200.0

void ec_init_timer(void);

void ec_init_timer_interrupt(void);

void ec_enable_timer_interrupt(void);

void ec_start_timer(void);

void ec_set_init_timer(uint32_t _base, uint32_t _period, uint16_t _prescaler);

void ec_start_get_timer(uint32_t _base, uint32_t* delay_time);

uint32_t ec_finish_get_timer(uint32_t _base, uint32_t* delay_time);

#endif /* INCLUDE_EC_TIMER_H_ */
