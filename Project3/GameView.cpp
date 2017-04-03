#include "GameView.h"


GameView::GameView(void) {}

GameView::~GameView(void) {}

GameView::GameView(const char * tittle, int screenWidth, int screenHeight) {
	window = SDL_CreateWindow(tittle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);	
	running = true;
	stage = new Stage(renderer, screenWidth, screenHeight);	
}

bool GameView::run() {
	input();
	update();
	render();
	return running;
}

void GameView::input() {
	while(SDL_PollEvent(&event)) {
		handleEvent();
	}
}

void GameView::handleEvent() {
	switch(event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEMOTION:	
		stage->mouseMotion(event);
		break;
	case SDL_MOUSEBUTTONDOWN:
		stage->mouseClick(event);
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	}
}

void GameView::update() {
	stage->action(Stage::UPDATE);
}

void GameView::render() {
	SDL_RenderClear(renderer);
	stage->render();
	SDL_RenderPresent(renderer);
}

void GameView::asignData(int ** data) {
	stage->asignData(data);
}

void GameView::insertDataIA(int i0, int j0, int i1, int j1) {
	stage->insertDataIA(i0, j0, i1, j1);
}

bool GameView::isApplyIA() {
	return stage->IsApplyIA();
}
