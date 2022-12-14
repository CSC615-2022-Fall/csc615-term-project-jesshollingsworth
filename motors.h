/**************************************************************
* Class:  CSC-615-01 Fall 2022
* Name: Tony Huang, Christopher Ling, Jess Hollingsworth, Jesse Henrick, Willi Vargas, Igor Tsygankov
* Student ID: 915090688, 918266861, 920974506, 921323452, 918778307, 918440047
* Github ID: tzphuang, dslayer1392, jesshollingsworth, jessehenrick, williv17, igortsygankov
* Project: Group Term Project
*
* File: motors.h
*
* Description: Header file for motors.c to store function calls
* that abstract the previous motor functions from our given librarys
* and simplifies them so we can call functions without needing to
* call the lower level functions. (example: so instead of calling
* set speed and turn on for each individual motor, we can just have a function
* that just says driveForward instead.)
*
**************************************************************/

#include <stdint-gcc.h>
#include <PCA9685.h>
#include <pigpio.h>

#define FRONT_HAT_ADDRESS   0x50
#define BACK_HAT_ADDRESS    0x40
#define LEFT_WHEEL          0x00
#define RIGHT_WHEEL         0x05
#define MOTOR_SPEED         80

#define FORWARD             1
#define BACKWARD            0

//#define PWMA PCA_CHANNEL_0
//#define AIN1 PCA_CHANNEL_1
//#define AIN2 PCA_CHANNEL_2
//#define PWMB PCA_CHANNEL_5
//#define BIN1 PCA_CHANNEL_3
//#define BIN2 PCA_CHANNEL_4

void initMotors ();
void uninitMotors ();

void setMotor (uint8_t hat, uint8_t channel, int16_t speed);

void moveForward (int16_t speed);
void moveBackward (int16_t speed);
void moveLeft (int16_t speed);
void moveRight (int16_t speed);
void turnLeft (int16_t speed);
void turnRight (int16_t speed);
void turnLeftAROUND (int16_t speed);
void driftLeftTest (int16_t speed);
void stopMotors ();
