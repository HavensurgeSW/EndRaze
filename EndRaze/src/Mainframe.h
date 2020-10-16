#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "raylib.h"
#include "Player.h"
#include "Obstacle.h"
#include "UnJumpObs.h"
#include "DestrucObs.h"
#include <iostream>
using namespace std;


namespace EZ {
	class Mainframe {
	private:
		int _winWidth;
		int _winHeight;
		bool _pause;
		bool _mainBool;
		int _parallax1;

	public:

		enum class screenID {
			menu,
			game
		};
		screenID screenId;
		Texture2D background1;
		Texture2D background2;
		Texture2D floor;
		Texture2D obstacle;
		Texture2D destructable;
		Texture2D unjumpable;
		Music mainTheme;
		Music gameTheme;
		Sound collision;

		Mainframe();
		~Mainframe();
		void init();
		void setScene(int scene);
		void mainLoop();
		void menuScreen();
		void gameScreen();
		
		void update();
		void draw();
		void input();
		void collisions();

		void resize();


	};
}
#endif