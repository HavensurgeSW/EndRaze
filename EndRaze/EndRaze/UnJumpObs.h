#pragma once
#include "raylib.h"

struct UnJump {
	Rectangle rec;
	Texture2D obstacle;
};

const int UnjMax = 2;
extern UnJump unj[UnjMax];

void setUnj();

