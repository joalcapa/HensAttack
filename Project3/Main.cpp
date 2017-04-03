#include "SDL2-2.0.3\include\SDL.h"
#include "SDL2-2.0.3\include\SDL_image.h"
#include <iostream>
#include <stdio.h>
#include "GameController.h"
#include "GameView.h"

using namespace std;

int main(int, char **) {
	SDL_Init(SDL_INIT_EVERYTHING);

	if(!IMG_Init (IMG_INIT_PNG)) {
		std::cerr<<"Error al inicializar las librearias SDL"<<std::endl;
	    SDL_Quit();
	    return 1;
	}

	GameModel * gameModel = new GameModel();
	GameView * gameView = new GameView("Hens-Attack", 700, 700);
        GameController * gameController = new GameController(gameView, gameModel);
	
	delete gameController;
	delete gameView;
	delete gameModel;

	SDL_Quit();
	return 0;
}
