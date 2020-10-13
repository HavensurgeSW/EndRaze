#pragma once
#include "raylib.h"

struct Obstacle {
	Rectangle rec;
	Texture2D obstacle;
};

const int ObstacleMax = 10;
extern Obstacle obs[ObstacleMax];

void setObs();
void randPos(Obstacle _obs);
