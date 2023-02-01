#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <cstdlib>//객체 배열 동적할당
using namespace std;

int i = 0;//학생 정보 저장 순서 (전역변수 선언)

class Student_info {
private:
	char name[10];
	int age = 0;
	char university[100];
	char major[100];

public:
	Student_info(char* name, int age, char* univ, char* major);//생성자
	bool find(char* name);//find 함수
	void print(); 
	void change(char* name, int age, char* univ, char* major);
};

//학생 정보 저장
Student_info::Student_info(char* name, int age, char* univ, char* major) {
	strcpy(this->name, name);
	this->age = age;
	strcpy(this->university, univ);
	strcpy(this->major, major);
};

bool Student_info::find(char* name) {
	if (strcmp(this->name, name) == 0) {//이름 동일
			//this->name  private에 저장되어 있는 학생 정보 이름 불러옴
		return 0;
	}
	else//이름 동일 X
		return 1;
}

void Student_info::change(char* name, int age, char* univ, char* major) {
	strcpy(this->name, name);
	this->age = age;
	strcpy(this->university, univ);
	strcpy(this->major, major);
}

//출력
void Student_info::print() {
	cout << "Name : " << this->name << endl;
	cout << "Age : " << this->age << endl;
	cout << "University : " << this->university << endl;
	cout << "Major : " << this->major << endl;
	cout << "----------------------" << endl;
};

int main() {
	Student_info* student[10] ;//객체 배열 정적으로 선언

	char input[20];//command 입력
	char name_i[10];
	char temp_name[10];
	int age_i;
	char univ_i[100];
	char major_i[100];
	//int i = 0;//학생 정보 저장 순서

	while (1) {//무한루프
		cout << "Command(insert, find, change, print, exit) : ";
		cin >> input;

		if (strcmp(input, "insert") == 0) {//insert 입력

			if (i < 10) {//학생 정보 10명 이하
				cin >> name_i >> age_i >> univ_i >> major_i;
				student[i] = new Student_info(name_i, age_i, univ_i, major_i);//동적 할당 (학생 정보 저장)
				i++;
			}

			else//학생 정보 10명 초과
				continue;
		}

		else if (strcmp(input, "find") == 0) {//find 입력
			cin >> name_i;
			for (int z = 0; z <= i; z++) {
				if (student[z]->find(name_i) == 0) {//동일 이름 존재 (객체 클라스 내부 함수 호출)
					cout << "---------find---------" << endl;
					student[z]->print();//동일 학생 정보 출력
				}

				else
					continue;
			}
		}
		
		else if (strcmp(input, "change") == 0) {//change 입력
			cin >> name_i >> temp_name >> age_i >> univ_i >> major_i;
			for (int z = 0; z <= i; z++) {
				if (student[z]->find(name_i) == 0) {//동일 이름 존재
					student[z]->change(temp_name, age_i, univ_i, major_i);
					break;
				}
			}
		}

		else if (strcmp(input, "print") == 0) {//print 입력
			cout << "---------print---------" << endl;
			for (int z = 0; z <= i; z++) {
				student[z]->print();
			}
			cout << "----------------------" << endl;
		}

		else if (strcmp(input, "exit") == 0)//프로그램 종료
			break;

		else//잘못 입력
			continue;
	}

	for (int z = 0; z <= i; z++)
		delete student[z];//동적 할당 해제
	return 0;
}


//print 함수 수정