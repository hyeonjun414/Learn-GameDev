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

int main()
{
    int a, b;
    a = 472;
    b = 385;

    cout << a * (b % 10) << endl;
    cout << a * ((b / 10)%10) << endl;
    cout << a * (b / 100) << endl;
    cout << a * b << endl;
}