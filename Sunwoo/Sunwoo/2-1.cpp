#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Student_info // 문제 기본 제공 class
{
private:
	char name[10];
	int age = 0;
	char university[100];
	char major[100];

public:
	Student_info(char* name, int age, char* univ, char* major);
	bool find(char* name);
	void print(); 
	void change(char* name, int age, char* univ, char* major);
};

Student_info::Student_info(char* name, int age, char* univ, char* major)
{ // 입력받은 값을 각 객체 멤버에 저장
	strcpy(this->name, name); 
	this->age = age;
	strcpy(this->university, univ);
	strcpy(this->major, major);
}
bool Student_info::find(char* name)
{ // 각 객체에서 이름 멤버를 비교하여 같으면 1 반환, 아니면 0 반환
	if (strcmp(this->name, name) == 0)
		return 1;
	else
		return 0;
}
void Student_info::print()
{ // 각 객체의 저장된 멤버 데이터들을 출력
	cout << "Name : " << this->name << endl;
	cout << "Age : " << this->age << endl;
	cout << "University : " << this->university << endl;
	cout << "Major : " << this->major << endl;
	cout << "-------------------------" << endl;
}
void Student_info::change(char* name, int age, char* univ, char* major)
{ // 입력받은 값을 해당 객체 멤버에 저장, Student_info 생성자와 구성 요소 동일
	strcpy(this->name, name);
	this->age = age;
	strcpy(this->university, univ);
	strcpy(this->major, major);
}

int main(void)
{
	char command[10] = "", temp_name[10], name[10], univ[100], major[100];
	int i, age, cnt = 0;
	Student_info* student[10]; // 정적 포인터 배열 객체 생성

	while (1)
	{
		cout << "Please Enter Command(insert, find, change, print, exit) :";
		cin >> command;

		if (strcmp(command, "insert") == 0)
		{ // command가 insert이면 이름 나이 
			cin >> name >> age >> univ >> major;
			student[cnt] = new Student_info(name, age, univ, major);
			cnt++;
		}
		else if (strcmp(command, "find") == 0)
		{ // command가 find이면 저장된 객체들의 find 멤버 함수 호출
			cout << "----------find----------" << endl;
			cin >> name;
			for (i = 0; i < cnt; i++)
			{
				if (student[i]->find(name)) // 동일한 이름을 찾으면
					student[i]->print(); // print 멤버함수로 출력
			}
		}
		else if (strcmp(command, "change") == 0)
		{ // command가 change면 순차적으로 객체들에 접근하여
			cin >> temp_name >> name >> age >> univ >> major;
			for (i = 0; i < cnt; i++)
				if (student[i]->find(temp_name))
				{ // find 멤버함수를 통해 같은 name을 가진 객체를 확인하여 데이터 변경
					student[i]->change(name, age, univ, major);
					break;
				}			
		}
		else if (strcmp(command, "print") == 0)
		{ // command가 print이면 for문으로 print멤버함수를 반복호출하여 데이터 출력
			cout << "----------print----------" << endl;
			for (i = 0; i < cnt; i++)
			{
				student[i]->print();
			}
			cout << "-------------------------" << endl;
		}
		else if (strcmp(command, "exit") == 0) // command가 exit이면 무한반복문을 나감
			break;
		else // 어떤 경우에도 해당되지 않으면 반복문 재실행
			continue;
	}
	
	for (i = 0; i < cnt; i++) // 동적할당 해제
		delete[] student[i];

	cout << "-------------------------" << endl;

	return 0;
}