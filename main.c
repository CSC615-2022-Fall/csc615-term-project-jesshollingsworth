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
#include <signal.h>
#include <unistd.h>

#include "motors.h"
#include "sensorFunctions.h"
#include "PCA9685.h"

void mainInit();
void mainUninit();
void sigintHandler(int sig);

const int16_t MAIN_SPEED = 80;

int main(int argc, char *argv[]) {
    mainInit();

    moveForward(MAIN_SPEED);
    sleep(1);
    moveBackward(MAIN_SPEED);
    sleep(1);
    turnRight(MAIN_SPEED);
    sleep(2);
    turnLeft(MAIN_SPEED);
    sleep(2);
    moveRight(MAIN_SPEED);
    sleep(1);
    moveLeft(MAIN_SPEED);
    sleep(1);


    mainUninit();
    return 0;
}

void mainInit() {
    if (gpioInitialise() == PI_INIT_FAILED)
    {
        exit(1);
    }
    initMotors();
    signal(SIGINT, sigintHandler);
}

void mainUninit() {
    uninitMotors();
    gpioTerminate();
}

void sigintHandler(int sig) {
    if (sig == SIGINT) {
        printf("\nCTRL-C received. Exiting...\n");
        mainUninit();
        exit(0);
    }
}