#include "Actor.h"

#pragma once
class Stage {
private:
	SDL_Renderer * renderer;

	Actor * headboard;
	Actor * runner;
	Actor * huntedCounter;
	Actor * notHunted;
	Actor * fox;
	Actor * hens;
	Actor * foxPlayer;
	Actor * relativeRunner;

	Imagen * wallpaper;
	Imagen * directionHuntedN;
	Imagen * directionHuntedS;
	Imagen * directionHuntedE;
	Imagen * directionHuntedO;
	Imagen * directionHuntedDNO;
	Imagen * directionHuntedDNE;
	Imagen * directionHuntedDSO;
	Imagen * directionHuntedDSE;
	Imagen * directionHuntedDDNO;
	Imagen * directionHuntedDDNE;
	Imagen * directionHuntedDDSO;
	Imagen * directionHuntedDDSE;
	Imagen * directionHuntedDNORTE;
	Imagen * directionHuntedDESTE;
	Imagen * directionHuntedDSUR;
	Imagen * directionHuntedDOESTE;
	
	int WIDTH;
	int HEIGHT;
	int typeDH;
	int foxFutureX;
	int foxFutureY;
	int killX;
	int killY;
	int ** data;
	bool isRunningFox;
	bool isDirection;
	bool isMomentFox;
	bool isKilling;
	bool isKiller;
	bool applyIA;
	bool isDelayIA;
	bool isDelayFox;

public:
	const static int RENDER = 0;
	const static int UPDATE = 1;

	const static int LOCATION_MOUSE_NORTE = 10;
	const static int LOCATION_MOUSE_SUR = 11;
	const static int LOCATION_MOUSE_ESTE = 12;
	const static int LOCATION_MOUSE_OESTE = 13;
	const static int LOCATION_MOUSE_DNORTE = 14;
	const static int LOCATION_MOUSE_DSUR = 15;
	const static int LOCATION_MOUSE_DESTE = 16;
	const static int LOCATION_MOUSE_DOESTE = 17;
	const static int LOCATION_MOUSE_X = 18;
	const static int LOCATION_MOUSE_Y = 19;

	const static int VISIBILITY_DH_NORTE = 20;
	const static int VISIBILITY_DH_SUR = 21;
	const static int VISIBILITY_DH_ESTE = 22;
	const static int VISIBILITY_DH_OESTE = 23;
	const static int VISIBILITY_DH_DNO = 24;
	const static int VISIBILITY_DH_DNE = 25;
	const static int VISIBILITY_DH_DSO = 26;
	const static int VISIBILITY_DH_DSE = 27;
	const static int VISIBILITY_DH_DDNO = 28;
	const static int VISIBILITY_DH_DDNE = 29;
	const static int VISIBILITY_DH_DDSO = 30;
	const static int VISIBILITY_DH_DDSE = 31;
	const static int VISIBILITY_DH_DNORTE = 32;
	const static int VISIBILITY_DH_DESTE = 33;
	const static int VISIBILITY_DH_DSUR = 34;
	const static int VISIBILITY_DH_DOESTE = 35;

	Stage(void);
	~Stage(void);
	Stage(SDL_Renderer * renderer, int WIDTH, int HEIGHT);
	
	void render();
	void action(int typeAction);
	void addActor(Actor * actor);
	void mouseClick(SDL_Event event);
	void mouseMotion(SDL_Event event);
	void momentFox(SDL_Event event);
	void renderLocationDH();
	void asignData(int ** data);
	void restartHunted();
	void insertDataIA(int i0, int j0, int i1, int j1);

	bool isLocationMouse(int typeLocationMouse, SDL_Event event);
	bool validateMoment(int i, int j);
	bool validateMoment(int i, int j, int iPre, int jPre);
	bool IsApplyIA();
};
