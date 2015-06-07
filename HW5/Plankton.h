#pragma once
#include "constants.h"
#include "Creature.h"

class Plankton : public Creature {
public:
	
	Plankton(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Plankton::eat();
	void Plankton::move(double c_x, double c_y);

private:

};
