#pragma once

#include "Creature.h"

class Cow : public Creature {
public:
	//Cow();

	Cow(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Cow::eat();
	void Cow::move(double c_x, double c_y);

private:
	
};
