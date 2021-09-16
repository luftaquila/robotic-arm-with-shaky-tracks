/*
 * ec_spi.c
 *
 *  Created on: 2021. 8. 30.
 *      Author: hosung
 */

#include "ec_device.h"

void ec_init_spi(void) //SPIA initialization
{
    SPI_disableModule(SPIA_BASE);
    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_MASTER, 1000000,     16);
    SPI_disableFIFO(SPIA_BASE);
    SPI_enableModule(SPIA_BASE);
}
