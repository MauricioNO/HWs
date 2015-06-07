#pragma once

#include "constants.h"
#include "Creature.h"

class Crocodile : public Creature {
public:

	Crocodile(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Crocodile::eat();
	void Crocodile::move(double c_x, double c_y);

private:

};
