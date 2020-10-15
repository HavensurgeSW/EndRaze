#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace EZ {

	struct Player {
		Rectangle rec;
		Rectangle atk;
		Color color;
		int lives;
		int lane;
	};
	extern Player player;
	void setPlayerParameters();
}
#endif