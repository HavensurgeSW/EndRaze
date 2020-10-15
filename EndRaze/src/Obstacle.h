#pragma once
#include "raylib.h"

struct Obstacle {
	Rectangle rec;
	Texture2D obstacle;
};

const int ObstacleMax = 4;
extern Obstacle obs[ObstacleMax];

void setObs();
Obstacle randPos(Obstacle _obs);
