#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int data;//데이터값
	Node* leftChild;
	Node* rightChild;
	Node* parent;

public:
	Node() {//자동생성자
		this->data = 0;//초기화
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}

	void setData(int data) { this->data = data; }
	int getData() { return this->data; }
	void setParent(Node* nextNode) { this->parent = nextNode; }
	Node* getParent() { return this->parent; }
	void setLeftChild(Node* leftChild) { this->leftChild = leftChild; }
	Node* getLeftChild() { return this->leftChild; }
	void setRightChild(Node* rightChild) { this->rightChild = rightChild; }
	Node* getRightChild() { return this->rightChild; }
};

class Tree {//tree 클래스 생성
private:
	Node* root;//최상 노드
	Node* parent;//부모 노드
	int size;//tree 길이
public:
	Tree() {//자동생성자
		this->root = NULL;//초기화
		this->parent = NULL;
		this->size = 0;
	}
	~Tree() {//동적 할당 해제 (노드 삭제)
		deallocate(root);
	}
	
	Node* getRoot() { return root; }
	void INSERT(Node* curNode, int data);
	//void DELETE(int data);
	//void FIND(int data);
	void PRINT_PRE(Node* curNode);
	void PRINT_IN(Node* curNode);
	void PRINT_POST(Node* curNode);
	void PRINT_LEAF(Node* curNode);//프린트 하나 돌리면서 자식 노드 없을 때만 출력
	void deallocate(Node* curNode);
};

void Tree::INSERT(Node* curNode, int data) {//삽입
	if (root == NULL) {//루트 노드가 없는 경우 (첫 삽입 (따라서 중복 가능성 없음))
		Node* newNode = new Node;
		newNode->setData(data);//뉴노드 데이터 저장
		root = newNode; //현재 노드 = root
		//curNode = root;
		this->size++;
	}
	else if (curNode->getData() > data) {//왼쪽 이동
		if (curNode->getLeftChild() == NULL) {//왼쪽 존재 X -> 왼쪽에 저장
			Node* newNode = new Node;
			newNode->setData(data);
			curNode->setLeftChild(newNode);
			this->size++;
		}
		else {//왼쪽 존재 0 -> curNode 왼쪽 자식으로 이동해 INSERT 함수 다시 실행
			if (curNode->getLeftChild()->getData() == data)
				return;//중복 제외
			INSERT(curNode->getLeftChild(), data);//INSERT 함수 다시 실행
		}
	}
	else if (curNode->getData() < data) {//오른쪽 이동
		if (curNode->getRightChild() == NULL) {//오른쪽 존재 X -> 오른쪽에 저장
			Node* newNode = new Node;
			newNode->setData(data);
			curNode->setRightChild(newNode);
			this->size++;
		}
		else {//오른쪽 존재 0 -> curNode 오른쪽 자식으로 이동해 INSERT 함수 다시 실행
			if (curNode->getRightChild()->getData() == data)
				return;//중복 제외
			INSERT(curNode->getRightChild(), data);
		}
	}
}

void Tree::PRINT_PRE(Node* curNode) { // 전위순회
	if (curNode == nullptr)
		return;
	cout << curNode->getData() << " ";
	PRINT_PRE(curNode->getLeftChild());
	PRINT_PRE(curNode->getRightChild());
}

void Tree::PRINT_IN(Node* curNode) { // 중위순회
	if (curNode == nullptr)
		return;
	PRINT_IN(curNode->getLeftChild());
	cout << curNode->getData() << " ";
	PRINT_IN(curNode->getRightChild());
}

void Tree::PRINT_POST(Node* curNode) { // 후위순회
	if (curNode == nullptr)
		return;
	PRINT_POST(curNode->getLeftChild());
	PRINT_POST(curNode->getRightChild());
	cout << curNode->getData() << " ";
}

void Tree::PRINT_LEAF(Node* curNode) {//leaf node 출력
	if (curNode == nullptr)
		return;
	PRINT_LEAF(curNode->getLeftChild());
	if(curNode->getLeftChild()==NULL&&curNode->getRightChild()==NULL)
		cout << curNode->getData() << " ";
	PRINT_LEAF(curNode->getRightChild());
}

void Tree::deallocate(Node* curNode) {
	if (curNode == nullptr)
		return;
	deallocate(curNode->getLeftChild());
	deallocate(curNode->getRightChild());
}

int main(void) {
	int command = 0;
	int data = 0;
	Tree* tree = new Tree;

	while (1) {
		cout << "Enter Any Command(1:Insert, 2:Delete, 3:Find, 4:Preorder, 5:Inorder, 6:Postorder, 7:Leaf node, 8:Exit): ";
		cin >> command;

		if (command == 1) {
			cin >> data;
			tree->INSERT(tree->getRoot(), data);
		}

		if (command == 2) {
			//
		}

		if (command == 3) {
			//
		}

		if (command == 4)
			tree->PRINT_PRE(tree->getRoot());

		if (command == 5)
			tree->PRINT_IN(tree->getRoot());

		if (command == 6)
			tree->PRINT_POST(tree->getRoot());

		if (command == 7) {
			//
		}

		if (command == 8)
			break;
	}

	delete tree;
	return 0;
}

//역방향 없음 아마도