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
        // i,j ��ŭ �߶��ִ� ���͸� �������� ������ ����� assign�� �̿��� �־��ش�.
        vector<int> temp;
        temp.assign(array.begin() + commands[i][0]-1, array.begin() + commands[i][1]);
        // ���� ���� ������ �ϳ���� �ش� ���ڸ� �信 �־��ش�.
        // �׸��� ���� commands�� �Ѿ��.
        if (temp.size() == 1)
        {
            answer.push_back(temp[0]);
            continue;
        }
        // �����Ѵ�.
        sort(temp.begin(), temp.end());
        // k��° ���� �־��ش�.
        answer.push_back(temp[commands[i][2] - 1]);
    }
    return answer;
}

int main()
{
    vector<int> arr = { 1, 5, 2, 6, 3, 7, 4 };
    vector<vector<int>> command = { {2,5,3},{4,4,1},{1,7,3} };
    

    cout << "�Է� �� :";
    PrintVector(arr);
    for (int i = 0; i < command.size(); i++)
    {
        PrintVector(command[i]);
    }
    vector<int> result = solution(arr, command);
    PrintVector(result);
    return 0;
}