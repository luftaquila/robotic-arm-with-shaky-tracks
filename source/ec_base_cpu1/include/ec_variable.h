/*
 * ec_variable.h
 *
 *  Created on: 2021. 8. 9.
 *      Author: hosung
 */

#ifndef INCLUDE_EC_VARIABLE_H_
#define INCLUDE_EC_VARIABLE_H_

typedef struct{

}ECInterrupt;


typedef struct{

}ECTimer;

typedef struct{

}ECPWM;

typedef struct{
    uint16_t adcAResult[16];
}ECADC;

typedef struct{
    uint32_t count[10];
    uint32_t *timer_buffer;
    uint32_t delay;
    float64_t delay_us;
}ECTest;

typedef struct{
    ECInterrupt isr;
    ECTimer timer;
    ECPWM pwm;
    ECADC adc;
    ECTest test;
}EC_Variable;

extern EC_Variable ec;

void ec_init_variable(void);

#endif /* INCLUDE_EC_VARIABLE_H_ */
