car: main.c
	gcc -o main PCA9685.c DEV_Config.c main.c motorDriver.c sensorFunctions.c -I. -lpigpio -lm
run:
	sudo ./car
cleanpigpio:
	rm car
