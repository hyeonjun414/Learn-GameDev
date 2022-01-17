#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(vector<string> seoul) {
    for (int i = 0; i < seoul.size(); i++)
    {
        if ("Kim" == seoul[i])
            return "김서방은 " + to_string(i) + "에 있다";
    }
    return "";
}


int main()
{
    vector<string> str = { "Jion", "Kim", "Lion" };
    cout << solution(str) << endl;
}