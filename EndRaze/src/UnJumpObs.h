#pragma once
#include "raylib.h"

struct UnJump {
	Rectangle rec;
	Texture2D obstacle;
	bool active;
};

const int UnjMax = 4;
extern UnJump unj[UnjMax];

void setUnj();

