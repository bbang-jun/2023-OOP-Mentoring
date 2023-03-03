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

// Tree Ŭ���� ����
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
	// root��尡 ���� ���
	if (curNode == NULL)
	{
		Node* newNode = new Node;
		newNode->setData(data);
		root = newNode;
		size++;
	}
	// root��尡 ���� ���
	else
	{
		// �̹� ���� ���� ���� ���
		if (curNode->getData() == data)
		{
			cout << "������ ���� �ֽ��ϴ�." << endl;
			return;
		}

		// �Է°��� curNode���� Ŭ ���
		if (curNode->getData() < data)
		{
			// curNode �����ʿ� ���� ���� ���
			if (curNode->getRight() != NULL)
			{
				INSERT(curNode->getRight(), data);
			}
			// curNode �����ʿ� ���� ���� ���
			else
			{
				Node* newNode = new Node;
				newNode->setData(data);
				curNode->setRight(newNode);
				size++;
			}
		}
		// �Է°��� curNode���� ���� ���
		else
		{
			// curNode ���ʿ� ���� ���� ���
			if (curNode->getLeft() != NULL)
			{
				INSERT(curNode->getLeft(), data);
			}
			// curNode ���ʿ� ���� ���� ���
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
		// �����Ϸ��� ���� ���� ����� ������ Ŭ ���
		if (curNode->getData() < data)
		{
			parent = curNode;
			curNode = parent->getRight();
		}
		// ''' ���� ���
		else if (curNode->getData() > data)
		{
			parent = curNode;
			curNode = parent->getLeft();
		}
		// ���� ���
		else
		{
			break;
		}
	}

	// �����ϴ� ��尡 �ڽĳ�尡 ���� ���
	if (curNode->getLeft() == NULL && curNode->getRight() == NULL)
	{
		// �����ϴ� ���� ��Ʈ����� ���
		if (data == root->getData())
		{
			delete root;
			root = NULL;
			this->size--;
		}
		// �����ϴ� ���� ��Ʈ��尡 �ƴ� ���
		else
		{
			// �θ����� �������� ���
			if (curNode = parent->getRight())
			{
				parent->setRight(NULL);
				delete curNode;
				curNode = NULL;
				this->size--;
			}
			// �θ����� ������ ���
			else
			{
				parent->setLeft(NULL);
				delete curNode;
				curNode = NULL;
				this->size--;
			}
		}
	}
	//�����ϴ� ��尡 �ڽĳ�尡 �ϳ��� ���� ���
	else if (curNode->getLeft() != NULL || curNode->getRight() != NULL)
	{
		delNode = curNode;
		// �����Ϸ��� ��尡 ��Ʈ ����� ���
		if (delNode == root)
		{
			// ������ �ڽĸ� ���� ���
			if (delNode->getRight() != NULL)
			{
				root = 
			}
			// ���� �ڽĸ� ���� ���
			else
			{

			}
		}
		// �����Ϸ��� ��尡 ��Ʈ ��尡 �ƴ� ���
		else
		{

		}
	}
	//�����ϴ� ��尡 �ڽĳ�尡 �ΰ� ���� ���
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