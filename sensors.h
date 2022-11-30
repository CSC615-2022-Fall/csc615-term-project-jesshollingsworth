#include <pigpio.h>

int continue_loop = 1;

typedef struct sensor {
    int pin;
    int status;
} Sensor;

int stopSensing ();
void * sense (void * ptr);
