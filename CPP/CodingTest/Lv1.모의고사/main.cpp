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

vector<int> solution(vector<int> answers) {
    int max = 0;
    vector<int> answer;
    vector<int> count = {0,0,0};
    vector<int> p1 = { 1,2,3,4,5 };
    vector<int> p2 = { 2,1,2,3,2,4,2,5 };
    vector<int> p3 = { 3,3,1,1,2,2,4,4,5,5 };
    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i] == p1[i % p1.size()]) count[0]++;
        if (answers[i] == p2[i % p2.size()]) count[1]++;
        if (answers[i] == p3[i % p3.size()]) count[2]++;
    }
    for (int i = 0; i < count.size(); i++)
        if (max < count[i]) max = count[i];
    for (int i = 0; i < count.size(); i++)
        if (max == count[i]) answer.push_back(i + 1);

    if (answer.size() == 1)
        return answer;
    sort(answer.begin(), answer.end());
    return answer;
}

int main()
{
    vector<int> answer = { 1,3,2,4,2 };
    vector<int> result = solution(answer);
    PrintVector(result);
    return 0;
}