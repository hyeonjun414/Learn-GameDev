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
    // n�� ������ 3���� ���·� ���Ϳ� �־��ش�.
    while (n != 0)
    {
        vec.push_back(n % 3);
        n = n / 3;
    }
    // �� �ڸ����� �°� ���� �־� �ش�.
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