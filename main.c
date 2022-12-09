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

#define DISTANCE_THRESHOLD 15

void mainInit();
void mainUninit();
void sigintHandler(int sig);
void wait_for_button();

int16_t MAIN_SPEED = 80;
int16_t SLOW_SPEED = 60;

pthread_t left_thread;
pthread_t midl_thread;
pthread_t rigt_thread;
Sensor left_sensor = {LEFT_PIN, 0};
Sensor midl_sensor = {MIDL_PIN, 0};
Sensor rigt_sensor = {RIGT_PIN, 0};
distanceSensor front_sensor = {ECHO_PIN, TRIG_PIN, 10000};
pthread_t front_thread;

int continue_lop = 1;

int main(int argc, char *argv[])
    {
    mainInit();

    // wait_for_button();

/*    if (argc > 2)
        {
        MAIN_SPEED = strtoi(argv[0], NULL, 10);
        SLOW_SPEED = strtoi(argv[1], NULL, 10);
        }*/

    while (continue_lop)
        {
        printf("main_loop, distance: %f\n", front_sensor.value);
        while (front_sensor.value > DISTANCE_THRESHOLD)
            {
            while (midl_sensor.status)
                {
                printf("MOVING FORWARD, distance: %f\n", front_sensor.value);
                moveForward(MAIN_SPEED);
                if (front_sensor.value < DISTANCE_THRESHOLD)
                    {
                    break;
                    }
                printf(ERASE);
                }
            if (rigt_sensor.status)
                {
                while (!midl_sensor.status)
                    {
                    printf("TURNING RIGHT, distance: %f\n", front_sensor.value);
                    //moveRight(SLOW_SPEED);
                    //usleep(250000);
                    turnRight( SLOW_SPEED);
                    printf(ERASE);
                    if (front_sensor.value < DISTANCE_THRESHOLD)
                        {
                        break;
                        }
                    }
                }
            if (left_sensor.status)
                {
                while (!midl_sensor.status)
                    {
                    printf("TURNING LEFT, distance: %f\n", front_sensor.value);
                    //moveLeft(SLOW_SPEED);
                    //usleep(250000);
                    turnLeft(SLOW_SPEED);
                    //driftLeftTest(MAIN_SPEED);
                    printf(ERASE);
                    if (front_sensor.value < DISTANCE_THRESHOLD)
                        {
                        break;
                        }
                    }
                }
            }
        stopMotors();
        sleep(1);

        printf("obstacle maneuver\n");

        moveRight(MAIN_SPEED);
        usleep(1300000);
        moveForward(MAIN_SPEED);
        usleep(1600000);
        while (!midl_sensor.status)
            {
            moveLeft(SLOW_SPEED);
            }
        printf("done obstacle maneuver\n");
        }

    mainUninit();
    return 0;
}

void mainInit() {
    if (gpioInitialise() == PI_INIT_FAILED)
    {
        printf("unable to initialize pigpio\n");
        exit(PI_INIT_FAILED);
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
    printf("main uninit\n");
    stopSensing();
    continue_lop = 0;
    pthread_join(left_thread, NULL);
    pthread_join(midl_thread, NULL);
    pthread_join(rigt_thread, NULL);
    pthread_join(front_thread, NULL);
    printf("all threads joined\n");
    uninitMotors();
    gpioTerminate();
    printf("gpio terminated\n");
}

void sigintHandler(int sig) {
    if (sig == SIGINT) {
        stopMotors();
        printf("\nCTRL-C received. Exiting...\n");
        mainUninit();
        exit(0);
    }
}

void wait_for_button()
    {
    gpioSetMode(BUTT_PIN, PI_INPUT);
    printf("waiting for button press\n");
    while (gpioRead(BUTT_PIN) == 0)
        {
        usleep(10000);
        }
    printf("button pressed\n");
    }