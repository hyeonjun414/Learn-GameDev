#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int solution(vector<int> d, int budget) {
    int answer = 0;
    // �ִ��� ���� �μ��� ������ �ֱ����� ���� ������ �����Ѵ�.
    sort(d.begin(), d.end());
    for (int i = 0; i < d.size(); i++)
    {
        // �ʿ� ������ �� ���� 0�̵Ǹ� ���̻� ������ �����ټ� ���� ������
        // �ݺ����� Ż���Ѵ�.
        if (budget - d[i] < 0)
        {
            break;
        }
        budget -= d[i];
        answer++;
    }
    return answer;
}

int main()
{
    vector<int> vec = { 1,3,2,5,4 };
    cout << solution(vec, 9);
}