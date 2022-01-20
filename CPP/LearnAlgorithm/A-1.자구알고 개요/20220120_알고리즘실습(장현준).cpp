// A-1.자구알고 개요.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

using namespace std;

// 1. 자연수 1을 n번 더한 결과를 반환하는 함수
// 시간 복잡도 : O(1)
int onePlusRepeater(int n)
{
    return n;
}

// 2. n까지의 수가 무작위로 존재하는 길이가 n인 배열에
//    숫자 i이 포함되어 있는지 확인하는 함수
// 시간 복잡도 : O(n)
bool isExist(vector<int> array, int i)
{
    for (int index = 0; index < array.size(); index++)
        if (array[index] == i) return true;

    return false;
}

// 3. 피보나치 수열의 index번째 숫자를 반환하는 함수
// 시간 복잡도 : O(2^n)
int Fibonacci(int index)
{
    if (index == 1)
        return 1;
    else if (index == 2)
        return 1;

    return Fibonacci(index - 2) + Fibonacci(index - 1);
}
// 4. 자연수 n의 n번 곱한 결과를 반환 하는 함수
// 시간 복잡도 : O(n)
long nMultipleRepeat(int n)
{
    long result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= n;
    }
    return result;
}

int main()
{
    vector<int> vec = { 1,5,4,2,3,6 };

    cout << onePlusRepeater(100000) << endl;
    cout << isExist(vec, 3) << endl;
    cout << Fibonacci(10) << endl;
    cout << nMultipleRepeat(5) << endl;
}
