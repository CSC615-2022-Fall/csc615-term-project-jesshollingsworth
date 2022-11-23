/************************************************************** 
* Class:  CSC-615-01 Fall 2022 
* Name: Tony Huang
* Student ID: 915090688 
* Github ID: tzphuang
* Project: Group Term Project
* 
* File: main.c
* 
* Description: Driver file of our self driving car. This file
* sets up our gpio pins, pthreads for updating our relevant sensor variables,
* and has the overarching logic for how our car will naviagate 
* the obstacle course. This file also contains helper functions that obfuscate
* certain lower level functionality for easier code reading.
* 
**************************************************************/ 

#include <stdio.h> //standard in/out
#include <stdlib.h>
#include <pigpio.h>

#include "main.h"
#include "motors.h"
#include "motorDriver.h"
#include "sensorFunctions.h"
#include "DEV_Config.h"
#include "PCA9685.h"

int main(int argc, char *argv[]) {
    //printf("Hello World!\n");
    //int speed = 0;

    if (gpioInitialise() < 0)
    {
        fprintf(stderr, "pigpio initialisation failed\n");
        return 1;
    }

//    UBYTE motorHat1FD = PCA9685_Init(MOTORHAT1ADDRESS);
//    printf("%X\n", motorHat1FD);

//    UBYTE motorHat2FD = PCA9685_Init(MOTORHAT2ADDRESS);

    // printf("Motorhat1: %d\n",motorHat1FD);
    // printf("Motorhat2: %d\n",motorHat2FD);

    //testing motors to see if they run properly
/*    for (int numLoops = 0; numLoops < 1; numLoops++) {
        //turn on motor to max speed
        speed = 100;
        // PCA9685_SetPwmDutyCycle(PWMA, speed); //for motor1
        // PCA9685_SetPwmDutyCycle(PWMB, speed); //for motor2

        setAllMotorsTo(motorHat1FD, speed);
        setAllMotorsTo(motorHat2FD, speed);


        //set motor to forwards
        //let us say this is forward
        // PCA9685_SetLevel(AIN1, 0); //make sure MA1 is off
        // PCA9685_SetLevel(AIN2, 1); //make sure MA2 is on
        driveForward(motorHat1FD);
        driveForward(motorHat2FD);

        //slow down the motor until the motor speed is 0
        while(speed > 0){
            if(speed < 0){
                speed = 0;
            }
            speed -= 5;
            //PCA9685_SetPwmDutyCycle(PWMA, speed);
            setAllMotorsTo(motorHat1FD, speed);
            setAllMotorsTo(motorHat2FD, speed);
            time_sleep(.2);

        }

        //stop the motor for 1 second
        time_sleep(1);

        //set motor to backwards
        //let us say this is backward
        // PCA9685_SetLevel(AIN1, 1); //make sure MA1 is on
        // PCA9685_SetLevel(AIN2, 0); //make sure MA2 is off
        driveBackward(motorHat1FD);
        driveBackward(motorHat2FD);


        //speed up the motor until the motor speed is 100
        while(speed < 100){
            if(speed > 100){
                speed = 100;
            }

            speed += 5;
            //PCA9685_SetPwmDutyCycle(PWMA, speed);
            setAllMotorsTo(motorHat1FD, speed);
            setAllMotorsTo(motorHat2FD, speed);
            time_sleep(.2);
        }

        //after this cycle reset the speed to 0
        speed = 0;
        //PCA9685_SetPwmDutyCycle(PWMA, speed);
        setAllMotorsTo(motorHat1FD, speed);
        setAllMotorsTo(motorHat2FD, speed);
        time_sleep(1);
    }*/

    initMotors();
    moveForward(100);
    time_sleep(2);
    moveForward(50);
    time_sleep(2);
    moveForward(0);
    uninitMotors();

    return 0;
}

void initializeGpioPins(){

}
