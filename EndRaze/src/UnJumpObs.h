#pragma once
#include "raylib.h"

namespace EZ {

	struct UnJump {
		Rectangle rec;
		Texture2D obstacle;
		bool active;
	};

	const int UnjMax = 2;
	extern UnJump unj[UnjMax];

	void setUnj();
}

