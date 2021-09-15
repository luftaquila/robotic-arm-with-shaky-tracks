/*
 * ec_interrupt.h
 *
 *  Created on: 2021. 7. 22.
 *      Author: hosung
 */

#ifndef INCLUDE_EC_INTERRUPT_H_
#define INCLUDE_EC_INTERRUPT_H_

void ec_init_interrupt(void);
void ec_enable_interrupt(void);
__interrupt void ec_cpuTimer0ISR(void);
__interrupt void ec_epwm1ISR(void);
__interrupt void ec_epwm1TZISR(void);
__interrupt void ec_adca1ISR(void);



#endif /* INCLUDE_EC_INTERRUPT_H_ */
