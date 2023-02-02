#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class animal {
private:
	char name[10];
	int year = 0;
	char species[100];
public:
	animal() {  };
	void save(char* name, int age, char* species)
	{
		strcpy(this->name, name);
		this->year = age;
		strcpy(this->species, species);
	}
};

class zoo {
private:
	class animal* animal_list[100];
	int size = 0;
public:
	zoo() {};
	void save(char* name, int age, char* species)
	{
		animal_list[size] = new animal;
		animal_list[size]->save(name, age, species);
		size++;
	};
	/*zoo() {
		animal* Animal[100];
	}
	void save();*/
};

int main()
{
	char command[20], name[10], species[100];
	int age, cnt = 0;
	zoo* Zoo = new zoo;

	while (1)
	{
		cout << "Please Enter Any Command(new_animal,print_all,print_species,exit) :";
		cin >> command;
		if (strcmp(command, "new_animal") == 0)
		{
			cin >> name >> age >> species;
			// ������ ���� ����Լ� ȣ��, cnt, name, age, species ����
			Zoo->save(name, age, species);
			cnt++;
		}
		else if (strcmp(command, "print_all") == 0)
		{
			cout << "------print_all------" << endl;
			// ������� ����Լ� ȣ��, cnt ����
			cout << "---------------------" << endl;
		}
		else if (strcmp(command, "print_species") == 0)
		{
			cin >> species;
			cout << "------print_species------" << endl;
			// �� ���� ���� ����Լ� ȣ��, species ����
			cout << "---------------------" << endl;
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else 
			continue;
	}



	return 0;
}