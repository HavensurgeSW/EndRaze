#pragma once
#include "raylib.h"

namespace EZ {
	struct Obstacle {
		Rectangle rec;
		Texture2D obstacle;
		bool active;
	};

	const int ObstacleMax = 3;
	extern Obstacle obs[ObstacleMax];

	void setObs();
}

