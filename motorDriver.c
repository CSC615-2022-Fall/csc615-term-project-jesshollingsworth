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
#include "motorDriver.h"
#include "DEV_Config.h"
#include "PCA9685.h"


void setAllMotorsTo(int speed){
    //needs to be filled out with motorhat2's motor1/motor2
    PCA9685_SetPwmDutyCycle(PWMA, speed); //for motor1
    PCA9685_SetPwmDutyCycle(PWMB, speed); //for motor2
}

void frontLeftMotorForward(){
    // PCA9685_SetLevel(AIN1, 0); //make sure MA1 is off
    // PCA9685_SetLevel(AIN2, 1); //make sure MA2 is on

    // PCA9685_SetLevel(BIN1, 0); //make sure MB1 is off
    // PCA9685_SetLevel(BIN2, 1); //make sure MB2 is on
}
void frontRightMotorForward(){

}
void rearLeftMotorForward(){

}
void rearRightMotorForward(){

}
void frontLeftMotorBackward(){

}
void frontRightMotorBackward(){

}
void rearLeftMotorBackward(){

}
void rearRightMotorBackward(){

}

void driveForward(){
    frontLeftMotorForward();
    frontRightMotorForward();
    rearLeftMotorForward();
    rearRightMotorForward();
}

void driveBackward(){
    frontLeftMotorBackward();
    frontRightMotorBackward();
    rearLeftMotorBackward();
    rearRightMotorBackward();
}

void turnLeft(){
    frontLeftMotorBackward();
    frontRightMotorForward();
    rearLeftMotorBackward();
    rearRightMotorForward();
}

void turnRight(){
    frontLeftMotorForward();
    frontRightMotorBackward();
    rearLeftMotorForward();
    rearRightMotorBackward();
}

void driveLeft(){ //needs testing to see if it actually moves left
    frontLeftMotorForward();
    frontRightMotorForward();
    rearLeftMotorBackward();
    rearRightMotorBackward();
}

void driveRight(){ //needs testing to see if it actually moves right
    frontLeftMotorBackward();
    frontRightMotorBackward();
    rearLeftMotorForward();
    rearRightMotorForward();
}