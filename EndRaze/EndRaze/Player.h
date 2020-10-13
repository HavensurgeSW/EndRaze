#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace EZ {

	struct Player {
		Rectangle rec;
		Color color;
		int lives;
	};
	extern Player player;
	void setPlayerParameters();
}
#endif