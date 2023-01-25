#include <iostream>
#include <cmath>//2의 지수 구하는데 사용
using namespace std;

int sigma(int N) {//재귀함수 선언
   int result;
   if (N == 0)//초기값
      return N;
   else
      result = N * pow(2, N) + sigma(N - 1);//재귀함수 호출
      return result;//결과값 반환
}

int main(void) {

   int N = 0;

   cout << "Enter Any Positive Number : ";
   cin >> N;//입력값

   cout << sigma(N);//출력값

   return 0;
}
