// ITP 365 Spring 2015
// HW1 – Sieve of Eratosthenes
// Name: Mauricio Nunes de Oliveira
// Email: nunesdeo@usc.edu
// Platform: Windows

#include "gwindow.h"
#include "sieve.h"
#include "vector.h"

int main(int argc, char** argv)
{
	// Create a 500x500 window
	GWindow gw(500, 500);
	
	//Initialize vectors
	Vector<int> label;
	Vector<NumberType> type;	
	initVectors(label, type);

	
	drawGrid(gw, label, type);


	//This section finds and colors the numbers accordingly
	int index = 0;
	int lastPrime = 0;
	while (lastPrime != -1)
	{
		lastPrime = calcNextPrime(label, type, index); //Receives the latest prime number found
		drawGrid(gw, label, type);
		pause(10.0);
		index = lastPrime - 1;	//Calculates which index should the next function call look for
					
	}
	return 0;
}


