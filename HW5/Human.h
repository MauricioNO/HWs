#pragma once

#include "constants.h"
#include "Creature.h"

class Human : public Creature {
public:

	Human(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Human::eat();
	void Human::move(double c_x, double c_y);

private:

};
