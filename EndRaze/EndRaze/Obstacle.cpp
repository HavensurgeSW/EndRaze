#include "Obstacle.h"

namespace EZ {
	Obstacle obs[ObstacleMax];

	void setObs() {
		for (int i = 0; i < ObstacleMax; i++) {
			obs[i].rec.height = 60;
			obs[i].rec.width = 25;
			randPos(obs[i]);
		}
	}
	void randPos(Obstacle _obs) {
		_obs.rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() + GetScreenWidth() / 2);
		switch (GetRandomValue(1, 3)) {
		case 1:
			_obs.rec.y = 75;
			break;
		case 2:
			_obs.rec.y = 225;
			break;
		case 3:
			_obs.rec.y = 375;
			break;
		}

	}
}