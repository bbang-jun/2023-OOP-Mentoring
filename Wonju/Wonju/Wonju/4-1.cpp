#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Node {
private:
	int value;
	Node* LeftChild;
	Node* RightChild;
	Node* Parent;

public:
	Node() {
		this->value = 0;
		this->LeftChild = NULL;
		this->RightChild = NULL;
		this->Parent = NULL;
	}
	void setValue(int data) { this->value = data; }
	int getValue() { return this->value; }

	void setLeftChild(Node* LeftChild) { this->LeftChild = LeftChild; }
	Node* getLeftChild() { return this->LeftChild; }

	void setRightChild(Node* RightChild) { this->RightChild = RightChild; }
	Node* getRightChild() { return this->RightChild; }
	
	void setParent(Node* Parent) { this->Parent = Parent; }
	Node* getParent() { return this->Parent; }

};

class Tree {
private:
	int size;
	Node* root;
	Node* Parent;
	Node* curNode;
	Node* delNode;
public:
	Tree() {
		size = 0;
		root = NULL;
		Parent = NULL;
		curNode = NULL;
		delNode = NULL;
		
	}
	~Tree() {
		allocate(root);
	}
	Node* getRoot(){return root; }
	void INSERT(Node* curNode, int integer);
	void DELETE(Node* curNode, int integer);
	void FIND(Node* curNode, int integer);
	void PrintPreorder(Node* curNode);
	void PrintInorder(Node* curNode);
	void PrintPostorder(Node* curNode);
	void PrintLeafnode(Node* curNode);
	void allocate(Node* curNode);
};
void Tree::INSERT(Node* curNode, int integer) { // ��Ʈ ��尡 ���� ���
	if (root == NULL)
	{
		Node* newNode = new Node;
		newNode->setValue(integer);
		root = newNode;
		curNode = root;
		this->size++;
	}
	else if (curNode->getValue() > integer) { //���ο� ����� ���� �� ���� ���
		if (curNode->getLeftChild() == NULL) {
			Node* newNode = new Node;
			newNode->setValue(integer);
			curNode->setLeftChild(newNode);
			this->size++;
		}
		else { //���� �ڽ��� �ִ� ���
			if (curNode->getLeftChild()->getValue() == integer)
				return;
			INSERT(curNode->getLeftChild(), integer);
		}
	}
	else if (curNode->getValue() < integer) // ���� ��忡 ����� ������ ū ���
	{
		if (curNode->getRightChild() == NULL) { //������ �ڽ��� �ִ� ���
			Node* newNode = new Node;
			newNode->setValue(integer);
			curNode->setRightChild(newNode);
			this->size++;
		}
		else {
			if (curNode->getRightChild()->getValue() == integer)
				return;
			INSERT(curNode->getRightChild(), integer);
		}
	}
}
void Tree::DELETE(Node* curNode, int integer) {
	if (curNode->getLeftChild() == NULL && curNode->getRightChild() == NULL) {
		if (curNode == root) { // child�� 0���� node�� root�� ���
			delete root; //root �׳� ���� �� �ʱ�ȭ
			root = NULL;
			size--;
			return;
			
		}
		else { // child�� 0���� node�� root�� �ƴ� ���
			delete curNode; //child�� 0���� �Ժη� ���� �����ϴϱ� ������� ��.
			curNode = NULL; // �翬�� �ʱ�ȭ
			size--;
			return;
		}
	}
	else if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL) { //�� �� �ϳ��� �ִ� ��� �� �� null�� ���� ������ ������
		if (curNode == root) { // child�� 1���� node�� root�� ���
			if (root->getLeftChild() != NULL) { // root�� left child�� �����ϴ� ��� ��Ʈ�� �������ְ� ������ ��Ʈ ����
				curNode = root->getLeftChild();
				delete root;
				root = curNode;
				size--;
				return;
			}
			else if (root->getRightChild() != NULL) { // root�� right child�� �����ϴ� ��� ��Ʈ�� �������ְ� ������ ��Ʈ ����
				curNode = root->getRightChild();
				delete root;
				root = curNode;
				size--;
				return;
			}
		}
		else { // child�� 1���� node�� root�� �ƴ� ���
			delNode = curNode;

			if (Parent->getLeftChild() == curNode) { // parent�� ���ο� left child�� ����
				if (curNode->getLeftChild() != NULL) { // curNode�� left child�� ������ �����Ƿ�
					Parent->setLeftChild(curNode->getLeftChild()); // parent�� ���ο� left child�� curNode�� left child�� ����
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
				else if (curNode->getRightChild() != NULL) { // curNode�� right child�� ������ �����Ƿ�
					Parent->setRightChild(curNode->getRightChild()); // parent�� ���ο� right child�� curNode�� right child�� ����
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
			}
			else if (Parent->getRightChild() == curNode) { // parent�� ���ο� right child�� ����
				if (curNode->getLeftChild() != NULL) { // curNode�� left child�� ������ �����Ƿ�
					Parent->setLeftChild(curNode->getLeftChild()); // parent�� ���ο� left child�� curNode�� left child�� ����
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
				else if (curNode->getRightChild() != NULL) { // curNode�� right child�� ������ �����Ƿ�
					Parent->setRightChild(curNode->getRightChild()); // parent�� ���ο� right child�� curNode�� right child�� ����
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
			}
		}
	}
	else if (curNode->getLeftChild() != NULL && curNode->getRightChild() != NULL) {
		Node* rightSmall = curNode->getRightChild();
		Node* rightSmallParent = rightSmall;

		if (rightSmall->getLeftChild() == NULL) { // rightSmall�� left child�� ���� ���
			curNode->setValue(rightSmall->getValue()); // curNode�� data�� rightSmall�� ���� �� rightSmall ����
			curNode->setRightChild(NULL);
			delete rightSmall;
			rightSmall = NULL;
			size--;
			return;
		}
		else { // rightSmall�� left child�� �ִ� ���
			while (rightSmall->getLeftChild() != NULL) { // ���� sub tree�� ���� ���� data�� ���� node�� �̵�
				rightSmallParent = rightSmall;
				rightSmall = rightSmall->getLeftChild();
			}

			curNode->setValue(rightSmall->getValue()); // ������ ����� data�� ���� sub tree�� ���� ���� data�� �ٲ�
			rightSmallParent->setLeftChild(NULL);
			delete rightSmall; // ���� sub tree�� ���� ���� node ����
			rightSmall = NULL;
			size--;
			return;
		}
	}
}
void Tree::FIND(Node* curNode, int integer){
	while (1)
	{
		if (curNode->getValue() == integer) { //���ٸ� ���
			cout << curNode->getValue()<<endl;
			break;
		}
		else if (curNode->getValue() > integer) //ã�� ���� �۴ٸ�
		{
			cout << curNode->getValue() << "->"; //���� �� ���
			curNode = curNode->getLeftChild(); // �ó�带 leftchild�� �ű��
		}
		else if (curNode->getValue() < integer) // ã�� ���� �� ũ�ٸ�
		{
			cout << curNode->getValue() << "->";
			curNode = curNode->getRightChild();
		}
	}
}
void Tree::PrintPreorder(Node* curNode) { // ������ȸ ���¿�
	if (curNode == nullptr)
		return;
	cout << curNode->getValue() << " ";
	PrintPreorder(curNode->getLeftChild()); 
	PrintPreorder(curNode->getRightChild());
}

void Tree::PrintInorder(Node* curNode) { // ������ȸ �����
	if (curNode == nullptr)
		return;
	PrintInorder(curNode->getLeftChild());
	cout << curNode->getValue() << " ";
	PrintInorder(curNode->getRightChild());
}

void Tree::PrintPostorder(Node* curNode) { // ������ȸ �¿���
	if (curNode == nullptr)
		return;
	PrintPostorder(curNode->getLeftChild());
	PrintPostorder(curNode->getRightChild());
	cout << curNode->getValue() << " ";
}
void Tree::PrintLeafnode(Node* curNode) { //������ȸ���� ��������� ���� ���
	if (curNode == nullptr)
		return;
	PrintLeafnode(curNode->getLeftChild());
	if(curNode->getLeftChild()==NULL&&curNode->getRightChild()==NULL)
		cout << curNode->getValue() << " ";
	PrintLeafnode(curNode->getRightChild());
}

int main(void) {
	Tree* tree = new Tree;
	int Command = 0;
	int integer = 0;

	while (1)
	{
		cout << "Enter Any Command(1: Insert, 2:Delete, 3:Find, 4:Preorder, 5:Inorder, 6:Postorder, 7:Leaf node, 8:Exit) : ";
		cin >> Command;
		if (Command == 1)
		{
			cin >> integer;
			tree->INSERT(tree->getRoot(), integer);
		}
		else if (Command == 2)
		{
			cin >> integer;
			tree->DELETE(tree->getRoot(), integer);
		}
		else if (Command == 3)
		{
			cin >> integer;
			cout << "path : ";
			tree->FIND(tree->getRoot(), integer);
		}
		else if (Command == 4)
		{
			tree->PrintPreorder(tree->getRoot());
			cout << endl;
		}
		else if (Command == 5)
		{
			tree->PrintInorder(tree->getRoot());
			cout << endl;
		}
		else if (Command == 6)
		{
			tree->PrintPostorder(tree->getRoot());
			cout << endl;
		}
		else if (Command == 7)
		{
			tree->PrintLeafnode(tree->getRoot());
			cout << endl;
		}
		else if (Command == 8)
		{
			break;
		}
		else
			cout << "���� ������ ���ڸ� �������ּ���";
	}
	
}