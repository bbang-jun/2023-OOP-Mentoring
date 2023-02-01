#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class animal {
private:
	char name[10];
	int year = 0;
	char species[100];
};

class zoo {
private:
	class animal* animal_list[100];
	int size = 0;
};

int main() {
	char input[100]={};

	while (1) {
		cout << "Please Enter Command(new_animal,print_all,print_species,exit) :";

		if (strcmp(input, "new_animal") == 0) {
			//d
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