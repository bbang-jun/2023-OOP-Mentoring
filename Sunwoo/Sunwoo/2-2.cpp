#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class animal {
private:
	string name;
	int year = 0;
	string species;
public:
	void save(string name, int age, string species);
	string getName();
	int getAge();
	string getSpecies();
};

// 동물 저장 멤버메서드; 이름과 나이 종을 각각의 객체에 저장함
void animal::save(string name, int age, string species)
{
	this->name = name;
	this->year = age;
	this->species = species;
}
// 이름 getter; 객체에 저장된 이름을 반환함
string animal::getName()
{
	return this->name;
}
// 나이 getter; 객체에 저장된 나이를 반환함
int animal::getAge()
{
	return this->year;
}
// 종 getter; 객체에 저장된 종을 반환함
string animal::getSpecies()
{
	return this->species;
}


class zoo {
private:
	class animal* animal_list[100];
	int size = 0;
public:
	void save(string name, int age, string species);
	void print(int i);
	bool find(int i, string species);
	~zoo();
};

// zoo 객체에서 animal 객체를 동적할당
void zoo::save(string name, int age, string species)
{
	animal_list[size] = new animal;
	animal_list[size]->save(name, age, species);
	size++;
};
// zoo클래스에서 animal 클래스에 접근하여 저장된 정보를 출력함
void zoo::print(int i)
{
	cout << "----------" << i << "----------" << endl;
	cout << "Name :" << animal_list[i]->getName() << endl;
	cout << "Year :" << animal_list[i]->getAge() << endl;
	cout << "Species :" << animal_list[i]->getSpecies() << endl;
	cout << "---------------------" << endl;
}
// 입력받은 종과 저장된 종이 같으면 1을 반환하는 메서드
bool zoo::find(int i, string species)
{
	if (animal_list[i]->getSpecies() == species)
	{
		return 1;
	}
	else
		return 0;
}
// 소멸자. 프로그램이 종료될 때 지정된 동적할당 해제
zoo::~zoo() {
	for (int i = 0; i < this->size; i++)
		delete[] animal_list[i];
}

int main()
{
	string command, name, species;
	int age, i, cnt = 0;
	zoo* Zoo = new zoo;

	while (1)
	{
		cout << "Please Enter Any Command(new_animal,print_all,print_species,exit) :";
		cin >> command;
		if (command == "new_animal") // command가 new_animal이면
		{
			cin >> name >> age >> species;
			// 데이터 저장 멤버함수 호출; name, age, species 전달
			Zoo->save(name, age, species);
			cnt++;
		}
		else if (command == "print_all") // command가 print_all이면
		{
			cout << "------print_all------" << endl;
			for (i = 0; i < cnt; i++) // 각각의 객체에 접근하여 zoo클래스의 print메서드 호출
				Zoo->print(i);
			cout << "---------------------" << endl;
		}
		else if (command == "print_species") // command가 print_species이면
		{
			int same = 0; // 같은 종을 세는 변수
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
		else if (command == "exit") // command가 exit이면 무한반복문 탈출
			break;
		else // 어느 것도 해당되지 않으면 반복
			continue;
	}

	delete Zoo; // 메모리 해제

	return 0;
}