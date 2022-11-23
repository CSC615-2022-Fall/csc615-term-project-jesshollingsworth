#include "motors.h"

int FRONT_HAT_HANDLE;
int BACK_HAT_HANDLE;

void initMotors() {
    FRONT_HAT_HANDLE = PCA9685_Init(FRONT_HAT_ADDRESS);
    BACK_HAT_HANDLE = PCA9685_Init(BACK_HAT_ADDRESS);
}

void uninitMotors() {
    i2cClose(FRONT_HAT_HANDLE);
    i2cClose(BACK_HAT_HANDLE);
}

void setSpeed(uint16_t speed) {
    //SPEED = speed;
    PCA9685_SetPwmDutyCycle(FRONT_HAT_HANDLE, LEFT_WHEEL, speed);
    PCA9685_SetPwmDutyCycle(FRONT_HAT_HANDLE, RIGHT_WHEEL, speed);
    PCA9685_SetPwmDutyCycle(BACK_HAT_HANDLE, LEFT_WHEEL, speed);
    PCA9685_SetPwmDutyCycle(BACK_HAT_HANDLE, RIGHT_WHEEL, speed);
}

void setMotor(uint8_t hat, uint8_t wheel, uint16_t direction, uint16_t speed) {
    // set correct hat address
    if (hat == FRONT_HAT_ADDRESS) {
        hat = FRONT_HAT_HANDLE;
    } else if (hat == BACK_HAT_ADDRESS) {
        hat = BACK_HAT_HANDLE;
    } else {
        // invalid hat address
        return;
    }

    //set speed
    PCA9685_SetPwmDutyCycle(hat, wheel, speed);

    if (wheel == LEFT_WHEEL) {
        wheel = 0;
    }
    if (wheel == RIGHT_WHEEL) {
        wheel = 2;
    }

    //set orientation
    if (direction == FORWARD) {
        PCA9685_SetLevel(hat, wheel+1, 0);
        PCA9685_SetLevel(hat, wheel+2, 1);
    }
    if (direction == BACKWARD) {
        PCA9685_SetLevel(hat, wheel+1, 1);
        PCA9685_SetLevel(hat, wheel+2, 0);
    }

}

// all four motors spin forward
void moveForward(uint16_t speed) {
    setMotor(FRONT_HAT_ADDRESS, LEFT_WHEEL, FORWARD, speed);
    setMotor(FRONT_HAT_ADDRESS, RIGHT_WHEEL, FORWARD, speed);
    setMotor(BACK_HAT_ADDRESS, LEFT_WHEEL, FORWARD, speed);
    setMotor(BACK_HAT_ADDRESS, RIGHT_WHEEL, FORWARD, speed);
}

// all four motors spin backwards
void moveBackward() {




}

// left motors spin inward, right motors spin outward
void moveLeft() {




}

// left motors spin outward, right motors spin inward
void moveRight() {



}

// left motors dont spin, right motors spin forward
void turnLeft() {

}

// left motors spin forward, right motors dont spin
void turnRight() {

}

