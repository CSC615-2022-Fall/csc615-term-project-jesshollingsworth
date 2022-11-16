/************************************************************** 
* Class:  CSC-615-01 Fall 2022 
* Name: Tony Huang
* Student ID: 915090688 
* Github ID: tzphuang
* Project: Group Term Project
* 
* File: motorDriver.c
* 
* Description: File implements motorDrive.h functions using a 
* lower level predefined library so we can abstract new function calls
* based on those lower level functionalities.
* 
**************************************************************/ 
#include <stdio.h>
#include <stdint.h>
#include "motorDriver.h"
#include "DEV_Config.h"
#include "PCA9685.h"

// #define PWMA        PCA_CHANNEL_0
// #define AIN1        PCA_CHANNEL_1
// #define AIN2        PCA_CHANNEL_2
// #define PWMB        PCA_CHANNEL_5
// #define BIN1        PCA_CHANNEL_3
// #define BIN2        PCA_CHANNEL_4


void setAllMotorsTo(UBYTE fd, int speed){
    //needs to be filled out with motorhat2's motor1/motor2
    PCA9685_SetPwmDutyCycle(fd, PWMA, speed); //for motor1
    PCA9685_SetPwmDutyCycle(fd, PWMB, speed); //for motor2
}

void frontLeftMotorForward(UBYTE fd){
    PCA9685_SetLevel(fd, AIN1, 0); //make sure MA1 is off
    PCA9685_SetLevel(fd, AIN2, 1); //make sure MA2 is on
}
void frontRightMotorForward(UBYTE fd){
    PCA9685_SetLevel(fd, BIN1, 0); //make sure MA1 is off
    PCA9685_SetLevel(fd, BIN2, 1); //make sure MA2 is on
}
void rearLeftMotorForward(UBYTE fd){
    PCA9685_SetLevel(fd, AIN1, 0); //make sure MA1 is off
    PCA9685_SetLevel(fd, AIN2, 1); //make sure MA2 is on
}
void rearRightMotorForward(UBYTE fd){
    PCA9685_SetLevel(fd, BIN1, 0); //make sure MA1 is off
    PCA9685_SetLevel(fd, BIN2, 1); //make sure MA2 is on
}
void frontLeftMotorBackward(UBYTE fd){
    PCA9685_SetLevel(fd, AIN1, 1); //make sure MA1 is off
    PCA9685_SetLevel(fd, AIN2, 0); //make sure MA2 is on
}
void frontRightMotorBackward(UBYTE fd){
    PCA9685_SetLevel(fd, BIN1, 1); //make sure MA1 is off
    PCA9685_SetLevel(fd, BIN2, 0); //make sure MA2 is on
}
void rearLeftMotorBackward(UBYTE fd){
    PCA9685_SetLevel(fd, AIN1, 1); //make sure MA1 is off
    PCA9685_SetLevel(fd, AIN2, 0); //make sure MA2 is on
}
void rearRightMotorBackward(UBYTE fd){
    PCA9685_SetLevel(fd, BIN1, 1); //make sure MA1 is off
    PCA9685_SetLevel(fd, BIN2, 0); //make sure MA2 is on
}

void driveForward(UBYTE fd){
    if(fd == 0){
        frontLeftMotorForward(fd);
        frontRightMotorForward(fd);
    }else{
        rearLeftMotorForward(fd);
        rearRightMotorForward(fd);
    }
}

void driveBackward(UBYTE fd){
    if(fd == 0){
        frontLeftMotorBackward(fd);
        frontRightMotorBackward(fd);
    }else{
        rearLeftMotorBackward(fd);
        rearRightMotorBackward(fd);
    }
}

// void turnLeft(){
//     frontLeftMotorBackward();
//     frontRightMotorForward();
//     rearLeftMotorBackward();
//     rearRightMotorForward();
// }

// void turnRight(){
//     frontLeftMotorForward();
//     frontRightMotorBackward();
//     rearLeftMotorForward();
//     rearRightMotorBackward();
// }

// void driveLeft(){ //needs testing to see if it actually moves left
//     frontLeftMotorForward();
//     frontRightMotorForward();
//     rearLeftMotorBackward();
//     rearRightMotorBackward();
// }

// void driveRight(){ //needs testing to see if it actually moves right
//     frontLeftMotorBackward();
//     frontRightMotorBackward();
//     rearLeftMotorForward();
//     rearRightMotorForward();
// }