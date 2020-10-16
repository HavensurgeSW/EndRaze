#include "Player.h"

namespace EZ {
	Player player;
	
	void setPlayerParameters() {
		player.rec.width = 25;
		player.rec.height = 35;
		player.rec.x = 15;
		player.rec.y = GetScreenHeight() / 2;
		player.color = RAYWHITE;
		player.lives = 3;
		player.atk.width = 50;
		player.atk.height = 35;
		player.atk.x = player.rec.x + player.rec.width;
		player.atk.y = player.rec.y;
		player.tex = LoadTexture("../res/CloakGuy.png");
		player.cloud = LoadTexture("../res/attackcloud.png");
		player.score = -80;
		player.gravity = 2.0f;
	}
}