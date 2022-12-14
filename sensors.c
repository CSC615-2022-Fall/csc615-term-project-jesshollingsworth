/**************************************************************
* Class:  CSC-615-01 Fall 2022
* Name: Tony Huang, Christopher Ling, Jess Hollingsworth, Jesse Henrick, Willi Vargas, Igor Tsygankov
* Student ID: 915090688, 918266861, 920974506, 921323452, 918778307, 918440047
* Github ID: tzphuang, dslayer1392, jesshollingsworth, jessehenrick, williv17, igortsygankov
* Project: Group Term Project
*
* File: sensors.c
*
* Description: This file holds the functions that will update their
* relevant global variables to be used in main.c. These functions
* specifically will be passed into pthreadCreate so we constantly
* have updated variables we can apply our self driving car's logic to.
* The global variables set here are instantiated in this file and
* shared across multiple source files.
*
**************************************************************/

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "sensors.h"

int continue_loop = 1;
uint32_t start1 = 0;
uint32_t end1 = 0;

uint32_t start2 = 0;
uint32_t end2 = 0;

void alertFunction1 (int gpio, int level, uint32_t tick)
    {
    if (level == 1)
        {
        start1 = tick;
        }
    if (level == 0)
        {
        end1 = tick;
        }
    }

void alertFunction2 (int gpio, int level, uint32_t tick)
    {
    if (level == 1)
        {
        start2 = tick;
        }
    if (level == 0)
        {
        end2 = tick;
        }
    }

void stopSensing ()
    {
    continue_loop = 0;
    printf("Set continue_loop to 0\n");
    }

void *sense (void *ptr)
    {
    Sensor *sensor = (Sensor *) ptr;
    gpioSetMode(sensor->pin, PI_INPUT);
    while (continue_loop)
        {
        sensor->status = gpioRead(sensor->pin);
        }
    printf("STOP SENSING on pin: %d\n", sensor->pin);
    return NULL;
    }

void *read_distance1 (void *args)
    {
    double distance;
    distanceSensor *arg_ptr = (distanceSensor *) args;
    gpioSetMode(arg_ptr->echo, PI_INPUT);
    gpioSetMode(arg_ptr->trig, PI_OUTPUT);
    while (continue_loop)
        {
        gpioDelay(100000);
        gpioTrigger(arg_ptr->trig, 10, 1);
        gpioSetAlertFunc(arg_ptr->echo, alertFunction1);
        distance = 0.017 * (end1 - start1);
        //printf("read_distance, distance: %f\n", distance);
        if (distance > 200)
            {
            distance = 200;
            }
        arg_ptr->value = distance;
        }
    printf("STOP FRONT DISTANCE READING\n");
    return NULL;
    }

void *read_distance2 (void *args)
    {
    double distance;
    distanceSensor *arg_ptr = (distanceSensor *) args;
    gpioSetMode(arg_ptr->echo, PI_INPUT);
    gpioSetMode(arg_ptr->trig, PI_OUTPUT);
    while (continue_loop)
        {
        gpioDelay(100000);
        gpioTrigger(arg_ptr->trig, 10, 1);
        gpioSetAlertFunc(arg_ptr->echo, alertFunction2);
        distance = 0.017 * (end2 - start2);
        //printf("read_distance, distance: %f\n", distance);
        if (distance > 200)
            {
            distance = 200;
            }
        arg_ptr->value = distance;
        }
    printf("STOP SIDE DISTANCE READING\n");
    return NULL;
    }
