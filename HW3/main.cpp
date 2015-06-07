// Mauricio Nunes de Oliveira
// ITP 365 Spring 2015
// Assignment 3
// Email: nunesdeo@usc.edu
// Platform: Windows

#include "disk.h"
#include "peg.h"
#include "gwindow.h"
#include "vector.h"
#include <math.h>

#define delay 100	//Time in ms between each disk move

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Prototypes 

//Function: updatePegs
//Purpose: Clear the screen and redraw the pegs with whatever disks are on them
//Input: GWindow to clear/draw on, vector of pegs to draw
//Output: none
void updatePegs(GWindow& gw, Vector <Peg>& myPeg);

//Function: towerOfHanoi
//Purpose: Recursive function that implements the logic behind the tower of hanoi problem
//Input: Source, destination and auxiliary peg. Number of diksks, GWindow, vector of Pegs and a counter
//Output: none
void towerOfHanoi(int& source, int& dest, int& auxPeg, int numDisk, GWindow& gw, Vector <Peg>& myPeg, int& counter);

//Function: moveDisk
//Purpose: Move a disk from a source peg to a destination peg
//Input: Source and destination pegs, GWindow and vector of Pegs
//Output: none
void moveDisk(int& source, int& dest, GWindow& gw, Vector <Peg>& myPeg);


int main(int argc, char** argv)
{
	cout << "Welcome to the Towers of Hanoi!" << endl;

	//Variables
	int diskAmount = 0;
	int startPeg = 0;
	int endPeg = 0;
	int startingWidth = 300;	//Width of the bottom most disk
	int widthDecrement = 30;	//How much width will be decremented from each following disk
	int counter = 0;			//Counter to keep track of the number of moves made
	

	// Input from the user
	while (diskAmount < 2 || diskAmount > 10)
	{
		cout << "How many disks do you want?(2-10)" << endl;
		cin >> diskAmount;
	}
	while (startPeg < 1 || startPeg > 3)
	{
		cout << "Which peg should be starting one?(1-3)" << endl;
		cin >> startPeg;
	}
	while ( (endPeg < 1) || (endPeg > 3) || (endPeg == startPeg) )
	{
		cout << "Which peg should be ending one?(1-3)" << endl;
		cin >> endPeg;
	}

	// Subtract one from both startPeg and endPeg so it translates to Vector indexes
	startPeg -= 1;
	endPeg -= 1;
	// Define the auxiliary peg based on the stard and end pegs
	int auxPeg = 3 - (startPeg+endPeg);		//pegs are from 0 to 2, so the sum must always be 3

	// Create a vector with 10 colors to assign to the disks
	Vector <int> widths;
	Vector <string> colors;
	colors.add("#FFA319");	//orange
	colors.add("#0000FF");	//blue
	colors.add("#FFFF00");	//yellow
	colors.add("#FF0000");	//red
	colors.add("#00FF00");	//green
	colors.add("#993399");	//purple
	colors.add("#996600");	//brown
	colors.add("#FF00FF");	//pink
	colors.add("#00FFFF");	//light blue
	colors.add("#000000");	//black

	// Creates the pegs
	Vector <Peg> myPeg;
	myPeg.add(Peg(200, 400));
	myPeg.add(Peg(520, 400));
	myPeg.add(Peg(840, 400));

	// Creates and allocates the disks in the starting Peg
	Vector <Disk> myDisks;
	for (int i = 0; i < diskAmount; i++)
	{
		widths.add(startingWidth - i*widthDecrement);
		myDisks.add(Disk(widths[i], colors[i]));
		myPeg[startPeg].addDisk(myDisks[i]);
	}

	// Create a 1040x400 window
	GWindow gw(1040, 400);
	updatePegs(gw, myPeg);
	towerOfHanoi(startPeg, endPeg, auxPeg, diskAmount, gw, myPeg, counter);
	cout << "The total amount of moves was: " << counter << endl;


	return 0;
}

void updatePegs(GWindow& gw, Vector <Peg>& myPeg)
{
	gw.clear();
	myPeg[0].drawPeg(gw);
	myPeg[1].drawPeg(gw);
	myPeg[2].drawPeg(gw);
}

void towerOfHanoi(int& source, int& dest, int& auxPeg, int numDisk, GWindow& gw, Vector <Peg>& myPeg, int& counter)
{
	if (numDisk == 1)	
	{
		moveDisk(source, dest, gw, myPeg);
		pause(delay);
		counter += 1;
	}
	else
	{
		towerOfHanoi(source, auxPeg, dest, numDisk - 1, gw, myPeg, counter);	//Leave disk 0 alone on source peg by moving to the auxiliar peg
		towerOfHanoi(source, dest, auxPeg, 1, gw, myPeg, counter);			//Move disk 0 from source peg to dest peg 
		towerOfHanoi(auxPeg, dest, source, numDisk - 1, gw, myPeg, counter);	//Move the rest of the discs from auxilir peg to dest peg
	}
	
}

void moveDisk(int& source, int& dest, GWindow& gw, Vector <Peg>& myPeg)
{		
	//Move disk to dest peg
	Disk tempDisk = myPeg[source].removeDisk();
	myPeg[dest].addDisk(tempDisk);
	updatePegs(gw, myPeg);
}
