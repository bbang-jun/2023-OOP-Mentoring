#include <iostream>
#include <cstdlib>//객체 배열 동적할당
using namespace std;

class Student_info {
private:
	char name[10];
	int age = 0;
	char university[100];
	char major[100];

public:
	Student_info(char* name, int age, char* univ, char* major);//얘도 밖에서 호출해야 되나
	bool find(char* name);
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

//출력
void Student_info::print() {
	cout << "---------print---------" << endl;
	//cout << "Name : "<< <<endl;
	//cout << "Age : "<< <<endl;
	//cout << "University : "<< <<endl;
	//cout << "Major : "<< <<endl;
};


int main() {
	Student_info* student = new Student_info[10];//객체 배열 동적할당 모르겠다...
	for (int z = 0; z < 10; z++) {
		student[z].name="a";
		student[z].age = 0;
		student[z].university = "a";
		student[z].major = "a";
	}//private이라서 접근 불가


	char input[100];//command 입력
	int i = 0;//학생 정보 저장 순서


	while (1) {//무한루프
		cin >> input;
		if (strcmp(input, "insert") == 0) {//같음
			//저장
			//저장할 때 strtok 함수도 써야되나
		}

		

		else if (strcmp(input, "exit") == 0)//프로그램 종료
			break;

		else//잘못 입력
			continue;
	}

	return 0;
}