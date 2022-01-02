#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> a, vector<int> b) {
    int answer = 0;
    for (int i = 0; i < a.size(); i++)
    {
        answer += a[i] * b[i];
    }
    return answer;
}

int main()
{
    vector<int> num1 = { 1,2,3,4 };
    vector<int> num2 = { -3,-1,0,2 };

    cout << solution(num1, num2);
    return 0;
}