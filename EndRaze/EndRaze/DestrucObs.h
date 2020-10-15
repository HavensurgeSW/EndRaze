#pragma once
#include "raylib.h"

namespace EZ {

	struct DestrucObs {
		Rectangle rec;
		bool active;
		Texture2D obstacle;
	};

	const int DestrucMax = 3;
	extern DestrucObs des[DestrucMax];

	void setDestruc();
}
