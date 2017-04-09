#include "Node.h"
#include <stddef.h>

Node::Node(void) {}

Node::Node(int ** data) {
	this->data = data;
	headNode = NULL;
	sucNode = NULL;
}

Node::~Node(void) {}

// Algorithm that assigns the successor actor
// for the implementation of the data structure of the scenario
void Node::addNode(Node * node) {
	if(!headNode)
		headNode = node;
	else {
		runner = headNode;
		while(runner->getSucNode())
			runner = runner->getSucNode();

		runner->setSucNode(node);
	}
}

void Node::setValueHeuristic(int valueHeuristic) {
	this->valueHeuristic = valueHeuristic;
}

void Node::setSucNode(Node * sucNode) {
	this->sucNode = sucNode;
}

void Node::setHeadNode(Node * headNode) {
	this->headNode = headNode;
}

int Node::getValueHeuristic() {
	return valueHeuristic;
}

int ** Node::getData() {
	return data;
}

Node * Node::getSucNode() {
	return sucNode;
}

Node * Node::getHeadNode() {
	return headNode;
}
