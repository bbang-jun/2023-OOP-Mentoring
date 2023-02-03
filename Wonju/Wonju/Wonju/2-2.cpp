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
	string getname() { return this->name; };
	int getyear() { return this->year; };
	string getspecies() { return this->species; };
};
class zoo{
private:
	class animal* animal_list[100];
	int size = 0;
public:
	void new_animal(char* name, int year, char* species, int cnt) 
	{
		animal_list[cnt]->setname(name);
		animal_list[cnt]->setyear(year);
		animal_list[cnt]->setspecies(species);

	};
	void print_all(int n) { 
		cout << "----------"<<n<<"----------" << endl;
		cout << "Name : " << animal_list[n - 1]->getname() << endl;
		cout << "Year : " << animal_list[n - 1]->getyear() << endl;
		cout << "Species : " << animal_list[n - 1]->getspecies() << endl;
		cout << "-------------------------" << endl;
	};
	void print_species(int k, char* find_species) {
		{

		}
	};

};
int main(void)
{
	while (1)
	{
		cout << "Please Enter Any Command(new_animal, print_all, print_species, exit) : ";
		int cnt = 0;
		char input[30]= {0};
		char find_species[100];
		if (strcmp(input, "new_animal") == 0)
		{
			cnt++;
		}
		else if (strcmp(input, "print_all") == 0)
		{
			for (int j = 0; j < cnt; j++) {
			}
		}
		else if (strcmp(input, "print_species") == 0)
		{

		}
		else if (strcmp(input, "exit") == 0)
			break;
		else
			cout << "Please Enter Any Command(new_animal, print_all, print_species, exit) : ";
		
		

	}
}