// MainHeader.h
// Author : Chang Hi Lee / lee.c@wustl.edu
// Header file for main.cpp. Contains a warning disable for Code C4018 and enums and functions for program execution.

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm> 
#pragma warning(disable : 4018) //Warning C4018(signed/unsigned mismatch) is acceptable because we are only comparing signed and unsigned ints in this lab
using namespace std;
enum lines { programName, inputFileName }; //should be equal to argc(=2), inputFileName will be a command line
enum messages { mainSuccess, wrongNumCmdArgs }; //collection of success/failure messages : success = 0 , 1st failure = 1, ...
enum expected { argcZero, argcOne, argcTwo, argcThree }; //expected value of argc = 2
enum args {argvZero, argvOne, argvTwo};

int helpMsg(); //Helper function for printing error message
