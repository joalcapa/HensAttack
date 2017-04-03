#include "GameModel.h"
#include <stdio.h>
#include <stdlib.h>

GameModel::GameModel(void) {
	data = (int**) malloc(sizeof(int*) * GameModel::LENGTH_MATRIZ);
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		data[i] = (int *) malloc(sizeof(int) * GameModel::LENGTH_MATRIZ);
	initData();
}

GameModel::~GameModel(void) {}

void GameModel::initData() {
	data[0][0] = -1; data[0][1] = -1; data[0][2] = 1; data[0][3] = 1; data[0][4] = 1; data[0][5] = -1; data[0][6] = -1;
	data[1][0] = -1; data[1][1] = -1; data[1][2] = 1; data[1][3] = 1; data[1][4] = 1; data[1][5] = -1; data[1][6] = -1;
	data[2][0] = 1; data[2][1] = 1; data[2][2] = 1; data[2][3] = 1; data[2][4] = 1; data[2][5] = 1; data[2][6] = 1;
	data[3][0] = 1; data[3][1] = 0; data[3][2] = 0; data[3][3] = 0; data[3][4] = 0; data[3][5] = 0; data[3][6] = 1;
	data[4][0] = 1; data[4][1] = 0; data[4][2] = 0; data[4][3] = 2; data[4][4] = 0; data[4][5] = 0; data[4][6] = 1;
	data[5][0] = -1; data[5][1] = -1; data[5][2] = 0; data[5][3] = 0; data[5][4] = 0; data[5][5] = -1; data[5][6] = -1;
	data[6][0] = -1; data[6][1] = -1; data[6][2] = 0; data[6][3] = 0; data[6][4] = 0; data[6][5] = -1; data[6][6] = -1;

	miniMaxPAB = new MiniMaxPAB(data, 1, 2, 8);
}

void GameModel::applyIA() {
	miniMaxPAB->applyIA();
}

int ** GameModel::getData() {
	return data;
}

int GameModel::getI0() {
	return miniMaxPAB->getI0();
}

int GameModel::getJ0(){
	return miniMaxPAB->getJ0();
}

int GameModel::getI1(){
	return miniMaxPAB->getI1();
}

int GameModel::getJ1(){
	return miniMaxPAB->getJ1();
}
