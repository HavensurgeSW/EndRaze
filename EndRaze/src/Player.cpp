#include "Player.h"

namespace EZ {
	Player player;
	

	void setPlayerParameters() {
		player.rec.width = 25;
		player.rec.height = 50;
		player.rec.x = 15;
		player.rec.y = GetScreenHeight() / 2;
		player.color = RAYWHITE;
		int live = 3;
		player.lane = 2;
	}
}