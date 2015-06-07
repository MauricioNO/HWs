// Mauricio Nunes de Oliveira
// ITP 365 Spring 2015
// Assignment 3
// Email: nunesdeo@usc.edu
// Platform: Windows

#pragma once
#include "gwindow.h"


using std::string;

class Disk{
	
private:
	int x;
	int y;
	int width;
	int height;
	string color;
public:
	// Prototypes

	//Function: Default constructor
	//Purpose: Used when temporary disks are created
	//Input: none
	//Output: none
	Disk();

	//Function: Constructor with parameters
	//Purpose: Creates a disk 
	//Input: Width of the Disk and its color
	//Output: none
	Disk(int d_width, string d_color);

	//Function: drawDisk
	//Purpose: Loads information from 2 txt files into member variables
	//Input: GWindow where disk should be drawn
	//Output: none
	void drawDisk(GWindow& gw);

	//Function: changePos
	//Purpose: Changes the x and y positions of the disk
	//Input: X and Y
	//Output: none
	void changePos(Disk& disk, int x, int y);

};
