/*
 * ec_adc.h
 *
 *  Created on: 2021. 8. 5.
 *      Author: hosung
 */

#ifndef INCLUDE_EC_ADC_H_
#define INCLUDE_EC_ADC_H_

void ec_init_adc(void);

void ec_init_adc_interrupt(void);   //pwm interrupt √ ±‚»≠

void ec_enable_adc_interrupt(void);

void ec_init_adcs(void);

void ec_init_socs(void);

#endif /* INCLUDE_EC_ADC_H_ */
