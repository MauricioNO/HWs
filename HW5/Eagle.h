#pragma once

#include "Creature.h"

class Eagle : public Creature {
public:
	//Eagle();

	Eagle(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Eagle::eat();
	void Eagle::move(double c_x, double c_y);

private:

};
