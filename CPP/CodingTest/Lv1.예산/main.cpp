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
    // 최대한 많은 부서에 예산을 주기위해 작은 순으로 정렬한다.
    sort(d.begin(), d.end());
    for (int i = 0; i < d.size(); i++)
    {
        // 필요 예산을 뺀 값이 0이되면 더이상 예산을 맞춰줄수 없기 때문에
        // 반복문을 탈출한다.
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