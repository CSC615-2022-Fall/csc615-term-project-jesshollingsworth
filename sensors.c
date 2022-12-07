#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "sensors.h"

int continue_loop = 1;

void stopSensing() {
    continue_loop = 0;
}

void *sense(void *ptr) {
    Sensor *sensor = (Sensor *) ptr;
    while (continue_loop) {
        usleep(10000);
        sensor->status = gpioRead(sensor->pin);
    }
    return NULL;
}


void *read_distance(void *args) {
    double distance;

    distanceSensor * arg_ptr  = (distanceSensor*) args;

    while (continue_loop) {
        usleep(333333);
// send trigger signal
        gpioWrite(arg_ptr->trig, 1);
        gpioDelay(10);
        gpioWrite(arg_ptr->trig, 0);

// wait for ECHO pin pullup
        while (gpioRead(arg_ptr->echo) == 1) { ; }

// start relative timer
        uint32_t micro_seconds_start = gpioTick();

// wait for echo pin pulldown
        while (gpioRead(arg_ptr->echo) == 1) { ; }

// count elapsed microseconds since ECHO pin pullup
        uint32_t micro_echo_time = gpioTick() - micro_seconds_start;

        distance = micro_echo_time * 0.017;
//							 ^^ conversion constant

        printf("%f\n", distance);
        arg_ptr->value = distance;


    }

    return NULL;
}
