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
#include <pthread.h>
#include <pigpio.h>
#include <signal.h>
#include <unistd.h>

#include "motors.h"
#include "sensors.h"

// line sensor pins
#define LEFT_PIN 17
#define MIDL_PIN 27
#define RIGT_PIN 22

// ultrasonic sensor pins
#define ECHO_PIN 23
#define TRIG_PIN 24

// button pin(s)
#define BUTT_PIN 25

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"
#define ERASE "\033[A\033[2K"

int continue_loop = 1;

void mainInit();
void mainUninit();
void sigintHandler(int sig);

const int16_t MAIN_SPEED = 80;

int main(int argc, char *argv[]) {
    mainInit();

/*
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
*/
    
    Sensor left_sensor = {LEFT_PIN, 0};
    Sensor * left_sensor_ptr = &left_sensor;

    Sensor midl_sensor = {MIDL_PIN, 0};
    Sensor * midl_sensor_ptr = &midl_sensor;

    Sensor rigt_sensor = {RIGT_PIN, 0};
    Sensor * rigtt_sensor_ptr = &rigt_sensor;

    pthread_t left_thread, midl_thread, rigt_thread;
    if (pthread_create(&left_thread, NULL, sense, (void *)left_sensor_ptr) != 0)
        {
        printf("failed to create thread\n");
        }
    if (pthread_create(&midl_thread, NULL, sense, (void *)midl_sensor_ptr) != 0)
        {
        printf("failed to create thread\n");
        }
    if (pthread_create(&rigt_thread, NULL, sense, (void *)rigt_sensor_ptr) != 0)
        {
        printf("failed to create thread\n");
        }


    while(continue_loop)
        {
            printf("LEFT LINE SENSOR:\t\t%s\n",
                (left_sensor.status) ? RED "NOT DETECTED" RESET : GREEN "DETECTED" RESET);
            }
            printf("MIDL LINE SENSOR:\t\t%s\n",
                (midl_sensor.status) ? RED "NOT DETECTED" RESET : GREEN "DETECTED" RESET);
            }
            printf("RIGT LINE SENSOR:\t\t%s\n",
                (rigt_sensor.status) ? RED "NOT DETECTED" RESET : GREEN "DETECTED" RESET);
            }
            sleep(.5);
            printf(ERASE ERASE ERASE);
        }

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
        stopSensing();
        continue_loop = 0;
        exit(0);
    }
}
