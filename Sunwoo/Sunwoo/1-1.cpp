#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
using namespace std;

int func(int N, int cnt, int result)
{
	if (N > cnt)
	{
		cnt++;
		result += cnt * pow(2, cnt);
		func(N, cnt, result); // 재귀함수로 호출
	}
	else // N이 cnt와 같게 되면 return
		return result;

}

int main()
{
	int N, cnt = 0, result = 0;

	cout << "Enter Any Positive Number : ";
	cin >> N;

	cout << func(N, cnt, result);
}