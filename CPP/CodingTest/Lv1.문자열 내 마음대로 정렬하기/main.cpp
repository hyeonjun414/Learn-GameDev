#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
int i;
bool comp(string a, string b)
{
    return a[i] == b[i] ? a < b : a[i] < b[i];
}

vector<string> solution(vector<string> strings, int n) {
    i = n;
    sort(strings.begin(), strings.end(), comp);
    return strings;
}

void PrintVector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}


int main()
{
    vector<string> strings = { "abce", "abcd", "cdx" };
    strings = solution(strings, 2);
    PrintVector(strings);
}