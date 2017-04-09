#include "Stage.h"
#include "GameModel.h"

Stage::Stage(void) {}

Stage::~Stage(void) {}

Stage::Stage(SDL_Renderer * renderer, int WIDTH, int HEIGHT) {
	headboard = runner = relativeRunner = NULL;
	this->renderer = renderer;
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
	isRunningFox = true;
	isDirection = isKilling = isKiller = isMomentFox = applyIA = isDelayIA = isDelayFox = false;

	wallpaper = new Imagen(renderer, "Imagenes/fondo.png", 0, 0);

	directionHuntedN = new Imagen(renderer, "Imagenes/Conexiones/N.png", 0, 100);
	directionHuntedS = new Imagen(renderer, "Imagenes/Conexiones/S.png", 0, 100);
	directionHuntedE = new Imagen(renderer, "Imagenes/Conexiones/E.png", 0, 100);
	directionHuntedO = new Imagen(renderer, "Imagenes/Conexiones/O.png", 0, 100);
	directionHuntedDNO = new Imagen(renderer, "Imagenes/Conexiones/DNO.png", 0, 100);
	directionHuntedDNE = new Imagen(renderer, "Imagenes/Conexiones/DNE.png", 0, 100);
	directionHuntedDSO = new Imagen(renderer, "Imagenes/Conexiones/DSO.png", 0, 100);
	directionHuntedDSE = new Imagen(renderer, "Imagenes/Conexiones/DSE.png", 0, 100);
	directionHuntedDDNO = new Imagen(renderer, "Imagenes/Conexiones/DDNO.png", 0, 100);
	directionHuntedDDNE = new Imagen(renderer, "Imagenes/Conexiones/DDNE.png", 0, 100);
	directionHuntedDDSO = new Imagen(renderer, "Imagenes/Conexiones/DDSO.png", 0, 100);
	directionHuntedDDSE = new Imagen(renderer, "Imagenes/Conexiones/DDSE.png", 0, 100);
	directionHuntedDNORTE = new Imagen(renderer, "Imagenes/Conexiones/DN.png", 0, 100);
	directionHuntedDESTE = new Imagen(renderer, "Imagenes/Conexiones/DE.png", 0, 100);
	directionHuntedDOESTE = new Imagen(renderer, "Imagenes/Conexiones/DO.png", 0, 100);
	directionHuntedDSUR = new Imagen(renderer, "Imagenes/Conexiones/DS.png", 0, 100);

	huntedCounter = new Actor(renderer, "Imagenes/cazadas/s0.png", 627, -7, Actor::BODY_OBJECT);
	notHunted = new Actor(renderer, "Imagenes/vivas/a17.png", -2, -7, Actor::BODY_OBJECT);
	fox = new Actor(renderer, "Imagenes/44.png", HEIGHT - 156, WIDTH - 133, Actor::BODY_OBJECT);
	hens = new Actor(renderer, "Imagenes/55.png", 0, HEIGHT, Actor::BODY_OBJECT);

	addActor(fox);
	addActor(hens);
}

void Stage::render() {
	wallpaper->render();

	if(isDirection) 
		renderLocationDH();

	this->action(Stage::RENDER);
	huntedCounter->render();
	notHunted->render();

	if(foxPlayer->getTypeAction() == Actor::ACTION_NULL && isMomentFox)
		restartHunted();

	if(foxPlayer->getTypeAction() == Actor::ACTION_NULL && isDelayFox) {
		isRunningFox = true;
		isDelayFox = false;
	}

	if(hens->getTypeAction() == Actor::ACTION_NULL && !isRunningFox && isDelayIA) {
		applyIA = true;
		isDelayIA = false;
	}

	if(relativeRunner)
		if(relativeRunner->getTypeAction() == Actor::ACTION_NULL) {
			relativeRunner = NULL;
			fox->addAction(Actor::ACTION_MOVE_TO, fox->getX(), HEIGHT - 156);
		    hens->addAction(Actor::ACTION_MOVE_TO, hens->getX(), HEIGHT); 
			isDelayFox = true;
		}
}

void Stage::action(int typeAction) {
	runner = headboard;
		while(runner) {
			if(typeAction == Stage::RENDER)
				runner->render();
			else
				runner->update();
			runner = runner->getActorSuccessor();
		}
}

void Stage::addActor(Actor * actor) {
	if(!headboard)
		headboard = actor;
	else {
		runner = headboard;
		while(runner->getActorSuccessor())
			runner = runner->getActorSuccessor();
		runner->setActorSuccessor(actor);
	}
}

void Stage::mouseClick(SDL_Event event) {
	if(isRunningFox)
		momentFox(event);
}

// Method that receives the event of the mouse, and assigns it to the local method 
// in charge of the treatment of the action of the fox
void Stage::mouseMotion(SDL_Event event) {
	isDirection = isKilling = false;
	foxFutureX = foxPlayer->getX();
	foxFutureY = foxPlayer->getY();

	if(isRunningFox && !isMomentFox) {
		if(isLocationMouse(Stage::LOCATION_MOUSE_OESTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_Y, event) && validateMoment((int) foxPlayer->getY() / 100, (int) (foxPlayer->getX() - 100) /100)) {
			foxFutureX = foxPlayer->getX() - 100;
			foxFutureY = foxPlayer->getY();
			typeDH = Stage::VISIBILITY_DH_OESTE;
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DOESTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_Y, event)) {
			if(validateMoment((int) foxPlayer->getY() / 100, (int) (foxPlayer->getX() - 200) /100, (int) foxPlayer->getY() / 100, (int) (foxPlayer->getX() - 100) /100)) {
			foxFutureX = foxPlayer->getX() - 200;
			foxFutureY = foxPlayer->getY();
			typeDH = Stage::VISIBILITY_DH_DOESTE;
			isDirection = isKilling = true;
			killX = foxPlayer->getX() - 100;
			killY = foxPlayer->getY();
			}
		}
		
		if(isLocationMouse(Stage::LOCATION_MOUSE_NORTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_X, event) && validateMoment((int) (foxPlayer->getY() - 100) / 100, (int) (foxPlayer->getX() /100))) {
			foxFutureX = foxPlayer->getX();
			foxFutureY = foxPlayer->getY() - 100;
			typeDH = Stage::VISIBILITY_DH_NORTE;
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DNORTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_X, event)) {
			if(validateMoment((int) (foxPlayer->getY() - 200) / 100, (int) foxPlayer->getX() /100, (int) (foxPlayer->getY() - 100) / 100, (int) foxPlayer->getX() /100)) {
			foxFutureX = foxPlayer->getX();
			foxFutureY = foxPlayer->getY() - 200;
			typeDH = Stage::VISIBILITY_DH_DNORTE;
			isDirection = isKilling = true;
			killX = foxPlayer->getX();
			killY = foxPlayer->getY() - 100;
			}
		}
		
		if(isLocationMouse(Stage::LOCATION_MOUSE_SUR, event) && isLocationMouse(Stage::LOCATION_MOUSE_X, event) && validateMoment((int) (foxPlayer->getY() + 100) / 100, (int) foxPlayer->getX() /100)) {
			foxFutureX = foxPlayer->getX();
			foxFutureY = foxPlayer->getY() + 100;
			typeDH = Stage::VISIBILITY_DH_SUR;	
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DSUR, event) && isLocationMouse(Stage::LOCATION_MOUSE_X, event)) {
			if(validateMoment((int) (foxPlayer->getY() + 200) / 100, (int) foxPlayer->getX() /100, (int) (foxPlayer->getY() + 100) / 100, (int) foxPlayer->getX() /100)) {
			foxFutureX = foxPlayer->getX();
			foxFutureY = foxPlayer->getY() + 200;
			typeDH = Stage::VISIBILITY_DH_DSUR;	
			isDirection = isKilling = true;
			killX = foxPlayer->getX();
			killY = foxPlayer->getY() + 100;
			}
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_ESTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_Y, event) && validateMoment((int) foxPlayer->getY() / 100, (int) (foxPlayer->getX() + 100) /100)) {
			foxFutureX = foxPlayer->getX() + 100;
			foxFutureY = foxPlayer->getY();
			typeDH = Stage::VISIBILITY_DH_ESTE;
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DESTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_Y, event)) {
			if(validateMoment((int) foxPlayer->getY() / 100, (int) (foxPlayer->getX() + 200) /100, (int) foxPlayer->getY() / 100, (int) (foxPlayer->getX() + 100) /100)) {
			foxFutureX = foxPlayer->getX() + 200;
			foxFutureY = foxPlayer->getY();
			typeDH = Stage::VISIBILITY_DH_DESTE;
			isDirection = isKilling = true;
			killX = foxPlayer->getX() + 100;
			killY = foxPlayer->getY();
			}
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_NORTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_OESTE, event) && validateMoment((int) (foxPlayer->getY() - 100) / 100, (int) (foxPlayer->getX() - 100) /100)) {
			foxFutureX = foxPlayer->getX() - 100;
			foxFutureY = foxPlayer->getY() - 100;
			typeDH = Stage::VISIBILITY_DH_DNO;	
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DNORTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_DOESTE, event)) {
			if(validateMoment((int) (foxPlayer->getY() - 200) / 100, (int) (foxPlayer->getX() - 200) /100, (int) (foxPlayer->getY() - 100) / 100, (int) (foxPlayer->getX() - 100) /100)) {
			foxFutureX = foxPlayer->getX() - 200;
			foxFutureY = foxPlayer->getY() - 200;
			typeDH = Stage::VISIBILITY_DH_DDNO;	
			isDirection = isKilling = true;
			killX = foxPlayer->getX() - 100;
			killY = foxPlayer->getY() - 100;
			}
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_NORTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_ESTE, event) && validateMoment((int) (foxPlayer->getY() - 100) / 100, (int) (foxPlayer->getX() + 100) /100)) {
			foxFutureX = foxPlayer->getX() + 100;
			foxFutureY = foxPlayer->getY() - 100;
			typeDH = Stage::VISIBILITY_DH_DNE;	
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DNORTE, event) && isLocationMouse(Stage::LOCATION_MOUSE_DESTE, event)) {
			if(validateMoment((int) (foxPlayer->getY() - 200) / 100, (int) (foxPlayer->getX() + 200) /100, (int) (foxPlayer->getY() - 100) / 100, (int) (foxPlayer->getX() + 100) /100)) {
			foxFutureX = foxPlayer->getX() + 200;
			foxFutureY = foxPlayer->getY() - 200;
			typeDH = Stage::VISIBILITY_DH_DDNE;	
			isDirection = isKilling = true;
			killX = foxPlayer->getX() + 100;
			killY = foxPlayer->getY() - 100;
			}
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_SUR, event) && isLocationMouse(Stage::LOCATION_MOUSE_OESTE, event) && validateMoment((int) (foxPlayer->getY() + 100) / 100, (int) (foxPlayer->getX() - 100) /100)) {
			foxFutureX = foxPlayer->getX() - 100;
			foxFutureY = foxPlayer->getY() + 100;
			typeDH = Stage::VISIBILITY_DH_DSO;	
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DSUR, event) && isLocationMouse(Stage::LOCATION_MOUSE_DOESTE, event)) {
			if(validateMoment((int) (foxPlayer->getY() + 200) / 100, (int) (foxPlayer->getX() - 200) /100, (int) (foxPlayer->getY() + 100) / 100, (int) (foxPlayer->getX() - 100) /100)) {
			foxFutureX = foxPlayer->getX() - 200;
			foxFutureY = foxPlayer->getY() + 200;
			typeDH = Stage::VISIBILITY_DH_DDSO;	
			isDirection = isKilling = true;
			killX = foxPlayer->getX() - 100;
			killY = foxPlayer->getY() + 100;
			}
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_SUR, event) && isLocationMouse(Stage::LOCATION_MOUSE_ESTE, event) && validateMoment((int) (foxPlayer->getY() + 100) / 100, (int) (foxPlayer->getX() + 100) /100)) {
			foxFutureX = foxPlayer->getX() + 100;
			foxFutureY = foxPlayer->getY() + 100;
			typeDH = Stage::VISIBILITY_DH_DSE;
			isDirection = true;
		}

		if(isLocationMouse(Stage::LOCATION_MOUSE_DSUR, event) && isLocationMouse(Stage::LOCATION_MOUSE_DESTE, event)) {
			if(validateMoment((int) (foxPlayer->getY() + 200) / 100, (int) (foxPlayer->getX() + 200) /100, (int) (foxPlayer->getY() + 100) / 100, (int) (foxPlayer->getX() + 100) /100)) {
			foxFutureX = foxPlayer->getX() + 200;
			foxFutureY = foxPlayer->getY() + 200;
			typeDH = Stage::VISIBILITY_DH_DDSE;
			isDirection = isKilling = true;
			killX = foxPlayer->getX() + 100;
			killY = foxPlayer->getY() + 100;
			}
		}
		
	}
}

void Stage::momentFox(SDL_Event event) {
	if(isDirection) {
		data[foxPlayer->getY()/100][foxPlayer->getX()/100] = 0;
		data[foxFutureY/100][foxFutureX/100] = 2;
		foxPlayer->addAction(Actor::ACTION_MOVE_TO, foxFutureX, foxFutureY);
		isMomentFox = true;
		
		if(isKilling) {
		//	isKiller = true;
			data[killY/100][killX/100] = 0;
		    runner = headboard;
			Actor * father = runner;
		    while(runner) {
				if(runner->getX() == killX && runner->getY() == killY) {
					Actor * deleteActor = runner;
					if(runner == headboard && runner->getActorSuccessor())
						headboard = runner->getActorSuccessor();
					else {
						if(runner->getActorSuccessor())
							father->setActorSuccessor(runner->getActorSuccessor());
					}
					delete deleteActor;
					runner = NULL;
			    } else {
					father = runner;
					runner = runner->getActorSuccessor();
				}
		    }
		}
	}
}

void Stage::renderLocationDH() {
	switch (typeDH)
		{
	case Stage::VISIBILITY_DH_NORTE:
		directionHuntedN->render();
		break;
	case Stage::VISIBILITY_DH_SUR:
		directionHuntedS->render();
		break;
	case Stage::VISIBILITY_DH_ESTE:
		directionHuntedE->render();
		break;
	case Stage::VISIBILITY_DH_OESTE:
		directionHuntedO->render();
		break;
	case Stage::VISIBILITY_DH_DNO:
		directionHuntedDNO->render();
		break;
	case Stage::VISIBILITY_DH_DNE:
		directionHuntedDNE->render();
		break;
	case Stage::VISIBILITY_DH_DSO:
		directionHuntedDSO->render();
		break;
	case Stage::VISIBILITY_DH_DSE:
		directionHuntedDSE->render();
		break;
	case Stage::VISIBILITY_DH_DDNO:
		directionHuntedDDNO->render();
		break;
	case Stage::VISIBILITY_DH_DDNE:
		directionHuntedDDNE->render();
		break;
	case Stage::VISIBILITY_DH_DDSO:
		directionHuntedDDSO->render();
		break;
	case Stage::VISIBILITY_DH_DDSE:
		directionHuntedDDSE->render();
		break;
	case Stage::VISIBILITY_DH_DNORTE:
		directionHuntedDNORTE->render();
		break;
	case Stage::VISIBILITY_DH_DESTE:
		directionHuntedDESTE->render();
		break;
	case Stage::VISIBILITY_DH_DOESTE:
		directionHuntedDOESTE->render();
		break;
	case Stage::VISIBILITY_DH_DSUR:
		directionHuntedDSUR->render();
		break;
	default:
		break;
		}
}

void Stage::asignData(int ** data) {
	this->data = data;
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		for(int j=0; j<GameModel::LENGTH_MATRIZ; j++)
			if(data[i][j] == 1)
				addActor(new Actor(renderer, "Imagenes/Personajes/gallina.png", j * 100, i * 100, Actor::BODY_HEN));
			else
				if(data[i][j] == 2) {
					foxFutureX = j * 100;
	                foxFutureY = i * 100;
				}

	foxPlayer = new Actor(renderer, "Imagenes/Personajes/zorro.png", foxFutureX, foxFutureY, Actor::BODY_FOX);
	addActor(foxPlayer);
}

void Stage::restartHunted() {
	directionHuntedN->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedS->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
    directionHuntedO->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDNO->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDNE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDSO->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDSE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDDNO->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDDNE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDDSO->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDDSE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDNORTE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDESTE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDOESTE->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);
	directionHuntedDSUR->setXY(foxPlayer->getX() - 300, foxPlayer->getY() - 300);

	if(isKiller)
		isRunningFox = true;
	else {
		fox->addAction(Actor::ACTION_MOVE_TO, fox->getX(), HEIGHT);
		hens->addAction(Actor::ACTION_MOVE_TO, hens->getX(), HEIGHT - 140);    ///// AQUI PORFA COLOCAR EN ACTOR EL WIDTH HEIGHT   ODPSAJDPASJDOSAFDJOAFOSDFHSODFHODSHFDSFHIUSDFHISDUF
		isRunningFox = false;
		isDelayIA = true;
	}
		
	isDirection = isMomentFox = isKiller = false;
}

void Stage::insertDataIA(int i0, int j0, int i1, int j1) {
	runner = headboard;
    while(runner) {
		if(runner->getX() == (j0 * 100) && runner->getY() == (i0 * 100)) {
			runner->addAction(Actor::ACTION_MOVE_TO, j1*100, i1*100);
			relativeRunner = runner;
			runner = NULL;
		} else
			runner = runner->getActorSuccessor();
    }

	applyIA = false;
}

bool Stage::isLocationMouse(int typeLocationMouse, SDL_Event event) {
	
	if(typeLocationMouse == Stage::LOCATION_MOUSE_X && event.motion.x >= foxPlayer->getX() && event.motion.x <= foxPlayer->getX() + 100)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_Y && event.motion.y >= foxPlayer->getY() && event.motion.y <= foxPlayer->getY() + 100)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_NORTE && event.motion.y <= foxPlayer->getY() && event.motion.y >= foxPlayer->getY() - 100)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_DNORTE && event.motion.y <= foxPlayer->getY() - 100 && event.motion.y >= foxPlayer->getY() - 200)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_SUR && event.motion.y <= foxPlayer->getY() + 200 && event.motion.y >= foxPlayer->getY() + 100)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_DSUR && event.motion.y <= foxPlayer->getY() + 300 && event.motion.y >= foxPlayer->getY() + 200)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_ESTE && event.motion.x >= foxPlayer->getX() + 100 && event.motion.x <= foxPlayer->getX() + 200)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_DESTE && event.motion.x >= foxPlayer->getX() + 200 && event.motion.x <= foxPlayer->getX() + 300)
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_OESTE && event.motion.x >= foxPlayer->getX() - 100 && event.motion.x <= foxPlayer->getX())
		return true;

	if(typeLocationMouse == Stage::LOCATION_MOUSE_DOESTE && event.motion.x >= foxPlayer->getX() - 200 && event.motion.x <= foxPlayer->getX() - 100)
		return true;

	return false;
}

bool Stage::validateMoment(int i, int j) {
	if(data[i][j] == 0)
		return true;
	else
		return false;
}

bool Stage::validateMoment(int i, int j, int iPre, int jPre) {
	if(data[i][j] == 0 && data[iPre][jPre] == 1)
		return true;
	else
		return false;
}

bool Stage::IsApplyIA() {
	return applyIA;
}
