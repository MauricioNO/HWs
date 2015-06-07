#include "Grass.h"
#include "constants.h"


Grass::Grass(int pos_x, int pos_y, int c_starveTime, int c_reprodRate) : Creature(pos_x, pos_y, Constants::grass_width, Constants::grass_height, "green", c_starveTime, c_reprodRate)
{
	Ctype = GRASS;
	Cterrain = LAND;
}

Grass::~Grass()
{
	
}

void Grass::eat()
{
	
}

void Grass::move(double c_x, double c_y)
{
	
}



