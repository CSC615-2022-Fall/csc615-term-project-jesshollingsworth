#include <stdint-gcc.h>
#include <PCA9685.h>
#include <pigpio.h>

#define FRONT_HAT_ADDRESS   0x40
#define BACK_HAT_ADDRESS    0x50
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

void initMotors();
void uninitMotors();

void setMotor(uint8_t hat, uint8_t channel, int16_t speed);

void moveForward(int16_t speed);
void moveBackward(int16_t speed);
void moveLeft(int16_t speed);
void moveRight(int16_t speed);
void turnLeft(int16_t speed);
void turnRight(int16_t speed);
void stopMotors();
