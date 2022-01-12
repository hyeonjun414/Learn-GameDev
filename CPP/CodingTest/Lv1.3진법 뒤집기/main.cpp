#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int solution(int n) {
    int answer = 0;
    vector<int> vec;
    // n을 뒤집힌 3진수 형태로 벡터에 넣어준다.
    while (n != 0)
    {
        vec.push_back(n % 3);
        n = n / 3;
    }
    // 각 자리수에 맞게 값을 넣어 준다.
    for (int i = 0; i < vec.size(); i++)
    {
        answer += vec[i] * pow(3, vec.size() - 1 - i);
    }
    PrintVector(vec);
    return answer;
}

int main()
{
    cout << solution(125);
}