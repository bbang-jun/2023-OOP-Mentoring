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
	int FIND(Node* curNode,string name,int found);//수정 필요
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

int Tree::FIND(Node* curNode, string name,int found) {//순회 아무거나 써도 될 듯
	if (curNode == nullptr)
		return found;

	if (curNode->getData()== name) {
		cout << name << " exists" << endl;
		found += 100;
		return found;
	}
	
	FIND(curNode->getleftChild(), name,found);
	FIND(curNode->getrightChild(), name,found);
	
	return found;
}

void Tree::DELETE(string name) {
	Node* curNode = root;
	Node* delNode = NULL;
	Node* tempNode = NULL;

	while (1) {
		if (curNode->getData() > name) {//왼쪽
			parent = curNode;
			curNode = curNode->getleftChild();
		}
		else if (curNode->getData() < name) {//오른쪽
			parent = curNode;
			curNode = curNode->getrightChild();
		}
		else
			break;
	}

	if (curNode->getleftChild() == NULL && curNode->getrightChild() == NULL) {
		if (curNode == root) {
			delete root;
			root = NULL;
			return;
		}
		else {
			if (parent->getleftChild() == curNode) {
				delete curNode;
				curNode = NULL;
				parent->setleftChild(NULL);
			}
			else if (parent->getrightChild() == curNode) {
				delete curNode;
				curNode = NULL;
				parent->setrightChild(NULL);
			}
		}
	}

	if (curNode->getleftChild() == NULL || curNode->getrightChild() == NULL) {
		if (curNode == root) {
			if (curNode->getleftChild() != NULL) {
				tempNode = curNode->getleftChild();
				delete root;
				root = tempNode;
				return;
			}
			if (curNode->getrightChild() != NULL) {
				tempNode = curNode->getrightChild();
				delete root;
				root = tempNode;
				return;
			}
		}
		else {
			delNode = curNode;
			if (parent->getleftChild() == curNode) {
				if (curNode->getleftChild() != NULL) {
					parent->setleftChild(curNode->getleftChild());
					delete delNode;
					curNode->setleftChild(NULL);
					delNode = NULL;
				}
				else if (curNode->getrightChild() != NULL) {
					parent->setleftChild(curNode->getrightChild());
					delete delNode;
					curNode->setrightChild(NULL);
					delNode = NULL;
				}
			}
			else if (parent->getrightChild() == curNode) {
				if (curNode->getleftChild() != NULL) {
					parent->setrightChild(curNode->getleftChild());
					delete delNode;
					curNode->setleftChild(NULL);
					delNode = NULL;
				}
				else if (curNode->getrightChild() != NULL) {
					parent->setrightChild(curNode->getrightChild());
					delete delNode;
					curNode->setrightChild(NULL);
					delNode = NULL;
				}
			}
		}
	}

	else if (curNode->getleftChild() != NULL && curNode->getrightChild() != NULL) {
		Node* rightsmall = curNode->getrightChild();
		Node* rightsmallparent = curNode;

		if (rightsmall->getleftChild() == NULL) {
			curNode->setData(rightsmall->getData());
			if (rightsmall->getrightChild() != NULL) {
				curNode->setrightChild(rightsmall->getrightChild());
			}
			else//rs=leafnode
				curNode->setrightChild(NULL);
			delete rightsmall;
			rightsmall = NULL;
			return;
		}

		else {
			while (rightsmall->getleftChild() != NULL) {
				rightsmallparent = rightsmall;
				rightsmall = rightsmall->getleftChild();
			}
			curNode->setData(rightsmall->getData());
			rightsmallparent->setleftChild(NULL);
			delete rightsmall;
			rightsmall = NULL;
		}
	}
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

	deallocate(curNode->getleftChild());
	deallocate(curNode->getrightChild());
	Node* delNode = curNode;
	delete delNode;
}

int main() {
	string command;
	string name;
	string temp_command;
	int found = 0;
	Tree* tree = new Tree;

	while (1) {
		getline(cin, command);

		temp_command = command.substr(0, 6);
		
		if (temp_command == "INSERT") {
			tree->INSERT(tree->getroot(), command.substr(7));
		}
		
		else if (temp_command == "DELETE") {
			tree->DELETE(command.substr(7));
		}

		else if (command.substr(0,4) == "FIND") {
			found += tree->FIND(tree->getroot(), command.substr(5), found);
			if (found==0)
				cout << "Not found" << endl;
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