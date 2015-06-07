#include "Land.h"

Land::Land(int pos_x, int pos_y, int t_width, int t_height) : Terrain(pos_x, pos_y, t_width, t_height, "#9B7653")
{
	type = LAND;
}
