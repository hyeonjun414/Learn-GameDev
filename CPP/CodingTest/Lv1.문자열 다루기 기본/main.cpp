#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
int i;
bool comp(char a, char b)
{
    return a > b;
}

bool solution(string s) {
    for (int i = 0; i < s.size(); i++)
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return false;
    }
    return true;
}

int main()
{
    cout << solution("akwnihdksneoiahsl");
}