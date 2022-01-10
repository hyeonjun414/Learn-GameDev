#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintVector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    for (int i = 0; i < numbers.size(); i++)
    {
        for (int j = i + 1; j < numbers.size(); j++)
        {
            int num = numbers[i] + numbers[j];
            if (find(answer.begin(), answer.end(), num) == answer.end())
                answer.push_back(num);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}

int main()
{
    vector<int> vec = { 2,1,3,4,1 };
    vector<int> result = solution(vec);
    PrintVector(result);
}