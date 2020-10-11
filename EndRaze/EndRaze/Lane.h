#pragma once
#include "raylib.h"

struct Lane {
	Rectangle layer;
};

extern Lane lane[3];
void setLanes();