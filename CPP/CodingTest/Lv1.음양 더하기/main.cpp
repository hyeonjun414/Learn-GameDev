#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> absolutes, vector<bool> signs) {
    int answer = 0;
    for (int i = 0; i < absolutes.size(); i++)
    {
        answer += signs[i] == true ? absolutes[i] : -absolutes[i];
    }
    return answer;
}

int main()
{
    vector<int> num = { 4, 7, 12 };
    vector<bool> sign = { true, false, true };

    cout << solution(num, sign);
    return 0;
}