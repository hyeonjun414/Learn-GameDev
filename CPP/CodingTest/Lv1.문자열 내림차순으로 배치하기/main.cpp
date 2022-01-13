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

string solution(string s) {
    sort(s.begin(), s.end(), comp);
    // sort(s.begin(), s.end(), greater<char>());
    return s;
}

int main()
{
    cout << solution("akwnihdksneoiahsl");
}