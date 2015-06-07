#include "Snake.h"
#include "constants.h"

Snake::Snake(int pos_x, int pos_y, int c_starveTime, int c_reprodRate) : Creature(pos_x, pos_y, Constants::snake_width, Constants::snake_height, "#59982f", c_starveTime, c_reprodRate)
{
	Ctype = SNAKE;
	movSpeed = 2;
	hungriness = Constants::snake_maxHunger;
	vision = 280;
	deathAge = 1600;
	maxHunger = Constants::snake_maxHunger;
	Cterrain = LAND;
}



void Snake::eat()
{

}

void Snake::move(double c_x, double c_y)
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
	if (!((x >= Constants::x_boundry) || (y >= Constants::y_boundry) || (x <= 0) || ( y <= 0)))
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
