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

void mainInit();
void mainUninit();
void sigintHandler(int sig);

const int16_t MAIN_SPEED = 45;
pthread_t left_thread;
pthread_t midl_thread;
pthread_t rigt_thread;
Sensor left_sensor = {LEFT_PIN, 0};
Sensor midl_sensor = {MIDL_PIN, 0};
Sensor rigt_sensor = {RIGT_PIN, 0};
distanceSensor front_sensor = {ECHO_PIN, TRIG_PIN, 0};
pthread_t front_thread;

int continue_lop = 1;


int main(int argc, char *argv[]) {
    mainInit();

    /*
    // send trigger signal
    gpioWrite(TRIG_PIN, 1);
    gpioDelay(10);
    gpioWrite(TRIG_PIN, 0);

    // wait for ECHO pin pullup
    while (gpioRead(ECHO_PIN) == 0) { ; }

    // start relative timer
    uint32_t micro_seconds_start = gpioTick();

    // wait for echo pin pulldown
    while (gpioRead(ECHO_PIN) == 1) { ; }

    // count elapsed microseconds since ECHO pin pullup
    uint32_t micro_echo_time = gpioTick() - micro_seconds_start;

    double distance = micro_echo_time * 0.017;
    printf("distance: %f\n", distance);
    */

    while(continue_lop)
        {
        /*
        turnLeftAROUND(MAIN_SPEED);

        while (midl_sensor.status)
            {
            printf("should move forward\n");
            moveForward(MAIN_SPEED);
            }
        if (rigt_sensor.status)
            {
            printf("should move right\n");
            while (!midl_sensor.status)
                {
                turnRight(MAIN_SPEED / (3);
                }
            }
        if (left_sensor.status)
            {
            printf("should move left\n");
            while (!midl_sensor.status)
                {
                turnLeft(MAIN_SPEED / 3);
                }
            }

        usleep(10000);
        printf(ERASE);
        */
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
    if (pthread_create(&left_thread, NULL, sense, &left_sensor) != 0) {
        printf("failed to create left thread\n");
    }
    if (pthread_create(&midl_thread, NULL, sense, &midl_sensor) != 0) {
        printf("failed to create middle thread\n");
    }
    if (pthread_create(&rigt_thread, NULL, sense, &rigt_sensor) != 0) {
        printf("failed to create right thread\n");
    }
    if (pthread_create(&front_thread, NULL, read_distance, &front_sensor) != 0) {
        printf("failed to create front thread\n");
    }
}

void mainUninit() {
    stopSensing();
    continue_lop = 0;
    pthread_join(left_thread, NULL);
    pthread_join(midl_thread, NULL);
    pthread_join(rigt_thread, NULL);
    pthread_join(front_thread, NULL);
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
