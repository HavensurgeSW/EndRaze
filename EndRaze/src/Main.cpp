#include "Mainframe.h"
using namespace EZ;

int main(void) {
Mainframe* EndRaze = new Mainframe;
	EndRaze->init();
	EndRaze->mainLoop();

	delete EndRaze;
	return 0;
}