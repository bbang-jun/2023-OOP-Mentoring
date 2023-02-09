#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
int func(int N, int cnt, int cur_val);

int sum;
int main()
{
	int N, cnt = 0, result = 0;

	cout << "Enter Any Positive Number : ";
	cin >> N;

	cout << func(N, cnt, result);
}

int func(int N, int cnt, int cur_val)
{
	if (cnt > N)
		return sum;

	sum += cur_val;
	func(N, cnt + 1, cur_val + 1);
	func(N, cnt + 1, cur_val + 1);

}
