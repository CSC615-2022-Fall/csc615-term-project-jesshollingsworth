#ifndef SENSORS_H
#define SENSORS_H

#include <pigpio.h>

typedef struct distanceSensor {
    int echo;
    int trig;
    double value;
} distanceSensor;

typedef struct sensor {
    int pin;
    int status;
} Sensor;

void stopSensing ();
void * sense (void * ptr);
void * read_distance1(void * args);
void * read_distance2(void * args);
#endif

