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

class Stack {//스택 클래스 생성
private:
	Node* top;
	Node* bottom;
	int size;//스택 사이즈
public:
	Stack() {//자동생성자
		this->top = NULL;//초기화
		this->bottom = NULL;
		this->size = 0;
	}
	bool isEmpty();//스택 데이터값 존재 유무 판단
	void push(int data);
	void pop();
	void printStack();
};

bool Stack::isEmpty() {
	if (this->size == 0)//스택에 데이터값이 없다면
		return true;
	else//데이터값이 있다면
		return false;
}

void Stack::push(int data) {//삽입
	Node* newNode = new Node;
	newNode->setValue(data);//뉴노드 데이터값 저장

	if (isEmpty()) {//true (데이터값 존재 X)
		top = bottom = newNode;//처음 노드 삽입
		this->size++;
	}
	else {//false (데이터값 존재함)
		top->setNext(newNode);//순방향 노드 연결
		newNode->setPrev(top);//역방향 노드 연결
		top = top->getNext();//top 위치 변경 (한 칸 위로)
		this->size++;//사이즈 증가
	}
}

void Stack::pop() {//삭제
	if (isEmpty()) {//데이터값 존재 X
		cout << "stack underflow" << endl;//stack underflow
	}
	else {
		if (this->size == 1) {//데이터값 1개 존재
			delete bottom;//bottom = top
			bottom = NULL;//쓰레기값 방지
			top = NULL;
			this->size--;//size=0
			cout << "stack underflow" << endl;//이젠 데이터값 존재 X
			return;
		}
		Node* popNode = top;//삭제할 노드
		top = top->getPrev();//top 위치 변경  (한 칸 아래로)
		delete popNode;//노드 삭제
		top->setNext(NULL);//쓰레기값 방지
		this->size--;
	}
}

void Stack::printStack() {//출력
	Node* curNode = top;

	while (curNode != NULL) {
		cout << curNode->getValue() << endl;//top부터 한 칸씩 내려가면서 출력
		curNode = curNode->getPrev();//전 노드로 이동
	}
	cout << "Data count: " << this->size;
	cout << endl;
}

int main(void) {

	string command;
	int data = 0;
	Stack* stack = new Stack;//스택 동적 할당

	while (1) {
		cout << "Please Enter Command(push, pop): ";
		cin >> command;

		if (command == "push") {
			cin >> data;
			stack->push(data);
			stack->printStack();
		}

		else if (command == "pop") {
			stack->pop();
			stack->printStack();
		}
	}

	delete stack;//동적 할당 해제

	return 0;
}