// A-1.자구알고 개요.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

#define DATA_SIZE   1

// 시간 측정
bool isStart = false;
clock_t start, finish;
void timeCheck()
{
    if (isStart)
    {
        finish = clock();
        isStart = !isStart;
        cout << "함수에서 걸린 시간 : " << (finish - start) << "\n\n";

    }
    else
    {
        start = clock();
        isStart = !isStart;
    }
}

// 1. 자연수 1을 n번 더한 결과를 반환하는 함수
// 시간 복잡도 : O(1)
int onePlusRepeater(int n)
{
    cout << "1. 자연수 1을 n번 더한 결과를 반환하는 함수" << endl;
    return n;
}

// 2. n까지의 수가 무작위로 존재하는 길이가 n인 배열에
//    숫자 i가 포함되어 있는지 확인하는 함수
// 시간 복잡도 : O(n)
bool isExist(vector<int> array, int i)
{
    cout << "2. n까지의 수가 무작위로 존재하는 길이가 n인 배열에 숫자 i가 포함되어 있는지 확인하는 함수" << endl;
    for (int index = 0; index < array.size(); index++)
        if (array[index] == i) return true;
    return false;
}

// 3. 피보나치 수열의 index번째 숫자를 반환하는 함수(재귀O)
// 시간 복잡도 : O(2^n)
int Fibonacci(int index)
{
    if (index == 1)
        return 1;
    else if (index == 2)
        return 1;

    return Fibonacci(index - 2) + Fibonacci(index - 1);
}
// 4. 피보나치 수열 반복문 하나로 실행 : O(n);
int Fibonacci_2(int index)
{
    cout << "4. 피보나치 수열의 index번째 숫자를 반환하는 함수(재귀X)" << endl;
    if (1 == index)
        return 1;
    else if (2 == index)
        return 1;

    int result = 0;
    int preNum = 1;
    int prepreNum = 1;
    for (int i = 3; i <= index; i++)
    {
        result = preNum + prepreNum;
        prepreNum = preNum;
        preNum = result;
    }
    return result;
}


// 4. 자연수 x의 n번 곱한 결과를 반환 하는 함수
// 시간 복잡도 : O(n)
long long nMultipleRepeat(int x, int n)
{
    // n이 짝수일 때, 일반적인 반복문 보다 각 재귀의 마지막 리프 노드가
    // 조금 간략화 되어 O(n)보다 조금 빠를 것으로 보인다.
    if (0 == n % 2)
    {
        if (2 == n)
            return x * x;

        return nMultipleRepeat(x, n/2) * nMultipleRepeat(x, n/2);
    }
    // n이 홀수일 때, n/2승의 연산을 하기 힘든 것으로 보이기 때문에
    // 반복문을 이용하여 연산한다. O(n)
    else
    {
        long long result = 1;

        for (int i = 0; i < n; i++)
            result *= x;

        return result;
    }
   
}

long long nMultipleRepeat(long long x, long long n)
{
    if (n == 1)
        return x;

    if (n % 2 == 0)
    {
        return nMultipleRepeat(x, n / 2) *
            nMultipleRepeat(x, n / 2);
    }
    // 나누는게 안되는 경우에는 n+1과 n으로 나누는 것으로 재귀 처리한다.
    else
    {
        return nMultipleRepeat(x, (n / 2) + 1);
        nMultipleRepeat(x, n / 2);
    }
}


int main()
{
    vector<int> vec = { 1,5,4,3,3,6 };
    timeCheck();
    cout << onePlusRepeater(100000) << endl;
    timeCheck();
    timeCheck();
    cout << isExist(vec, 3) << endl;
    timeCheck();
    timeCheck();
    cout << isExist(vec, 2) << endl;
    timeCheck();
    timeCheck();
    cout << "3. 피보나치 수열의 index번째 숫자를 반환하는 함수(재귀O)" << endl;
    cout << Fibonacci(30) << endl;
    timeCheck();
    timeCheck();
    cout << Fibonacci_2(30) << endl;
    timeCheck();
    timeCheck();
    cout << nMultipleRepeat(2,59) << endl;
    timeCheck();
    timeCheck();
    cout << nMultipleRepeat(2,60) << endl;
    timeCheck();
}
