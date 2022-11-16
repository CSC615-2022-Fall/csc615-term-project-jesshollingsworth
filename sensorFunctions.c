/************************************************************** 
* Class:  CSC-615-01 Fall 2022 
* Name: Tony Huang, Jess Hollingsworth, Jesse Henrick
* Student ID: 915090688, 920974506, 921323452
* Github ID: tzphuang, jesshollingsworth, jessehenrick
* Project: Group Term Project
* 
* File: sensorFunctions.c
* 
* Description: This file holds the functions that will update their 
* relevant global variables to be used in main.c. These functions 
* specifically will be passed into pthreadCreate so we constantly 
* have updated variables we can apply our self driving car's logic to.
* The global variables set here are instantiated in this file and 
* shared across multiple source files. 
* 
**************************************************************/ 

#include "sensorFunctions.h"

// shared (using extern) global variables set by our sensors go here
int leftTapeLineSensor;
int rightTapeLineSensor;
