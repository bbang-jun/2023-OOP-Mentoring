#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int value; // 적어도 하나의 데이터
	Node* next;  // 다음 노드를 가리키는 포인터
public:
	Node() {//생성자
		value = 0;//초기화
		this->next = NULL;//초기화
	}
	void setValue(int value) { this->value = value; }//데이터 저장
	int getValue() { return this->value; }//데이터 불러옴
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
	void INSERT(int value);
	void FIND(int value);
	void PRINT();
	void DELETE(int value);
};

void List::INSERT(int value) {
	Node* curNode = head;//첫번째 노드 cur노드로 저장
	Node* newNode = new Node;//새 노드 동적할당
	newNode->setValue(value);//새 노드에 데이터 저장

	if (head == NULL) { // 앞에 삽입(head가 없는 경우) //첫번째 노드 저장
		tail = head = newNode;//head, tail 노드 동일
		this->size++;//리스트 길이 증가
	}
	else { // head 가 있는 경우
		if (this->size == 5) { // 중간 삽입 //size가 5일 때만 중간 삽입
			int temp = 0;
			while (temp != 3) {//5번째 자리에 삽입
				curNode = curNode->getNext();//노드 이동
				temp++;
			}
			// 1
			newNode->setNext(curNode->getNext()); // 2 //
			curNode->setNext(newNode); // 3
			//순서 바뀌면 안됨

			this->size++;
		}
		else { // 끝에 삽입
			tail->setNext(newNode);//다음 노드 화살표
			tail = tail->getNext();//새로운 tail
			this->size++;
		}
	}
}

void List::FIND(int value) {
	int index = 1;
	Node* curNode = head;//처음부터 탐색
	while (curNode != NULL) {//데이터값 있는 동안만
		if (curNode->getValue() == value) {//찾는 값과 같을 때
			cout << "Found Index:" << index << endl;
		}
		curNode = curNode->getNext();//찾는 값 아니면 다음 노드로 이동
		index++;
	}
}

void List::PRINT() {
	Node* curNode = head;//첫번째 노드부터 차례로 출력

	while (curNode != NULL) {
		cout << curNode->getValue() << endl;
		curNode = curNode->getNext();
	}
	cout << "Number of nodes in the list: " << size << endl;
}

void List::DELETE(int value) {
	Node* curNode = head;
	//변수 느낌
	Node* prevNode = NULL;
	Node* delNode = NULL;

	while (curNode != NULL) {//노드에 데이터가 있을 때
		if (curNode->getValue() == value)//지우고 싶은 값일 때 while문 탈출
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
	string command;
	int num = 0;
	//int index = 0;

	List* valueList = new List;

	while (1) {
		cout << "Enter Command : ";
		cin >> command;
		if (command == "insert") {
			cin >> num;
			valueList->INSERT(num);
			//index++;
		}

		else if (command == "find") {
			cin >> num;
			valueList->FIND(num);
		}

		else if (command == "delete") {
			cin >> num;
			valueList->DELETE(num);
		}

		else if (command == "print") {
			valueList->PRINT();
		}

		else if (command == "quit")
			break;

		else
			continue;
	}
	return 0;
}