#pragma once

#include "Creature.h"

class Snake : public Creature {
public:
	//Snake();

	Snake(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Snake::eat();
	void Snake::move(double c_x, double c_y);

private:

};
