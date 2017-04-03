#include "Node.h"
#include <stddef.h>

Node::Node(void) {}

Node::Node(int ** data) {
	this->data = data;
	headNode = NULL;
	sucNode = NULL;
}

Node::~Node(void) {}

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
