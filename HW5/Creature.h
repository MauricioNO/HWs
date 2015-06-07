#pragma once

#include <string>
#include "gobjects.h"
using std::string;

class Creature{

public:
	//Creature();

	//Constructor
	Creature(int pos_x, int pos_y, int c_width, int c_height, string color, int starve_time, int reprod_rate);

	virtual void eat() = 0;	//Function eat is actually implemented by reducing the hungriness level through other functions, for now there is nothing written for this function in any class
	
	//Make creatue move to c_x and c_y
	virtual void move(double c_x, double c_y) = 0;

	//Adds the creature to the world
	virtual void draw(GWindow& gw);

	//Return x and y position
	virtual double get_X();
	virtual double get_Y();

	// Returns or sets a creature vision(will be used on next assignment
	virtual int getVision();
	virtual void setVision(int radius);

	//Return and changes a creature hungriness level
	virtual int getHunger();
	virtual void reduceHunger();
	virtual void increaseHunger();

	//Return and add to a creature age
	virtual int getAge();
	virtual void addAge();

	//Return if the creature is able to reproduce
	virtual bool isAbleToReprod();
	//Set if the creature is able to reproduce or not
	virtual void setHeat(bool heat);
	//Check if the creature is alive
	virtual bool isAlive();
	//Kill the creature
	virtual void kill();

	//Get the time when the creture started to starve
	virtual int getStarveStart();
	//Set the time when the creature started to starve
	virtual void setStarveStart(int time);

	//Returns the death age of a creature(in ticks of the clock)
	virtual int getDeathAge();

	//Returns the max hunger of a creature(amount it must eat to be full)
	virtual int getMaxHunger();

	//Returns Creature type
	virtual int getCreatureType();

	//Gets the starve time
	virtual int getStarveTime();

	//Gets the reproduction rate of the creature
	virtual int getReprodRate();

	// Returns the allowed terrains for the creature to move on
	virtual int getAllowedTerrain();

	//destructor
	~Creature();


	
protected:
	enum CreatureType
	{
		GRASS = 0,
		COW = 1,
		SNAKE = 2,
		EAGLE = 3,
		RABBIT = 4,
		PLANKTON = 5,
		FISH = 6,
		CROCODILE = 7,
		WHALE = 8,
		HUMAN = 9
	};
	enum allowedTerrain
	{
		LAND = 1,
		WATER = 2,
		ALL = 3
	};
	CreatureType Ctype;
	allowedTerrain Cterrain;
	int x;
	int y;
	int movSpeed;
	int hungriness;
	int vision;
	int age;
	bool ableToReprod;
	GRect* rect = new GRect(0, 0);
	bool alive;
	int starveStart;
	int deathAge;
	int maxHunger;
	int starveTime;
	int reprodRate;


};
