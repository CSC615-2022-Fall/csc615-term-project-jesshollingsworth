/************************************************************** 
* Class:  CSC-615-01 Fall 2022 
* Name: Tony Huang
* Student ID: 915090688 
* Github ID: tzphuang
* Project: Group Term Project
* 
* File: motorDriver.h
* 
* Description: Header file for motorDriver.c to store function calls
* that abstract the previous motor functions from our given librarys
* and simplifies them so we can call functions without needing to 
* call the lower level functions. (example: so instead of calling 
* set speed and turn on for each individual motor, we can just have a function
* that just says driveForward instead.)
* 
**************************************************************/ 

#ifndef MOTORDRIVER

#define UBYTE uint8_t
#define MOTORHAT1ADDRESS 0x40
#define MOTORHAT2ADDRESS 0x50

//GPIO config
#define PWMA        0
#define AIN1        1
#define AIN2        2
#define PWMB        5
#define BIN1        3
#define BIN2        4

#define MOTORA       0
#define MOTORB       1

#define MOTORDRIVER

void setAllMotorsTo(UBYTE fd, int speed);

//normal car functions we will need to move the car through the obstacle course

//the following functions do not actually propel the car, the car is always "on"
//we are just setting the direction of the car motors 
void frontLeftMotorForward(UBYTE fd);
void frontRightMotorForward(UBYTE fd);
void rearLeftMotorForward(UBYTE fd);
void rearRightMotorForward(UBYTE fd);

void frontLeftMotorBackward(UBYTE fd);
void frontRightMotorBackward(UBYTE fd);
void rearLeftMotorBackward(UBYTE fd);
void rearRightMotorBackward(UBYTE fd);

void driveForward(UBYTE fd);    
void driveBackward(UBYTE fd);
void turnLeft();
void turnRight();

//omni-directional wheel functions we may choose to implement
void driveLeft();
void driveRight();

#endif