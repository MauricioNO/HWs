#include "Water.h"

Water::Water(int pos_x, int pos_y, int t_width, int t_height) : Terrain(pos_x, pos_y, t_width, t_height, "blue")
{
	type = WATER;
}
