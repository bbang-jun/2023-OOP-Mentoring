#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
private:
	string data;
	Node* left;
	Node* right;
public:
	Node()
	{
		this->data = "";
		this->left = NULL;
		this->right = NULL;
	}
	string getData() { return this->data; }
	void setData(string input) { this->data = input; }

	Node* getLeft() { return this->left; }
	void setLeft(Node* leftChild) { this->left = leftChild; }

	Node* getRight() { return this->right; }
	void setRight(Node* rightChild) { this->right = rightChild; }
};

// Tree 클래스 선언
class Tree
{
private:
	Node* parent;
	Node* root;
	int size;
public:
	Tree()
	{
		this->parent = NULL;
		this->root = NULL;
		this->size = 0;
	}

	Node* getRoot() { return this->root; }
	void INSERT(Node* curNode, string data);
	void FIND(Node* curNode, string data);
	void DELETE(string data);
	void PRINT_PRE(Node* curNode);
	void PRINT_IN(Node* curNode);
	void PRINT_POST(Node* curNode);
};


void Tree::INSERT(Node* curNode, string data)
{
	// root노드가 없을 경우
	if (curNode == NULL)
	{
		Node* newNode = new Node;
		newNode->setData(data);
		root = newNode;
		size++;
	}
	// root노드가 있을 경우
	else
	{
		// 이미 같은 값이 있을 경우
		if (curNode->getData() == data)
		{
			cout << "동일한 값이 있습니다." << endl;
			return;
		}

		// 입력값이 curNode보다 클 경우
		if (curNode->getData() < data)
		{
			// curNode 오른쪽에 값이 있을 경우
			if (curNode->getRight() != NULL)
			{
				INSERT(curNode->getRight(), data);
			}
			// curNode 오른쪽에 값이 없을 경우
			else
			{
				Node* newNode = new Node;
				newNode->setData(data);
				curNode->setRight(newNode);
				size++;
			}
		}
		// 입력값이 curNode보다 작을 경우
		else
		{
			// curNode 왼쪽에 값이 있을 경우
			if (curNode->getLeft() != NULL)
			{
				INSERT(curNode->getLeft(), data);
			}
			// curNode 왼쪽에 값이 없을 경우
			else
			{
				Node* newNode = new Node;
				newNode->setData(data);
				curNode->setLeft(newNode);
				size++;
			}
		}
	}
}

void Tree::FIND(Node* curNode, string data)
{
	if (curNode == nullptr)
	{
		cout << "Not found" << endl;
		return;
	}
	FIND(curNode->getLeft(), data);
	if (curNode->getData().compare(data) == 0)
	{
		cout << data << " exists" << endl;
		return;
	}
	FIND(curNode->getRight(), data);
}

void Tree::DELETE(string data)
{
	Node* curNode = this->root;
	Node* delNode = NULL;
	Node* tempNode = NULL;

	while (1)
	{
		if (curNode->getData() == "")
		{
			cout << "Not found" << endl;
			return;
		}
		// 삭제하려는 값이 현재 노드의 값보다 클 경우
		if (curNode->getData() < data)
		{
			parent = curNode;
			curNode = parent->getRight();
		}
		// ''' 작을 경우
		else if (curNode->getData() > data)
		{
			parent = curNode;
			curNode = parent->getLeft();
		}
		// 같을 경우
		else
		{
			break;
		}
	}

	// 삭제하는 노드가 자식노드가 없을 경우
	if (curNode->getLeft() == NULL && curNode->getRight() == NULL)
	{
		// 삭제하는 값이 루트노드일 경우
		if (data == root->getData())
		{
			delete root;
			root = NULL;
			this->size--;
		}
		// 삭제하는 값이 루트노드가 아닐 경우
		else
		{
			// 부모노드의 오른쪽일 경우
			if (curNode = parent->getRight())
			{
				parent->setRight(NULL);
				delete curNode;
				curNode = NULL;
				this->size--;
			}
			// 부모노드의 왼쪽일 경우
			else
			{
				parent->setLeft(NULL);
				delete curNode;
				curNode = NULL;
				this->size--;
			}
		}
	}
	//삭제하는 노드가 자식노드가 하나만 있을 경우
	else if (curNode->getLeft() != NULL || curNode->getRight() != NULL)
	{
		delNode = curNode;
		// 삭제하려는 노드가 루트 노드일 경우
		if (delNode == root)
		{
			// 오른쪽 자식만 있을 경우
			if (delNode->getRight() != NULL)
			{
				root = 
			}
			// 왼쪽 자식만 있을 경우
			else
			{

			}
		}
		// 삭제하려는 노드가 루트 노드가 아닐 경우
		else
		{

		}
	}
	//삭제하는 노드가 자식노드가 두개 있을 경우
	else
	{
		Node* smallRight = curNode;
		Node* smallRightParent = smallRight;
	}
}

void Tree::PRINT_PRE(Node* curNode) 
{
	if (curNode == nullptr)
		return;
	cout << curNode->getData() << " ";
	PRINT_PRE(curNode->getLeft());
	PRINT_PRE(curNode->getRight());
}

void Tree::PRINT_IN(Node* curNode)
{
	if (curNode == nullptr)
		return;
	PRINT_IN(curNode->getLeft());
	cout << curNode->getData() << " ";
	PRINT_IN(curNode->getRight());
}

void Tree::PRINT_POST(Node* curNode)
{
	if (curNode == nullptr)
		return;
	PRINT_POST(curNode->getLeft());
	PRINT_POST(curNode->getRight());
	cout << curNode->getData() << " ";
}

int main()
{
	Tree* tree = new Tree;
	string command = "", input, temp;

	while (command != "END")
	{
		getline(cin, command);
		istringstream ss(command);
		ss >> temp >> input;

		if (temp == "INSERT")
		{
			tree->INSERT(tree->getRoot(), input);
		}
		else if (temp == "FIND")
		{
			tree->FIND(tree->getRoot(), input);
		}
		else if (temp == "DELETE")
		{
			tree->DELETE(input);
		}
		else if (command == "PRINT PRE")
		{
			tree->PRINT_PRE(tree->getRoot());
		}
		else if (command == "PRINT IN")
		{
			tree->PRINT_IN(tree->getRoot());
			cout << endl;
		}
		else if (command == "PRINT POST")
		{
			tree->PRINT_POST(tree->getRoot());
		}
	}
}