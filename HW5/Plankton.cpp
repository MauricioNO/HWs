#include "Plankton.h"


Plankton::Plankton(int pos_x, int pos_y,  int c_starveTime, int c_reprodRate) : Creature(pos_x, pos_y, Constants::plankton_width, Constants::plankton_height, "#69c0f0", c_starveTime, c_reprodRate)
{
	Ctype = PLANKTON;
	Cterrain = WATER;
}


void Plankton::eat()
{

}

void Plankton::move(double c_x, double c_y)
{

}
