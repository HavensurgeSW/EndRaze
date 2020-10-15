#include "DestrucObs.h"

DestrucObs des[DestrucMax];


void setDestruc() {
	for (int i = 0; i < DestrucMax; i++) {
		des[i].rec.height = 30;
		des[i].rec.width = 25;
		des[i].rec.x = -51;
		des[i].active = true;
	}
}