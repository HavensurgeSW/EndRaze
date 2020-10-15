#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace EZ {

	struct Player {
		Rectangle rec;
		Rectangle atk;
		Color color;
		int lives;
		Texture2D tex;
		int score;
	};
	extern Player player;
	void setPlayerParameters();
}
#endif