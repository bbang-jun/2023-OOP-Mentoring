#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Node
{
private:
	int ID;
	string name;
	Node* prev;
	Node* next;
public:
	Node()
	{
		this->ID = 0;
		this->name = "";
		this->prev = NULL;
		this->next = NULL;
	}
	void setValue(int input, string name) { this->ID = input; this->name = name; }
	int getID() { return this->ID; }
	string getName() { return this->name; }
	void setPrev(Node* prevNode) { this->prev = prevNode; }
	void setNext(Node* nextNode) { this->next = nextNode; }
	Node* getPrev() { return this->prev; }
	Node* getNext() { return this->next; }
};

class List
{
private:
	Node* head;
	Node* tail;
	int size;
public:
	List()
	{
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
	~List()
	{

	}
	void INSERT(int input, string name);
	void PRINT();
	void PRINT_REVERSE();
	void SORT_NAME();
	void SORT_ID();
};

void List::INSERT(int input, string name)
{
	Node* curNode = head;
	Node* newNode = new Node;
	newNode->setValue(input, name);

	if (head == NULL)
	{
		tail = head = newNode;
		this->size++;
	}
	else
	{
		while (curNode != NULL)
		{
			if (curNode->getID() == input)
				return;
			else if (curNode->getID() > input)
			{
				if (curNode == head)
				{
					newNode->setNext(curNode);
					curNode->setPrev(newNode);
					head = newNode;
					this->size++;
					return;
				}
				else
				{
					curNode->getPrev()->setNext(newNode);
					newNode->setPrev(curNode->getPrev());
					newNode->setNext(curNode);
					curNode->setPrev(newNode);
					this->size++;
					return;
				}
			}
			curNode = curNode->getNext();
		}

		tail->setNext(newNode);
		newNode->setPrev(tail);
		tail = tail->getNext();
		this->size++;
	}
}

void List::PRINT()
{
	Node* curNode = head;

	while (curNode != NULL)
	{
		cout << curNode->getID() << " " << curNode->getName() << endl;
		curNode = curNode->getNext();
	}
}

void List::PRINT_REVERSE()
{
	Node* curNode = tail;

	while (curNode != NULL)
	{
		cout << curNode->getID() << " " << curNode->getName() << endl;
		curNode = curNode->getPrev();
	}
}

void List::SORT_NAME()
{
	int temp_ID;
	string temp_name;
	Node* curNode = head;
	Node* lastNode = tail;

	while (head != lastNode)
	{
		curNode = head;
		while (curNode != lastNode)
		{
			if (curNode->getName() > curNode->getNext()->getName())
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

	PRINT();
}

void List::SORT_ID()
{
	int temp_ID;
	string temp_name;
	Node* curNode = head;
	Node* lastNode = tail;
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

int main()
{
	int command = 0, input;
	string name;
	List* Linked_List = new List;

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
	}
}