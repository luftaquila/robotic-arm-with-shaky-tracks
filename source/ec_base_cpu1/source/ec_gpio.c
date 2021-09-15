/*
 * ec_gpio.c
 *
 *  Created on: 2021. 7. 19.
 *      Author: hosung
 */
#include "ec_device.h"

void ec_init_gpio(void)    // gpio √ ±‚»≠
{
    ec_set_init_gpio(31U,       //gpio31 output set
                     GPIO_DIR_MODE_OUT,
                     GPIO_CORE_CPU1,
                     GPIO_QUAL_ASYNC);
    ec_set_init_gpio(12U,       //gpio12 input set
                     GPIO_DIR_MODE_IN,
                     GPIO_CORE_CPU1,
                     GPIO_QUAL_ASYNC);
}

void ec_init_xbar(void)
{
    XBAR_setInputPin(XBAR_INPUT1, 12);
}

void ec_set_init_gpio(uint32_t _pin, GPIO_Direction _pinio, GPIO_CoreSelect _core, GPIO_QualificationMode _qualification)
{
    GPIO_setDirectionMode(_pin, _pinio);      //31-pin, Output
    GPIO_setMasterCore(_pin, _core);            //MasterCore set
    GPIO_setQualificationMode(_pin, _qualification);    //SYNC set
}
