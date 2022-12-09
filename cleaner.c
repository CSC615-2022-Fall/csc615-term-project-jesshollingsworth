#include <stdio.h>
#include <pigpio.h>

int main(int argc, char *argv[]) {

    gpioTerminate();
    printf("terminated\n");
    return 0;

}