#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int ID;
	char name[100];
	Node* next;  // 다음 노드를 가리키는 포인터
public:
	Node() {//생성자
		ID = 0;//초기화
		strcpy(this->name, "");
		this->next = NULL;//초기화
	}
	void setID(int ID) { this->ID = ID; }//데이터 저장
	int getID() { return this->ID; }//데이터 불러옴
	void setname(char* name) { strcpy(this->name, name); }
	char* getname() { return this->name; }
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
	void INSERT(int ID,char* name);
	void PRINT();
	void FIND(int value);
	void DELETE(int value);
};

void List::INSERT(int ID, char* name) {
	Node* curNode = head;
	Node* newNode = new Node;
	newNode->setID(ID);
	newNode->setname(name);//노드 데이터 저장

	if (head == NULL) {
		tail = head = newNode;
		this->size++;
	}

	else {
		tail->setNext(newNode);
		tail = tail->getNext();
		this->size++;
	}
}

void List::PRINT() {
	Node* curNode = head;//첫번째 노드부터 차례로 출력

	while (curNode != NULL) {
		cout << curNode->getID() << " " << curNode->getname() << endl;
		curNode = curNode->getNext();
	}
}

int main(void) {
	int command;
	int ID = 0;
	char name[100];

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
			//cin >> num;
			//valueList->DELETE(num);
		}

		else if (command == 4) {
			valueList->PRINT();
		}

		else if (command == 5) {
			valueList->PRINT();
		}

		else if (command == 6) {
			valueList->PRINT();
		}

		else if (command == 7)
			break;

		else
			continue;
	}
	return 0;
}