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
    vector<int> answer;
    return answer;
}

int main()
{
    vector<int> answer = { 1,3,2,4,2 };
    vector<int> result = solution(answer);
    PrintVector(result);
    return 0;
}