
#include "ec_main.h"

inline void ec_init_pinmux(void)
{
    GPIO_setPinConfig(GPIO_0_EPWM1A);       //GPIO_0    -> EPWM1A
    GPIO_setPinConfig(GPIO_1_EPWM1B);       //GPIO_1    -> EPWM1B
    GPIO_setPinConfig(GPIO_2_SDAB);         //GPIO_2    -> SDAB
    GPIO_setPinConfig(GPIO_3_SCLB);         //GPIO_3    -> SCLB
    GPIO_setPinConfig(GPIO_12_GPIO12);      //GPIO_12   -> GPIO12   // for X-bar Input
    GPIO_setPinConfig(GPIO_16_SPISIMOA);    //GPIO_16   -> SPISIMOA
    GPIO_setPinConfig(GPIO_17_SPISOMIA);    //GPIO_17   -> SPISOMIA
    GPIO_setPinConfig(GPIO_18_SPICLKA);     //GPIO_18   -> SPICLKA
    GPIO_setPinConfig(GPIO_19_SPISTEA);     //GPIO_19   -> SPISTEA
    GPIO_setPinConfig(GPIO_31_GPIO31);      //GPIO_31   -> GPIO31   // output

    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);     //EPWM1A
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_PULLUP);     //EPWM1B
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_PULLUP);     //SDAB
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_PULLUP);     //SCLB
    GPIO_setPadConfig(12, GPIO_PIN_TYPE_PULLUP);    //X-bar Input
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_PULLUP);    //SPISIMOA
    GPIO_setPadConfig(17, GPIO_PIN_TYPE_PULLUP);    //SPISOMIA
    GPIO_setPadConfig(18, GPIO_PIN_TYPE_PULLUP);    //SPICLKA
    GPIO_setPadConfig(19, GPIO_PIN_TYPE_PULLUP);    //SPISTEA
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_STD);       //GPIO Output

}

inline void ec_init(void)  // main �ʱ�ȭ �� Ȱ��ȭ
{
    Device_init();  // Initialize device clock and peripherals

    Device_initGPIO();      // Disable pin locks and enable internal pull-ups.

    ec_init_variable();
    ec_init_interrupt();    // interrupt �ʱ�ȭ
    ec_init_pinmux();       // pinmux �ʱ�ȭ
    ec_init_timer();        // timer �ʱ�ȭ
    ec_init_gpio();         // gpio �ʱ�ȭ
    ec_init_xbar();         // xbar �ʱ�ȭ
    ec_init_epwm();         // epwm �ʱ�ȭ
    ec_init_adc();          // adc �ʱ�ȭ
    ec_init_spi();          // spi �ʱ�ȭ
    ec_init_i2c();          // i2c �ʱ�ȭ

    ec_enable_interrupt();  // interrupt Ȱ��ȭ
    ec_start_timer();       // timer interrupt ����

    ERTM;
}

int main(void)  //main �Լ�
{
    ec_init();  //main �ʱ�ȭ �� Ȱ��ȭ

    for(;;) //loop
    {
        ec.test.count[0]++;

        ECCLKS;
        DEVICE_DELAY_US(10);
        ECCLKF;
        ADC_forceMultipleSOC(ADCA_BASE, ADC_FORCE_SOC0);
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);
        ec.adc.adcAResult[0] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    }
}
