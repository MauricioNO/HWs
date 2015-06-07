// Mauricio Nunes de Oliveira
// ITP 365 Spring 2015
// Assignment 3
// Email: nunesdeo@usc.edu
// Platform: Windows

#include "peg.h"
#include "disk.h"
#include "vector.h"

#define peg_height 350
#define peg_width 10

using std::cout;
using std::cin;
using std::endl;

Peg::Peg()
{
	//Does nothing
}

Peg::Peg(int p_x, int p_y)
{
	x = p_x;
	y = p_y;
	width = peg_width;
	height = peg_height;
}

void Peg::drawPeg(GWindow& gw)
{
	gw.setColor("#663300");
	gw.fillRect(x - width / 2, y - height, width, height);
	for (int i = 0; i < containedDisks.size(); i++)
	{
		containedDisks[i].drawDisk(gw);	//Draws every disk at that peg
	}
	

}

void Peg::addDisk(Disk& disk)
{
	disk.changePos(disk, x, y - containedDisks.size()*30);	//Passes the x and y of the peg so the disk goes there
	containedDisks.add(disk);
	
}

Disk Peg::removeDisk()		
{
	if (containedDisks.size() > 0)
	{
		Disk tempDisk = containedDisks[containedDisks.size() - 1];
		containedDisks.remove(containedDisks.size() - 1);
		return tempDisk;
	}
	
}
