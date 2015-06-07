// Mauricio Nunes de Oliveira
// ITP 365 Spring 2015
// Assignment 3
// Email: nunesdeo@usc.edu
// Platform: Windows

#pragma once

#include "disk.h"
#include "vector.h"

class Peg{
	
private:
	
	int x;
	int y;
	int width;
	int height;
	Vector<Disk> containedDisks;

public:
	// Prototypes

	//Function: Default constructor
	//Purpose: 
	//Input: none
	//Output: none
	Peg();

	//Function: Constructor with parameters
	//Purpose: Creates a Peg
	//Input: X and Y positions
	//Output: none
	Peg(int p_x, int p_y);

	//Function: drawPeg
	//Purpose: Draws the peg and all the disks contained on it
	//Input: GWindow to draw on
	//Output: none
	void drawPeg(GWindow& gw);

	//Function: addDisk
	//Purpose: Adds a disk to a peg, changing its position
	//Input: Disk to be added
	//Output: none
	void addDisk(Disk& disk);

	//Function: removeDisk
	//Purpose: Removes a disk from a peg
	//Input: none
	//Output: Returns the removed disk so it can be added to another peg
	Disk removeDisk();	

};

