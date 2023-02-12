#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

// Node 클래스 선언
class Node
{
private:
	int ID;
	string name;
	Node* prev;
	Node* next;
public:
	Node() // Node 초기화
	{
		this->ID = 0;
		this->name = "";
		this->prev = NULL;
		this->next = NULL;
	}
	void setValue(int input, string name) { this->ID = input; this->name = name; } // ID와 이름 저장
	int getID() { return this->ID; } // ID getter
	string getName() { return this->name; } // 이름 getter
	void setPrev(Node* prevNode) { this->prev = prevNode; } // 이전 노드로 설정
	void setNext(Node* nextNode) { this->next = nextNode; } // 다음 노드로 설정
	Node* getPrev() { return this->prev; } // 이전 노드 가져오기
	Node* getNext() { return this->next; } // 다음 노드 가져오기
};

// List 클래스 선언
class List
{
private:
	Node* head;
	Node* tail;
	int size;
public:
	List() // List 초기화
	{
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
	~List() // List 소멸자
	{
		Node* curNode = head;
		Node* delNode = NULL;
		while (curNode != NULL) // 앞쪽 노드부터 순차적으로 삭제
		{
			delNode = curNode;
			curNode = curNode->getNext();
			delete delNode;
		}
		delNode = NULL;
	}
	Node* FIND(int input); // input과 노드에 저장된 ID가 같으면 해당 노드 반환
	void INSERT(int input, string name); // ID와 이름을 링크드 리스트에 삽입
	void PRINT(); // 출력
	void PRINT_REVERSE(); // 역순으로 출력
	void SORT_NAME(); // 이름으로 정렬
	void SORT_ID(); // ID로 정렬
	void DEL(int input); // input과 동일한 ID를 가진 노드를 삭제
};

Node* List::FIND(int input)
{
	Node* curNode = head;

	while (curNode != NULL) // 모든 노드를 확인하는 반복문
	{
		if (curNode->getID() == input) // input과 노드에 저장된 ID가 같으면
			return curNode; // 해당 노드 반환
		curNode = curNode->getNext(); // 모든 노드를 확인하는 반복문
	}
}

void List::INSERT(int input, string name)
{
	Node* curNode = head;

	if (FIND(input)!=NULL) // 중복되는 ID가 있으면
		return; // 해당 메서드 탈출

	Node* newNode = new Node;
	newNode->setValue(input, name);

	if (head == NULL) // 저장된 노드가 하나도 없으면
	{
		tail = head = newNode; // 새로운 노드를 head이자 tail로 선언
		this->size++; // 노드의 갯수 1 증가
	}
	else // 이미 저장된 노드가 하나라도 있으면
	{
		while (curNode != NULL) // 모든 노드를 확인하는 반복문
		{
			if (curNode->getID() > input) // 노드에 저장된 ID가 input보다 크면
			{
				if (curNode == head) // 해당 노드가 head이면 맨 앞에 추가하고 size 1 증가
				{
					newNode->setNext(curNode);
					curNode->setPrev(newNode);
					head = newNode;
					this->size++;
					return;
				}
				else // 해당 노드가 head가 아니면 새로운 노드를 추가
				{ // 추가된 새로운 노드를 앞뒤로 next, prev 노드 연결
					curNode->getPrev()->setNext(newNode);
					newNode->setPrev(curNode->getPrev());
					newNode->setNext(curNode);
					curNode->setPrev(newNode);
					this->size++; // size 1 증가
					return;
				}
			}
			curNode = curNode->getNext();
		}

		// 노드에 저장된 ID가 input보다 큰 노드가 없으면 맨 뒤에 노드 추가
		tail->setNext(newNode); 
		newNode->setPrev(tail);
		tail = tail->getNext();
		this->size++;
	}
}

void List::PRINT()
{
	Node* curNode = head;

	while (curNode != NULL) // 모든 노드에 접근하여 getNext 메서드로 하나씩 출력
	{
		cout << curNode->getID() << " " << curNode->getName() << endl;
		curNode = curNode->getNext();
	}
}

void List::PRINT_REVERSE()
{
	Node* curNode = tail;

	while (curNode != NULL) // 모든 노드에 접근하여 getPrev 메서드로 하나씩 출력
	{
		cout << curNode->getID() << " " << curNode->getName() << endl;
		curNode = curNode->getPrev();
	}
}

void List::SORT_NAME()
{
	int temp_ID; // 임시 ID 및
	string temp_name; // 임시 이름 선언
	Node* curNode = head;
	Node* lastNode = tail;

	// 버블 정렬 구현
	while (head != lastNode) // 마지막 노드가 head가 아니면 계속 반복
	{
		curNode = head;
		while (curNode != lastNode) // 마지막 노드가 현재 노드가 아니면 반복
		{
			if (curNode->getName() > curNode->getNext()->getName()) // 현재 노드에 저장된 이름과 다음 노드에 저장된 이름 비교
			{ // 현재 노드에 저장된 이름이 더 크면 오름차순 정렬을 위해 변경
				temp_ID = curNode->getID();
				temp_name = curNode->getName();
				curNode->setValue(curNode->getNext()->getID(), curNode->getNext()->getName());
				curNode->getNext()->setValue(temp_ID, temp_name);
			}
			curNode = curNode->getNext();
		}
		lastNode = lastNode->getPrev(); // 마지막 노드를 getPrev 메서드로 한 노드씩 앞으로 이동
	}

	PRINT(); // 정렬된 노드 출력
}

void List::SORT_ID()
{
	int temp_ID; // 임시 ID 및
	string temp_name; // 임시 이름 선언
	Node* curNode = head;
	Node* lastNode = tail;

	//버블 정렬 구현 SORT_NAME 메서드에서 이름 대신 ID로 비교한다는 것 빼고 동일
	while (head != lastNode)
	{
		curNode = head;
		while (curNode != lastNode)
		{
			if (curNode->getID() > curNode->getNext()->getID())
			{
				temp_ID = curNode->getID();
				temp_name = curNode->getName();
				curNode->setValue(curNode->getNext()->getID(), curNode->getNext()->getName());
				curNode->getNext()->setValue(temp_ID, temp_name);
			}
			curNode = curNode->getNext();
		}
		lastNode = lastNode->getPrev();
	}
}

void List::DEL(int input) 
{
	Node* curNode = FIND(input);
		
	if (curNode == head) // 삭제하는게 첫번째 노드일 경우
	{
		if (curNode->getNext() == NULL) // 첫번째 노드 하나밖에 없는 경우
		{
			delete head; // 메모리 먼저 삭제
			head = NULL; // 변수 삭제, 서순 주의
		}
		else // 첫번째 노드를 삭제하면서 노드가 여러개일 경우
		{
			head = curNode->getNext(); // head를 다음 노드로 지정 후
			delete curNode; // 메모리와 변수 삭제
			curNode = NULL;
		}
		this->size--; // size 1 감소
	}
	else if (curNode == tail) // 삭제하는 게 마지막 노드일 경우
	{
		tail = curNode->getPrev(); // tail을 삭제하려는 노드 전 노드로 변경
		delete curNode; // 메모리와 변수 삭제
		curNode = NULL;
		this->size--; // size 1 감소
	}
	else // 중간 삽입
	{
		curNode->getPrev()->setNext(curNode->getNext()); // 현재 노드를 기준으로 앞 뒤 노드끼리 연결
		curNode->getNext()->setPrev(curNode->getPrev());
		delete curNode; // 현재 노드 삭제
		curNode = NULL;
		this->size--;
	}
}

int main()
{
	int command = 0, input;
	string name;
	List* Linked_List = new List;

	// command에 따라 다른 메서드 호출
	while (command != 7)
	{
		cout << "Please Enter Command (1:insert, 2:print, 3:print_reverse, 4:sort_by_name, 5:sort_by_ID, 6:delete, 7:exit) :";
		cin >> command;
		if (command == 1)
		{
			cin >> input >> name;
			Linked_List->INSERT(input, name);
		}
		else if (command == 2)
		{
			Linked_List->PRINT();
		}
		else if (command == 3)
		{
			Linked_List->PRINT_REVERSE();
		}
		else if (command == 4)
		{
			Linked_List->SORT_NAME();
		}
		else if (command == 5)
		{
			Linked_List->SORT_ID();
		}
		else if (command == 6)
		{
			cin >> input;
			Linked_List->DEL(input);
		}
		else if (command == 7)
		{
			break;
		}
		else
			continue;
	}

	// 동적할당 해제
	delete Linked_List;

	return 0;
}