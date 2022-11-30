#include "sensors.h"

void stopSensing ()
    {
    continue_loop = 0;
    }

void * sense (void * ptr)
    {
    Sensor * sensor = (Sensor *) ptr;
    while (continue_loop)
        {
        sensor->status = gpioRead(sensor->pin);
        }
    }
