/**************************************************************
* Class:  CSC-615-01 Fall 2022
* Name: Tony Huang, Jess Hollingsworth, Jesse Henrick
* Student ID: 915090688, 920974506, 921323452
* Github ID: tzphuang, jesshollingsworth, jessehenrick
* Project: Group Term Project
*
* File: motors.c
*
* Description: File implements motors.h functions using a
* lower level predefined library so we can abstract new function calls
* based on those lower level functionalities.
*
**************************************************************/

#include "motors.h"
#include <stdio.h>

int FRONT_HAT_HANDLE;
int BACK_HAT_HANDLE;

void initMotors() {
    FRONT_HAT_HANDLE = PCA9685_Init(FRONT_HAT_ADDRESS);
    BACK_HAT_HANDLE = PCA9685_Init(BACK_HAT_ADDRESS);
}

void uninitMotors() {
    printf("insite uninit motors\n");
    stopMotors();
    i2cClose(FRONT_HAT_HANDLE);
    i2cClose(BACK_HAT_HANDLE);
    printf("motors uninited\n");
}

void setMotor(uint8_t hat, uint8_t wheel, int16_t speed) {

    // set correct hat address
    if (hat == FRONT_HAT_ADDRESS) {
        hat = FRONT_HAT_HANDLE;
    } else if (hat == BACK_HAT_ADDRESS) {
        hat = BACK_HAT_HANDLE;
    } else {
        // invalid hat address
        return;
    }

    // set correct address for positive and negative terminals
    uint8_t powerAddress = 0;
    if (wheel == RIGHT_WHEEL) {
        powerAddress = 2;
    }

    if (speed < 0) { // set direction backwards
        PCA9685_SetLevel(hat, powerAddress + 1, 1);
        PCA9685_SetLevel(hat, powerAddress + 2, 0);
        // flip sign on speed
        speed *= -1;
    }
    else { // set direction forwards
        PCA9685_SetLevel(hat, powerAddress + 1, 0);
        PCA9685_SetLevel(hat, powerAddress + 2, 1);
    }

    //set speed
    PCA9685_SetPwmDutyCycle(hat, wheel, speed);
}

// all four motors spin forward
void moveForward(int16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL,speed);
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, speed);
}

void stopMotors() {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL, 0);
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, 0);
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, 0);
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, 0);
}

// all four motors spin backwards
void moveBackward(int16_t speed) {

    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL,(int16_t)(-speed));
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(-speed));
}

// left motors spin inward, right motors spin outward
void moveLeft(int16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL, speed);
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, speed);
}

// left motors spin outward, right motors spin inward
void moveRight(int16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL,(int16_t)(-speed));
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(-speed));
}

// left motors dont spin, right motors spin forward
void turnRight(int16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL,(int16_t)(-speed));
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, speed);
}

// left motors spin forward, right motors dont spin
void turnLeft(int16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL,speed);
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(-speed));
}

void turnLeftAROUND(int16_t speed) {

    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, (int16_t)(-speed));
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, speed);
}

void driftLeftTest(int16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL,speed);
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(speed / 2));
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, speed);
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, (int16_t)(speed / 2));
    }
