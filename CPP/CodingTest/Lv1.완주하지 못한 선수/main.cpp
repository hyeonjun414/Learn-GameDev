#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

string solution(vector<string> participant, vector<string> completion) {

    // �� ���͸� ���� �����Ѵ�.
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());

    // ������ ��� ������ ũ�⸸ŭ �ݺ��Ѵ�.

    for (int i = 0; i < completion.size(); i++)
    {
        //�Ȱ��� �����ߴµ� ������ �ٸ��ٸ� �� ����� �������� ���� ����̴�.
        if (participant[i] != completion[i])
            return participant[i]; // �ٷ� ��ȯ
    }
    // ������ ����� �� Ȯ���ߴµ� ���ٸ� ������ �ѻ���� ������� ���� ���̴�.
    return participant[participant.size() - 1];
}

int main()
{
    vector<string> part = { "marina", "josipa", "nikola", "vinko", "filipa" };
    vector<string> comp = { "josipa", "filipa", "marina", "nikola" };
    cout << "������ :"; 
    PrintVector(part);
    cout << "������ :";
    PrintVector(comp);

    cout << "�������� ���� ��� : " << solution(part, comp);
    return 0;
}