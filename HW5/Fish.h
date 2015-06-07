#pragma once
#include "constants.h"
#include "Creature.h"

class Fish : public Creature {
public:

	Fish(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Fish::eat();
	void Fish::move(double c_x, double c_y);

private:

};
