#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class animal {
private:
	char name[10];
	int year = 0;
	char species[100];

public:
	animal(char* name, int year, char* species);//생성자
	char* get_name() { return this->name; }//이름 접근
	int get_year() { return this->year; }//나이 접근
	char* get_species() { return this->species; }//종 접근
};

class zoo {
private:
	class animal* animal_list[100];//동적 할당 (최대 동물 100마리 저장 가능)
	int size = 0;//동물 개수

public:
	void save(char* name, int year, char* species) {//저장 함수
		animal_list[size] = new animal(name, year, species);//개체 별 동적할당
		size++;//개체 별 개수 저장
	}
	void size_setter(int size) { this->size = size; }//동물 수 저장
	int size_getter() { return this->size; }//동물 수 알려줌

	void print(int i);//동물 정보 출력
	int find(char* species_i,int cnt);//같은 종 검색
	
	~zoo() {//소멸자
		delete[]animal_list;//동적할당 해제
	}
};

animal::animal(char* name, int year, char* species) {//동물 정보 저장
	strcpy(this->name, name);
	this->year = year;
	strcpy(this->species, species);
}

void zoo::print(int i) {//출력
	cout << "----------" << i << "----------" << endl;
	cout << "Name : " << animal_list[i]->get_name() << endl;
	cout << "Year : " << animal_list[i]->get_year() << endl;
	cout << "Species : " << animal_list[i]->get_species() << endl;
	cout << "---------------------" << endl;
}

int zoo::find(char* species_i,int cnt) {//같은 종 검색
	int size = size_getter();
	for (int i = 0; i < size; i++) {
		if (strcmp(animal_list[i]->get_species(), species_i) == 0) {//종이 같다면
			print(i);//출력
			cnt++;//마릿수++
		}
	}
	return cnt;
}

int main() {
	zoo* Zoo = new zoo;//zoo 객체 선언
	char input[100]={};//command 입력
	char name_i[10];
	int year_i;
	char species_i[100];
	int size;

	while (1) {
		cout << "Please Enter Command(new_animal,print_all,print_species,exit) :";
		cin >> input;

		if (strcmp(input, "new_animal") == 0) {
			cin >> name_i >> year_i >> species_i;
			Zoo->save(name_i, year_i, species_i);//동물 정보 저장
		}

		else if (strcmp(input, "print_all") == 0) {
			size=Zoo->size_getter();//저장되어 있는 동물 마릿수 불러옴
			cout << "------print_all------" << endl;
			for (int i = 0; i < size; i++) {//동물 마릿수만큼 반복 (모두 출력)
				Zoo->print(i);
			}
			cout << "---------------------" << endl;
		}

		else if (strcmp(input, "print_species") == 0) {
			int cnt = 0;//같은 종 개수 저장
			cin >> species_i;
			cout << "------print_species------" << endl;
			cnt=Zoo->find(species_i,cnt);
			cout << "Number of species is :" << cnt << endl;
			cout << "---------------------" << endl;
		}

		else if (strcmp(input, "exit") == 0)//exit 입력
			break;//무한루프 탈출

		else//잘못 입력
			continue;//무시
	}

	delete Zoo;//동적할당 해제
	return 0;
}