#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(vector<string> seoul) {
    for (int i = 0; i < seoul.size(); i++)
    {
        if ("Kim" == seoul[i])
            return "�輭���� " + to_string(i) + "�� �ִ�";
    }
    return "";
}


int main()
{
    vector<string> str = { "Jion", "Kim", "Lion" };
    cout << solution(str) << endl;
}