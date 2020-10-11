#include "Lane.h"

Lane lane[3];
void setLanes() {
	for (int i = 0; i < 3; i++){
		lane[i].layer.height = 15;
		lane[i].layer.width = 100;
	}
	
}