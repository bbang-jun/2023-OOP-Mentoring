#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;


class animal {
private:
	char name[10];
	int year = 0;
	char species[100];
public:
	void setname(char* name) { strcpy(this->name,name); };
	void setyear(int year) { this->year = year; };
	void setspecies(char* species) { strcpy(this->species,species); };
	char* getname() { return this->name; };
	int getyear() { return this->year; };
	char* getspecies() { return this->species; };
};
class zoo{
private:
	class animal* animal_list[100];
	int size = 0;
public:
	void new_animal(char* name, int year, char* species) 
	{
		animal_list[size] = new animal();
		animal_list[size]->setname(name);
		animal_list[size]->setyear(year);
		animal_list[size]->setspecies(species);
		size++;
	};
	void print_all(int n) { 
		cout << "----------"<<n<<"----------" << endl;
		cout << "Name : " << animal_list[n]->getname() << endl;
		cout << "Year : " << animal_list[n]->getyear() << endl;
		cout << "Species : " << animal_list[n]->getspecies() << endl;
		cout << "-------------------------" << endl;
	};
	int print_species(char* find_species, int k) {
		{
			if (strcmp(animal_list[k]->getspecies(), find_species) == 0)
				return 0;
		}
	};
	~zoo() {
			delete[] animal_list;
	}

};
int main(void)
{
	zoo* Wonju = new zoo;
	char input[30] = { 0 };
	char find_species[100];
	char name[10] = { 0 };
	int year = 0;
	char species[100] = { 0 };
	int cnt = 0;

	while (1)
	{
		cout << "Please Enter Any Command(new_animal, print_all, print_species, exit) : ";
		cin >> input;
		if (strcmp(input, "new_animal") == 0)
		{
			cin >> name >> year >> species;
			Wonju->new_animal(name, year, species);
			cnt++;
		}
		else if (strcmp(input, "print_all") == 0)
		{
			for (int j = 0; j < cnt ; j++) {
				Wonju->print_all(j);
			}
		}
		else if (strcmp(input, "print_species") == 0)
		{
			cin >> find_species;
			for (int i = 0; i < cnt; i++) {
				Wonju->print_species(find_species, i);
				if (Wonju->print_species(find_species, i) == 0)
					Wonju->print_all(i);
				
			}
		}
		else if (strcmp(input, "exit") == 0)
			break;
	}
	delete Wonju;
	return 0;
}