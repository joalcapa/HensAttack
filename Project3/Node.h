#pragma once
class Node {
private:
	Node * headNode;
	Node * sucNode;
	Node * runner;

	int ** data;
	int valueHeuristic;
public:
	Node(void);
	Node(int ** data);
	~Node(void);

	void addNode(Node * node);
	void setValueHeuristic(int valueHeuristic);
	void setSucNode(Node * sucNode);
	void setHeadNode(Node * headNode);
	int getValueHeuristic();
	int ** getData();
	Node * getSucNode();
	Node * getHeadNode();
};
