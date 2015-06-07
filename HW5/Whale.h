#pragma once

#include "constants.h"
#include "Creature.h"

class Whale : public Creature {
public:

	Whale(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Whale::eat();
	void Whale::move(double c_x, double c_y);

private:

};
