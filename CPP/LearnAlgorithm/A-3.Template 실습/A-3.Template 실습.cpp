// A-3.Template 실습.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

#define DATA_SIZE   1
#pragma region 실습
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

// 2. n까지의 수가 무작위로 존재하는 길이가 n인 배열에
//    숫자 i가 포함되어 있는지 확인하는 함수
// 시간 복잡도 : O(n)
template <typename T>
bool isExist(vector<T> array, T i)
{
    cout << "2. n까지의 수가 무작위로 존재하는 길이가 n인 배열에 숫자 i가 포함되어 있는지 확인하는 함수" << endl;
    for (int index = 0; index < array.size(); index++)
        if (array[index] == i) return true;
    return false;
}

template <typename T>
T nMultipleRepeat(T x, int n)
{
    if (n == 1)
        return x;
    else if (n % 2 == 0)
    {
        return nMultipleRepeat(x, n / 2) *
            nMultipleRepeat(x, n / 2);
    }
    else
    {
        return x * nMultipleRepeat(x, n / 2) *
            nMultipleRepeat(x, n / 2);
    }
}

template <typename T>
T power(T x, int y)
{
    T temp;
    if (y == 1)
        return x;
    temp = power(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else
        return x * temp * temp;
}

#pragma endregion




int main()
{
#pragma region 실습
    vector<int> vec = { 1,5,4,3,3,6 };
    vector<double> vec2 = { 1.8,2.1,4.2,3.4,3.8,2.5 };

    timeCheck();
    cout << isExist(vec, 3) << endl;
    timeCheck();
    timeCheck();
    cout << isExist(vec2, 3.4) << endl;
    timeCheck();
    timeCheck();
    cout << nMultipleRepeat(2.1, 10) << endl;
    timeCheck();
    timeCheck();
    cout << power(2.1, 10) << endl;
    timeCheck();
#pragma endregion

 
}
