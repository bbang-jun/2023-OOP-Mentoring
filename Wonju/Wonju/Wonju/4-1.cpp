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
void Tree::INSERT(Node* curNode, int integer) { // 루트 노드가 없는 경우
	if (root == NULL)
	{
		Node* newNode = new Node;
		newNode->setValue(integer);
		root = newNode;
		curNode = root;
		this->size++;
	}
	else if (curNode->getValue() > integer) { //새로운 노드의 값이 더 작은 경우
		if (curNode->getLeftChild() == NULL) {
			Node* newNode = new Node;
			newNode->setValue(integer);
			curNode->setLeftChild(newNode);
			this->size++;
		}
		else { //왼쪽 자식이 있는 경우
			if (curNode->getLeftChild()->getValue() == integer)
				return;
			INSERT(curNode->getLeftChild(), integer);
		}
	}
	else if (curNode->getValue() < integer) // 현재 노드에 저장된 값보다 큰 경우
	{
		if (curNode->getRightChild() == NULL) { //오른쪽 자식이 있는 경우
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
		if (curNode == root) { // child가 0개인 node가 root인 경우
			delete root; //root 그냥 삭제 후 초기화
			root = NULL;
			size--;
			return;
			
		}
		else { // child가 0개인 node가 root가 아닐 경우
			delete curNode; //child가 0개면 함부로 삭제 금지하니까 고려해준 것.
			curNode = NULL; // 당연히 초기화
			size--;
			return;
		}
	}
	else if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL) { //좌 우 하나라도 있는 경우 둘 다 null인 경우는 위에서 컷해줌
		if (curNode == root) { // child가 1개인 node가 root인 경우
			if (root->getLeftChild() != NULL) { // root의 left child만 존재하는 경우 루트를 변경해주고 기존의 루트 삭제
				curNode = root->getLeftChild();
				delete root;
				root = curNode;
				size--;
				return;
			}
			else if (root->getRightChild() != NULL) { // root의 right child만 존재하는 경우 루트를 변경해주고 기존의 루트 삭제
				curNode = root->getRightChild();
				delete root;
				root = curNode;
				size--;
				return;
			}
		}
		else { // child가 1개인 node가 root가 아닌 경우
			delNode = curNode;

			if (Parent->getLeftChild() == curNode) { // parent의 새로운 left child를 설정
				if (curNode->getLeftChild() != NULL) { // curNode가 left child만 가지고 있으므로
					Parent->setLeftChild(curNode->getLeftChild()); // parent의 새로운 left child를 curNode의 left child로 설정
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
				else if (curNode->getRightChild() != NULL) { // curNode가 right child만 가지고 있으므로
					Parent->setRightChild(curNode->getRightChild()); // parent의 새로운 right child를 curNode의 right child로 설정
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
			}
			else if (Parent->getRightChild() == curNode) { // parent의 새로운 right child를 설정
				if (curNode->getLeftChild() != NULL) { // curNode가 left child만 가지고 있으므로
					Parent->setLeftChild(curNode->getLeftChild()); // parent의 새로운 left child를 curNode의 left child로 설정
					delete delNode;
					delNode = NULL;
					size--;
					return;
				}
				else if (curNode->getRightChild() != NULL) { // curNode가 right child만 가지고 있으므로
					Parent->setRightChild(curNode->getRightChild()); // parent의 새로운 right child를 curNode의 right child로 설정
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

		if (rightSmall->getLeftChild() == NULL) { // rightSmall의 left child가 없는 경우
			curNode->setValue(rightSmall->getValue()); // curNode의 data를 rightSmall로 변경 후 rightSmall 삭제
			curNode->setRightChild(NULL);
			delete rightSmall;
			rightSmall = NULL;
			size--;
			return;
		}
		else { // rightSmall의 left child가 있는 경우
			while (rightSmall->getLeftChild() != NULL) { // 우측 sub tree의 가장 작은 data를 가진 node로 이동
				rightSmallParent = rightSmall;
				rightSmall = rightSmall->getLeftChild();
			}

			curNode->setValue(rightSmall->getValue()); // 삭제할 노드의 data를 우측 sub tree의 가장 작은 data로 바꿈
			rightSmallParent->setLeftChild(NULL);
			delete rightSmall; // 우측 sub tree의 가장 작은 node 삭제
			rightSmall = NULL;
			size--;
			return;
		}
	}
}
void Tree::FIND(Node* curNode, int integer){
	while (1)
	{
		if (curNode->getValue() == integer) { //같다면 출력
			cout << curNode->getValue()<<endl;
			break;
		}
		else if (curNode->getValue() > integer) //찾는 값이 작다면
		{
			cout << curNode->getValue() << "->"; //현재 값 출력
			curNode = curNode->getLeftChild(); // 컬노드를 leftchild로 옮긴다
		}
		else if (curNode->getValue() < integer) // 찾는 값이 더 크다면
		{
			cout << curNode->getValue() << "->";
			curNode = curNode->getRightChild();
		}
	}
}
void Tree::PrintPreorder(Node* curNode) { // 전위순회 출좌우
	if (curNode == nullptr)
		return;
	cout << curNode->getValue() << " ";
	PrintPreorder(curNode->getLeftChild()); 
	PrintPreorder(curNode->getRightChild());
}

void Tree::PrintInorder(Node* curNode) { // 중위순회 좌출우
	if (curNode == nullptr)
		return;
	PrintInorder(curNode->getLeftChild());
	cout << curNode->getValue() << " ";
	PrintInorder(curNode->getRightChild());
}

void Tree::PrintPostorder(Node* curNode) { // 후위순회 좌우출
	if (curNode == nullptr)
		return;
	PrintPostorder(curNode->getLeftChild());
	PrintPostorder(curNode->getRightChild());
	cout << curNode->getValue() << " ";
}
void Tree::PrintLeafnode(Node* curNode) { //중위순회에서 리프노드일 때만 출력
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
			cout << "보기 내에서 숫자를 선택해주세요";
	}
	
}