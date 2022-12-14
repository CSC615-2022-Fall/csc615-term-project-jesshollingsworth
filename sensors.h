/**************************************************************
* Class:  CSC-615-01 Fall 2022
* Name: Tony Huang, Christopher Ling, Jess Hollingsworth, Jesse Henrick, Willi Vargas, Igor Tsygankov
* Student ID: 915090688, 918266861, 920974506, 921323452, 918778307, 918440047
* Github ID: tzphuang, dslayer1392, jesshollingsworth, jessehenrick, williv17, igortsygankov
* Project: Group Term Project
*
* File: sensor.h
*
* Description: Header file for sensors.c
**************************************************************/

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

