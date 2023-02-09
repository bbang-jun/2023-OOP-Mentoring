#define _CRT_SECURE_NO_WARNINGS
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
	Student_info(char* name, int age, char* univ, char* major)
	{
		strcpy(this->name, name);
		strcpy(this->university, univ);
		strcpy(this->major, major);
		this->age = age;
	};
	bool find(char* name)
	{
		if (strcmp(this->name, name) == 0)
			return 0;
		else
			return 1;
	};
	void print()  //private의 저장된 것 출력
	{
		cout << "----------print----------" << endl;
		cout << "Name : " << this->name << endl;
		cout << "Age : " << this->age << endl;
		cout << "University : " << this->university << endl;
		cout << "Major : " << this->major << endl;
		cout << "-------------------------" << endl;
	};
	void change(char* name, int age, char* univ, char* major)
	{
			strcpy(this->name, name);
			strcpy(this->university, univ);
			strcpy(this->major, major);
			this->age = age;
	};
	~Student_info() {
	};
	};
	int main (void)
	{
		Student_info* Student[10] = {0};
		char input[10] ={0}; // 커맨드 저장
			// 클래스 메소드에 전달할 정보 저장
		char mainname[10] = { 0 };
		int mainage = 0;
		char mainuniv[100] = { 0 };
		char mainmajor[100] = { 0 };
		char findname[10] = { 0 };
		int i = 0;
		
		while (1) // 무한 반복
		{
			cout << "Please Enter Command(insert, find, change, print, exit) : ";
			cin >> input; // 커맨드를 입력받음
			if (strcmp(input,"insert")==0) // insert인 경우
			{	
				cin >> mainname >> mainage >> mainuniv >> mainmajor;
				Student[i] = new Student_info(mainname, mainage, mainuniv, mainmajor); 
				i++; // 다음 사람거
			}
			else if (strcmp(input, "find") == 0)
			{
				cin >> findname;
				for (int j = 0; j < i; j++) {
					if (Student[j]->find(findname) == 0)
						Student[j]->print();
				}
			}
			else if (strcmp(input, "change")==0)
			{
				cin >> findname >> mainname >> mainage >> mainuniv >> mainmajor;
				for (int l = 0; l < i; l++)
				{
					Student[l]->find(findname);
					if (Student[l]->find(findname) == 0)
					{
						Student[l]->change(mainname, mainage, mainuniv, mainmajor);
					}
				}
			}
			else if (strcmp(input, "print") == 0)
			{
				for(int k=0;k<i;k++)
					Student[k]->print();
			}
			else if (strcmp(input, "exit")==0)
				break;

			else
			{
				cout << "Please Enter Command(insert, find, change, print, exit) : ";
				cin >> input; // 커맨드를 입력받음
			}
		}
			delete[] Student;
		return 0;
	}
