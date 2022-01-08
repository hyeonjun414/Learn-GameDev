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

string solution(int a, int b) {
    int daysum = 0;
    string day[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    int month[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
    for (int i = 0; i < a - 1; i++) daysum += month[i];
    daysum += b - 1;
    int dayday = (daysum + 5) % 7;
    return day[dayday];
}

int main()
{
    cout << solution(5, 24);
}