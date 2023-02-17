#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int value;//데이터값
	Node* next;//전 노드 포인터
	Node* prev;//다음 노드 포인터

public:
	Node() {//자동생성자
		this->value = 0;//초기화
		this->next = NULL;
		this->prev = NULL;
	}
	void setValue(int data) { this->value = data; }
	int getValue() { return this->value; }
	void setNext(Node* nextNode) { this->next = nextNode; }
	Node* getNext() { return this->next; }
	void setPrev(Node* prevNode) { this->prev = prevNode; }
	Node* getPrev() { return this->prev; }
};

class Queue {//큐 클래스 생성
private:
	Node* front;//앞
	Node* rear;//뒤
	int size;//큐 길이
public:
	Queue() {//자동생성자
		this->front = NULL;//초기화
		this->rear = NULL;
		this->size = 0;
	}
	bool isEmpty();//데이터 존재 유무 확인
	void enqueue(int data);//삽입
	void dequeue();//삭제
	void printQueue();//출력
};

bool Queue::isEmpty() {
	if (this->size == 0)
		return true;
	else
		return false;
}

void Queue::enqueue(int data) {
	Node* newNode = new Node;
	newNode->setValue(data);

	if (isEmpty()) {
		front = rear = newNode;
		this->size++;
	}
	else {
		newNode->setNext(rear);//rear 뒤에 뉴노드 삽입
		rear->setPrev(newNode);//양방향 연결
		rear = newNode;//새 노드 rear로 설정
		Node* curNode = rear;
		while (curNode != NULL)
			curNode = curNode->getNext();//front 찾기
		curNode = front;
		this->size++;
	}
}

void Queue::dequeue() {
	if (isEmpty()) {//데이터 존재 X
		cout << "queue underflow";
	}
	else {
		if (this->size == 1) {
			delete rear;
			rear = NULL;//쓰레기값 방지
			front = NULL;
			this->size--;
			cout << "queue underflow";//이젠 데이터 없음
			return;
		}
		Node* dequeueNode = front;
		front = front->getPrev();//front 노드 이동 (한 칸 뒤로)
		delete dequeueNode;
		front->setNext(NULL);//쓰레기값 방지 (초기화)
		this->size--;
	}
}

void Queue::printQueue() {
	Node* curNode = rear;

	while (curNode != NULL) {//rear부터 노드 이동하면서 출력
		cout << curNode->getValue() << "    ";
		curNode = curNode->getNext();
	}
	cout << endl << "Data count: " << this->size << endl;
}

int main(void) {

	string command;
	int data = 0;
	Queue* queue = new Queue;//큐 동적 할당

	while (1) {
		cout << "Please Enter Command(enqueue, dequeue): ";
		cin >> command;

		if (command == "enqueue") {
			cin >> data;
			queue->enqueue(data);
			queue->printQueue();
		}

		else if (command == "dequeue") {
			queue->dequeue();
			queue->printQueue();
		}
	}

	delete queue;//동적 할당 해제

	return 0;
}