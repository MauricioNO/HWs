// ITP 365 Spring 2015
// HW6 – Augmenting Your World
// Name: Mauricio Nunes de Oliveira
// Email: nunesdeo@usc.edu
// Platform: Windows

#include "gwindow.h"
#include "gtimer.h"
#include "gevents.h"
#include "ginteractors.h"
#include "iostream"
#include "functions.h"	// File containing some used functions
#include "Grass.h"
#include <random>
#include "constants.h"	// File containing constants used across several files
#include "Vector.h"
#include "Cow.h"
#include "Snake.h"
#include "Eagle.h"
#include "Rabbit.h"
#include "Water.h"
#include "Land.h"
#include "Plankton.h"
#include "Fish.h"
#include "Crocodile.h"
#include "Whale.h"
#include "Human.h"


using std::cout;
using std::endl;


//Description: Make creatures move looking for food when hungry and for partners when able to reproduce(full and old enough)
void creatureMove(Vector <Creature*> predator, Vector <Creature*> prey);

//Description: Checks if all the requrimentes for a creature to be eaten are met, then kill it and feed the predator
void creatureEat(Vector <Creature*> predator, Vector <Creature*> prey);

//Description: Checks and removes every creature that died
void deleteDead(Vector <Creature*>& creature);

//Description: Adds to every creature age, checking if they are too old and die, and also making them able to reproduce once they are old enough
void growOld(Vector <Creature*> creature);

//Description: Increases creatures hingriness based on time to get hungry
void getHungry(Vector <Creature*> creature);

//Description: Checks if all the requriments for reproduction are met, if so a new born is added to the world
void reproduction(Vector <Creature*>& creature);

//Description:	Checks if any creature has been starving for the determined time and if it is, kills it
void checkStarvers(Vector <Creature*> creature);

//Draws Creatures and Terrains contained in a Vector
template <typename T>
void drawVector(GWindow& gw, Vector <T*> myVec);

//Global variables




std::random_device rd; // obtain a random number from hardware
std::mt19937 eng(rd()); // seed the generator
std::uniform_int_distribution<> rand_x(0, Constants::x_boundry-1); // define the range
std::uniform_int_distribution<> rand_y(0, Constants::y_boundry-1); // define the range
std::uniform_int_distribution<> jitter(-1, 1); // define the range

int numGrass = 0;
int grassReprodRate = 0;

int numPlankton = 0;
int planktonReprodRate = 0;

int numCows = 0;
int cowReprodRate = 0;
int cowStarveTime = 0;		//Starve time in tickts(dies when it stays at max hungriness level for this time)

int numSnake = 0;
int snakeReprodRate = 0;
int snakeStarveTime = 0;

int numEagle = 0;
int eagleReprodRate = 0;
int eagleStarveTime = 0;

int numRabbit = 0;
int rabbitReprodRate = 0;
int rabbitStarveTime = 0;

int numFish = 0;
int fishReprodRate = 0;
int fishStarveTime = 0;

int numCroc = 0;
int crocReprodRate = 0;
int crocStarveTime = 0;

int numWhale = 0;
int whaleReprodRate = 0;
int whaleStarveTime = 0;

int numHuman = 0;
int humanReprodRate = 0;
int humanStarveTime = 0;



int getHungryRate = 25; //Time(in seconds) for creatures to get another level of hungriness

int waterWidth = 0;
int waterPercent = 0;
int counter = 0;

Land* myLand;
Water* myWater;



int main(int argc, char** argv)
{
	
	Vector <Creature*> grassVec;
	Vector <Creature*> cowVec;
	Vector <Creature*> snakeVec;
	Vector <Creature*> eagleVec;
	Vector <Creature*> rabbitVec;
	Vector <Creature*> planktonVec;
	Vector <Creature*> fishVec;
	Vector <Creature*> crocVec;
	Vector <Creature*> whaleVec;
	Vector <Creature*> humanVec;

	Vector <Creature*> preysVec;	//Auxiliar vector used to concatenate several creatures vectors to be eaten by predators that eat more then one kind of creature

	Vector <Terrain*> terrains;

	GWindow gw(1170, 855);
	bool started = false;
	drawWorld(gw);


	GButton* startButton = new GButton("Start");
	gw.addToRegion(startButton, "NORTH");
	
	GButton* pauseButton = new GButton("Pause");
	gw.addToRegion(pauseButton, "NORTH");
	GButton* continueButton = new GButton("Continue");
	gw.addToRegion(continueButton, "NORTH");
	GButton* restartButton = new GButton("Restart");
	gw.addToRegion(restartButton, "NORTH");
	GButton* quitButton = new GButton("Quit");
	gw.addToRegion(quitButton, "NORTH");

	
	GLabel* grassLabel1 = new GLabel("Initial amount of Grass");
	gw.addToRegion(grassLabel1, "WEST");
	GTextField* grassText1 = new GTextField();
	gw.addToRegion(grassText1, "WEST");
	grassText1->setText("150");
	GLabel* grassLabel2 = new GLabel("Time for Grass to grow");
	gw.addToRegion(grassLabel2, "WEST");
	GTextField* grassText2 = new GTextField();
	gw.addToRegion(grassText2, "WEST");
	grassText2->setText("2");


	GLabel* cowLabel1 = new GLabel("Initial amount of Cows");
	gw.addToRegion(cowLabel1, "WEST");
	GTextField* cowText1 = new GTextField();
	gw.addToRegion(cowText1, "WEST");
	cowText1->setText("8");
	GLabel* cowLabel2 = new GLabel("Time for Cow to reproduce");
	gw.addToRegion(cowLabel2, "WEST");
	GTextField* cowText2 = new GTextField();
	gw.addToRegion(cowText2, "WEST");
	cowText2->setText("15");
	GLabel* cowLabel3 = new GLabel("Time for Cow to starve");
	gw.addToRegion(cowLabel3, "WEST");
	GTextField* cowText3 = new GTextField();
	gw.addToRegion(cowText3, "WEST");
	cowText3->setText("100");


	GLabel* snakeLabel1 = new GLabel("Initial amount of Snakes");
	gw.addToRegion(snakeLabel1, "WEST");
	GTextField* snakeText1 = new GTextField();
	gw.addToRegion(snakeText1, "WEST");
	snakeText1->setText("9");
	GLabel* snakeLabel2 = new GLabel("Time for Snake to reproduce");
	gw.addToRegion(snakeLabel2, "WEST");
	GTextField* snakeText2 = new GTextField();
	gw.addToRegion(snakeText2, "WEST");
	snakeText2->setText("10");
	GLabel* snakeLabel3 = new GLabel("Time for Snake to starve");
	gw.addToRegion(snakeLabel3, "WEST");
	GTextField* snakeText3 = new GTextField();
	gw.addToRegion(snakeText3, "WEST");
	snakeText3->setText("100");

	GLabel* fishLabel1 = new GLabel("Initial amount of Fish");
	gw.addToRegion(fishLabel1, "WEST");
	GTextField* fishText1 = new GTextField();
	gw.addToRegion(fishText1, "WEST");
	fishText1->setText("26");
	GLabel* fishLabel2 = new GLabel("Time for Fish to reproduce");
	gw.addToRegion(fishLabel2, "WEST");
	GTextField* fishText2 = new GTextField();
	gw.addToRegion(fishText2, "WEST");
	fishText2->setText("11");
	GLabel* fishLabel3 = new GLabel("Time for Fish to starve");
	gw.addToRegion(fishLabel3, "WEST");
	GTextField* fishText3 = new GTextField();
	gw.addToRegion(fishText3, "WEST");
	fishText3->setText("100");

	GLabel* whaleLabel1 = new GLabel("Initial amount of Whales");
	gw.addToRegion(whaleLabel1, "WEST");
	GTextField* whaleText1 = new GTextField();
	gw.addToRegion(whaleText1, "WEST");
	whaleText1->setText("2");
	GLabel* whaleLabel2 = new GLabel("Time for Whales to reproduce");
	gw.addToRegion(whaleLabel2, "WEST");
	GTextField* whaleText2 = new GTextField();
	gw.addToRegion(whaleText2, "WEST");
	whaleText2->setText("25");
	GLabel* whaleLabel3 = new GLabel("Time for Whales to starve");
	gw.addToRegion(whaleLabel3, "WEST");
	GTextField* whaleText3 = new GTextField();
	gw.addToRegion(whaleText3, "WEST");
	whaleText3->setText("150");


	GLabel* planktonLabel1 = new GLabel("Initial amount of Plankton");
	gw.addToRegion(planktonLabel1, "EAST");
	GTextField* planktonText1 = new GTextField();
	gw.addToRegion(planktonText1, "EAST");
	planktonText1->setText("320");
	GLabel* planktonLabel2 = new GLabel("Time for Plankton to reproduce");
	gw.addToRegion(planktonLabel2, "EAST");
	GTextField* planktonText2 = new GTextField();
	gw.addToRegion(planktonText2, "EAST");
	planktonText2->setText("3");



	GLabel* eagleLabel1 = new GLabel("Initial amount of Eagles");
	gw.addToRegion(eagleLabel1, "EAST");
	GTextField* eagleText1 = new GTextField();
	gw.addToRegion(eagleText1, "EAST");
	eagleText1->setText("2");
	GLabel* eagleLabel2 = new GLabel("Time for Eagle to reproduce");
	gw.addToRegion(eagleLabel2, "EAST");
	GTextField* eagleText2 = new GTextField();
	gw.addToRegion(eagleText2, "EAST");
	eagleText2->setText("20");
	GLabel* eagleLabel3 = new GLabel("Time for Eagle to starve");
	gw.addToRegion(eagleLabel3, "EAST");
	GTextField* eagleText3 = new GTextField();
	gw.addToRegion(eagleText3, "EAST");
	eagleText3->setText("100");


	GLabel* rabbitLabel1 = new GLabel("Initial amount of Rabbits");
	gw.addToRegion(rabbitLabel1, "EAST");
	GTextField* rabbitText1 = new GTextField();
	gw.addToRegion(rabbitText1, "EAST");
	rabbitText1->setText("15");
	GLabel* rabbitLabel2 = new GLabel("Time for Rabbits to reproduce");
	gw.addToRegion(rabbitLabel2, "EAST");
	GTextField* rabbitText2 = new GTextField();
	gw.addToRegion(rabbitText2, "EAST");
	rabbitText2->setText("5");
	GLabel* rabbitLabel3 = new GLabel("Time for Rabbits to starve");
	gw.addToRegion(rabbitLabel3, "EAST");
	GTextField* rabbitText3 = new GTextField();
	gw.addToRegion(rabbitText3, "EAST");
	rabbitText3->setText("80");

	GLabel* crocLabel1 = new GLabel("Initial amount of Crocodiles");
	gw.addToRegion(crocLabel1, "EAST");
	GTextField* crocText1 = new GTextField();
	gw.addToRegion(crocText1, "EAST");
	crocText1->setText("3");
	GLabel* crocLabel2 = new GLabel("Time for Crocodiles to reproduce");
	gw.addToRegion(crocLabel2, "EAST");
	GTextField* crocText2 = new GTextField();
	gw.addToRegion(crocText2, "EAST");
	crocText2->setText("12");
	GLabel* crocLabel3 = new GLabel("Time for Crocodiles to starve");
	gw.addToRegion(crocLabel3, "EAST");
	GTextField* crocText3 = new GTextField();
	gw.addToRegion(crocText3, "EAST");
	crocText3->setText("100");

	GLabel* humanLabel1 = new GLabel("Initial amount of Humans");
	gw.addToRegion(humanLabel1, "EAST");
	GTextField* humanText1 = new GTextField();
	gw.addToRegion(humanText1, "EAST");
	humanText1->setText("2");
	GLabel* humanLabel2 = new GLabel("Time for Humans to reproduce");
	gw.addToRegion(humanLabel2, "EAST");
	GTextField* humanText2 = new GTextField();
	gw.addToRegion(humanText2, "EAST");
	humanText2->setText("18");
	GLabel* humanLabel3 = new GLabel("Time for Humans to starve");
	gw.addToRegion(humanLabel3, "EAST");
	GTextField* humanText3 = new GTextField();
	gw.addToRegion(humanText3, "EAST");
	humanText3->setText("100");
	
	GLabel* obsLabel = new GLabel("*All times are in seconds*");
	gw.addToRegion(obsLabel, "EAST");

	GLabel* waterLabel = new GLabel("% of Water in the World");
	gw.addToRegion(waterLabel, "EAST");
	GTextField* waterText = new GTextField();
	gw.addToRegion(waterText, "EAST");
	waterText->setText("50");

	GLabel* cowAmount = new GLabel("Cows:");
	gw.addToRegion(cowAmount, "SOUTH");
	GTextField* cowText = new GTextField();
	gw.addToRegion(cowText, "SOUTH");
	cowText->setText("0");

	GLabel* rabbitAmount = new GLabel("Rabbits:");
	gw.addToRegion(rabbitAmount, "SOUTH");
	GTextField* rabbitText = new GTextField();
	gw.addToRegion(rabbitText, "SOUTH");
	rabbitText->setText("0");

	GLabel* snakeAmount = new GLabel("Snakes:");
	gw.addToRegion(snakeAmount, "SOUTH");
	GTextField* snakeText = new GTextField();
	gw.addToRegion(snakeText, "SOUTH");
	snakeText->setText("0");

	GLabel* eagleAmount = new GLabel("Eagles:");
	gw.addToRegion(eagleAmount, "SOUTH");
	GTextField* eagleText = new GTextField();
	gw.addToRegion(eagleText, "SOUTH");
	eagleText->setText("0");

	GLabel* humanAmount = new GLabel("Humans:");
	gw.addToRegion(humanAmount, "SOUTH");
	GTextField* humanText = new GTextField();
	gw.addToRegion(humanText, "SOUTH");
	humanText->setText("0");

	GLabel* fishAmount = new GLabel("Fishes:");
	gw.addToRegion(fishAmount, "SOUTH");
	GTextField* fishText = new GTextField();
	gw.addToRegion(fishText, "SOUTH");
	fishText->setText("0");

	GLabel* crocAmount = new GLabel("Crocs:");
	gw.addToRegion(crocAmount, "SOUTH");
	GTextField* crocText = new GTextField();
	gw.addToRegion(crocText, "SOUTH");
	crocText->setText("0");

	GLabel* whaleAmount = new GLabel("Whales:");
	gw.addToRegion(whaleAmount, "SOUTH");
	GTextField* whaleText = new GTextField();
	gw.addToRegion(whaleText, "SOUTH");
	whaleText->setText("0");
		
	GTimer timer(Constants::refresh_rate); //Timer fires every 100 milliseconds
	timer.start(); //Starts time timer
	while (true) {
		GEvent e;
		e = waitForEvent();


		if (e.getEventType() == ACTION_PERFORMED) {
			GActionEvent ae = (GActionEvent)e;
			if (ae.getSource() == startButton && !started)	//Start button only triggers if world is new or reset
			{
				timer.start();

				numGrass = std::stoi(grassText1->getText());
				numCows = std::stoi(cowText1->getText());
				numSnake = std::stoi(snakeText1->getText());
				numEagle = std::stoi(eagleText1->getText());
				numRabbit = std::stoi(rabbitText1->getText());
				numPlankton = std::stoi(planktonText1->getText());
				numFish = std::stoi(fishText1->getText());
				numCroc = std::stoi(crocText1->getText());
				numWhale = std::stoi(whaleText1->getText());
				numHuman = std::stoi(humanText1->getText());

				grassReprodRate = std::stoi(grassText2->getText());
				planktonReprodRate = std::stoi(planktonText2->getText());
				cowReprodRate = std::stoi(cowText2->getText()) * 10;		//Below this point, this variables will be compared to age which is increased every 100msec, thats the reason for the *10
				snakeReprodRate = std::stoi(snakeText2->getText()) * 10;
				eagleReprodRate = std::stoi(eagleText2->getText()) * 10;
				rabbitReprodRate = std::stoi(rabbitText2->getText()) * 10;
				fishReprodRate = std::stoi(fishText2->getText()) * 10;
				crocReprodRate = std::stoi(crocText2->getText()) * 10;
				whaleReprodRate = std::stoi(whaleText2->getText()) * 10;
				humanReprodRate = std::stoi(humanText2->getText()) * 10;

				cowStarveTime = std::stoi(cowText3->getText()) * 10;
				snakeStarveTime = std::stoi(snakeText3->getText()) * 10;
				eagleStarveTime = std::stoi(eagleText3->getText()) * 10;
				rabbitStarveTime = std::stoi(rabbitText3->getText()) * 10;
				fishStarveTime = std::stoi(fishText3->getText()) * 10;
				crocStarveTime = std::stoi(crocText3->getText()) * 10;
				whaleStarveTime = std::stoi(whaleText3->getText()) * 10;
				humanStarveTime = std::stoi(humanText3->getText()) * 10;

				waterPercent = std::stoi(waterText->getText());
				waterWidth = waterPercent * (Constants::x_window/100);	//This determines the size of the water based on the input %

				myLand = new Land(0, 0, Constants::x_boundry, Constants::y_boundry);
				myWater = new Water(0, 0, waterWidth, Constants::y_boundry);
				
				terrains.add(myLand);
				terrains.add(myWater);
				drawVector(gw, terrains);

				for (int i = 0; i < numGrass; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					grassVec.push_back(new Grass(x, y, 0, 0));
				}
				for (int i = 0; i < numPlankton; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (!myWater->contains(x, y))		//If the position is outside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					planktonVec.push_back(new Plankton(x, y, 0, 0));
				}
				for (int i = 0; i < numCows; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					cowVec.push_back(new Cow(x, y, cowStarveTime, cowReprodRate));
				}
				for (int i = 0; i < numSnake; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					snakeVec.push_back(new Snake(x, y, snakeStarveTime, snakeReprodRate));
				}
				for (int i = 0; i < numEagle; i++)
				{

					eagleVec.push_back(new Eagle(rand_x(eng), rand_y(eng), eagleStarveTime, eagleReprodRate));
				}
				for (int i = 0; i < numRabbit; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					rabbitVec.push_back(new Rabbit(x, y, rabbitStarveTime, rabbitReprodRate));
				}
				for (int i = 0; i < numFish; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (!myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					fishVec.push_back(new Fish(x, y, fishStarveTime, fishReprodRate));
				}
				for (int i = 0; i < numCroc; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (!myWater->contains(x, y))		//If the position is outside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					crocVec.push_back(new Crocodile(x, y, crocStarveTime, crocReprodRate));
				}
				for (int i = 0; i < numWhale; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (!myWater->contains(x, y))		//If the position is outside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					whaleVec.push_back(new Whale(x, y, whaleStarveTime, whaleReprodRate));
				}
				for (int i = 0; i < numHuman; i++)
				{
					int x = rand_x(eng);
					int y = rand_y(eng);
					while (myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
					{
						x = rand_x(eng);
						y = rand_y(eng);
					}
					humanVec.push_back(new Human(x, y, humanStarveTime, humanReprodRate));
				}

				//Change to a function call
				drawVector(gw, grassVec);
				drawVector(gw, cowVec);
				drawVector(gw, snakeVec);
				drawVector(gw, eagleVec);
				drawVector(gw, rabbitVec);
				drawVector(gw, planktonVec);
				drawVector(gw, fishVec);
				drawVector(gw, crocVec);
				drawVector(gw, whaleVec);
				drawVector(gw, humanVec);
				started = true;
			}


		}

		if (e.getEventType() == TIMER_TICKED && started) //Every 100 millisecons as long as bool started is true
		{
			counter++;
		
			if ((counter % (grassReprodRate * Constants::refresh_rate/10)) == 0)	//Happens every ReprodRate(in seconds)
			{
				int x = rand_x(eng);
				int y = rand_y(eng);
				while (myWater->contains(x, y))		//If the position is inside a water field, do it again, until its not
				{
					x = rand_x(eng);
					y = rand_y(eng);
				}
				grassVec.push_back(new Grass(x, y, 0, 0));				
			}
			if ((counter % (planktonReprodRate * Constants::refresh_rate / 10)) == 0)	//Happens every ReprodRate(in seconds)
			{
				int x = rand_x(eng);
				int y = rand_y(eng);
				while (!myWater->contains(x, y))		//If the position is outside a water field, do it again, until its not
				{
					x = rand_x(eng);
					y = rand_y(eng);
				}
				planktonVec.push_back(new Plankton(x, y, 0, 0));
			}
			if ((counter % (getHungryRate * Constants::refresh_rate / 10)) == 0)	//Every Hungry Rate seconds make creatures hungriness increase one
			{
				getHungry(cowVec);
				getHungry(rabbitVec);
				getHungry(snakeVec);
				getHungry(eagleVec);
				getHungry(fishVec);
				getHungry(crocVec);
				getHungry(whaleVec);
				getHungry(humanVec);
			}

			//Add to creature age every tick
			growOld(cowVec);	
			growOld(rabbitVec);
			growOld(snakeVec);
			growOld(eagleVec);
			growOld(fishVec);
			growOld(crocVec);
			growOld(whaleVec);
			growOld(humanVec);


			//make creatures move
			creatureMove(cowVec, grassVec);
			creatureMove(rabbitVec, grassVec);
			creatureMove(snakeVec, rabbitVec);
			creatureMove(eagleVec, snakeVec);
			creatureMove(fishVec, planktonVec);

			preysVec.addAll(fishVec);
			preysVec.addAll(rabbitVec);
			creatureMove(crocVec, preysVec);	//As Crocodiles can eat both fishes and rabbits
			preysVec.clear();

			creatureMove(whaleVec, fishVec);
			creatureMove(humanVec, cowVec);
			
			//make creatures eat
			creatureEat(cowVec, grassVec);
			creatureEat(rabbitVec, grassVec);
			creatureEat(snakeVec, rabbitVec);
			creatureEat(eagleVec, snakeVec);
			creatureEat(fishVec, planktonVec);

			preysVec.addAll(fishVec);
			preysVec.addAll(rabbitVec);
			creatureEat(crocVec, preysVec);
			preysVec.clear();

			creatureEat(whaleVec, fishVec);
			creatureEat(humanVec, cowVec);

			//Reproduction
			reproduction(cowVec);
			reproduction(rabbitVec);
			reproduction(snakeVec);
			reproduction(eagleVec);
			reproduction(fishVec);
			reproduction(crocVec);
			reproduction(whaleVec);
			reproduction(humanVec);
			//Check for starving creatures
			checkStarvers(cowVec);
			checkStarvers(rabbitVec);
			checkStarvers(snakeVec);
			checkStarvers(eagleVec);
			checkStarvers(fishVec);
			checkStarvers(crocVec);
			checkStarvers(whaleVec);
			checkStarvers(humanVec);

			//Add new borns to the world
			//Change to a function call - update
			drawVector(gw, grassVec);
			drawVector(gw, cowVec);
			drawVector(gw, snakeVec);
			drawVector(gw, eagleVec);
			drawVector(gw, rabbitVec);
			drawVector(gw, planktonVec);
			drawVector(gw, fishVec);
			drawVector(gw, crocVec);
			drawVector(gw, whaleVec);
			drawVector(gw, humanVec);

			//delete dead creatures
			deleteDead(grassVec);
			deleteDead(rabbitVec);
			deleteDead(cowVec);
			deleteDead(snakeVec);
			deleteDead(eagleVec);
			deleteDead(planktonVec);
			deleteDead(fishVec);
			deleteDead(crocVec);
			deleteDead(whaleVec);
			deleteDead(humanVec);

			//Update creature counters
			cowText->setText(std::to_string(cowVec.size()));
			rabbitText->setText(std::to_string(rabbitVec.size()));
			snakeText->setText(std::to_string(snakeVec.size()));
			eagleText->setText(std::to_string(eagleVec.size()));
			humanText->setText(std::to_string(humanVec.size()));
			fishText->setText(std::to_string(fishVec.size()));
			crocText->setText(std::to_string(crocVec.size()));
			whaleText->setText(std::to_string(whaleVec.size()));

		
		}
		if (e.getEventType() == ACTION_PERFORMED) {
			GActionEvent ae = (GActionEvent)e;
			if (ae.getSource() == pauseButton)
			{
				//cout << "timer stopped" << endl;
				timer.stop();
			}

			if (ae.getSource() == continueButton)
			{
				timer.start();
			}

			if (ae.getSource() == restartButton)	//Make it clear the screen
			{
				//Clear Vectors and wait for start to be pressed again to obtain values from text fields
				counter = 0;
				timer.stop();
				grassVec.clear();
				cowVec.clear();
				snakeVec.clear();
				rabbitVec.clear();
				eagleVec.clear();
				planktonVec.clear();
				fishVec.clear();
				crocVec.clear();
				whaleVec.clear();
				humanVec.clear();
				started = false;
				//Call update, maybe kill them all
				drawWorld(gw);//not doing anything atm

			}

			if (ae.getSource() == quitButton)
			{
				gw.close();
				return 0;
			}
		}
	}
	return 0;
}

void creatureMove(Vector <Creature*> predator, Vector <Creature*> prey)
{
	for (int i = 0; i < predator.size(); i++)
	{
		if (predator[i]->getHunger() != 0)	//If creature is hungry look for food (PRIORITY)
		{
			double deltaX = 0;
			double deltaY = 0;
			double distance = 10000;
			//Find closest food
			for (int j = 0; j < prey.size(); j++)
			{
				double temp_dist = calcDistance(predator[i], prey[j]);
				if ((temp_dist < distance) && (temp_dist < predator[i]->getVision()))	//Finds the closest food in range(if there is any)
				{
					distance = temp_dist;
					deltaX = predator[i]->get_X() - prey[j]->get_X();
					deltaY = predator[i]->get_Y() - prey[j]->get_Y();
				}
			}
			if (deltaX == 0 && deltaY == 0)		//If there is no food nearby -> jitter
			{	
				double x = jitter(eng);
				double y = jitter(eng);
				if (predator[i]->getAllowedTerrain() == 1)	//Only allowed on land
				{
					while (myWater->contains(predator[i]->get_X() - x, predator[i]->get_Y() - y))
					{
						x = jitter(eng);
						y = jitter(eng);
					}
					predator[i]->move(x, y);
				}
				else if (predator[i]->getAllowedTerrain() == 2)	//Only allowed on water
				{
					while (!myWater->contains(predator[i]->get_X() - x, predator[i]->get_Y() - y) )
					{
						x = jitter(eng);
						y = jitter(eng);
					}
					predator[i]->move(x, y);
				}
				else   //Allowed on both terrains
				{
					predator[i]->move(x, y);
				}						
			}
			else
				predator[i]->move(deltaX, deltaY);	//Move towards food
		}
		else   //Creature is Full
		{
			if (predator[i]->isAbleToReprod() == true)		//Full and able to reproduce -> Look for mate to reproduce with
			{
				double deltaX = 0;
				double deltaY = 0;
				double distance = 10000;
				//Find closest mate that is also able to reproduce
				for (int j = 0; j < predator.size(); j++)
				{

					if ((i != j) && predator[j]->isAbleToReprod() == true && predator[j]->getHunger() == 0)//Checks if the other creature is also able to reproduce
					{
						double temp_dist = calcDistance(predator[i], predator[j]);
						if ((temp_dist < distance) && (temp_dist < predator[i]->getVision()))
						{
							distance = temp_dist;
							deltaX = predator[i]->get_X() - predator[j]->get_X();
							deltaY = predator[i]->get_Y() - predator[j]->get_Y();
						}
					}
				}
				if (deltaX == 0 && deltaY == 0)		//If there is no available mate nearby -> jitter
				{
					double x = jitter(eng);
					double y = jitter(eng);
					if (predator[i]->getAllowedTerrain() == 1)	//Only allowed on land
					{
						while (myWater->contains(predator[i]->get_X() - x, predator[i]->get_Y() - y))
						{
							x = jitter(eng);
							y = jitter(eng);
						}
						predator[i]->move(x, y);
					}
					else if (predator[i]->getAllowedTerrain() == 2)	//Only allowed on water
					{
						while (!myWater->contains(predator[i]->get_X() - x, predator[i]->get_Y() - y) )
						{
							x = jitter(eng);
							y = jitter(eng);
						}
						predator[i]->move(x, y);
					}
					else   //Allowed on both terrains
					{
						predator[i]->move(x, y);
					}
				}
				else
					predator[i]->move(deltaX, deltaY);	//Move towards mate
			}
			else   //Creature is Full but not able to reproduce
			{
				predator[i]->move(jitter(eng), jitter(eng));	//Jitter around in order to not stand still
			}
		}
	}

}

void creatureEat(Vector <Creature*> predator, Vector <Creature*> prey)
{
	for (int i = 0; i < prey.size(); i++)	//predator eating prey
	{
		for (int j = 0; j < predator.size(); j++)
		{
			if ((abs(prey[i]->get_X() - predator[j]->get_X()) <= Constants::maxMoveSpeed) && (abs(prey[i]->get_Y() - predator[j]->get_Y()) <= Constants::maxMoveSpeed) && (predator[j]->getHunger() != 0))	//If the difference between their X and Y is <= the maximum move speed(currently 4) then they are close enough
			{
				prey[i]->kill();
				predator[j]->reduceHunger();	//Reduces hungriness by one
			}
		}

	}
}

void deleteDead(Vector <Creature*>& creature)
{
	for (int i = 0; i < creature.size(); i++)
	{
		if (creature[i]->isAlive() == false)
		{
			delete creature[i];
			creature.remove(i);
		}
	}
}

void growOld(Vector <Creature*> creature)
{
	for (int i = 0; i < creature.size(); i++)
	{
		creature[i]->addAge();
		if (creature[i]->getAge() == creature[i]->getDeathAge())
			creature[i]->kill();
		else if (creature[i]->getAge() % creature[i]->getReprodRate() == 0)	//Every reproduction rate it sets heat to true
		{
			creature[i]->setHeat(true);
		}
	}
}

void getHungry(Vector <Creature*> creature)
{
	for (int i = 0; i < creature.size(); i++)
	{
		if (creature[i]->getHunger() != creature[i]->getMaxHunger())	
		{
			creature[i]->increaseHunger();
			if (creature[i]->getHunger() == creature[i]->getMaxHunger()) 
			{
				creature[i]->setStarveStart(counter);		//Sets the starvation start time as the current world counter
			}
		}
	}
}


void reproduction(Vector <Creature*>& creature)
{
	for (int i = 0; i < creature.size(); i++)	//Creature mating
	{
		if (creature[i]->getHunger() == 0)	//Must be full to reproduce
		{
			for (int j = 0; j < creature.size(); j++)
			{
				if (creature[j]->getHunger() == 0)
				{
					if ((i != j) && (creature[i]->isAbleToReprod() == true) && (creature[j]->isAbleToReprod() == true) && (abs(creature[i]->get_X() - creature[j]->get_X()) <= Constants::maxMoveSpeed) && (abs(creature[i]->get_Y() - creature[j]->get_Y()) <= Constants::maxMoveSpeed))
					{
						//creature[i]->increaseHunger();	//Get hungry after having a baby
						//creature[j]->increaseHunger();
						creature[i]->setHeat(false);
						creature[j]->setHeat(false);
						if (creature[i]->getCreatureType() == 1)
							creature.push_back(new Cow(creature[i]->get_X(), creature[i]->get_Y(), cowStarveTime, cowReprodRate));
						else if (creature[i]->getCreatureType() == 2)
							creature.push_back(new Snake(creature[i]->get_X(), creature[i]->get_Y(),  snakeStarveTime, cowReprodRate));
						else if (creature[i]->getCreatureType() == 3)
							creature.push_back(new Eagle(creature[i]->get_X(), creature[i]->get_Y(),  eagleStarveTime, cowReprodRate));
						else if (creature[i]->getCreatureType() == 4)
							creature.push_back(new Rabbit(creature[i]->get_X(), creature[i]->get_Y(),  rabbitStarveTime, cowReprodRate));
						else if (creature[i]->getCreatureType() == 6)
							creature.push_back(new Fish(creature[i]->get_X(), creature[i]->get_Y(), fishStarveTime, fishReprodRate));
						else if (creature[i]->getCreatureType() == 7)
							creature.push_back(new Crocodile(creature[i]->get_X(), creature[i]->get_Y(), crocStarveTime, crocReprodRate));
						else if (creature[i]->getCreatureType() == 8)
							creature.push_back(new Whale(creature[i]->get_X(), creature[i]->get_Y(), whaleStarveTime, whaleReprodRate));
						else if (creature[i]->getCreatureType() == 9)
							creature.push_back(new Human(creature[i]->get_X(), creature[i]->get_Y(), humanStarveTime, humanReprodRate));
						
					}
				}
			}
		}

	}
}

void checkStarvers(Vector <Creature*> creature)
{
	for (int i = 0; i < creature.size(); i++)
	{
		if (creature[i]->getHunger() == creature[i]->getMaxHunger() && counter - creature[i]->getStarveStart() >= creature[i]->getStarveTime())
		{
			creature[i]->kill();
		}
	}
}


template <typename T>
void drawVector(GWindow& gw, Vector <T*> myVec)
{
	for (int i = 0; i < myVec.size(); i++)
	{
		myVec[i]->draw(gw);
	}
}
