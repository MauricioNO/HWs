#pragma once

#include <string>
#include "gobjects.h"

using std::string;

class Terrain{
public:
	//Constructor
	Terrain();
	Terrain(int pos_x, int pos_y, int t_width, int t_height, string color);
	virtual void draw(GWindow& gw);
	virtual bool contains(double x, double y);

		
	~Terrain();

	
protected:
	
	enum TerrainType
	{
		LAND,
		WATER
	};

	int x;
	int y;
	int width;
	int height;
	string type;
	GRect* rect = new GRect(0, 0);
};
