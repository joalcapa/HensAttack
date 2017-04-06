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

	# Initialization of the application oriented to MVC (Model-View-Controller)
	# GameModel, Establishes the algorithm of analysis and solution of the movements of the hens 
	# GameView, Establishes the parameters for the SDL context
	# GameController, Establishes the control of the application, receives the model and the view
	GameModel * gameModel = new GameModel();
	GameView * gameView = new GameView("Hens-Attack", 700, 700);
        GameController * gameController = new GameController(gameView, gameModel);
	
	delete gameController;
	delete gameView;
	delete gameModel;

	SDL_Quit();
	return 0;
}
