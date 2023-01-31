#include <iostream>
#include <cstring>

using namespace std;
class Student_info {
private:
	char name[10];
	int age = 0;
	char university[100];
	char major[100];

public: // 값을 입력받아서 private에 저장
	Student_info() {};
	Student_info(char* name, int age, char* univ, char* major)
	{
		name = new char[10];
		strcpy(this->name, name);
		univ = new char[100];
		strcpy(this->university, univ);
		major = new char[100];
		strcpy(this->major, major);
		this->age = age;
	};
	bool find(char* name)
	{

	};
	void print()  //private의 저장된 것 출력
	{
		cout << "----------print----------";
		cout << "Name : " << name << endl;
		cout << "Age : " << age << endl;
		cout << "University : " << university << endl;
		cout << "Major : " << major << endl;
		cout << "-------------------------" << endl;
	};
	void change(char* name, int age, char* univ, char* major)
	{

	};
	~Student_info() {};

	int main (void)
	{
		Student_info* Student[10] = {};
		char input[10]; // 커맨드 저장
			// 클래스 메소드에 전달할 정보 저장
		char name1[10];
		int age1;
		char univ1[100];
		char major1[100];
		int i = 0;
		
		while (1) // 무한 반복
		{
			cout << "Please Enter Command(Insert, find, change, print, exit) : ";
			cin >> input; // 커맨드를 입력받음
			if (input == "insert") // insert인 경우
			{
				cin >> name1 >> age1 >> univ1 >> major1; // 정보를 모두 입력받음.
				Student[i] = new Student_info(name1,age1, univ1, major1);
				i++; // 다음 사람거
			}
			else if (input == "find")
			{

			}
			else if (input == "print")
			{

			}
			else if (input == "exit")
			{
				break;
			}
			else
			{
				cout << "Please Enter Command(insert, find, change, print, exit) : ";
				cin >> input; // 커맨드를 입력받음
			}
		}
	}
	};