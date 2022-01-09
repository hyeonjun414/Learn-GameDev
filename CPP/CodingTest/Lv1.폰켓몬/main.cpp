#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


void PrintVector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int solution(vector<int> nums)
{
    int answer = 0;
    vector<int> temp;
    vector<int>::iterator iter;
    for (iter = nums.begin(); iter != nums.end(); iter++)
    {
        if (find(temp.begin(), temp.end(), *iter) == temp.end())
        {
            temp.push_back(*iter);
            answer++;
            if (answer == nums.size() / 2)
                break;
        }

    }
    return answer;
}

int main()
{
    vector<int> answer = {3,2,2,1};
    cout << solution(answer);
}