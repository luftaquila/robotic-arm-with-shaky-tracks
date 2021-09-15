/*
 * ec_pwm.h
 *
 *  Created on: 2021. 7. 21.
 *      Author: hosung
 */

#ifndef INCLUDE_EC_PWM_H_
#define INCLUDE_EC_PWM_H_

void ec_init_epwm(void);

void ec_init_epwm_interrupt(void);

void ec_enable_epwm_interrupt(void);

void ec_init_epwm1(void);

#endif /* INCLUDE_EC_PWM_H_ */
