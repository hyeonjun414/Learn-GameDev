// Lv1. 평균 구하기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

double solution(vector<int> arr) {
    double answer = 0;
    for (int i = 0; i < arr.size(); i++)
        answer += arr[i];
    return answer / arr.size();
}

int main()
{
    vector<int> arr = { 1,56,22,6,3,12,5 };
    cout << solution(arr) << endl;
}