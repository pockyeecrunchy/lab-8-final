#ifndef STANDARD_H
#define STANDARD_H

#include <iostream>
#include <string>
#include <fstream>   // For CreateCSVFile
#include <iomanip>
#include <cstdlib>   // For rand()
#include <ctime>     // For seeding rand()
#include <stdexcept> // For throwing exceptions

using namespace std;

typedef unsigned char byte;

const string NAME = "Program Written by: Oscar Lan";
const string SCHOOL = "Broome Community College";
const string LAB = "Module 8 Lab - Binary Tree ";

#define DASH '-'
#define STAR '*'
#define SPACE ' '
#define EQUAL '='
// Macros for length (string length or table length)
#define SCREEN_WIDTH 100
#define SM_DIVIDER 25
#define MED_DIVIDER 50
#define LG_DIVIDER 75

// The following character is block that will only properly print in the console. 
#define BLOCK static_cast<char>(177)

// Prototypes
int ReturnRandomNumber(int min, int max);
void PrintHeader(ostream& out, char dividerCharacter);
void PrintDivider(ostream& out, char character, int width);
void CenterString(ostream& out, string stringData, int widthToCenterAccross);

#endif

