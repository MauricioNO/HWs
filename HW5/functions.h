#pragma once
#include "gwindow.h"
#include "Creature.h"
#include "Terrain.h"


void drawWorld(GWindow& gw);
void refreshWindow(GWindow& gw);

double calcDistance(Creature* c1, Creature* c2);
