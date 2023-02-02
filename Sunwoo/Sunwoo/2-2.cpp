#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;


#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif


class animal {
private:
	char name[10];
	int year = 0;
	char species[100];
public:
	animal() {};
	void save(char* name, int age, char* species);
	char* getName();
	int getAge();
	char* getSpecies();
};

void animal::save(char* name, int age, char* species)
{
	strcpy(this->name, name);
	this->year = age;
	strcpy(this->species, species);
}
char* animal::getName()
{
	return this->name;
}
int animal::getAge()
{
	return this->year;
}
char* animal::getSpecies()
{
	return this->species;
}


class zoo {
private:
	class animal* animal_list[100];
	int size = 0;
public:
	void save(char* name, int age, char* species);
	void print(int i);
	bool find(int i, char* species);
	~zoo();
};

void zoo::save(char* name, int age, char* species)
{
	animal_list[size] = new animal;
	animal_list[size]->save(name, age, species);
	size++;
};
void zoo::print(int i)
{
	cout << "----------" << i << "----------" << endl;
	cout << "Name :" << animal_list[i]->getName() << endl;
	cout << "Year :" << animal_list[i]->getAge() << endl;
	cout << "Species :" << animal_list[i]->getSpecies() << endl;
	cout << "---------------------" << endl;
}
bool zoo::find(int i, char* species)
{
	if (strcmp(animal_list[i]->getSpecies(), species) == 0)
	{
		return 1;
	}
	else
		return 0;
}
zoo::~zoo() {
	for (int i = 0; i < this->size; i++)
		delete[] animal_list[i];
}

int main()
{
	char command[20], name[10], species[100];
	int age, i, cnt = 0;
	zoo* Zoo = new zoo;

	while (1)
	{
		cout << "Please Enter Any Command(new_animal,print_all,print_species,exit) :";
		cin >> command;
		if (strcmp(command, "new_animal") == 0)
		{
			cin >> name >> age >> species;
			// 데이터 저장 멤버함수 호출; name, age, species 전달
			Zoo->save(name, age, species);
			cnt++;
		}
		else if (strcmp(command, "print_all") == 0)
		{
			cout << "------print_all------" << endl;
			for (i = 0; i < cnt; i++)
				Zoo->print(i);
			cout << "---------------------" << endl;
		}
		else if (strcmp(command, "print_species") == 0)
		{
			int same = 0;
			cin >> species;
			cout << "------print_species------" << endl;
			// 종 개수 세는 멤버함수 호출, species 전달
			for (i = 0; i < cnt; i++)
				if (Zoo->find(i, species))
				{
					Zoo->print(i);
					same++;
				}
			cout << "Number of Species is :" << same << endl;
			cout << "---------------------" << endl;
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else 
			continue;
	}

	_CrtDumpMemoryLeaks();

	return 0;
}