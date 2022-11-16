/************************************************************** 
* Class:  CSC-615-01 Fall 2022 
* Name: Tony Huang
* Student ID: 915090688 
* Github ID: tzphuang
* Project: Group Term Project
* 
* File: sensorFunctions.h
* 
* Description: Header file for sensorFunctions.c to store
* some shared variables using the "extern" keyword
**************************************************************/ 

#ifndef SENSORFUNCTIONS
#define SENSORFUNCTIONS

//shared global variables 
extern int leftTapeLineSensor;
extern int rightTapeLineSensor;

void initAllSensorsTo(int currState);
void leftLineSensorUpdaterThread();

#endif