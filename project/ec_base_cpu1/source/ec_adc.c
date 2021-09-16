/*
 * ec_adc.c
 *
 *  Created on: 2021. 8. 5.
 *      Author: hosung
 */

#include "ec_device.h"

void ec_init_adc(void)
{
    ec_init_adcs();
    ec_init_socs();
}

void ec_init_adcs(void)
{
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);   //Set ADCDLK divider to /4
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);    // Set resolution and signal mode and load

    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);    // Set pulse positions to late
    ADC_enableConverter(ADCA_BASE);     // Power up the ADC
    DEVICE_DELAY_US(1000U); //delay_us
}

void ec_init_adc_interrupt(void)   //pwm interrupt 초기화
{
    Interrupt_register(INT_ADCA1, &ec_adca1ISR);
}

void ec_enable_adc_interrupt(void)   //pwm interrupt 활성화
{
    Interrupt_enable(INT_ADCA1);
}

void ec_init_socs(void)
{
    // Configure SOCs
    // - Both will be triggered by software only.
    // - For 12-bit resolution, a sampling window of 15 (75 ns at a 200MHz
    //   SYSCLK rate) will be used.  For 16-bit resolution, a sampling window
    //   of 64 (320 ns at a 200MHz SYSCLK rate) will be used.
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 15);   // - SOC0 will convert pin A0.

    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
}
