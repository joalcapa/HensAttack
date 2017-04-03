#include "GameView.h"
#include "GameModel.h"

#pragma once
class GameController {
private:
	GameModel * gameModel;
	GameView * gameView;

	bool running;

public:
	GameController(void);
	GameController(GameView * gameView, GameModel * gameModel);
	~GameController(void);
	void run();
};
