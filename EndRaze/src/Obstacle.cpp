#include "Obstacle.h"

namespace EZ {

	Obstacle obs[ObstacleMax];

	void setObs() {
		for (int i = 0; i < ObstacleMax; i++) {
			obs[i].rec.height = 30;
			obs[i].rec.width = 25;
			obs[i].rec.x = -51;
			obs[i].active = true;
		}
	}
}
