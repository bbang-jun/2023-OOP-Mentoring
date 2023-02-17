#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Node {
private:
	int number;
	char name[10];
	Node* next;
	Node* prev;
public:
	Node() {
		number = 0;
		this->next = NULL;
		this->prev = NULL;
		
	}
	void setinfo(int number, char* name) { 
		this->number = number;
		strcpy(this->name, name);
	}
	int getnumber() { return this->number;}
	void setnext(Node* nextnode) { this->next = nextnode; }
	Node* getnext() { return this->next;}
	void setprev(Node* prevnode) { this->prev = prevnode; }
	Node* getprev() { return this->prev; }
	char* getname() { return this->name; }
	
};

class List {
private:
	Node* head;
	int size; //길이
	Node* tail;
public:
	List() {
		this->head = NULL;
		this->tail = NULL;
		size = 0;
	}
	~List() {
		Node* curNode = head;
		Node* delNode = NULL;
		while (curNode != NULL) {
			delNode = curNode;
			curNode = curNode->getnext();
			delete delNode;
		}
	}
	void INSERT(int number, char* name);
	void PRINT();
	void PRINT_REVERSE();
	void SORT_BY_NAME();
	void SORT_BY_ID();
	void DELETE(int number);

};

void List::INSERT(int number, char* name) { // 완성
	Node* newNode = new Node;
	Node* curNode = head;
	Node* prevNode = NULL;
	newNode->setinfo(number, name);

	if (head == NULL) { //head가 없는 경우
		tail = head = newNode;
		this->size++;
	} 
	else { //head가 있는 경우
		if (curNode->getnext() == NULL) //tail일에 삽입하는 경우
		{
			if (curNode->getnumber() < number)
			{
				curNode->setnext(newNode);
				tail = curNode->getnext();
			}
			else if (curNode->getnumber() == number)
			{
				cout << "중복된 ID입니다";
				delete newNode;
			}
		}
		else // 중간에 삽입하는 경우
		{
			while (curNode->getnumber() < number)
			{
				prevNode = curNode;
				curNode = curNode->getnext();
				if(curNode->getnumber()>number)
				{
					prevNode->setnext(newNode);
					newNode->setnext(curNode);
				}
				else if (curNode->getnumber() == number)
				{
					cout << "중복된 ID입니다";
					delete newNode;
				}
			}
		}

	}
		
}
void List::PRINT() { //완성
	Node* curNode = head;
	while (curNode != NULL) {
		cout << curNode->getnumber() << curNode->getname() << endl;
		curNode = curNode->getnext();
	}
	cout << curNode->getnumber() << curNode->getname() << endl;
}
void List::PRINT_REVERSE() { //완성
	Node* curNode = tail;
	Node* prevNode = curNode->getprev();
	while (prevNode != head){
		cout << curNode->getnumber() << curNode->getname() << endl;
		curNode = prevNode;
		prevNode = curNode->getprev();
	}
	if (prevNode == head)
	{
		cout << curNode->getnumber() << curNode->getname() << endl;
		cout << prevNode->getnumber() << prevNode->getname() << endl;
	}
}
void List::SORT_BY_NAME() { //완성
	Node* curNode = head;
	Node* nextNode = curNode->getnext();
	Node* prevNode = NULL;
	while (nextNode != NULL)
	{
		if (strcmp(curNode->getname(), nextNode->getname())>0)
		{
			prevNode = curNode;
			curNode = nextNode;
		}
		else
		{
			curNode->setnext(nextNode->getnext());
			nextNode->setnext(curNode);
			prevNode = nextNode;
		}
		nextNode = curNode->getnext();
	}
	
}
void List::SORT_BY_ID() { //완성
	Node* curNode = head;
	Node* nextNode = curNode->getnext();
	Node* prevNode = NULL;
	while (nextNode != NULL)
	{
		if (curNode->getnumber() < nextNode->getnumber()) 
		{
			prevNode = curNode;
			curNode = nextNode;
		}
		else
		{
			curNode->setnext(nextNode->getnext());
			nextNode->setnext(curNode);
		}
		nextNode = curNode->getnext();
	}


}


void List::DELETE(int number) {
	Node* curNode = head;
	Node* prevNode = NULL;
	Node* delNode = NULL;

	while (curNode != NULL) {
		if (curNode->getnumber() == number)
			break;
		prevNode = curNode;
		curNode = curNode->getnext();
	}

	if (curNode == head) {
		if (head->getnext() == NULL) { // list에 head만 존재하는 경우
			delNode = head;
			delete head;
			head = NULL;
			this->size--;
		}
		else { // list에 head 외에 다른 노드들도 존재하는 경우
			delNode = head;
			head = head->getnext();
			delete delNode;
			this->size--;
		}
	}
	else if (curNode == tail) { // tail삭제
		delNode = tail;
		tail = prevNode;
		delete delNode;
		tail->setnext(NULL);
		this->size--;
	}
	else {
		delNode = curNode;
		prevNode->setnext(curNode->getnext());
		delete delNode;
		this->size--;
	}
}
int main(void) {
	char command;
	char* name = new char[10];
	int number = 0;
	List* info = new List;

	while (1)
	{
		cout << "Please Enter command(1 : insert, 2: print, 3: print_reverse, 4: sort_by_name, 5: sort_by_ID, 6: delete, 7 : exit) : ";
		cin >> command;
		if (command == '1')
		{
			cin >> number >> name;
			info->INSERT(number, name);
		}
		else if (command == '2') {
			info->PRINT();
		}
		else if (command == '3') {
			info->PRINT_REVERSE();
		}
		else if (command == '4') {
			info->SORT_BY_NAME();
		}
		else if (command == '5') {
			info->SORT_BY_ID();
		}
		else if (command == '6') {
			cin >> number;
			info->DELETE(number);
		}
		else if (command == '7')
			break;

	}
	delete info;
}
