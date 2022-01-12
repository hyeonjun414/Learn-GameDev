#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintVector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << "";
    }
    cout << endl;
}


vector<int> solution(vector<int> arr)
{
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    return arr;
}

int main()
{
    vector<int> arr = { 1,1,3,3,3,0,1,1 };
    arr = solution(arr);
    PrintVector(arr);
}