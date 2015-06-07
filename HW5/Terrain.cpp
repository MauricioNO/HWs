#include "Terrain.h"

Terrain::Terrain(int pos_x, int pos_y, int t_width, int t_height, string color)
{
	rect->setLocation(pos_x, pos_y);
	rect->setSize(t_width, t_height);
	rect->setFilled(true);
	rect->setColor(color);
}


void Terrain::draw(GWindow& gw)
{
	gw.add(rect);
}

bool Terrain::contains(double x, double y)
{
	if (rect->contains(x, y))
		return true;
	else
		return false;
}

Terrain::~Terrain()
{

}
