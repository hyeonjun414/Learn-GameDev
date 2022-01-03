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


vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for (int i = 0; i < commands.size(); i++)
    {
        // i,j 만큼 잘라주는 벡터를 저장해줄 공간을 만들고 assign을 이용해 넣어준다.
        vector<int> temp;
        temp.assign(array.begin() + commands[i][0]-1, array.begin() + commands[i][1]);
        // 만약 나온 공간이 하나라면 해당 숫자를 답에 넣어준다.
        // 그리고 다음 commands로 넘어간다.
        if (temp.size() == 1)
        {
            answer.push_back(temp[0]);
            continue;
        }
        // 정렬한다.
        sort(temp.begin(), temp.end());
        // k번째 수를 넣어준다.
        answer.push_back(temp[commands[i][2] - 1]);
    }
    return answer;
}

int main()
{
    vector<int> arr = { 1, 5, 2, 6, 3, 7, 4 };
    vector<vector<int>> command = { {2,5,3},{4,4,1},{1,7,3} };
    

    cout << "입력 값 :";
    PrintVector(arr);
    for (int i = 0; i < command.size(); i++)
    {
        PrintVector(command[i]);
    }
    vector<int> result = solution(arr, command);
    PrintVector(result);
    return 0;
}