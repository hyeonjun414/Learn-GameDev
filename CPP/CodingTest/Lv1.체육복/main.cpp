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

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    vector<int> students;
    for (int i = 0; i <= n; i++)
        students.push_back(0);
    for (int i = 0; i < lost.size(); i++)
        students[lost[i]]--;
    for (int i = 0; i < reserve.size(); i++)
        students[reserve[i]]++;
    for (int i = 1; i <= n; i++)
    {
        if (students[i] == -1)
        {
            if (students[i - 1] == 1)
                students[i - 1] = students[i] = 0;
            else if (students[i + 1] == 1)
                students[i + 1] = students[i] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (students[i] != -1) answer++;
    }
    return answer;
}

int main()
{
    vector<int> lost = { 2,4 };
    vector<int> reserve = { 1,3,5 };
    int n = solution(5, lost, reserve);
    cout << n << endl;
}