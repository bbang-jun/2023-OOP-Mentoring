#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Node {
private:
	char word[30];
	Node* Left;
	Node* Right;
	Node* parent; 
public:
	Node() {

		this->Left = NULL;
		this->Right = NULL;
		this->parent = NULL;
	}
	void setword(char* word) { strcpy(this->word,word); }
	char* getword() { return this->word; }

	void setLeft(Node* Left) { this->Left = Left;}
	Node* getLeft() { return this-> Left; }

	void setRight(Node* Right) { this->Right = Right; }
	Node* getRight() { return this->Right; }

	void setparent(Node* parent) { this->parent = parent; }
	Node* getparent() { return this->parent; }
};
class Tree {
private:
	Node* curNode;
	Node* root;
	Node* delNode;
	int size;
public:
	Tree() {
		size = 0;
		curNode = NULL;
		root = NULL;
		delNode = NULL;
	}
	~Tree() {
		deallocate(root);
	}
	Node* getroot() { return this->root; }
	void deallocate(Node* root);
	void INSERT(Node* curNode, char* word);
	void FIND(Node* curNode, char* word);
	void DELETE(Node* curNode, char* word);
	void PRINTPRE(Node* curNode);
	void PRINTPOST(Node* curNode);
	void PRINTIN(Node* curNode);
};
void Tree::INSERT(Node* curNode, char* word) {
	if (root = NULL) {
		Node* newNode = new Node;
		newNode->setword(word);
		root = newNode;
		curNode = root;
		this->size++;
	}
	else if(strcmp(curNode->getLeft(),curNode->getword()))
	{
		
	}
}
void PRINTPRE(Node* curNode) {
	cout << curNode->getword() << endl;;
	PRINTPRE(curNode->getLeft());
	PRINTPRE(curNode->getRight());
};
void PRINTPOST(Node* curNode) {
	PRINTPOST(curNode->getLeft());
	cout << curNode->getword() << endl;
	PRINTPOST(curNode->getRight());
}
void PRINTIN(Node* curNode) {
	PRINTIN(curNode->getLeft());
	PRINTIN(curNode->getRight());
	cout << curNode->getword() << endl;
}
int main(void) {
	char command[30] = { 0 };
	cin >> command;
	if (strcmp(command, "INSERT") == 0)
	{

	}
	else if (strcmp(command, "FIND") == 0) 
	{

	}
	else if (strcmp(command, "DELETE") == 0)
	{

	}
	else if (strcmp(command, "PRINTPRE") == 0)
	{

	}
	else if (strcmp(command, "PRINTPOST") == 0)
	{

	}
	else if (strcmp(command, "PRINTIN") == 0)
	{

	}
	else if (strcmp(command, "END") == 0)
	{

	}


}