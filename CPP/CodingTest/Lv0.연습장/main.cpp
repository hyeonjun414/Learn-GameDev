#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    int* arr = new int[10];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = 0;
    }
    int a, b, c;
    cin >> a >> b >> c;
    int result = a * b * c;
    while (result != 0)
    {
        arr[result%10]++;
        result /= 10;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << endl;
    }
}