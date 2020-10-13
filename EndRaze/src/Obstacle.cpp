#include "Obstacle.h"

Obstacle obs[ObstacleMax];


void setObs() {
	for (int i = 0; i < ObstacleMax; i++) {
		obs[i].rec.height = 60;
		obs[i].rec.width = 25;
		randPos(obs[i]);
	}
}
void randPos(Obstacle _obs) {
	/*_obs.rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() + GetScreenWidth() / 2);*/
	_obs.rec.x = 800;

	int random = GetRandomValue(1, 3);
	switch (random) {
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