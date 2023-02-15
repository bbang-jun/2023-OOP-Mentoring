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

	void setData(int data) { this->data = data; }//데이터
	int getData() { return this->data; }
	void setParent(Node* nextNode) { this->parent = nextNode; }//부모 노드
	Node* getParent() { return this->parent; }
	void setLeftChild(Node* leftChild) { this->leftChild = leftChild; }//자식 노드
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
	void DELETE(int data);
	void FIND(Node* curNode, int data);//재귀하면서 출력 (전위순회 사용)
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
		this->size++;
	}
	else if (curNode->getData() > data) {//왼쪽 이동
		if (curNode->getLeftChild() == NULL) {//왼쪽 존재 X -> 왼쪽에 저장
			Node* newNode = new Node;
			newNode->setData(data);
			curNode->setLeftChild(newNode);
			this->size++;
		}
		else {//왼쪽 존재 O -> curNode 왼쪽 자식으로 이동해 INSERT 함수 다시 실행
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

void Tree::DELETE(int data) {
	Node* curNode = root;
	Node* delNode = NULL;
	Node* tempNode = NULL;

	while (1) {//노드 탐색
		if (curNode->getData() < data) {//오른쪽
			parent = curNode;
			curNode = curNode->getRightChild();
		}
		else if (curNode->getData() > data) {//왼쪽
			parent = curNode;
			curNode = curNode->getLeftChild();
		}
		else//데이터값 동일 (노드 탐색 끝)
			break;//데이터값 같은 노드 curNode에 저장해서 while문 빠져나감
	}

	//child가 0개인 node가 삭제될 경우(leaf node가 삭제될 경우)
	if (curNode->getLeftChild() == NULL && curNode->getRightChild() == NULL) {
		if (curNode == root) {//삭제할 노드 = root
			delete root;
			root = NULL;//쓰레기값 방지
			return;
		}
		else {//찐 leaf 노드
			delete curNode;
			curNode = NULL;//쓰레기값 방지
			return;
		}
	}

	//child가 1개인 node가 삭제될 경우
	else if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL) {//child 2개는 여기서 돌아가지 않음 (0개는 이미 앞의 if에서 다 돌아감)
		if (curNode == root) {//삭제할 노드 = root
			if (root->getLeftChild() != NULL) {//왼쪽 자식 존재
				tempNode = root->getLeftChild();
				delete root;
				root = tempNode;//기존 root 삭제하고 새로운 root 설정
				return;
			}
			else if (root->getRightChild() != NULL) {//오른쪽 자식 존재
				tempNode = root->getRightChild();
				delete root;
				root = tempNode;
				return;
			}
		}
		else {//가지노드 삭제
			delNode = curNode;

			if (parent->getLeftChild() == curNode) {//curNode가 왼쪽 자식일 때
				if (curNode->getLeftChild() != NULL) {//curNode에게 왼쪽 자식만 있을 때
					parent->setLeftChild(curNode->getLeftChild());//parent의 새로운 left child를 curNode의 left child로 설정
					delete delNode;
					delNode = NULL;//중요!!!!!
					return;
				}
				else if (curNode->getRightChild() != NULL) {//curNode에게 오른쪽 자식만 있을 때
					parent->setRightChild(curNode->getRightChild());//parent의 새로운 right child를 curNode의 right child로 설정
					delete delNode;
					delNode = NULL;
					return;
				}
			}
			else if (parent->getRightChild() == curNode) {//curNode가 오른쪽 자식일 때
				if (curNode->getLeftChild() != NULL) {//curNode에게 왼쪽 자식만 있을 때
					parent->setLeftChild(curNode->getLeftChild()); // parent의 새로운 left child를 curNode의 left child로 설정
					delete delNode;
					delNode = NULL;
					return;
				}
				else if (curNode->getRightChild() != NULL) {//curNode에게 오른쪽 자식만 있을 때
					parent->setRightChild(curNode->getRightChild());//parent의 새로운 right child를 curNode의 right child로 설정
					delete delNode;
					delNode = NULL;
					return;
				}
			}
		}
	}

	//child가 2개인 node가 삭제될 경우
	else if (curNode->getLeftChild() != NULL && curNode->getRightChild() != NULL) {
		Node* rightSmall = curNode->getRightChild();
		Node* rightSmallParent = curNode;

		if (rightSmall->getLeftChild() == NULL) {//rightSmall의 left child가 없는 경우
			curNode->setData(rightSmall->getData());
			if (rightSmall->getRightChild() != NULL)//rightSmall 오른쪽 존재할 때
				curNode->setRightChild(rightSmall->getRightChild());//연결
			else//rightSmall, leaf node일 때
				curNode->setRightChild(NULL);
			delete rightSmall;
			rightSmall = NULL;
			return;
		}
		else {//rightSmall의 left child가 있는 경우
			while (rightSmall->getLeftChild() != NULL) {//오른쪽  sub tree의 가장 작은 data를 가진 node로 이동
				rightSmallParent = rightSmall;
				rightSmall = rightSmall->getLeftChild();
			}
			//curNode의 오른쪽 tree에서 가장 작은값이 rightSmall, 그에 맞는 rightSmallParent 설정

			curNode->setData(rightSmall->getData());//삭제할 노드의 data를 우측 sub tree의 가장 작은 data로 바꿈
			rightSmallParent->setLeftChild(NULL);
			delete rightSmall; // 우측 sub tree의 가장 작은 node 삭제
			rightSmall = NULL;

			return;
		}
	}
}

void Tree::FIND(Node* curNode,int data) {
	if (curNode == nullptr)
		return;

	cout << curNode->getData();//먼저 출력
	if (curNode->getLeftChild() != NULL || curNode->getRightChild() != NULL) {//leaf node 아니라면
		cout << " -> ";
		if (curNode->getData() > data) {//왼쪽
			FIND(curNode->getLeftChild(), data);
		}
		else if (curNode->getData() < data) {//오른쪽
			FIND(curNode->getRightChild(), data);
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

		else if (command == 2) {//delete
			cin >> data;
			tree->DELETE(data);
		}

		else if (command == 3) {//find
			cin >> data;
			cout << "Path : ";
			tree->FIND(tree->getRoot(), data);
			cout << endl;
		}

		else if (command == 4) {
			tree->PRINT_PRE(tree->getRoot());
			cout << endl;
		}

		else if (command == 5) {
			tree->PRINT_IN(tree->getRoot());
			cout << endl;
		}

		else if (command == 6) {
			tree->PRINT_POST(tree->getRoot());
			cout << endl;
		}

		else if (command == 7) {
			tree->PRINT_LEAF(tree->getRoot());
			cout << endl;
		}

		else if (command == 8)
			break;

		else
			continue;
	}

	delete tree;
	return 0;
}