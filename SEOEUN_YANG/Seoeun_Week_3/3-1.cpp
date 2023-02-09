#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int ID;
	string name;
	Node* prev;//이전 노드 가리킴
	Node* next;//다음 노드 가리킴
public:
	Node() {//생성자
		ID = 0;//초기화
		name = "";
		this->next = NULL;//초기화
		this->prev = NULL;
	}
	void setID(int ID) { this->ID = ID; }//데이터 저장
	int getID() { return this->ID; }//데이터 불러옴
	void setname(string name) { this->name=name; }
	string getname() { return this->name; }

	void setPrev(Node* prevNode) { this->prev = prevNode; }//이전 노드 포인터 저장
	Node* getPrev() { return this->prev; }//노드 앞으로 이동
	void setNext(Node* nextNode) { this->next = nextNode; }//다음 노드 포인터 저장
	Node* getNext() { return this->next; }//다음 노드 포인터 불러옴 (노드 이동)
};

class List {//리스트 클래스 생성
private:
	Node* head;//head 노드
	int size;//리스트 길이(크기)
	Node* tail;//tail 노드
public:
	List() {//생성자 (초기화)
		this->head = NULL;
		this->tail = NULL;
		size = 0;
	}
	~List() {//소멸자 (동적할당 해제)
		Node* curNode = head;//첫번째 노드
		Node* delNode = NULL;//초기화
		while (curNode != NULL) {
			delNode = curNode;//해당 노드 삭제할 노드로 저장
			curNode = curNode->getNext();//curNode 다음 노드로 이동
			//순서 바뀌면 안됨
			delete delNode;//노드 삭제
		}
	}

	bool FIND(int ID);
	void INSERT(int ID,string name);
	void PRINT();
	void PRINT_REV();
	void SORT_NAME();
	//void SORT_ID();
	void DELETE(int ID);
};

bool List::FIND(int ID) {
	Node* curNode = head;//처음부터 탐색
	while (curNode != NULL) {//데이터값 있는 동안만
		if (curNode->getID() == ID) {//찾는 값과 같을 때
			return true;
		}
		curNode = curNode->getNext();//찾는 값 아니면 다음 노드로 이동
	}
	return false;
}

void List::INSERT(int ID, string name) {
	Node* curNode = head;
	Node* newNode = new Node;
	newNode->setID(ID);
	newNode->setname(name);//노드 데이터 저장

	if (FIND(ID) == true)//중복 제거
		return;

	if (head == NULL) {//처음
		tail = head = newNode;
		this->size++;
		return;
	}

	else {//리스트 연결
		while (curNode != NULL) {
			if (curNode->getID() > ID) {
				if (curNode == head) {//head 앞에 삽입해야 할 경우
					newNode->setNext(curNode);//head 다음 삽입
					curNode->setPrev(newNode);//역방향 연결
					head = newNode;
					this->size++;
					return;//INSERT 끝
				}
				else {//리스트 중간 삽입 //curNode 앞에 newNode 삽입
					//역방향 연결
					curNode->getPrev()->setNext(newNode);//curNode의 prev, newNode의 next으로 연결
					newNode->setPrev(curNode->getPrev());//newNode의 prev, curNode 전 노드의 next으로 연결
					//순방향 연결
					curNode->setPrev(newNode);
					newNode->setNext(curNode);
					this->size++;
					return;
				}
			}
			curNode = curNode->getNext();
		}
	}

	//마지막 연결
	tail->setNext(newNode);//새 노드 tail로 연결
	newNode->setPrev(tail);//역방향 연결
	tail = tail->getNext();//tail 이동
	this->size++;
}

void List::PRINT() {
	Node* curNode = head;//첫번째 노드부터 차례로 출력

	while (curNode != NULL) {
		cout << curNode->getID() << " " << curNode->getname() << endl;
		curNode = curNode->getNext();
	}
}

void List::PRINT_REV() {
	Node* curNode = tail;//마지막 노드부터 차례로 출력

	while (curNode != NULL) {
		cout << curNode->getID() << " " << curNode->getname() << endl;
		curNode = curNode->getPrev();
	}
}

void List::SORT_NAME() {
	int temp_ID = 0;
	string temp_name = "";
	Node* Node_1 = head;
	Node* Node_2 = head->getNext();

	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < (this->size) - 1; j++) {
			if (Node_1->getname() > Node_2->getname()) {
				temp_ID = Node_1->getID();
				temp_name = Node_1->getname();
				Node_1->setID(Node_2->getID());
				Node_1->setname(Node_2->getname());
				Node_2->setID(temp_ID);
				Node_2->setname(temp_name);
			}
			Node_1->getNext();
			Node_2->getNext();
		}

		Node_1 = head;
		Node_2 = head->getNext();
		for (int z = 0; z < i + 1; z++) {
			Node_1->getNext();
			Node_2->getNext();
		}
	}
	PRINT();
}


void List::DELETE(int ID) {
	Node* curNode = head;
	//변수 느낌
	Node* prevNode = NULL;
	Node* delNode = NULL;

	while (curNode != NULL) {//노드에 데이터가 있을 때
		if (curNode->getID() == ID)//지우고 싶은 값일 때 while문 탈출
			break;
		prevNode = curNode;//지우고 싶은 값이 아니면 노드 이동 (prev에 현재 노드 저장, 포인터 옮길 때 이용)
		curNode = curNode->getNext();
	}

	//while문 탈출 이후
	if (curNode == head) { // 1. head를 삭제하는 경우
		if (head->getNext() == NULL) { // list에 head만 존재하는 경우
			delNode = head;
			delete head;
			// head = NULL; 팁1

			this->size--;//-> size=0
		}
		else { // list에 head 외에 다른 노드들도 존재하는 경우
			delNode = head;
			head = head->getNext();//head 다음 노드를 head로 설정
			delete delNode;
			this->size--;
		}
	}
	else if (curNode == tail) { // 3. tail을 삭제하는 경우
		delNode = tail;
		tail = prevNode;//tail 전 노드 tail로 설정
		delete delNode;
		tail->setNext(NULL); // 팁2 //쓰레기값 방지 (tail 항상 NULL 가리킴)
		this->size--;
	}
	else { // 2. head와 tail을 제외한 다른 노드들을 제거하는 경우
		delNode = curNode;
		prevNode->setNext(curNode->getNext());//cur노드 전의 노드를 cur노드 이후의 노드를 가리키게 만듦
		delete delNode;//cur노드 삭제
		this->size--;
	}
}

int main(void) {
	int command;
	int ID = 0;
	string name;
	List* valueList = new List;
	
	while (1) {
		cout << "Please Enter Command(1 : insert, 2 : print, 3 : print_reverse, 4 : sort_by_name, 5 : sort_by_ID, 6 : delete, 7 : exit) : ";
		cin >> command;

		if (command == 1) {
			cin >> ID >> name;
			valueList->INSERT(ID,name);
		}

		else if (command == 2) {
			valueList->PRINT();
		}

		else if (command == 3) {
			valueList->PRINT_REV();
		}

		else if (command == 4) {
			valueList->SORT_NAME();//출력까지
		}

		else if (command == 5) {
			//valueList->SORT_ID();
		}

		else if (command == 6) {
			cin >> ID;
			valueList->DELETE(ID);
		}

		else if (command == 7)
			break;

		else
			continue;
	}

	delete valueList;
	return 0;
}