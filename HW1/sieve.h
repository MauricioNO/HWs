// ITP 365 Spring 2015
// HW1 – Sieve of Eratosthenes
// Name: Mauricio Nunes de Oliveira
// Email: nunesdeo@usc.edu
// Platform: Windows

#pragma once

enum NumberType
{
		UNKOWN,
		PRIME,
		COMPOSITE
};

//Prototypes

// Function: drawSquare
// Purpose: Draws 50 by 50 squares
// Input: Window to draw into, label of the square, type of the number and position of the square
// Output: None
void drawSquare(GWindow& gw, int label, NumberType type, double x, double y);

// Function: initVectors
// Purpose: Fill the input vectors with the initial values
// Input: Vector of labels(initialized from 2 to 101) and vector of NumberType(initialized as UNKOWN)
// Output: None
void initVectors(Vector<int>& label, Vector<NumberType>& type);

// Function: drawGrid
// Purpose: Draws the grid of squares for each index in the vectors
// Input: Window to draw into, Vector of labels and vector of NumberTypes
// Output: None
void drawGrid(GWindow& gw, Vector<int>& label, Vector<NumberType>& type);

// Function: calcNextPrime
// Purpose: Decides wether a number is prime or composite and colors it accordingly
// Input: Vector of labels, Vector of NumberTypes and an integer to start testing at
// Output: Either the prime number found or -1 when there are no more prime numbers
int calcNextPrime(Vector<int>& label, Vector<NumberType>& type, int startAt);
