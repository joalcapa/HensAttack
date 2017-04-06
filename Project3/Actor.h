#include "Imagen.h"

#pragma once
class Actor {
private:
	Imagen * image;
	Actor * actorSuccessor;
	int typeAction;
	int typeBody;
	int X;
	int Y;
	char * route;
	bool isRendering;

public:
	//Types of action that an actor can perform
	const static int ACTION_NULL = 0;
	const static int ACTION_MOVE_TO = 1;
	const static int BODY_FOX = 8;
	const static int BODY_HEN = 9;
	const static int BODY_OBJECT = 10;

	Actor(void);
	~Actor(void);
	Actor(SDL_Renderer * renderer, const char * ruta, int x, int y, int typeBody);
	
	void setActorSuccessor(Actor * actorSuccessor);
	void update();
	void render();
	void addAction(int typeAction, int x, int y);
	void addAction(int typeAction, char * route);
	void setIsRendering(bool isRendering);

	Actor * getActorSuccessor();
	int getX();
	int getY();
	int getTypeAction();
};
