#include "MiniMaxPAB.h"
#include "GameModel.h"
#include <stdio.h>
#include <stdlib.h>

MiniMaxPAB::MiniMaxPAB() {}

MiniMaxPAB::MiniMaxPAB(int ** data, int numberPlayerCollective, int numberPlayerSingle, int profundity) {
	this->data = data;
	this->numbrePlayerCollective = numberPlayerCollective;
	this->numberPlayerSingle = numberPlayerSingle;
	this->profundity = profundity;
	node = new Node(data);
}

MiniMaxPAB::~MiniMaxPAB(void) {}

void MiniMaxPAB::applyIA() {
	node->setValueHeuristic(alphaBeta(node, data, 1, MiniMaxPAB::INFINITY_LESS, MiniMaxPAB::INFINITY_MORE, MiniMaxPAB::MODE_MAX));
	searchNode();
	deleteNodes(node);
	node->setHeadNode(NULL);
}

void MiniMaxPAB::searchNode() {
	Node * nodeAux = node->getHeadNode();
	int co = 0;
	while(nodeAux) {
		if(nodeAux->getValueHeuristic() == node->getValueHeuristic()) {
			for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
				for(int j=0; j<GameModel::LENGTH_MATRIZ; j++) {
					if(nodeAux->getData()[i][j] != node->getData()[i][j]) {
						if(nodeAux->getData()[i][j] == 0) {
							i0 = i;
							j0 = j;
							co++;
						} 
						if(nodeAux->getData()[i][j] == 1) {
							i1 = i;
							j1 = j;
							co++;
						}
					}
					node->getData()[i][j] = nodeAux->getData()[i][j];
				}	

				nodeAux = NULL;
		} else 
			nodeAux = nodeAux->getSucNode();
	}

	if(co > 2) {
		node->getData()[-2][0] = 2;
	}
}

Node * MiniMaxPAB::deleteNodes(Node * node) {
	Node * runner = node->getHeadNode();
	Node * deleteNode;

		while(runner) {
			deleteNode = deleteNodes(runner);
			runner = runner->getSucNode();
			delete (*deleteNode->getData());
			delete deleteNode->getData();
			delete deleteNode;
		}
		return node;
}

int MiniMaxPAB::alphaBeta(Node * nodeAB, int ** dataAB, int profundity, int alpha, int beta, int modePlayer) {
	bool running = true;
if(this->profundity == profundity || isBoardEmpty(dataAB))
		return heuristic(dataAB);
	if(modePlayer == MiniMaxPAB::MODE_MAX) {
		for(int i=0; i<GameModel::LENGTH_MATRIZ && running; i++)
			for(int j=0; j<GameModel::LENGTH_MATRIZ && running; j++) {
				if(dataAB[i][j] == 1) {
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_LEFT)) {
						int ** newData = returnNewData(dataAB, i, j, i-1, j, 1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						alpha = MinMax(alpha, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MIN), MiniMaxPAB::SEARCH_MAX);
						myNode->setValueHeuristic(alpha);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_RIGHT)) {
						int ** newData = returnNewData(dataAB, i, j, i+1, j, 1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						alpha = MinMax(alpha, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MIN), MiniMaxPAB::SEARCH_MAX);
						myNode->setValueHeuristic(alpha);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_SOUTH)) {
						int ** newData = returnNewData(dataAB, i, j, i, j+1, 1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						alpha = MinMax(alpha, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MIN), MiniMaxPAB::SEARCH_MAX);
						myNode->setValueHeuristic(alpha);
				        if(beta <= alpha)
							running = false;
					}
				}
			}
		return alpha;
	} else {
		for(int i=0; i<GameModel::LENGTH_MATRIZ && running; i++)
			for(int j=0; j<GameModel::LENGTH_MATRIZ && running; j++) {
				if(dataAB [i][j] == 2) {
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_LEFT)) {
						int ** newData = returnNewData(dataAB, i, j, i-1, j, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_RIGHT)) {
						int ** newData = returnNewData(dataAB, i, j, i+1, j, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_SOUTH)) {
						int ** newData = returnNewData(dataAB, i, j, i, j+1, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_NORTH)) {
						int ** newData = returnNewData(dataAB, i, j, i-1, j, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DNL)) {
						int ** newData = returnNewData(dataAB, i, j, i+1, j-1, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DNR)) {
						int ** newData = returnNewData(dataAB, i, j, i-1, j-1, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DSL)) {
						int ** newData = returnNewData(dataAB, i, j, i+1, j+1, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DSR)) {
						int ** newData = returnNewData(dataAB, i, j, i-1, j+1, 2);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDN)) {
						int ** newData = returnNewData(dataAB, i, j, i, j-2, 2, i, j-1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDS)) {
						int ** newData = returnNewData(dataAB, i, j, i, j+2, 2, i, j+1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDL)) {
						int ** newData = returnNewData(dataAB, i, j, i-2, j, 2, i-1, j);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDR)) {
						int ** newData = returnNewData(dataAB, i, j, i+2, j, 2, i+1, j);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDNL)) {
						int ** newData = returnNewData(dataAB, i, j, i-2, j-2, 2, i-1, j-1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDNR)) {
						int ** newData = returnNewData(dataAB, i, j, i+2, j-2, 2, i+1, j-1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDSL)) {
						int ** newData = returnNewData(dataAB, i, j, i-2, j+2, 2, i-1, j+1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
					if(isValidMovement(dataAB, i, j, MiniMaxPAB::MOVEMENT_DDSR)) {
						int ** newData = returnNewData(dataAB, i, j, i+2, j+2, 2, i+1, j+1);
						Node * myNode = new Node(newData);
						nodeAB->addNode(myNode);
						beta = MinMax(beta, alphaBeta(myNode, newData, profundity+1, alpha, beta, MiniMaxPAB::MODE_MAX), MiniMaxPAB::SEARCH_MIN);
						myNode->setValueHeuristic(beta);
				        if(beta <= alpha)
							running = false;
					}
				}
				/*
				beta = MinMax(beta, alphaBeta(data, profundity + 1, alpha, beta, modePlayer), MiniMaxPAB::SEARCH_MIN);
				if(beta <= alpha)
					break;
					*/
			}
			return beta;
	}
}

int MiniMaxPAB::heuristic(int ** dataAux) {
	int lenghtPlayerCollective = 0, valueHeuristic = 0;
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		for(int j=0; j<GameModel::LENGTH_MATRIZ; j++)
			if(dataAux[i][j] == 1)
				lenghtPlayerCollective++;

	valueHeuristic = valueHeuristic - (GameModel::LENGTH_PLAYER_COLLECTIVE - lenghtPlayerCollective);

	//   POSIBLES MOVIMIENTOS DEL ZORRO
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
			for(int j=0; j<GameModel::LENGTH_MATRIZ; j++) {
				if(dataAux [i][j] == 2) {
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_LEFT)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_RIGHT)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_SOUTH)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_NORTH)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DNL)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DNR)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DSL)) 
						valueHeuristic++;
						
					
					if(!isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DSR)) 
						valueHeuristic++;
					
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDN)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;
					
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDS)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;
						
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDL)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;	
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDR)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDNL)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDNR)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;
					
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDSL)) 
						valueHeuristic = valueHeuristic - 2;
					else
						valueHeuristic++;
						
					if(isValidMovement(data, i, j, MiniMaxPAB::MOVEMENT_DDSR)) 
						valueHeuristic = valueHeuristic - 2;	
					else
						valueHeuristic++;
				}
				/*
				beta = MinMax(beta, alphaBeta(data, profundity + 1, alpha, beta, modePlayer), MiniMaxPAB::SEARCH_MIN);
				if(beta <= alpha)
					break;
					*/
			}

	return valueHeuristic;
}

int MiniMaxPAB::MinMax(int a, int b, int modeOperation) {
	if(modeOperation == MiniMaxPAB::SEARCH_MAX) 
		if(a >= b)
			return a;
		else
			return b;
	else
		if(a <= b)
			return a;
		else
			return b;
}

int MiniMaxPAB::getI0() {
	return i0;
}

int MiniMaxPAB::getJ0(){
	return j0;
}

int MiniMaxPAB::getI1(){
	return i1;
}

int MiniMaxPAB::getJ1(){
	return j1;
}

bool MiniMaxPAB::isBoardEmpty(int ** dataAux) {
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		for(int j=0; j<GameModel::LENGTH_MATRIZ; j++)
			if(dataAux[i][j] == 1)
				return false;

	return true;
}

bool MiniMaxPAB::isValidMovement(int ** auxData, int i, int j, int typeMovement) {
	switch (typeMovement) {
	case MiniMaxPAB::MOVEMENT_LEFT:
		if(i-1 >= 0)
			if(auxData [i-1][j] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_RIGHT:
		if(i+1 < GameModel::LENGTH_MATRIZ)
			if(auxData [i+1][j] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_SOUTH:
		if(j+1 < GameModel::LENGTH_MATRIZ)
			if(auxData [i][j+1] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_NORTH:
		if(i-1 >= 0)
			if(auxData [i-1][j] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DNL:
		if(i+1 < GameModel::LENGTH_MATRIZ && j-1 >= 0)
			if(auxData [i+1][j-1] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DNR:
		if(i-1 >= 0 && j-1 >= 0)
			if(auxData [i-1][j-1] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DSL:
		if(i+1 < GameModel::LENGTH_MATRIZ && j+1 < GameModel::LENGTH_MATRIZ)
			if(auxData [i+1][j+1] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DSR:
		if(i-1 >= 0 && j+1 < GameModel::LENGTH_MATRIZ)
			if(auxData [i-1][j+1] == 0)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDN:
		if(j-2 >= 0)
			if(auxData [i][j-2] == 0 && auxData [i][j-1] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDL:
		if(i-2 >= 0)
			if(auxData [i-2][j] == 0 && auxData [i-1][j] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDR:
		if(i+2 < GameModel::LENGTH_MATRIZ)
			if(auxData [i+2][j] == 0 && auxData [i+1][j] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDS:
		if(j+2 < GameModel::LENGTH_MATRIZ)
			if(auxData [i][j+2] == 0 && auxData [i][j+1] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDNL:
		if(j-2 >= 0 && i-2 >= 0)
			if(auxData [i-2][j-2] == 0 && auxData [i-1][j-1] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDNR:
		if(j-2 >= 0 && i+2 < GameModel::LENGTH_MATRIZ)
			if(auxData [i+2][j-2] == 0 && auxData [i+1][j-1] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDSL:
		if(j+2 < GameModel::LENGTH_MATRIZ && i-2 >= 0)
			if(auxData [i-2][j+2] == 0 && auxData [i-1][j+1] == 1)
				return true;
		break;
	case MiniMaxPAB::MOVEMENT_DDSR:
		if(j+2 < GameModel::LENGTH_MATRIZ && i+2 < GameModel::LENGTH_MATRIZ)
			if(auxData [i+2][j+2] == 0 && auxData [i+1][j+1] == 1)
				return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

int ** MiniMaxPAB::returnNewData(int ** dataAux, int posI, int posJ, int posW, int posH, int value) {
	int ** auxData = (int**) malloc(sizeof(int*) * GameModel::LENGTH_MATRIZ);
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		auxData[i] = (int *) malloc(sizeof(int) * GameModel::LENGTH_MATRIZ);

	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		for(int j=0; j<GameModel::LENGTH_MATRIZ; j++)
			auxData[i][j] = dataAux[i][j];

	auxData[posI][posJ] = 0;
	auxData[posW][posH] = value;

	return auxData;
}

int ** MiniMaxPAB::returnNewData(int ** dataAux, int posI, int posJ, int posW, int posH, int value, int i2, int j2) {
	int ** auxData = (int**) malloc(sizeof(int*) * GameModel::LENGTH_MATRIZ);
	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		auxData[i] = (int *) malloc(sizeof(int) * GameModel::LENGTH_MATRIZ);

	for(int i=0; i<GameModel::LENGTH_MATRIZ; i++)
		for(int j=0; j<GameModel::LENGTH_MATRIZ; j++)
			auxData[i][j] = dataAux[i][j];

	auxData[posI][posJ] = 0;
	auxData[i2][j2] = 0;
	auxData[posW][posH] = value;

	return auxData;
}
