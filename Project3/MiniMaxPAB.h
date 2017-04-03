#include "Node.h"

#pragma once
class MiniMaxPAB {
private:
	Node * node;

	int ** data;
	int numbrePlayerCollective;
	int numberPlayerSingle;
	int profundity;
	int i0;
	int i1;
	int j0;
	int j1;

public:
	static const int INFINITY_LESS = -999999;
	static const int INFINITY_MORE = 999999;

	static const int MODE_MIN = 0;
	static const int MODE_MAX = 1;

	static const int SEARCH_MIN = 2;
	static const int SEARCH_MAX = 3;

	static const int MOVEMENT_LEFT = 4;
	static const int MOVEMENT_RIGHT = 5;
	static const int MOVEMENT_SOUTH = 6;
	static const int MOVEMENT_NORTH = 7;
	static const int MOVEMENT_DNL = 8;
	static const int MOVEMENT_DNR = 9;
	static const int MOVEMENT_DSL = 10;
	static const int MOVEMENT_DSR = 11;
	static const int MOVEMENT_DDN = 12;
	static const int MOVEMENT_DDS = 13;
	static const int MOVEMENT_DDL = 14;
	static const int MOVEMENT_DDR = 15;
	static const int MOVEMENT_DDNL = 16;
	static const int MOVEMENT_DDNR = 17;
	static const int MOVEMENT_DDSL = 18;
	static const int MOVEMENT_DDSR = 19;

	MiniMaxPAB(void);
	MiniMaxPAB(int ** data, int numberPlayerCollective, int numberPlayerSingle, int profundity);
	~MiniMaxPAB(void);

	void applyIA();
	void searchNode();
	Node * deleteNodes(Node * node);

	int alphaBeta(Node * node, int ** data, int profundity, int alpha, int beta, int modePlayer);
	int heuristic(int ** data);
	int MinMax(int a, int b, int modeOperation);
	int ** returnNewData(int ** data, int posI, int posJ, int posW, int posH, int value);
	int ** returnNewData(int ** data, int posI, int posJ, int posW, int posH, int value, int i2, int j2);
	int getI0();
	int getJ0();
	int getI1();
	int getJ1();
	bool isBoardEmpty(int ** data);
	bool isValidMovement(int ** data, int i, int j, int typeMovement);
};
