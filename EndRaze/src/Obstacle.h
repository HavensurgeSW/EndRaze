#pragma once
#include "raylib.h"

struct Obstacle {
	Rectangle rec;
	Texture2D obstacle;
	bool active;
};

const int ObstacleMax = 3;
extern Obstacle obs[ObstacleMax];

void setObs();

