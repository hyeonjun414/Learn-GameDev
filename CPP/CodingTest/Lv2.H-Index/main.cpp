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

int solution(vector<int> citations) {
    int answer = 0;
    // ���� �ο� Ƚ���� ������������ �����Ѵ�.
    sort(citations.begin(), citations.end(), greater<int>());
    //���� ū���� 0�̶�� H-index �� 0�̴�
    if (!citations[0])        return 0;

    for (int i = 0; i < citations.size(); i++) {
        //h-index���� ���̶�� h-index�� �ϳ� �÷��ش�.
        if (citations[i] > i)    answer++;

        //i�� h-index�� ����ٸ� Ž���� �����.
        else
            break;
    }
    return answer;
}

// �� ������ �ε��� ������ ����Ƚ���� ���ϴ� ���� ����Ʈ����.
int main()
{
    vector<int> arr = { 3, 0, 6, 1, 5 };



    cout << "�Է� �� :";
    PrintVector(arr);
    cout << "���� ��� : " << solution(arr);
    return 0;
}