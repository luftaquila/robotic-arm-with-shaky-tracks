/*
 * ec_i2c.c
 *
 *  Created on: 2021. 8. 31.
 *      Author: hosung
 */

#include "ec_device.h"

void ec_init_i2c(void){
    I2C_disableModule(I2CB_BASE);
    I2C_initMaster(I2CB_BASE, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CB_BASE, I2C_MASTER_SEND_MODE);
    I2C_setSlaveAddress(I2CB_BASE, 60);
    I2C_enableLoopback(I2CB_BASE);
    I2C_setOwnSlaveAddress(I2CB_BASE, 0);
    I2C_setBitCount(I2CB_BASE, I2C_BITCOUNT_8);
    I2C_setDataCount(I2CB_BASE, 2);
    I2C_setAddressMode(I2CB_BASE, I2C_ADDR_MODE_7BITS);
    I2C_enableFIFO(I2CB_BASE);
    I2C_clearInterruptStatus(I2CB_BASE, I2C_INT_RXFF | I2C_INT_TXFF);
    I2C_setFIFOInterruptLevel(I2CB_BASE, I2C_FIFO_TX2, I2C_FIFO_RX2);
    I2C_enableInterrupt(I2CB_BASE, I2C_INT_RXFF | I2C_INT_TXFF);
    I2C_setEmulationMode(I2CB_BASE, I2C_EMULATION_STOP_SCL_LOW);
    I2C_enableModule(I2CB_BASE);
}
