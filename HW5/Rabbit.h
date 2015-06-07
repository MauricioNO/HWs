#pragma once

#include "Creature.h"

class Rabbit : public Creature {
public:
	//Rabbit();

	Rabbit(int pos_x, int pos_y, int c_starveTime, int c_reprodRate);

	void Rabbit::eat();
	void Rabbit::move(double c_x, double c_y);

private:

};
