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
		CloseAudioDevice();
		CloseWindow();
	}

	void Mainframe::init() {
		screenId = screenID::menu;
		InitWindow(_winWidth, _winHeight, "HSS - End-Raze");
		SetTargetFPS(60);
		SetExitKey(KEY_VOLUME_UP);
		InitAudioDevice();
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
		mainTheme = LoadMusicStream("../res/sounds/MenuTheme.ogg");
		SetMusicVolume(mainTheme,0.4f);

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

		PlayMusicStream(mainTheme);

		while (!WindowShouldClose() && screenId == screenID::menu&&_mainBool) {
			UpdateMusicStream(mainTheme);
			BeginDrawing();
			ClearBackground(BLACK);

			DrawTextureEx(background1, {0,0}, 0.0f, 3.0f,RAYWHITE);
			DrawTextureEx(background2, { 0,0 }, 0, 3.0f, RAYWHITE);
			

			DrawText(FormatText("END-RAZE"), 20, 10, 120, BLACK);

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


			DrawText(FormatText("v 0.5"), GetScreenWidth() - 50, 1, 20, WHITE);
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
		floor = LoadTexture("../res/Floor.png");
		obstacle = LoadTexture("../res/obs.png");
		destructable = LoadTexture("../res/destructable.png");
		gameTheme = LoadMusicStream("../res/sounds/GameplayTheme.ogg");
		collision = LoadSound("../res/sounds/collision.ogg");
		SetMusicVolume(gameTheme, 0.2f);

		_parallax1 = GetFrameTime()*350.0f;
		setPlayerParameters();
		setObs();
		setUnj();
		setDestruc();

		PlayMusicStream(gameTheme);

		while (!WindowShouldClose() && screenId == screenID::game&&_mainBool) {
			if (!_pause) {
				input();
				update();
#if DEBUG
				cout << player.lives << endl;
			/*	cout << GetScreenHeight() / 2 + player.rec.height << endl;*/
			/*	cout << player.rec.y << endl;*/
			/*	cout << obs[0].rec.x << endl;
				cout << obs[0].rec.y << endl;*/
#endif
				collisions();
				draw();
			}

		}

		UnloadTexture(floor);
		UnloadTexture(obstacle);
		UnloadTexture(destructable);
		UnloadMusicStream(gameTheme);
		UnloadSound(collision);
	}


	void Mainframe::input() {
		if (IsKeyPressed(KEY_W)){
			if (player.rec.y==125.0f){
				
			}
			else {
				player.rec.y -= 100.0f;
				player.atk.y -= 100.0f;
			}
		}
		if (IsKeyPressed(KEY_S)) {
			if (player.rec.y == 325.0f) {

			}
			else {
				player.rec.y += 100.0f;
				player.atk.y += 100.0f;
			}
		}
		
		if (IsKeyDown(KEY_E)){
			for (int i = 0; i < DestrucMax; i++){
				if (CheckCollisionRecs(player.atk,des[i].rec)){
					des[i].active = false;
				}
			}
		}
	}
	void Mainframe::update() {
		//---------------MUSIC UPDATE-----------------------//
		UpdateMusicStream(gameTheme);
		//---------------LOSE CONDITION---------------------//
		if (player.lives<=0){
			setScene(0);
		}

		//---------------Moving Obstacles-------------------//
		for (int i = 0; i < ObstacleMax; i++) {
			obs[i].rec.x = obs[i].rec.x - _parallax1;

		}
		for (int i = 0; i < ObstacleMax; i++) {
			if (obs[i].rec.x < -50) {
				player.score += 10;
				obs[i].active = true;
				obs[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
				switch (GetRandomValue(1, 3)) {
				case 1:
					obs[i].rec.y = 160 - obs[i].rec.height;
					break;
				case 2:
					obs[i].rec.y = 260 - obs[i].rec.height;
					break;
				case 3:
					obs[i].rec.y = 360 - obs[i].rec.height;
					break;
				}
				for (int j = 0; j < ObstacleMax; j++) {
					if (CheckCollisionRecs(obs[i].rec, obs[j].rec)) {
						obs[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
					}
				}


			}
		}
		//---------------Moving UnJumpables-------------------//
		for (int i = 0; i < UnjMax; i++) {
			unj[i].rec.x = unj[i].rec.x - _parallax1;

		}
		for (int i = 0; i < UnjMax; i++) {
			if (unj[i].rec.x < -50) {
				player.score += 10;
				unj[i].active = true;
				unj[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
				switch (GetRandomValue(1, 3)) {
				case 1:
					unj[i].rec.y = 160 - unj[i].rec.height;
					break;
				case 2:
					unj[i].rec.y = 260 - unj[i].rec.height;
					break;
				case 3:
					unj[i].rec.y = 360 - unj[i].rec.height;
					break;
				}
				for (int j = 0; j < UnjMax; j++) {
					if (CheckCollisionRecs(unj[i].rec, unj[j].rec)) {
						unj[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
					}
				}


			}
		}
		//---------------Moving destructibles-------------------//
		for (int i = 0; i < DestrucMax; i++) {
			des[i].rec.x = des[i].rec.x - _parallax1;

		}
		for (int i = 0; i < DestrucMax; i++) {
			if (des[i].rec.x < -50) {
				player.score += 10;
				des[i].active = true;
				des[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
				switch (GetRandomValue(1, 3)) {
				case 1:
					des[i].rec.y = 160 - des[i].rec.height;
					break;
				case 2:
					des[i].rec.y = 260 - des[i].rec.height;
					break;
				case 3:
					des[i].rec.y = 360 - des[i].rec.height;
					break;
				}
				for (int j = 0; j < DestrucMax; j++) {
					if (CheckCollisionRecs(des[i].rec, unj[j].rec)) {
						des[i].rec.x = GetRandomValue(GetScreenWidth() + 10, GetScreenWidth() * 2);
					}
				}


			}
		}

	}
	void Mainframe::collisions() {
		for (int i = 0; i < DestrucMax; i++){
			if (des[i].active&&CheckCollisionRecs(player.rec, des[i].rec) && des[i].active){
				PlaySound(collision);
				des[i].active = false;
				player.lives--;

			}
		}
		for (int i = 0; i < ObstacleMax; i++) {
			if (CheckCollisionRecs(player.rec, obs[i].rec)&&obs[i].active) {
				PlaySound(collision);
				obs[i].active = false;
				player.lives--;
			}
		}
		for(int i = 0; i <UnjMax; i++) {
			if (CheckCollisionRecs(player.rec, unj[i].rec) && unj[i].active) {
				PlaySound(collision);
				unj[i].active = false;
				player.lives--;
			}
		}
	
	}
	void Mainframe::draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextureEx(background1, { 0,0 }, 0.0f, 3.0f, RAYWHITE);
		DrawTextureEx(background2, { 0 , 50 }, 0.0f, 3.0f, RAYWHITE);

#if DEBUG
		DrawLine(0, GetScreenHeight() / 2 + player.rec.height - 100.0f, GetScreenWidth(), GetScreenHeight() / 2 + player.rec.height - 100.0f, RED);
		DrawLine(0,GetScreenHeight()/2+player.rec.height,GetScreenWidth(), GetScreenHeight() / 2 + player.rec.height, RED);
		DrawLine(0, GetScreenHeight() / 2 + player.rec.height + 100.0f, GetScreenWidth(), GetScreenHeight() / 2 + player.rec.height + 100.0f , RED);
#endif
		for (int i = 0; i < ObstacleMax; i++){
			if (obs[i].active){
				DrawTexture(obstacle, obs[i].rec.x, obs[i].rec.y, RAYWHITE);
			}
		}

		for (int i = 0; i < UnjMax; i++) {
			if (unj[i].active){
				DrawRectangleRec(unj[i].rec, BLUE);
			}
		}
		for (int i = 0; i < DestrucMax; i++) {
			if (des[i].active){
				DrawTexture(destructable, des[i].rec.x, des[i].rec.y, RAYWHITE);
			}
		}
	
		DrawTexture(player.tex,player.rec.x,player.rec.y, RAYWHITE);
	/*	DrawRectangleRec(player.rec,player.color);*/
#if DEBUG
		DrawRectangleLines(player.atk.x, player.atk.y, player.atk.width, player.atk.height, WHITE);
#endif

		for (int i = 0; i < 8; i++){
			DrawTexture(floor, 100 * i, 160, RAYWHITE);
			DrawTexture(floor, 100 * i, 260, RAYWHITE);
			DrawTexture(floor, 100 * i, 360, RAYWHITE);
		}

		DrawText("SCORE:", player.rec.x, GetScreenHeight()/15,20,BLACK);
		DrawText(FormatText("%i", player.score), player.rec.x + 80, GetScreenHeight() / 15, 20, BLACK);

		DrawText("LIVES:", player.rec.x, GetScreenHeight() / 9, 20, BLACK);
		DrawText(FormatText("%i", player.lives), player.rec.x + 80, GetScreenHeight() / 9, 20, BLACK);

		EndDrawing();
	}

}