#include <iostream>
#include <cmath>

void loop(int n, int i, int result);
int main(void)
{
	char name[30];
	int result = 0;
	int n;
	int i = 0;
	std::cout << name << "Enter Any Positive Number : ";
	std::cin >> n;
	loop(n, i, result);
	return 0;
}

void loop(int n, int i, int result)
{
	if (i != n + 1)
	{
		result += i * pow(2, i);
		i++;
		loop(n, i, result);
	}
	else
		std::cout << result;
}