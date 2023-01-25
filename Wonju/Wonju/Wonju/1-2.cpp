#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int main(void)
{
	srand(time(NULL));
	int Matrix[10][10] = { 0 };
	int a = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			Matrix[i][k] = rand() % 101;
		}
	}
}
