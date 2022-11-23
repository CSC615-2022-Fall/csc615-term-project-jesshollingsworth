#ifndef CSC615_TERM_PROJECT_JESSHOLLINGSWORTH_MOTORS_H
#define CSC615_TERM_PROJECT_JESSHOLLINGSWORTH_MOTORS_H

#include <stdint-gcc.h>
#include <PCA9685.h>

#define FRONT_HAT_ADDRESS   0x40
#define BACK_HAT_ADDRESS    0x50
#define LEFT_WHEEL          0x00
#define RIGHT_WHEEL         0x05

#define FORWARD             1
#define BACKWARD            0



//#define PWMA PCA_CHANNEL_0
//#define AIN1 PCA_CHANNEL_1
//#define AIN2 PCA_CHANNEL_2
//#define PWMB PCA_CHANNEL_5
//#define BIN1 PCA_CHANNEL_3
//#define BIN2 PCA_CHANNEL_4

//uint16_t SPEED = 0;

void initMotors();
void uninitMotors();

void setSpeed(uint16_t speed);

void setMotor(uint8_t hat, uint8_t channel, uint16_t direction, uint16_t speed);

void moveForward(uint16_t speed);
void moveBackward();
void moveLeft();
void moveRight();
void turnLeft();
void turnRight();

#endif //CSC615_TERM_PROJECT_JESSHOLLINGSWORTH_MOTORS_H
