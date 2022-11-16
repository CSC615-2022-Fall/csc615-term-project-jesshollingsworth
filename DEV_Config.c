/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"
#include <unistd.h>
#include <fcntl.h>
#include <pigpio.h>
uint32_t fd;
int INT_PIN;
/******************************************************************************
function:	Equipment Testing
parameter:
Info:   Only supports Jetson Nano and Raspberry Pi
******************************************************************************/
/*
static int DEV_Equipment_Testing(void)
{
-	int i;
	int fd;
	char value_str[20];
	fd = open("/etc/issue", O_RDONLY);
    printf("Current environment: ");
	while(1) {
		if (fd < 0) {
			return -1;
		}
		for(i=0;; i++) {
			if (read(fd, &value_str[i], 1) < 0) {
				return -1;
			}
			if(value_str[i] ==32) {
				printf("\r\n");
				break;
			}
			printf("%c",value_str[i]);
		}
		break;
	}
	if(i<5) {
		printf("Unrecognizable\r\n");
        return -1;
	} else {
		char RPI_System[10]   = {"Raspbian"};
		for(i=0; i<6; i++) {
			if(RPI_System[i] != value_str[i]) {
                return -1;
			}
		}
        return 'R';
	}
	return -1;
}
*/

/******************************************************************************
function:	GPIO Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    /*
        0:  INPT
        1:  OUTP
    */

// USE_WIRINGPI_LIB
// USE GPIO library
    if(Mode == 0 || Mode == PI_INPUT){
        gpioSetMode(Pin, PI_INPUT);
        gpioSetPullUpDown(Pin, PI_PUD_UP);
    }else{
        gpioSetMode(Pin, PI_OUTPUT);
    }

}

void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{

// USE_WIRINGPI_LIB
    gpioWrite(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
    UBYTE Read_value = 0;
// USE_WIRINGPI_LIB
    Read_value = gpioRead(Pin);

    return Read_value;
}


/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms) //still need to figure this out
{

   usleep(1000);

}


void GPIO_Config(void)
{
   if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialisation failed\n");
      return ;
   }

}

/******************************************************************************
function:	I2C Function initialization and transfer
parameter:
Info:
******************************************************************************/
UBYTE DEV_I2C_Init(uint8_t Add) // Add is hexadex i2c address
{
        printf("Pigpio I2C Device\n");
        fd = i2cOpen(1,Add,0);
        printf("fd = %d\n", fd);
        return fd;
}


void I2C_Write_Byte(uint8_t fd ,uint8_t Cmd, uint8_t value)
{
    char * val = &value;
    int ref0 = i2cWriteI2CBlockData(fd, Cmd, val, 1);
    i2cWriteI2CBlockData(fd, Cmd, ptrVal, 1);
}

int I2C_Read_Byte(uint8_t fd ,uint8_t Cmd)
{
    int ref;
    ref = i2cReadByteData (fd, (int)Cmd);
    return ref;
}


int I2C_Read_Word(uint8_t fd, uint8_t Cmd)
{
        int ref;
        ref = i2cReadWordData (fd, (int) Cmd);
    return ref;
}

/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{

    //GPIO_Config();

    DEV_I2C_Init(0x29);

    return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{
 // gpioTerminate();
  i2cClose(fd);
}
