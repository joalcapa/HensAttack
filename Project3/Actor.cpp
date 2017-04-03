#include "Actor.h"

Actor::Actor(void) {}

Actor::~Actor(void) {}

Actor::Actor(SDL_Renderer * renderer, const char * route, int x, int y, int typeBody) {
	image = new Imagen(renderer, route, x, y);
	actorSuccessor = NULL;
	isRendering = true;
	typeAction = Actor::ACTION_NULL;
	this->typeBody = typeBody;
}

void Actor::setActorSuccessor(Actor * actorSuccessor) {
	this->actorSuccessor = actorSuccessor;
}

void Actor::update() {
	if(typeAction != Actor::ACTION_NULL)
			if(image->moveTo(X, Y))
				typeAction = Actor::ACTION_NULL;
}

void Actor::render() {
	if(isRendering)
		image->render();
}

void Actor::addAction(int typeAction, int x, int y) {
	this->typeAction = typeAction;
	X = x;
	Y = y;
}

void Actor::addAction(int typeAction, char * route) {
	this->typeAction = typeAction;
	this->route = route;
}

void Actor::setIsRendering(bool isRendering) {
	this->isRendering = isRendering;
}

Actor * Actor::getActorSuccessor() {
	return actorSuccessor;
}

int Actor::getX() {
	return image->getX();
}

int Actor::getY() {
	return image->getY();
}

int Actor::getTypeAction() {
	return typeAction;
}
