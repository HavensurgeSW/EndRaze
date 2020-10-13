#include "Mainframe.h"


namespace EZ {
	Mainframe::Mainframe() {
		_winWidth = 800;
		_winHeight = 450;
		_pause = false;
		_mainBool = true;
		screenID screenId;
		_parallax1 = 0;
	
	}
	Mainframe::~Mainframe() {
		CloseWindow();
	}

	void Mainframe::init() {
		screenId = screenID::menu;
		InitWindow(_winWidth, _winHeight, "HSS - End-Raze");
		SetTargetFPS(60);
		SetExitKey(KEY_VOLUME_UP);
	}
	void Mainframe::setScene(int scene) {
		switch (scene) {
		case 0:
			screenId = screenID::menu;
			break;
		case 1:
			screenId = screenID::game;
			break;
		}
	}
	void Mainframe::mainLoop() {

		while (!WindowShouldClose() && _mainBool) {
			switch (screenId) {
			case screenID::menu:
				menuScreen();
			case screenID::game:
				gameScreen();
			}
		}
	}
	void Mainframe::menuScreen() {
		background1 = LoadTexture("../res/parallax-mountain-bg.png");
		background2 = LoadTexture("../res/parallax-mountain-mountains.png");

		Rectangle playButton;
		playButton.x = 20.0f;
		playButton.y = GetScreenHeight() / 2.0f;
		playButton.height = 30.0f;
		playButton.width = 65.0f;

		Rectangle creditsButton;
		creditsButton.x = 20.0f;
		creditsButton.y = (GetScreenHeight() / 2) + 100.0f;
		creditsButton.height = 30.0f;
		creditsButton.width = 113.0f;
		Rectangle closeButton;
		closeButton.x = 20.0f;
		closeButton.y = (GetScreenHeight() / 2) + 150.0f;
		closeButton.height = 30.0f;
		closeButton.width = 81.25f;

		Vector2 background2pos = { 0,0 };

		while (!WindowShouldClose() && screenId == screenID::menu&&_mainBool) {
			BeginDrawing();
			ClearBackground(BLACK);
			DrawTextureEx(background1, {0,0}, 0.0f, 3.0f,RAYWHITE);

			/*DrawTextureEx(background2, { 0,0 }, 0, 3.0f, RAYWHITE);*/
			DrawTextureEx(background2, { background2pos.x - 2.0f , 50 }, 0.0f, 3.0f, RAYWHITE);

			DrawText(FormatText("END-RAZE"), 20, 10, 120, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), playButton))
				DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, RED);
			else
				DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, WHITE);


			if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
				DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, RED);
			else
				DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), closeButton))
				DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, RED);
			else
				DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, WHITE);


			DrawText(FormatText("v 0.1"), GetScreenWidth() - 50, 1, 20, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
				DrawText(FormatText("Engine: Raylib 3.0"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 20, 30, WHITE);
				DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 100, 30, WHITE);
				DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 130, 30, WHITE);
			}
			EndDrawing();
			if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
				exit(0);
			}
			if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				setScene(1);
			}
		}
	}
	void Mainframe::gameScreen() {
		_parallax1 = GetFrameTime()*400.0f;
		setPlayerParameters();
		setObs();
		while (!WindowShouldClose() && screenId == screenID::game&&_mainBool) {
			if (!_pause) {
				input();
				update();
#if DEBUG
				cout << player.rec.y << endl;
			/*	cout << obs[0].rec.x << endl;
				cout << obs[0].rec.y << endl;*/
#endif
				collisions();
				draw();
			}
		}

	}


	void Mainframe::input() {
		if (IsKeyPressed(KEY_W)){
			if (player.rec.y==125.0f){
				
			}
			else {
				player.rec.y -= 100.0f;
			}
		}
		if (IsKeyPressed(KEY_S)) {
			if (player.rec.y == 325.0f) {

			}
			else {
				player.rec.y += 100.0f;
			}
				
		}
	}
	void Mainframe::update() {
		for (int i = 0; i < ObstacleMax; i++) {
			obs[i].rec.x = obs[i].rec.x - _parallax1;

		}
		for (int i = 0; i < ObstacleMax; i++){
			if (obs[i].rec.x < -50) {
				obs[i].rec.x = GetRandomValue(GetScreenWidth()+10, GetScreenWidth()*2);
				switch (GetRandomValue(1,3)) {
				case 1:
					obs[i].rec.y = 125;
					break;
				case 2:
					obs[i].rec.y = 225;
					break;
				case 3:
					obs[i].rec.y = 325;
					break;
				}
				for (int j = 0; j < ObstacleMax; j++){
					if (CheckCollisionRecs(obs[i].rec, obs[j].rec)) {
						obs[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
					}
				}
				

			}
		}
	}
	void Mainframe::collisions() {
	
	}
	void Mainframe::draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleRec(player.rec,player.color);
		DrawLine(0, GetScreenHeight() / 2 + player.rec.height - 100.0f, GetScreenWidth(), GetScreenHeight() / 2 + player.rec.height - 100.0f, RED);
		DrawLine(0,GetScreenHeight()/2+player.rec.height,GetScreenWidth(), GetScreenHeight() / 2 + player.rec.height, RED);
		DrawLine(0, GetScreenHeight() / 2 + player.rec.height + 100.0f, GetScreenWidth(), GetScreenHeight() / 2 + player.rec.height + 100.0f , RED);
		EndDrawing();
		for (int i = 0; i < ObstacleMax; i++){
			DrawRectangleRec(obs[i].rec, YELLOW);
		}
	
	}

	













}