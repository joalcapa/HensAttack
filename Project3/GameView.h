#include "Stage.h"

#pragma once
class GameView{
private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Event event;

	bool running;
	Stage * stage;

public:
	GameView(void);
	~GameView(void);
	GameView(const char * title, int screenWidth, int screenHeight);

    bool run();
	void input();
	void handleEvent();
	void update();
	void render();
	void asignData(int ** data);
	void insertDataIA(int i0, int j0, int i1, int j1);
	bool isApplyIA();
};
