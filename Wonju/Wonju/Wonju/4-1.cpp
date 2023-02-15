#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Node {
private:
	int value;
	Node* next;
	Node* prev;

public:
	Node() {
		this->value = 0;
		this->next = NULL;
		this->prev = NULL;
	}
	void setValue(int data) { this->value = data; }
	int getValue() { return this->value; }
	void setNext(Node* nextNode) { this->next = nextNode; }
	Node* getNext() { return this->next; }
	void setPrev(Node* prevNode) { this->prev = prevNode; }
	Node* getPrev() { return this->prev; }
};
class Tree {
private:
	int size;
	Node* root;

public:
	void INSERT(Node* curNode, int integer);
	void DELETE();
	void PRINT();
};
void Tree::INSERT(Node* curNode, int integer) {
	if (root == NULL)
	{
		Node* newNode = new Node;
		newNode->setValue(integer);
	}
}