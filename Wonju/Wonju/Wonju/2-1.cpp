#include <iostream>

class Student_info {
private:
	char name[10];
	int age = 0;
	char university[100];
	char major[100];

public:
	Student_info(char* name, int age, char* univ, char* major);
	bool find(char* name);
	void print();
	void change(char* name, int age, char* univ, char* major);
};
int main(void)
{

}