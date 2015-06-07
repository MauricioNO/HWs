#include "functions.h"
#include "constants.h"



void drawWorld(GWindow& gw)
{
	gw.setColor("white");
	gw.fillRect(0, 0, Constants::x_window, Constants::y_window);
	gw.setColor("black");
	gw.drawRect(0, 0, Constants::x_window, Constants::y_window);
	
}

double calcDistance(Creature* c1, Creature* c2)
{
	double distance;
	distance = sqrt(pow(c1->get_X() - c2->get_X(), 2) + pow(c1->get_Y() - c2->get_Y(), 2));
	return distance;

}
