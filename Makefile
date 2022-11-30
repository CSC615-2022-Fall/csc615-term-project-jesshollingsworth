ROOTNAME=main
FOPTION=
CC=gcc
CFLAGS= -g -I. -Wall -pthread -lpigpio -lrt
LIBS =
DEPENDENCIES_C_FILES =  sensorFunctions.c PCA9685.c main.c motors.c
DEPENDENCIES_OBJECT_FILES = sensorFunctions.o PCA9685.o motors.o
OBJ = $(ROOTNAME).o

%.o: %.c $(DEPENDENCIES_C_FILES)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ROOTNAME): $(DEPENDENCIES_OBJECT_FILES) $(ROOTNAME).o
	$(CC) -o $@ $^ $(CFLAGS)  $(LIBS) -lm

clean:
	rm *.o $(ROOTNAME)

run: $(ROOTNAME)
	sudo ./$(ROOTNAME)