#include "Creature.h"
#include "gobjects.h"
#include "constants.h"

/*
Creature::Creature()
{
	//Do nothing
}
*/

Creature::Creature(int pos_x, int pos_y, int c_width, int c_height, string color, int starve_time, int reprod_rate)
{
	x = pos_x;
	y = pos_y;
	alive = true;
	age = 0;
	ableToReprod = false;
	starveStart = counter;	//Counter is the time of birth of the creature, the moment it started to be starving, taking from the global time keep(counter)
	rect->setLocation(pos_x, pos_y);
	rect->setSize(c_width, c_height);
	rect->setFilled(true);
	rect->setColor(color);
	starveTime = starve_time;
	reprodRate = reprod_rate;
}

Creature::~Creature()
{
	//std::cout << "deleting creature: " << Ctype << std::endl;
}

void Creature::draw(GWindow& gw)
{
	gw.add(rect);
}

double Creature::get_X()
{
	return rect->getX();
}

double Creature::get_Y()
{
	return rect->getY();
}

bool Creature::isAlive()
{
	return alive;
}

void Creature::kill()
{
	alive = false;
	rect->setVisible(false);
}

int Creature::getVision()
{
	return vision;
}

void Creature::setVision(int radius)
{
	vision = radius;
}

int Creature::getHunger()
{
	return hungriness;
}


void Creature::reduceHunger()
{
	if (hungriness > 0) 
		hungriness--;
}
void Creature::increaseHunger()
{
	hungriness++;
}

int Creature::getAge()
{
	return age;
}

void Creature::addAge()
{
	age++;
}

bool Creature::isAbleToReprod()
{
	return ableToReprod;
}

void Creature::setHeat(bool heat)
{
	ableToReprod = heat;
	
}

int Creature::getStarveStart()
{
	return starveStart;
}
void Creature::setStarveStart(int time)
{
	starveStart = time;
}

int Creature::getDeathAge()
{
	return deathAge;
}

int Creature::getMaxHunger()
{
	return maxHunger;
}

int Creature::getCreatureType()
{
	return Ctype;
}

int Creature::getStarveTime()
{
	return starveTime;
}

int Creature::getReprodRate()
{
	return reprodRate;
}

int Creature::getAllowedTerrain()
{
	return Cterrain;
}

