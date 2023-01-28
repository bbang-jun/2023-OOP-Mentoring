#include <iostream>
using namespace std;

int sum = 0;//결과값 전역변수 선언

int sigma(int N,int current_i,int current_value) {//재귀함수 선언
	if (current_i > N)
		return sum;

	sum += current_value;//결과값 다 더해주기
	sigma(N, current_i + 1, current_value + 1);
	sigma(N, current_i + 1, current_value + 1);
	//가지치기 느낌으로 재귀함수 호출 (-> 2번 호출)
}

int main(void) {//메인 함수

	int N;//초기값 0으로 초기화
	int current_i = 0;
	int current_value = 0;

	cout << "Enter Any Positive Number : ";
	cin >> N;//입력값

	cout << sigma(N,current_i,current_value);//출력값

	return 0;//함수 끝
}