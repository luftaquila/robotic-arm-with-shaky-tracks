/*
 * ec_gpio.h
 *
 *  Created on: 2021. 7. 21.
 *      Author: hosung
 */

#ifndef INCLUDE_EC_GPIO_H_
#define INCLUDE_EC_GPIO_H_

void ec_init_gpio (void);
void ec_init_xbar(void);
void ec_set_init_gpio(uint32_t _pin, GPIO_Direction _pinio, GPIO_CoreSelect _core, GPIO_QualificationMode _qualification);


#endif /* INCLUDE_EC_GPIO_H_ */
