#include "GameController.h"
#include "time.h"

GameController::GameController(void) {}

GameController::GameController(GameView * gameView, GameModel * gameModel) {
	this->gameView = gameView;
	this->gameModel = gameModel;

	gameView->asignData(gameModel->getData());
	running = true;
	run();
}

GameController::~GameController(void) {}

void GameController::run() {
	while(running) {
		running = gameView->run();
		
		if(gameView->isApplyIA()) {
			gameModel->applyIA();
			gameView->insertDataIA(gameModel->getI0(), gameModel->getJ0(), gameModel->getI1(), gameModel->getJ1());
		}
	}
}
