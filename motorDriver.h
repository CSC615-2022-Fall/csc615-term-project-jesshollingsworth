/************************************************************** 
* Class:  CSC-615-01 Fall 2022 
* Name: Tony Huang
* Student ID: 915090688 
* Github ID: tzphuang
* Project: Group Term Project
* 
* File: motorDriver.h
* 
* Description: Header file for motorDriver.c to store function calls
* that abstract the previous motor functions from our given librarys
* and simplifies them so we can call functions without needing to 
* call the lower level functions. (example: so instead of calling 
* set speed and turn on for each individual motor, we can just have a function
* that just says driveForward instead.)
* 
**************************************************************/ 

#ifndef MOTORDRIVER
#define MOTORDRIVER

//normal car functions we will need to move the car through the obstacle course
void driveForward();
void turnLeft();
void turnRight();

//omni-directional wheel functions we may choose to implement
void driveLeft();
void driveRight();

#endif