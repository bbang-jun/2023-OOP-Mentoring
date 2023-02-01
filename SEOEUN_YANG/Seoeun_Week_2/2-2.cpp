#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class animal {
private:
	char name[10];
	int year = 0;
	char species[100];

public:
	animal(char* name, int year, char* species);
};

class zoo {
private:
	class animal* animal_list[100];
	int size = 0;//동물 개수

public:

	//zoo(animal_list[]);
};

animal::animal(char* name, int year, char* species) {
	//d
}

int main() {
	char input[100]={};
	char name_i[10];
	int year_i;
	char species_i[100];

	while (1) {
		cout << "Please Enter Command(new_animal,print_all,print_species,exit) :";
		cin >> input;

		if (strcmp(input, "new_animal") == 0) {
			cin >> name_i >> year_i >> species_i;
			
		}

		else if (strcmp(input, "print_all") == 0) {
			//d
		}

		else if (strcmp(input, "print_species") == 0) {
			//d
		}

		else if (strcmp(input, "exit") == 0)
			break;

		else
			continue;
	}

	return 0;
}