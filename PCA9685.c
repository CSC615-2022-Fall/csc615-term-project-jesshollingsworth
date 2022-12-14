/*****************************************************************************
* | File        :   PCA9685.c
* | Author      :   Waveshare team
* | Function    :   Drive PCA9685
* | Info        :
*                The PCA9685 is an I2C-bus controlled 16-channel LED
*                controller optimized for LCD Red/Green/Blue/Amber
*                (RGBA) color backlighting applications.
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-04
* | Info        :   Basic version
*
******************************************************************************/
#include "PCA9685.h"
#include <math.h>   //floor()
#include <stdio.h>
#include <pigpio.h>
#include <unistd.h> //for usleep



int DEV_I2C_Init(uint8_t Add) // Add is hexadex i2c address
{

    return i2cOpen(1,Add,0);

}


void I2C_Write_Byte(uint8_t handle ,uint8_t Cmd, uint8_t value)
{
    char val[1];
    val[0] = value;
    i2cWriteI2CBlockData(handle, Cmd, val, 1);
}

int I2C_Read_Byte(uint8_t fd ,uint8_t Cmd)
{
    int ref;
    ref = i2cReadByteData (fd, (int)Cmd);
    return ref;
}




/**
 * Write bytes in PCA9685
 *
 * @param reg: register.
 * @param value: value.
 *
 * Example:
 * PCA9685_WriteByte(0x00, 0xff);
 */

static void PCA9685_WriteByte(uint8_t handle, UBYTE reg, UBYTE value)
{
    I2C_Write_Byte(handle, reg, value);
}

/**
 * read byte in PCA9685.
 *
 * @param reg: register.
 *
 * Example:
 * UBYTE buf = PCA9685_ReadByte(0x00);
 */
static UBYTE PCA9685_ReadByte(UBYTE fd, UBYTE reg)
{
    return I2C_Read_Byte(fd, reg);
}

/**
 * Set the PWM output.
 *
 * @param channel: 16 output channels.  //(0 ~ 15)
 * @param on: 12-bit register will hold avalue for the ON time.  //(0 ~ 4095)
 * @param off: 12-bit register will hold the value for the OFF time.  //(0 ~ 4095)
 *
 * @For more information, please see page 15 - page 19 of the datasheet.
 * Example:
 * PCA9685_SetPWM(0, 0, 4095);
 */
static void PCA9685_SetPWM(UBYTE handle, UBYTE channel, UWORD on, UWORD off)
{
    PCA9685_WriteByte(handle, LED0_ON_L + 4*channel, on & 0xFF);
    PCA9685_WriteByte(handle, LED0_ON_H + 4*channel, on >> 8);
    PCA9685_WriteByte(handle, LED0_OFF_L + 4*channel, off & 0xFF);
    PCA9685_WriteByte(handle, LED0_OFF_H + 4*channel, off >> 8);
}

/**
 * PCA9685 Initialize.
 * For the PCA9685, the device address can be controlled by setting A0-A5.
 * On our driver board, control is set by setting A0-A4, and A5 is grounded.
 *
 * @param addr: PCA9685 address.  //0x40 ~ 0x5f
 *
 * Example:
 * PCA9685_Init(0x40);
 */
int PCA9685_Init(char addr)
{
    int handle = DEV_I2C_Init(addr);
    I2C_Write_Byte(handle, MODE1, 0x00);
    return handle;
}

/**
 * Set the frequency (PWM_PRESCALE) and restart.
 *
 * For the PCA9685, Each channel output has its own 12-bit
 * resolution (4096 steps) fixed frequency individual PWM
 * controller that operates at a programmable frequency
 * from a typical of 40 Hz to 1000 Hz with a duty cycle
 * that is adjustable from 0 % to 100 %
 *
 * @param freq: Output frequency.  //40 ~ 1000
 *
 * Example:
 * PCA9685_SetPWMFreq(50);
 */
void PCA9685_SetPWMFreq(UBYTE fd, UWORD freq)
{
    freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
    double prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= freq;
    prescaleval -= 1;
    DEBUG("prescaleval = %lf\r\n", prescaleval);

    UBYTE prescale = floor(prescaleval + 0.5);
    DEBUG("prescaleval = %lf\r\n", prescaleval);
    UBYTE oldmode = PCA9685_ReadByte(fd, MODE1);
    UBYTE newmode = (oldmode & 0x7F) | 0x10; // sleep
    PCA9685_WriteByte(fd, MODE1, newmode); // go to sleep
    PCA9685_WriteByte(fd, PRESCALE, prescale); // set the prescaler
    PCA9685_WriteByte(fd, MODE1, oldmode);
    //usleep(5000);
    PCA9685_WriteByte(fd, MODE1, oldmode | 0x80);  //  This sets the MODE1 register to turn on auto increment.
}

/**
 * Set channel output the PWM duty cycle.
 *
 * @param channel: 16 output channels.  //(0 ~ 15)
 * @param pulse: duty cycle.  //(0 ~ 100  == 0% ~ 100%)
 *
 * Example:
 * PCA9685_SetPwmDutyCycle(1, 100);
 */
void PCA9685_SetPwmDutyCycle(UBYTE handle, UBYTE channel, UWORD pulse)
{
    PCA9685_SetPWM(handle, channel, 0, pulse * (4096 / 100) - 1);
}

/**
 * Set channel output level.
 *
 * @param channel: 16 output channels.  //(0 ~ 15)
 * @param value: output level, 0 low level, 1 high level.  //0 or 1
 *
 * Example:
 * PCA9685_SetLevel(3, 1);
 */
void PCA9685_SetLevel(UBYTE handle, UBYTE channel, UWORD value)
{
    if (value == 1)
        PCA9685_SetPWM(handle, channel, 0, 4095);
    else
        PCA9685_SetPWM(handle, channel, 0, 0);
}
