#pragma once
#include "raylib.h"

namespace EZ {
	struct Obstacle {
		Rectangle rec;
		Texture2D obstacle;
	};

	const int ObstacleMax = 10;
	extern Obstacle obs[ObstacleMax];

	void setObs();
	void randPos(Obstacle _obs);
}
