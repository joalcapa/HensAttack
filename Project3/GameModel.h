#include "MiniMaxPAB.h"

#pragma once
class GameModel {
private:
	int ** data;
	MiniMaxPAB * miniMaxPAB;
public:
	static const int LENGTH_MATRIZ = 7;
	static const int LENGTH_PLAYER_COLLECTIVE = 17;

	GameModel(void);
	~GameModel(void);

	void initData();
	void applyIA();

	int ** getData();
	int getI0();
	int getJ0();
	int getI1();
	int getJ1();
};
