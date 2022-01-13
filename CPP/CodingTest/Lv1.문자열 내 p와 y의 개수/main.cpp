#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool solution(string s)
{
    int y = 0, p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'p' || s[i] == 'P') p++;
        else if (s[i] == 'y' || s[i] == 'Y') y++;
    }
    return y == p;
}
int main()
{
    cout << solution("pPoooyY");
}