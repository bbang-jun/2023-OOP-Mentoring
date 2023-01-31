#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Student_info
{
private:
	char name[10];
	int age = 0;
	char university[100];
	char major[100];

public:
	Student_info() {};
	Student_info(char* name, int age, char* univ, char* major)
	{
		name = new char[10];
		strcpy(this->name, name);
		this->age = age;
		univ = new char[100];
		strcpy(this->university, univ);
		major = new char[10];
		strcpy(this->major, major);
	};
	bool find(char* name);
	void print()
	{
		cout << "----------print----------" << endl;
		cout << "Name : " << this->name << endl;
		cout << "University : " << this->university << endl;
		cout << "Major : " << this->major << endl;
		cout << "----------print----------" << endl;
	};
	void change(char* name, int age, char* univ, char* major);
};

int main(void)
{
	char command[10] = "", name[10], univ[100], major[100];
	int age;
	Student_info* student = new Student_info[10];

	cout << "Please Enter Command(insert, find, change, print, exit) :";
	cin >> command;






	cout << "-------------------------" << endl;
}