#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(int n) {
    string answer = "";
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 != 0)
            answer += "��";
        else
            answer += "��";
    }
    return answer;
}

int main()
{
    cout << solution(5291823) << endl;
}