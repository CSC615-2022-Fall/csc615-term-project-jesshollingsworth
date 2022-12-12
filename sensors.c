#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "sensors.h"

int continue_loop = 1;
uint32_t start = 0;
uint32_t end = 0;

void alertFunction (int gpio, int level, uint32_t tick)
    {
    if (level == 1)
        {
        start = tick;
        }
    if (level == 0)
        {
        end = tick;
        }
    }

void stopSensing()
    {
    continue_loop = 0;
    printf("Set continue_loop to 0\n");
    }

void * sense (void *ptr)
    {
    Sensor *sensor = (Sensor *) ptr;
    gpioSetMode(sensor->pin, PI_INPUT);
    while (continue_loop)
        {
        usleep(5000);
        sensor->status = gpioRead(sensor->pin);
        }
    printf("STOP SENSING on pin: %d\n", sensor->pin);
    return NULL;
    }

void * read_distance (void *args)
    {
    double distance;
    distanceSensor * arg_ptr  = (distanceSensor*) args;
    gpioSetMode(arg_ptr->echo, PI_INPUT);
    gpioSetMode(arg_ptr->trig, PI_OUTPUT);
    while (continue_loop)
        {
        gpioDelay(5000);
        gpioTrigger(arg_ptr->trig, 10, 1);
        gpioSetAlertFunc(arg_ptr->echo, alertFunction);
        distance = 0.017 * (end - start);
        //printf("read_distance, distance: %f\n", distance);
        if (distance > 200) {
            distance = 200;
        }
        arg_ptr->value = distance;
        }
    printf("STOP DISTANCE READING\n");
    return NULL;
    }

// wait for ECHO pin pullup
//while (gpioRead(arg_ptr->echo) == 0) { ; }
// start relative timer
//uint32_t micro_seconds_start = gpioTick();
// wait for echo pin pulldown
//while (gpioRead(arg_ptr->echo) == 1) { ; }
// count elapsed microseconds since ECHO pin pullup
//uint32_t micro_echo_time = gpioTick() - micro_seconds_start;
//distance = micro_echo_time * 0.017;
//							 ^^ conversion constant
