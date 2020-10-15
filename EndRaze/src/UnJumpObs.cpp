#include "UnJumpObs.h"

UnJump unj[UnjMax];


void setUnj() {
	for (int i = 0; i < UnjMax; i++) {
		unj[i].rec.height = 60;
		unj[i].rec.width = 25;
		unj[i].rec.x = -51;
		unj[i].active = true;
	}
}