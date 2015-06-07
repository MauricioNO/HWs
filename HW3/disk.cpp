// Mauricio Nunes de Oliveira
// ITP 365 Spring 2015
// Assignment 3
// Email: nunesdeo@usc.edu
// Platform: Windows

#include "disk.h"
#include "gwindow.h"
#define disk_height 30


using std::string;

Disk:: Disk()
{	
	//Does nothing
}

Disk::Disk(int d_width, string d_color)
{
	x = 0;
	y = 0;
	height = disk_height;
	width = d_width;
	color = d_color;
}

void Disk::drawDisk(GWindow& gw)
{
	gw.setColor(color);
	gw.fillRect(x-width/2, y-height, width, height);
}

void Disk::changePos(Disk& disk, int d_x, int d_y)
{
	x = d_x;
	y = d_y;

}
