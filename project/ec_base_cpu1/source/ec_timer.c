/*
 * ec_timer.c
 *
 *  Created on: 2021. 8. 5.
 *      Author: hosung
 */

#include "ec_device.h"

void ec_init_timer(void)    //timer 초기화
{
    ec_set_init_timer(CPUTIMER0_BASE, 200000000U, CPUTIMER_CLOCK_PRESCALER_1);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
//    ec_set_init_timer(CPUTIMER1_BASE, 2000U, CPUTIMER_CLOCK_PRESCALER_1);
//    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
//    ec_set_init_timer(CPUTIMER2_BASE, 2000U, CPUTIMER_CLOCK_PRESCALER_1);
//    CPUTimer_enableInterrupt(CPUTIMER2_BASE);
}

void ec_init_timer_interrupt(void)  //timer interrupt 초기화
{
    Interrupt_register(INT_TIMER0, &ec_cpuTimer0ISR);
//    Interrupt_register(INT_TIMER1, &ec_cpuTimer1ISR);
//    Interrupt_register(INT_TIMER2, &ec_cpuTimer2ISR);
}

void ec_enable_timer_interrupt(void)    //timer interrupt 활성화
{
    Interrupt_enable(INT_TIMER0);
//    Interrupt_enable(INT_TIMER1);
//    Interrupt_enable(INT_TIMER2);
}

void ec_start_timer(void)   //cputimer 시작
{
    CPUTimer_startTimer(CPUTIMER0_BASE);
//    CPUTimer_startTimer(CPUTIMER1_BASE);
//    CPUTimer_startTimer(CPUTIMER2_BASE);
}

void ec_set_init_timer(uint32_t _base, uint32_t _period, uint16_t _prescaler)   // 타이머 초기화 및 설정
{
    CPUTimer_setPeriod(_base, _period); // Initialize timer period
    CPUTimer_setPreScaler(_base, _prescaler);   // Initialize pre-scale
    CPUTimer_stopTimer(_base);     // Make sure timer is stopped
    CPUTimer_reloadTimerCounter(_base);    // Reload all counter register with period value
}

void ec_start_get_timer(uint32_t _base, uint32_t* delay_time)
{
    *delay_time = CPUTimer_getTimerCount(_base);
}

uint32_t ec_finish_get_timer(uint32_t _base, uint32_t* delay_time)
{
    uint32_t Current_Time = CPUTimer_getTimerCount(_base);
    return *delay_time - Current_Time;    //ec_start_get_timer & ec_finish_get_timer used 39 clocky
}
