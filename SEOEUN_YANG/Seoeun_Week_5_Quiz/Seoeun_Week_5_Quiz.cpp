#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Node {
private:
	string name;
	Node* parent;
	Node* leftChild;
	Node* rightChild;

public:
	Node() {
		this->name = {};
		this->parent = NULL;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}

	void setData(string name) { this->name=name; }
	string getData() { return this->name; }

	void setParent(Node* nextNode) { this->parent = nextNode; }
	Node* getParent() { return this->parent; }
	void setleftChild(Node* leftChild) { this->leftChild = leftChild; }
	Node* getleftChild() { return this->leftChild; }
	void setrightChild(Node* rightChild) { this->rightChild = rightChild; }
	Node* getrightChild() { return this->rightChild; }
};

class Tree {
private:
	Node* root;
	Node* parent;
	int size;

public:
	Tree() {
		this->root = NULL;
		this->parent = NULL;
		this->size = 0;
	}

	~Tree() {
		deallocate(root);
	}

	Node* getroot() { return root; }
	void INSERT(Node* curNode,string name);
	void FIND(Node* curNode,string name);
	void DELETE(string name);
	void PRINT_PRE(Node* curNode);
	void PRINT_IN(Node* curNode);
	void PRINT_POST(Node* curNode);
	void deallocate(Node* curNode);
};

void Tree::INSERT(Node* curNode, string name) {
	if (root == NULL) {
		Node* newNode = new Node;
		newNode->setData(name);
		root = newNode;
		this->size++;
	}
	else if (curNode->getData()>name) {//왼쪽
		if (curNode->getleftChild() == NULL) {
			Node* newNode = new Node;
			newNode->setData(name);
			curNode->setleftChild(newNode);
			this->size++;
		}
		else {
			if (curNode->getleftChild()->getData()==name)
				return;
			INSERT(curNode->getleftChild(), name);
		}
	}
	else if (curNode->getData() < name) {//오른쪽
		if (curNode->getrightChild() == NULL) {
			Node* newNode = new Node;
			newNode->setData(name);
			curNode->setrightChild(newNode);
			this->size++;
		}
		else {
			if (curNode->getrightChild()->getData()== name)
				return;
			INSERT(curNode->getrightChild(), name);
		}
	}
}

void Tree::FIND(Node* curNode, string name) {//순회 아무거나 써도 될 듯
	int found = 0;
	if (curNode == nullptr)
		return;

	if (curNode->getData()== name) {
		cout << name << " exists";
		found++;
		return;
	}
	else {
		FIND(curNode->getleftChild(), name);
		FIND(curNode->getrightChild(), name);
	}

	if (found == 0)
		cout << "Not found" << endl;
}

void Tree::DELETE(string name) {

}

void Tree::PRINT_PRE(Node* curNode) {//전
	if (curNode == nullptr)
		return;

	cout << curNode->getData() << "  ";
	PRINT_PRE(curNode->getleftChild());
	PRINT_PRE(curNode->getrightChild());
}

void Tree::PRINT_IN(Node* curNode) {//중
	if (curNode == nullptr)
		return;

	PRINT_IN(curNode->getleftChild());
	cout << curNode->getData() << "  ";
	PRINT_IN(curNode->getrightChild());
}

void Tree::PRINT_POST(Node* curNode) {//후
	if (curNode == nullptr)
		return;

	PRINT_POST(curNode->getleftChild());
	PRINT_POST(curNode->getrightChild());
	cout << curNode->getData() << "  ";
}

void Tree::deallocate(Node* curNode) {//후위순회 사용해야 함
	if (curNode == nullptr)
		return;

	PRINT_POST(curNode->getleftChild());
	PRINT_POST(curNode->getrightChild());
	Node* delNode = curNode;
	delete delNode;
}

int main() {
	string command;
	string name;
	string temp_command;
	Tree* tree = new Tree;

	while (1) {
		getline(cin, command);

		temp_command = command.substr(0, 6);
		
		if (temp_command == "INSERT") {
			//cin >> name;
			tree->INSERT(tree->getroot(), command.substr(7));
		}
		
		else if (temp_command == "DELETE") {
			//cin >> name;
			tree->DELETE(command.substr(7));
		}

		else if (command.substr(0,4) == "FIND") {
			//cin >> name;
			tree->FIND(tree->getroot(), command.substr(5));
		}

		if (command == "PRINT PRE") {
			tree->PRINT_PRE(tree->getroot());
			cout << endl;
		}
		else if (command == "PRINT POST") {
			tree->PRINT_POST(tree->getroot());
			cout << endl;
		}
		else if (command == "PRINT IN") {
			tree->PRINT_IN(tree->getroot());
			cout << endl;
		}
		else if (command.substr(0,4) == "END")
			break;

		else
			continue;
	}

	delete tree;
	return 0;
}