#include "Fish.h"


Fish::Fish(int pos_x, int pos_y, int c_starveTime, int c_reprodRate) : Creature(pos_x, pos_y, Constants::fish_width, Constants::fish_height, "#666699", c_starveTime, c_reprodRate)
{
	Ctype = FISH;
	movSpeed = 2;
	hungriness = Constants::fish_maxHunger;;
	vision = 240;
	deathAge = 1600;
	maxHunger = Constants::fish_maxHunger;
	Cterrain = WATER;
}


void Fish::eat()
{

}

void Fish::move(double c_x, double c_y)
{
	if (c_x < 0)	// If object to move is to the right, increase x
	{
		x += movSpeed;
	}
	else if (c_x > 0)
	{
		x -= movSpeed;
	}

	if (c_y < 0)	// If object to move is below, increase y
	{
		y += movSpeed;
	}
	else if (c_y > 0)
	{
		y -= movSpeed;
	}

	if (!((x >= Constants::x_boundry) || (y >= Constants::y_boundry) || (x <= 0) || (y <= 0)))
		rect->setLocation(x, y);
	else   // In case creature is going over the world boundries, make sure it stays in
	{
		if (x < 0)
			x = 1;
		else if (x >= Constants::x_boundry)
			x = Constants::x_boundry - 1;
		if (y < 0)
			y = 1;
		else if (y >= Constants::y_boundry)
			y = Constants::y_boundry - 1;

		rect->setLocation(x, y);
	}
}
