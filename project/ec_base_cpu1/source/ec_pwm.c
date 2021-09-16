/*
 * ec_pwm.c
 *
 *  Created on: 2021. 7. 21.
 *      Author: hosung
 */

#include "ec_device.h"

void ec_init_epwm(void)         //pwm 초기화
{
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);  // Disable sync(Freeze clock to PWM as well)
    ec_init_epwm1();
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);   // Initialize ePWM1 and ePWM2
}

void ec_init_epwm_interrupt(void)   //pwm interrupt 초기화
{
    Interrupt_register(INT_EPWM1_TZ, &ec_epwm1TZISR);
    Interrupt_register(INT_EPWM1, &ec_epwm1ISR);
}

void ec_enable_epwm_interrupt(void)   //pwm interrupt 활성화
{
    Interrupt_enable(INT_EPWM1_TZ);
    Interrupt_enable(INT_EPWM1);
}

void ec_init_epwm1(void)
{
    //Set-up Trip-Zone ////////////////////////////////////////////////////////

    EPWM_enableTripZoneSignals(EPWM1_BASE, EPWM_TZ_SIGNAL_CBC1);   // Enable TZ1 as one cycle-by-cycle trip sources

    EPWM_setTripZoneAction(EPWM1_BASE,      // Action on TZ1
                           EPWM_TZ_ACTION_EVENT_TZA,
                           EPWM_TZ_ACTION_HIGH);

    EPWM_enableTripZoneInterrupt(EPWM1_BASE, EPWM_TZ_INTERRUPT_CBC);    // Enable TZ interrupt

    ///////////////////////////////////////////////////////////////////////////

    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(EPWM1_BASE);
    EPWM_setPhaseShift(EPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);
    // TBCLK = SYSCLK / (HSPCLKDIV × CLKDIV)
    // Period = (TBPRD + 1 ) × TBCLK, Period(UP_DOWN) = 2 × TBPRD × TBCLK
    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_10);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 20000U - 1U);    //16bit 0x0000-0xffff, 0-65,535

    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE,        // Set up shadowing
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE,        // Set up shadowing
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 10000U); // Set-up first compare
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_B, 30U); // Set-up first compare

    // Set actions////////////////////////////////////////////////////////////////
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM1_BASE);
    EPWM_setInterruptEventCount(EPWM1_BASE, 1U);
}
