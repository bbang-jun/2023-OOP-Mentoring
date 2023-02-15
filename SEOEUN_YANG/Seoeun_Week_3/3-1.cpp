#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int ID;//아이디
	string name;//이름
	Node* prev;//이전 노드 가리킴
	Node* next;//다음 노드 가리킴
public:
	Node() {//생성자
		ID = 0;//초기화
		name = "";
		this->next = NULL;//포인터 초기화
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

	bool FIND(int ID);//중복 검색
	void INSERT(int ID,string name);//저장
	void PRINT();//출력
	void PRINT_REV();//역출력
	void SORT_NAME();//이름 오름차순 정렬
	void SORT_ID();//아이디 오름차순 정리
	void DELETE(int ID);//삭제
};

bool List::FIND(int ID) {//중복 검색
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
	Node* newNode = new Node;//새 노드 생성
	newNode->setID(ID);
	newNode->setname(name);//노드 데이터 저장

	if (FIND(ID) == true) {//중복 제거
		return;//중복이라면 INSERT 함수 종료
	}

	if (head == NULL) {//처음
		tail = head = newNode;
		this->size++;
		return;
	}

	else {//리스트 연결
		while (curNode != NULL) {//저장할 위치 찾기
			if (curNode->getID() > ID) {//위치 찾음
				if (curNode == head) {//head 앞에 삽입해야 할 경우
					newNode->setNext(curNode);//새 노드 순방향 연결
					curNode->setPrev(newNode);//역방향 연결
					head = newNode;//head 재설정
					this->size++;
					return;//INSERT 끝
				}
				else {//리스트 중간 삽입 //curNode 앞에 newNode 삽입
					//curNode 전 노드와 newNode 연결
					curNode->getPrev()->setNext(newNode);//curNode의 전노드의 next 포인터 new노드로 연결
					newNode->setPrev(curNode->getPrev());//newNode의 prev, curNode 전 노드로 연결
					//newNode와 curNode 연결
					curNode->setPrev(newNode);
					newNode->setNext(curNode);
					this->size++;
					return;
				}
			}
			curNode = curNode->getNext();//위치 탐색
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
		curNode = curNode->getPrev();//전 노드로 이동
	}
}

void List::SORT_NAME() {
	int temp_ID = 0;
	string temp_name = "";
	Node* Node_1 = head;
	Node* Node_2 = tail;

	while (head != Node_2) {//node 2개 이상
		Node_1 = head;//초기화
		while (Node_1 != Node_2) {//처음부터 좌아악 움직이면서 정렬
			if (Node_1->getname() > Node_1->getNext()->getname()) {//이름 크기
				temp_ID = Node_1->getID();//swap
				temp_name = Node_1->getname();
				Node_1->setID(Node_1->getNext()->getID());
				Node_1->setname(Node_1->getNext()->getname());
				Node_1->getNext()->setID(temp_ID);
				Node_1->getNext()->setname(temp_name);
			}
			Node_1 = Node_1->getNext();//다음 노드로 이동
		}
		Node_2 = Node_2->getPrev();//안의 while문 한 번 돌면 이름 제일 큰 게 맨 마지막에 저장됨 그래서 정렬 다시 안해도 됨
	}

	PRINT();
}

void List::SORT_ID() {
	int temp_ID = 0;
	string temp_name = "";
	Node* Node_1 = head;
	Node* Node_2 = tail;

	while (head != Node_2) {//node 2개 이상
		Node_1 = head;
		while (Node_1 != Node_2) {
			if (Node_1->getID() > Node_1->getNext()->getID()) {
				temp_ID = Node_1->getID();
				temp_name = Node_1->getname();
				Node_1->setID(Node_1->getNext()->getID());
				Node_1->setname(Node_1->getNext()->getname());
				Node_1->getNext()->setID(temp_ID);
				Node_1->getNext()->setname(temp_name);
			}
			Node_1 = Node_1->getNext();
		}
		Node_2 = Node_2->getPrev();
	}
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
	if (curNode == head) {//head 삭제
		if (head->getNext() == NULL) {//head만 존재
			delNode = head;
			delete delNode;
			this->size--;//-> size=0
			head=NULL;
		}
		else {//노드 2개 이상
			delNode = head;
			head = head->getNext();//head 다음 노드를 head로 설정
			delete delNode;
			this->size--;
		}
	}
	else if (curNode == tail) {//tail 삭제
		delNode = tail;
		tail = prevNode;//tail 전 노드 tail로 설정
		delete delNode;
		tail->setNext(NULL); // 팁2 //쓰레기값 방지 (tail 항상 NULL 가리킴)
		this->size--;
	}
	else {//중간 삭제
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
	List* valueList = new List;//동적할당
	
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
			valueList->SORT_NAME();
		}

		else if (command == 5) {
			valueList->SORT_ID();
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

	delete valueList;//동적할당 해제
	return 0;
}