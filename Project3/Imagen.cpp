#include "Imagen.h"

Imagen::Imagen(void) {
}

Imagen::~Imagen(void) {
	SDL_DestroyTexture(texture);
}

Imagen::Imagen(SDL_Renderer * renderer, const char * route, int x, int y) {
    texture = IMG_LoadTexture(renderer, route);
	this->renderer = renderer;
	position.x = x;
	position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void Imagen::render() {
	SDL_RenderCopy(renderer, texture, NULL, &position);
}

void Imagen::recharge(const char * route) {
    SDL_Texture * forDelete;
	forDelete = texture;
	texture = IMG_LoadTexture(renderer, route);
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_DestroyTexture(forDelete);
}

void Imagen::setXY(int X, int Y) {
	position.x = X;
	position.y = Y;
}

bool Imagen::moveTo(int X, int Y) {
	if(position.x < X)
		position.x = position.x + 1;
	else
		if(position.x > X)
			position.x = position.x - 1;

	if(position.y < Y)
		position.y = position.y + 1;
	else
		if(position.y > Y)
			position.y = position.y - 1;

	if(position.x == X && position.y == Y)
		return true;
	else
		return false;
}

int Imagen::getX() {
	return position.x;
}

int Imagen::getY() {
	return position.y;
}
