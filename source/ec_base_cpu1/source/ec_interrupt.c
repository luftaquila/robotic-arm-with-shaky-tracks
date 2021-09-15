/*
 * ec_interrupt.c
 *
 *  Created on: 2021. 7. 22.
 *      Author: hosung
 */

#include "ec_device.h"

void ec_init_interrupt(void)
{
    //
    // Interrupts 비활성화, Clear all PIE registers
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    ec_init_timer_interrupt();
    ec_init_epwm_interrupt();
    ec_init_adc_interrupt();
}

void ec_enable_interrupt(void)
{
    ec_enable_timer_interrupt();
    ec_enable_epwm_interrupt();
    ec_enable_adc_interrupt();
    EINT;   // Interrupt 활성화
}

__interrupt void ec_cpuTimer0ISR(void)
{
    ec.test.count[1]++;
    GPIO_togglePin(31U);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void ec_epwm1ISR(void)
{
    ec.test.count[2]++;
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

__interrupt void ec_epwm1TZISR(void)
{
    ec.test.count[3]++;
    DEVICE_DELAY_US(10U); // 비어있을 경우 에러 발생함
    EPWM_clearTripZoneFlag(EPWM1_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_CBC));
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

__interrupt void ec_adca1ISR(void)
{
    ec.test.count[4]++;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
