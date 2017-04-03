#include "SDL2-2.0.3\include\SDL_image.h"

#pragma once
class Imagen {
private:
	SDL_Rect  position;
	SDL_Renderer * renderer;
	SDL_Texture * texture;

public:
	Imagen(SDL_Renderer * renderer, const char * route, int x, int y);
	Imagen(void);
	~Imagen(void);

	void render();
	void recharge(const char * route);
	void setXY(int X, int Y);

	bool moveTo(int X, int Y);
	int getX();
	int getY();
};
